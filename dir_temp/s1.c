#include <stdarg.h> /* va_list */
#include <stddef.h> /* NULL */
#include <stdint.h> /* int64_t */
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<kcgi.h>

#define listenport 1234


enum key{
	KEY_STRING1,
	KEY_STRING2,
	KEY_STRING3,
	KEY_STRING4,
	KEY_STRING5,
	KEY_STRING6,
	KEY_STRING7,
	KEY_MAX
};

static const struct kvalid keys[KEY_MAX]={
	{kvalid_stringne,"ID"},
	{kvalid_stringne,"name"},
	{kvalid_stringne,"add"},
	{kvalid_stringne,"stream"},
	{kvalid_stringne,"pass"},
	{kvalid_stringne,"degree"},
	{kvalid_stringne,"college_id"},
};

enum valid{
	INPUT_OK,
	INPUT_NOT_PROVIDED
};

enum valid input_validation (struct kreq *r) {
	
	struct kpair *p;
	int i=0;
	while(i<KEY_MAX)
	{
		if((p=r->fieldmap[i])){
			i++;	
		}
		else
		{
			return INPUT_NOT_PROVIDED;
		}
	}
	
	return INPUT_OK;
}


enum page{
	PAGE_INDEX,
	PAGE_MAX
};

const char *const pages[PAGE_MAX]={
	"index",
};

static enum khttp sanitise(const struct kreq *r){
	if(r->page != PAGE_INDEX)
		return KHTTP_404;
	else if(*r->path != '\0')
		return KHTTP_404;
	else if(r->mime != KMIME_TEXT_HTML)
		return KHTTP_404;
	else if(r->method != KMETHOD_POST)
		return KHTTP_405;
	return KHTTP_200;
}

void show(struct kreq *r){		
			khttp_puts(r,"<h1>");
			khttp_puts(r,"SignUp Failed");
			khttp_puts(r,"</h1>\n");
			khttp_puts(r,"<a href=\"signup.html\">Click here to Login </a>\n");
	}	
void show1(struct kreq *r){		
			khttp_puts(r,"<h1>");
			khttp_puts(r,"Signup Failed");
			khttp_puts(r,"</h1>\n");
			khttp_puts(r,"<a href=\"signup.html\">Click here to Login </a>\n");
	}
	
void show2(struct kreq *r){		
			khttp_puts(r,"<h1>");
			khttp_puts(r,"submited successfully");
			khttp_puts(r,"</h1>\n");
			khttp_puts(r,"<a href=\"login.html\">Click here to Login </a>\n");
	}
	

void sendinput(struct kreq *r)
{
	char *s;
        struct sockaddr_in myaddr,other_sock;
        int sockfd=socket(AF_INET,SOCK_STREAM,0);


        memset(&myaddr,0,sizeof(myaddr));
        
	myaddr.sin_family=AF_INET;
        myaddr.sin_port= htons(listenport);
        myaddr.sin_addr.s_addr=INADDR_ANY;

        int l,i=0,rc=0;
        
	socklen_t len=sizeof(other_sock);
        
	int bnd=bind(sockfd,(struct sockaddr *)&myaddr,sizeof(myaddr));
        
	l=listen(sockfd,1);
	
	if(l!=0)
	{
		khttp_puts(r,"connection failed\n");
	}
       	
	if(accept( sockfd,(struct sockaddr *)&other_sock, &len)<0)
	{
		khttp_puts(r,"acceptance failed\n");
	}
	
/*	while(i<KEY_MAX)
	{
		s=(char*)r->fieldmap[i]->parsed.s;
		send(sockfd,(const char *)s,strlen(s),0);
                i++;
        }

	
	while(rc==0)
	{
		rc=recv(sockfd,s,100,0);
		
		if(s[0]=='0')
		{
			show1(r);
		}
		
		else if(s[0]=='1')
		{
			show1(r);	
		}
		
		else
		{
			show2(r);
		}
	}*/
        close(sockfd);
}


int main(void) {
	struct kreq r;
	enum khttp er;
	if (khttp_parse(&r, keys, KEY_MAX,pages, PAGE_MAX, PAGE_INDEX) != KCGI_OK)
	{
		return 0;
	}
	if ((er = sanitise(&r)) != KHTTP_200) 
	{
		khttp_head(&r, kresps[KRESP_STATUS],"%s", khttps[er]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE],"%s", kmimetypes[KMIME_TEXT_PLAIN]);
		khttp_body(&r);
		if (KMIME_TEXT_HTML == r.mime)
		{
			khttp_puts(&r, "Could not service request.");
		}
	} 

	else 
	
	{
		khttp_head(&r, kresps[KRESP_STATUS],"%s", khttps[KHTTP_200]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE],"%s", kmimetypes[r.mime]);
		khttp_body(&r);
		khttp_puts(&r,"<html>\n");
		khttp_puts(&r,"<head>\n<title>print</title>\n</head>\n");
		
		khttp_puts(&r,"<body>\n<p>Successful</p>\n");	
		
		if ( input_validation (&r) == INPUT_OK)
		{
			khttp_puts(&r,"<h1>");
			khttp_puts(&r,"submited successfully");
			khttp_puts(&r,"</h1>\n");
			khttp_puts(&r,"<a href=\"login.html\">Click here to Login </a>\n");
			sendinput(&r);
		}
		else
		{	
			khttp_puts(&r,"<h1>");
			khttp_puts(&r,"Provide Required data");
			khttp_puts(&r,"</h1>\n");
			khttp_puts(&r,"<a href=\"/signup.html\">Click here to Signup</a>\n");
		}
		khttp_puts(&r,"</body>\n</html>");
		khttp_puts(&r,"Done");

	}
	khttp_free(&r);
	return 0;
}


