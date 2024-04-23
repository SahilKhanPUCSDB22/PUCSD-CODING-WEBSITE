#include"headers.c"
#include<kcgi.h>

#define portnum 1237
#define CAPACITY 1024
#define INPUT_MAX 5
#define UTYPE_LEN 3

enum key 
{
	KEY_SESSION,
	KEY_UTYPE,
	KEY_FILE,
	KEY__MAX
};

static const struct kvalid keys[KEY__MAX] = 
{
	{ kvalid_stringne , "sessionid" } /* KEY_STRING */,
	{ kvalid_stringne , "utype" },
	{ NULL , "file"}
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

enum erno {INPUT_NA,INPUT_OK,FILE_BIG,SEND_OK,SEND_NA,PAGE_OK,PAGE_NA};

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

	int rr=1,l,size;

	while(rr!=0)
	{
		if((rr=connect(sockfd,(const struct sockaddr*)&back,(socklen_t) sizeof(back)))<0)
		{
			khttp_puts(r,"connect");
			return SEND_NA;
		}
	}

	char *input[INPUT_MAX],temp[10];
	input[0]=(char*)r->fieldmap[KEY_SESSION]->parsed.s;	
	input[1]=(char*)r->fieldmap[KEY_UTYPE]->parsed.s;	
	input[2]=(char*)r->fieldmap[KEY_FILE]->file;	
	input[3]=(char*)r->fieldmap[KEY_FILE]->ctype;
	myitoa((int)r->fieldmap[KEY_FILE]->valsz,temp); //filesize
	input[4]=(char*)temp;	

	rr=1;

	char INP_STREAM[size=(SESSION_LEN+FNAME_LEN+FSIZE_LEN+FTYPE_LEN+UTYPE_LEN+INPUT_MAX+1)];
	
	mycpy(INP_STREAM,input[0]);
	
	while(rr<INPUT_MAX)
	{
		myappend(INP_STREAM,input[rr]);
		rr++;
	}

	if( (l=send(sockfd,INP_STREAM,strlen(INP_STREAM),0))<0)
	{
		khttp_puts(r,"send");
		return SEND_NA;
	}

	return SEND_OK;
}

enum erno send_file(struct kreq* r)
{
	int n;

	char buffer[CAPACITY];

	n=recv(sockfd,buffer,SEG_SIZE,0);
	if(n<0)
	{
		return PAGE_NA;
	}

	buffer[n]=0;

	if(buffer[0]>65)
	{
		if(buffer[0]=='u')
		{
			khttp_puts(r,"<p>Failed to upload file , please try again ");
		}
		if(buffer[0]=='p')
		{
			khttp_puts(r,"<p>Failed to load page (bck pg failure) ");
		}
		if(buffer[0]=='f')
		{
			khttp_puts(r,"<p>File Already uploaded, please try renaming or upload a new one ");
		}
		if(buffer[0]=='i')
		{
			khttp_puts(r,"<p>Failed to load page (bck inp failure</p>");
		}
		return PAGE_NA;
	}
	else
	{
		int segno,fsize,maxseg,pos,left,buflen,re,flag=0;
		
		segno = myatoi((char*)buffer);

		fsize = (int)r->fieldmap[KEY_FILE]->valsz;

		maxseg=MAX_SEG(fsize);
		
		left = fsize - SEG_SIZE*segno;

		char *file = (char*) r->fieldmap[KEY_FILE]->val;

		pos = segno*SEG_SIZE;

		while(segno<maxseg && (flag==0))
		{
			if(left<SEG_SIZE)
                	{
                        	buflen=left;
                	}
                	else
                	{
                        	buflen=SEG_SIZE;
                	}

		/*	if(segno==4)
			{
				close(sockfd);
				return 0;
			}*/

                	if( (re=send(sockfd,(void*)(file+pos),buflen,0)) < 0 )
                	{
                        	logg("File rec failed");
                        	flag=1;
                	}
			
			if( (re==buflen) && (flag==0))
			{
				left-=buflen;
				pos+=buflen;
				segno++;
			}
			else
			{
				flag=1;
			}
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
				if( (er=send_file(&r)) != PAGE_OK)
				{
					khttp_puts(&r,"<p>Failure(Page)</p>");
				}
				else
				{
					khttp_puts(&r,"File was uploaded");
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
	close(sockfd);
	khttp_free(&r);
	return 0;
}

