#include<stdio.h>

#include <sys/types.h> /* size_t, ssize_t */
#include <stdarg.h> /* va_list */
#include <stddef.h> /* NULL */
#include <stdint.h> /* int64_t */
#include <kcgi.h>
#include <kcgihtml.h>



enum key {
	KEY_STRING,
	KEY_INTEGER,
	KEY__MAX
};

static const struct kvalid keys[KEY__MAX] = {
	{ kvalid_stringne, "string" }, /* KEY_STRING */
	{ kvalid_int, "integer" }, /* KEY_INTEGER */
};

static void process(struct kreq *r) {
	struct kpair *p;
	khttp_puts(r, "<p>\n");
	khttp_puts(r, "The string value is ");
	if ((p = r->fieldmap[KEY_STRING]))
		khttp_puts(r, p->parsed.s);
	else if (r->fieldnmap[KEY_STRING])
		khttp_puts(r, "<i>failed parse</i>");
	else 
		khttp_puts(r, "<i>not provided</i>");
	khttp_puts(r, "</p>\n");
}

static void process_safe(struct kreq *r) {
	struct kpair *p;
	struct khtmlreq req;
	khtml_open(&req, r, 0);
	khtml_elem(&req, KELEM_P);
	khtml_puts(&req, "The string value is ");
	if ((p = r->fieldmap[KEY_STRING])) {
		khtml_puts(&req, p->parsed.s);
	} else if (r->fieldnmap[KEY_STRING]) {
		khtml_elem(&req, KELEM_I);
		khtml_puts(&req, "failed parse");
	} else {
		khtml_elem(&req, KELEM_I);
		khtml_puts(&req, "not provided");
	}
	khtml_close(&req);
}

enum page {
	PAGE_INDEX,
	PAGE__MAX
};
const char *const pages[PAGE__MAX] = {
	"index", /* PAGE_INDEX */
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

int main(void) {
	struct kreq r;
	enum khttp er;
	if (khttp_parse(&r, keys, KEY__MAX,
				pages, PAGE__MAX, PAGE_INDEX) != KCGI_OK)
		return 0;
	if ((er = sanitise(&r)) != KHTTP_200) {
		khttp_head(&r, kresps[KRESP_STATUS],
				"%s", khttps[er]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE],
				"%s", kmimetypes[KMIME_TEXT_PLAIN]);
		khttp_body(&r);
		if (KMIME_TEXT_HTML == r.mime)
			khttp_puts(&r, "Could not service request.");
	} else {
		khttp_head(&r, kresps[KRESP_STATUS],
				"%s", khttps[KHTTP_200]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE],
				"%s", kmimetypes[r.mime]);

		FILE * fp =fopen("/usr/local/www/apache24/log/errlog","w+");
		if(fp!=NULL)	
		{
			khttp_body(&r);
			khttp_puts(&r,"hello");
		}
	}
	khttp_free(&r);
	return 0;
};


