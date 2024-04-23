#include"headers.c"
#include<time.h>
#include<kcgi.h>

#define portnum 1235
#define portown 1236
#define CAPACITY 1024

FILE* logp;
char *err;

enum key {
	KEY_STRING1,
	KEY_STRING2,
	KEY_STRING3,
	KEY__MAX
};

static const struct kvalid keys[KEY__MAX] = 
{
	{ kvalid_stringne, "ab" }, /* KEY_STRING */
	{ kvalid_stringne, "cd" }, /* KEY_STRING */
	{ kvalid_stringne, "s/i" }
};

enum page {
	PAGE_INDEX,
	PAGE__MAX
};
const char *const pages[PAGE__MAX] = {
	"index" /* PAGE_INDEX */
};

static enum khttp sanitise(const struct kreq *r) {
	if (r->page != PAGE_INDEX)
		return KHTTP_404;
	else if (*r->path != '\0') /* no index/xxxx */
		return KHTTP_404;
	else if (r->mime != KMIME_TEXT_HTML)
		return KHTTP_404;
	else if (r->method != KMETHOD_POST)
		return KHTTP_405;
	return KHTTP_200;
}

enum erno { INPUT_OK , INPUT_NA ,SEND_OK,SEND_NA,PAGE_OK,PAGE_NA ,SESSION_OK,SESSION_NA,ERR_USERNAME,ERR_PASSWORD,DATA_READ_ERROR};

static enum erno check_input(struct kreq* r)
{
	char i=0;

	struct kpair *p;

	while(i<KEY__MAX)
	{
		if( (p=r->fieldmap[i]))
		{
			i++;
		}
		else
		{
			return INPUT_NA;
		}
	}
	return INPUT_OK;
}

int sockfd[2];
struct sockaddr_in recaddr[2],senaddr;
socklen_t LEN=sizeof(senaddr);

static enum erno send_input(struct kreq* r)
{
	char i;
	char *input;
	if((sockfd[0]=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		err="Socket syscall failed fun:send_input\n";
		logg(err);
		return SEND_NA;
	}
	memset(&recaddr,0,sizeof(recaddr[0]));

	recaddr[0].sin_family=AF_INET;
	recaddr[0].sin_port=htons(portnum);
	recaddr[0].sin_addr.s_addr=INADDR_ANY;

	i=0;

	while(i<KEY__MAX)
	{
		input=(char*)r->fieldmap[i]->parsed.s;
		if((sendto(sockfd[0],input,strlen(input),0,(const struct sockaddr*)&recaddr[0],sizeof(recaddr[0])))<1)
		{
			err="Sending failed fun:send_input\n";
			logg(err);
			return SEND_NA;
		}
		i++;
	}

	close(sockfd[0]);

	return SEND_OK;
}

static enum erno getset_session(struct kreq *r)
{
	char len;
	char buffer[34],buf[32];
	if((sockfd[1]=socket(AF_INET,SOCK_DGRAM,0))<0)
	{

		return SESSION_NA;
	}

	memset(&recaddr[1],0,sizeof(recaddr[1]));
	memset(&senaddr,0,sizeof(senaddr));

	recaddr[1].sin_family=AF_INET;
	recaddr[1].sin_port = htons(portown);
	recaddr[1].sin_addr.s_addr=INADDR_ANY;

	if( (bind(sockfd[1],(const struct sockaddr*)&recaddr[1],sizeof(recaddr[1])))<0 )
	{
		err="Binding failed fun:getset_session\n";
		logg(err);
		return SESSION_NA;
	}

	if( (len=recvfrom(sockfd[1],(void*) buffer ,CAPACITY, MSG_WAITALL , (struct sockaddr*)&senaddr,&LEN))<2 )
	{
		if(buffer[0]=='u')
		{
			return ERR_USERNAME;
		}
		if(buffer[0]=='p')
		{
			return ERR_PASSWORD;
		}
		if(buffer[0]=='d')
		{
			return DATA_READ_ERROR;
		}
	}

	buffer[len]=0;
	buffer[len+1]=10;

	khttp_head(r,kresps[KRESP_SET_COOKIE],"%s=%s; path=/; expires=%s;","session_id",buffer,khttp_epoch2str(time(NULL)+60*60,buf,sizeof(buf)));

	fwrite((void*)buffer,sizeof(char),len,logp);

	return SESSION_OK;
}

static enum erno get_page(struct kreq *r)
{
	unsigned int i=1,n=0,bytes=0;
	char buffer[CAPACITY];

	khttp_body(r);
	while(i!=0)
	{
		n=recvfrom(sockfd[1],(void*)buffer ,CAPACITY,  MSG_WAITALL , (struct sockaddr*)&senaddr,&LEN);
		bytes+=n;
		if(n<0)
		{
			err="Failed to recieve data fun:get_page\n";
			logg(err);
			return PAGE_NA;
		}

		if(bytes<2)
		{
			return PAGE_NA;
		}
	
		if(n<CAPACITY)
		{
			i=0;
		}

		khttp_puts(r,buffer);
	}
	return PAGE_OK;
}

void put_err(struct kreq* r)
{
	khttp_body(r);
	khttp_puts(r,"<p>Failed to load page.Please try again</p>");
}

int main(void)
{
	if( (logp=fopen(klog,"a"))==NULL)
	{
		perror("Failed to open log\n");
		return EXIT_FAILURE;
	}
	
	struct kreq r;
	enum khttp er;
	enum erno re;
	if (khttp_parse( &r , keys , KEY__MAX , pages , PAGE__MAX , PAGE_INDEX ) != KCGI_OK )
	{
		return 0;
	}

	if ((er = sanitise(&r)) != KHTTP_200) 
	{
		khttp_head(&r, kresps[KRESP_STATUS],"%s", khttps[er]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE],"%s", kmimetypes[KMIME_TEXT_HTML]);
		khttp_body(&r);

		if ( KMIME_TEXT_HTML == r.mime )
		{
			khttp_puts(&r, "Could not service request.");
		}
	}	

	else 
	{
		khttp_head(&r, kresps[KRESP_STATUS],"%s", khttps[KHTTP_200]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE],"%s", kmimetypes[r.mime]);
		
		if(check_input(&r)==INPUT_OK)
		{
			if(send_input(&r)==SEND_OK)
			{
				re=getset_session(&r);
				if( re == SESSION_OK )
				{
					if(get_page(&r)!=PAGE_OK)
					{
						khttp_puts(&r,"Failed to Load Page!\n");						
					}
				}
				else 
				{
					if(re == ERR_USERNAME)
					{
						khttp_body(&r);
						khttp_puts(&r,"<p>INVALID USERNAME!</p>");
					}
					else if(re == ERR_PASSWORD)
					{
						khttp_body(&r);
						khttp_puts(&r,"<p>INVALID PASSWORD!</p>");
					}
					else if(re== DATA_READ_ERROR)
					{
						err="Reading Failure from Back program\n";
						logg(err);
					}
					else
					{
						put_err(&r);	
					}
				}
			}
			else
			{
				put_err(&r);				
			}
		}
		else
		{
			put_err(&r);			
		}
	}

	khttp_free(&r);
	return 0;
}

