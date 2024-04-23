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
		khttp_body(&r);
		{		
			process_safe(&r);
		}
	}

	khttp_free(&r);
	return 0;
}

