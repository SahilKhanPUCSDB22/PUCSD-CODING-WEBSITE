#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h> 
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <kcgi.h>
#include <unistd.h>

#define portnum 1237

enum key {
	KEY_STRING1,
	KEY_STRING2,
	KEY_STRING3,
	KEY_STRING4,
	KEY_STRING5,
	KEY_STRING6,
	KEY_STRING7,
	KEY_STRING8,
	KEY_MAX
};



static const struct kvalid keys[KEY_MAX] = {
	{ kvalid_stringne, "ID" }, /* KEY_STRING */
	{ kvalid_stringne, "name" }, /* KEY_STRING */
	{ kvalid_stringne, "lname"},
	{ kvalid_stringne, "add" }, /* KEY_STRING */
	{ kvalid_stringne, "stream" }, /* KEY_STRING */
	{ kvalid_stringne, "pass" }, /* KEY_STRING */
	{ kvalid_stringne, "degree" }, /* KEY_STRING */
	{ kvalid_stringne, "college_id" }, /* KEY_STRING */
};



enum page {
	PAGE_INDEX,
	PAGE__MAX
};
const char *const pages[PAGE__MAX] = {
	"index", /* PAGE_INDEX */
};

enum valid{
	INPUT_OK,
	INPUT_NOT_PROVIDED
};

enum valid input_validation (struct kreq *r) {

	struct kpair *p;
	int i=0;
	while(i<KEY_MAX){
		if((p=r->fieldmap[i])){
			i++;	
		}
		else{
			return INPUT_NOT_PROVIDED;
		}
	}

	return INPUT_OK;
}



static enum khttp sanitise(const struct kreq *r) {
	if (r->page != PAGE_INDEX)
		return KHTTP_404;
	else if (*r->path != '\0') 
		return KHTTP_404;
	else if (r->mime != KMIME_TEXT_HTML)
		return KHTTP_404;
	else if (r->method != KMETHOD_POST)
		return KHTTP_405;
	return KHTTP_200;
}



int main(void) {
	struct kreq r;
	enum khttp er;


	if (khttp_parse(&r, keys, KEY_MAX,pages, PAGE__MAX, PAGE_INDEX) != KCGI_OK)
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

		int sockfd;
		int i=0,rc=0,c=1;
		char buf[1];


		struct sockaddr_in server_addr;
		socklen_t slen= sizeof(server_addr);

		sockfd=socket(AF_INET,SOCK_STREAM,0);

		server_addr.sin_family = AF_INET ;
		server_addr.sin_port = htons(portnum) ;
		server_addr.sin_addr.s_addr = INADDR_ANY ;

		int re=1;
		while(re!=0)
		{
			re=connect(sockfd,(struct sockaddr*)&server_addr,sizeof(server_addr));
		}
		khttp_body(&r);	

		if ( input_validation (&r) == INPUT_OK)
		{
			while(i<KEY_MAX)
			{
				send(sockfd,(char *)r.fieldmap[i]->parsed.s,100,0);
				i++;
			}

			rc=recv(sockfd,(char *)buf,1,MSG_WAITALL);
			
			if(buf[0]=='1'){
				khttp_puts(&r,"<h1>\n");
				khttp_puts(&r,"SignUP AGain\n");
				khttp_puts(&r,"</h1>\n");
				khttp_puts(&r,"<a href=\"/signup.html\">Click Here to Signup Again </a>\n");
			}
			if(buf[0]=='2'){
				khttp_puts(&r,"<h1>\n");
				khttp_puts(&r,"SignUP Successfull\n");
				khttp_puts(&r,"</h1>\n");
				khttp_puts(&r,"<a href=\"/login.html\">Click Here to Login</a>\n");
			}

		}
		else
		{
			khttp_puts(&r,"<h1>");
			khttp_puts(&r,"Provide Required Inputs\n");
			khttp_puts(&r,"</h1>");
			khttp_puts(&r,"<a href=\"/signup.html\">Click Here to Signup Again </a>\n");
		}
		close(sockfd);
	}
	khttp_free(&r);
	return 0;
}


