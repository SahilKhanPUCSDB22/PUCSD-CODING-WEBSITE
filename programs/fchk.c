#include"headers.c"
#include<kcgi.h>
#include<libpq-fe.h>

#define MAX_SIZE 20*1024*1024
#define PART_SIZE 4096
#define INPUT_MAX 3
#define MAX_PARTS(x) (x/PART_SIZE) + ((x%PART_SIZE)/(x%PART_SIZE))

PGconn *conn;
PGresult *res;

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

enum erno {INPUT_NA,INPUT_OK,FILE_BIG,FILE_PART,FILE_DIFF,FILE_EXIST,FILE_NEXIST,DB_OK,DB_NA};

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

	if( (r->fieldmap[KEY_FILE]->valsz) > MAX_SIZE )
	{
		return FILE_BIG;
	}

	logg((char*)r->fieldmap[KEY_SESSION]->parsed.s);

	logg("\n");
	return INPUT_OK;
}

enum erno checkindb(struct kreq *r)
{
	char * command,*type,*id;
	char *params[4];

	command="select userid,usertype from sessions where session_id=$1";
	
	params[0]=(char*)r->fieldmap[KEY_SESSION]->parsed.s;

	res=PQexecParams(conn,(char*)command,1,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_TUPLES_OK)
	{
		logg(PQerrorMessage(conn));
		return DB_NA;
	}

	int rows=PQntuples(res),cols=PQnfields(res);	

	if(cols>0 && rows >0)
	{
		id=(char*)PQgetvalue(res,0,0);
		type=PQgetvalue(res,0,1);
	}
	else
	{
		err="Userid ,type fetch failure\n";
		logg(err);
		return DB_NA; 
	}

	if(type[0]=='s')
	{
		command="select * from sfiles where fname=$1 and owner=$2::bigint";
	}
	else
	{
		command="select * from ifiles where fname=$1 and owner=$2::bigint";
	}
	
	params[0]=(char*)r->fieldmap[KEY_FILE]->file;
	params[1]=(char*)id;

	res=PQexecParams(conn,(char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_TUPLES_OK)
	{
		logg(PQerrorMessage(conn));
		return DB_NA;
	}

	if(PQntuples(res)>0)
	{
		if(type[0]=='s')
		{
			command="select * from sfiles where fname=$1 and fsize=$2::bigint";
		}
		else
		{
			command="select * from ifiles where fname=$1 and fsize=$2::bigint";
		}

		char size[1024];
		myitoa((int)r->fieldmap[KEY_FILE]->valsz,size);
		params[1]=(char*)size;

		res=PQexecParams(conn,(char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);

		if(PQresultStatus(res)!=PGRES_TUPLES_OK)
		{
			logg(PQerrorMessage(conn));
			return DB_NA;
		}

		if(PQntuples(res)>0)
		{
			if(type[0]=='s')
			{
				command="select * from sfiles where fname=$1 and parts=$2::bigint";
			}
			else
			{
				command="select * from ifiles where fname=$1 and parts=$2::bigint";
			}
			
			char parts[SEG_SIZE];

			int pp=MAX_SEG(r->fieldmap[KEY_FILE]->valsz);

			myitoa(pp,parts);

			logg(parts);
			params[1]=(char*)parts;

			res=PQexecParams(conn,(char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);
			
			if(PQresultStatus(res)!=PGRES_TUPLES_OK)
			{
				logg(PQerrorMessage(conn));
				return DB_NA;
			}
			
			if(PQntuples(res)>0)
			{
				return FILE_EXIST;
			}
			else
			{
				return FILE_PART;
			}
		}
		else
		{
			return FILE_DIFF;
		}
	}
	else
	{
		logg("yena\n");
		return FILE_NEXIST;
	}
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
		char *out;

		conn=PQconnectdb("dbname=pucsd_hackerrank user=postgres password=1234 port=5432");

		if(PQstatus(conn)!=CONNECTION_OK)
		{
			out=PQerrorMessage(conn);
			khttp_puts(&r,out);
			khttp_free(&r);
			return 1;
		}

		logp = fopen(klog,"a");
		if(logp==NULL)
		{
			khttp_puts(&r,"Failed to open log");
			khttp_free(&r);
			return 1;
		}

		if( (er=check_input(&r))==INPUT_OK)
		{
			if((er=checkindb(&r))!=DB_OK)
			{
				if(er==FILE_PART)
				{
					out="0";
				}
				if(er==FILE_DIFF)
				{
					out="1";
				}
				if(er==FILE_EXIST)
				{
					out="2";
				}
				if(er==FILE_NEXIST)
				{
					out="3";
				}
				if(er==DB_NA)
				{
					out="Failure to fetch details";
				}
			}
		}
		else
		{
			if(er==FILE_BIG)
			{
				out="4";
			}
			else
			{
				out="Couldnt get page , try again";
			}
		}
		khttp_puts(&r,out);
	}
	PQfinish(conn);
	khttp_free(&r);
	return 0;
}

