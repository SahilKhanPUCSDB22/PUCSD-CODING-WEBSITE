#include <sys/types.h> /* size_t, ssize_t */
#include <stdarg.h> /* va_list */
#include <stddef.h> /* NULL */
#include <stdint.h> /* int64_t */
#include <kcgi.h>
#include<libpq-fe.h>

enum key {
	KEY_STRING1,
	KEY_STRING2,
	KEY__MAX
};

static const struct kvalid keys[KEY__MAX] = {
	{ kvalid_stringne, "val" } /* KEY_STRING */,
	{ kvalid_stringne, "id" }
};


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
	} else 
	{
		khttp_head(&r, kresps[KRESP_STATUS],
				"%s", khttps[KHTTP_200]);
		khttp_head(&r, kresps[KRESP_CONTENT_TYPE],
				"%s", kmimetypes[r.mime]);
		khttp_body(&r);

		PGconn* conn=PQconnectdb("dbname=pucsd_hackerrank password=1234 user=postgres");
	
		char * command="insert into data values ( $1::bigint )";
		
		char* params[2];
		params[0]=(char*)r.fieldmap[KEY_STRING2]->parsed.s;
		params[1]=(char*)r.fieldmap[KEY_STRING1]->parsed.s;

		PGresult * res = PQexecParams(conn,(const char*)command,1,NULL,(const char* const*)params,NULL,NULL,0);
		if( PQresultStatus(res)!=PGRES_COMMAND_OK)
		{
//			khttp_puts(&r,"failure\n");
//			khttp_puts(&r,PQerrorMessage(conn));
			//return 1;
		}

		command="update data set last_data=$1 where user_id=$2::bigint";
		
		params[0]=(char*)r.fieldmap[KEY_STRING1]->parsed.s;
		params[1]=(char*)r.fieldmap[KEY_STRING2]->parsed.s;

		res = PQexecParams(conn,(const char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);
	
		if( PQresultStatus(res)!=PGRES_COMMAND_OK)
		{
			khttp_puts(&r,"failure\n");
		}
		else
		{
			khttp_puts(&r,"Value updated\n");
			khttp_puts(&r,"<a href=\"/login.html\"> Click here to login again</a>\n");
		}
	}
	  khttp_free(&r);
  return 0;
};
