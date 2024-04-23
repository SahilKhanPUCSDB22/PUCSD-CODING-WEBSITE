#include"headers.c"
#include<libpq-fe.h>
#include<kcgihtml.h>
#include<sodium.h>
#include<time.h>
#include<string.h>

enum key {
	KEY_STRING1,
	KEY_STRING2,
	KEY__MAX
};

static const struct kvalid keys[KEY__MAX] = {
	{ kvalid_stringne, "ab" }, /* KEY_STRING */
	{ kvalid_stringne, "cd" }, /* KEY_STRING */
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

int ret_session(struct kreq **r)
{
	int ret=0;
	char buf[32];
	if(sodium_init() != -1)
	{
		const int len = crypto_secretbox_NONCEBYTES;
		char nonce[len];
		randombytes_buf(nonce,len);
   	 	for (int i = 0; i < len; ++i) 
		{
        		nonce[i] = 'a' + (nonce[i] % 26); // Convert to lowercase letters
    		}	
		khttp_head(*r, kresps[KRESP_SET_COOKIE],"%s=%s; Path=/; expires=%s","session_id", nonce , khttp_epoch2str( time(NULL) + 5, buf, sizeof(buf) ));
		ret=1;
	}
	return ret;
}

static void process_safe(struct kreq *r) 
{
	//khttp_body(r);
	struct khtmlreq req;

	khtml_open(&req, r, 0);

	khtml_elem(&req,KELEM_DOCTYPE);
	khtml_elem(&req,KELEM_HTML);

	khtml_elem(&req,KELEM_HEAD);

	khtml_elem(&req,KELEM_TITLE);
	khtml_puts(&req,"DASHBOARD");
	khtml_closeelem(&req,1); //close title

	khttp_puts(r,"<link rel=\"stylesheet\" href=\"/csssnehal.css\">");
	khtml_closeelem(&req,1); //closehead

	khtml_elem(&req, KELEM_BODY); //body start

	khtml_elem(&req,KELEM_H1);
	khtml_puts(&req,"Welcome : ");
	khtml_puts(&req,r->fieldmap[KEY_STRING1]->parsed.s);
	khtml_closeelem(&req,1);

	khtml_close(&req);
}

char check(const char *username,const char *password)
{
	char re=0;

	const char *info="dbname=pucsd_hackerrank user=postgres password=123";
	PGconn *conn;
	PGresult * res;

	conn=PQconnectdb(info);
	if(PQstatus(conn) == CONNECTION_OK)
	{
		const char *const paramvalues=username;
		//++(paramvalues);
		//paramvalues=&password;
		//res=PQexecParams(conn,"select * from students where stud_fname = $1",1,NULL,&paramvalues,NULL,NULL,0);
//		res=PQexec(conn,strcat("select * from students where stud_fame =",username));
		int row = PQntuples(res);
		if(/*some query result*/1 )
		{
			if(/*details match*/1)
			{
				re=3;
			}
			else
			{
				re=2;
			}
		}
		else
		{
			re=1;
		}
	}
	return re;
}


char validate(struct kreq *r)
{
	char re=0;
	struct kpair *p[2];
	p[0]=r->fieldmap[KEY_STRING1];
	p[1]=r->fieldmap[KEY_STRING2];

	char c=check ( p[0]->parsed.s , p[1]->parsed.s );

	if( c==3 )
	{
		if(ret_session(&r))
		{
			re=1;
			khttp_body(r);
			khttp_puts(r,"<p>session_id set sucessfully</p>\n");
		}
		else
		{
			//put session creation failed
			khttp_body(r);
			khttp_puts(r,"Session creation failed!!!\nPlease try again");
		}
	}
	else
	{
		khttp_body(r);
		switch(c)
		{
			case 0 :khttp_puts(r,"Failed to fetch values(DB FAILURE)!!\nPlease try again later");
				break;
			case 1 :khttp_puts(r,"No such username present\n");
				break;
			case 2 :khttp_puts(r,"Incorrect password\n");
				break;
		}
	}
	return re;
}	

int main(void)
{
	struct kreq r;
	enum khttp er;
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
		//khttp_body(&r);
		if(validate(&r))
		{		
			process_safe(&r);
		}
	}

	khttp_free(&r);
	return 0;
}

