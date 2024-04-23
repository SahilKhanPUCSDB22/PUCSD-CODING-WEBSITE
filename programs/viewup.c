#include"headers.c"
#include<time.h>
#include<kcgi.h>

#define portnum 1236
#define CAPACITY 1024
#define MAX_SIZE 1024
#define INPUT_MAX 1
enum key 
{
	KEY_STRING,
	KEY__MAX
};

static const struct kvalid keys[KEY__MAX] = 
{
	{ kvalid_stringne, "userid" } /* KEY_STRING */
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
	else if (r->method != KMETHOD_GET)
		return KHTTP_405;
	return KHTTP_200;
}

enum erno {INPUT_NA,INPUT_OK,SEND_OK,SEND_NA,PAGE_OK,PAGE_NA};

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

int sockfd;

enum erno send_input(struct kreq *r)
{
	struct sockaddr_in back;

	back.sin_family=AF_INET;
	back.sin_port=htons(portnum);
	back.sin_addr.s_addr=INADDR_ANY;

	if( (sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		khttp_puts(r,"socket");
		return SEND_NA;
	}

	int rr=1,l;

	while(rr!=0)
	{
		if((rr=connect(sockfd,(const struct sockaddr*)&back,(socklen_t) sizeof(back)))<0)
		{
			khttp_puts(r,"connect");
			return SEND_NA;
		}
	}

	rr=0;

	char uid[CAPACITY];
	strcpy(uid,r->fieldmap[KEY_STRING]->parsed.s);

	while(rr<INPUT_MAX)
	{
		if( (l=send(sockfd,uid,strlen(uid),0))<0)
		{
			khttp_puts(r,"send");
			return SEND_NA;
		}
		rr++;
	}

	return SEND_OK;
}

enum erno get_page(struct kreq* r)
{
	int n,i=1;

	char buffer[CAPACITY];

	while(i!=0)
	{
		n=recv(sockfd,buffer,CAPACITY,MSG_WAITALL);
		if(n<0)
		{
			return PAGE_NA;
		}
		if(n==1)
		{
			if(buffer[0]=='p')
			{
				khttp_puts(r,"<p>Failed to load page , please try again ");
			}
			if(buffer[0]=='f')
			{
				khttp_puts(r,"<p>Failed to load page (bck pg failure) ");
			}
			if(buffer[0]=='a')
			{
				khttp_puts(r,"<p>Nothing uploaded by user , try uploading one ");
			}
			if(buffer[0]=='i')
			{
				khttp_puts(r,"<p>Failed to load page (bck inp failure</p>");
			}
			return PAGE_NA;
		}
		else
		{
			if(n<CAPACITY)
			{
				i=0;
			}
			khttp_puts(r,buffer);
		}
	}
	return PAGE_OK;
}


int main(void)
{
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

		khttp_body(&r);
		enum erno er;

		logp = fopen(klog,"a");
		if(logp==NULL)
		{
			khttp_puts(&r,"Failed to open log");
			khttp_free(&r);
			return 1;
		}

		if( (er=check_input(&r))==INPUT_OK)
		{
			if( send_input(&r) == SEND_OK)
			{
				if( get_page(&r) == PAGE_NA)
				{
					khttp_puts(&r,"Filed to load page,please try again");
				}
			}
			else
			{
				khttp_puts(&r,"Failure");
			}
		}
		else
		{
			khttp_puts(&r,"Couldnt get page , try again");
		}
	}

	khttp_free(&r);
	return 0;
}

