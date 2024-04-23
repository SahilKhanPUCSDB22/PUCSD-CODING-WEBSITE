#include"headers.c"
#include<libpq-fe.h>
#include<sodium.h>
#include<ctype.h>

#define portown 1234
#define CAPACITY 1024
#define Len 32
#define range 9
#define INPUT_MAX 3

enum erno{INPUT_OK,INPUT_NA,VALUES_OK,VALUES_NA,UID_NA,PASS_NA,DATA_F,SESSION_OK,SESSION_NA,PAGE_OK,PAGE_NA,UPDATE_NA,UPDATE_OK};

PGconn* con;
PGresult* res;

static enum erno getinput( char **input , int sockfd)
{
	int len;
	char i=0;

	while(i<INPUT_MAX)
	{
		input[i]=(char*)malloc(sizeof(char)*CAPACITY);
		i++;
	}
	
	i=0;
	
	while(i<INPUT_MAX)
	{
		if( (len=recv(sockfd,input[i],CAPACITY,MSG_WAITALL))<0)
		{
			err="Failed to recieve inputs from kcgi fun:getinput()\n";
			logg(err);
			return INPUT_NA;
		}
		input[i][len]=0;
		i++;
	}

	i=0;

	while(i<INPUT_MAX)
	{
		logg(input[i++]);
		logg("#");
	}
	logg("\n");
	
	return INPUT_OK;
}

static enum erno db_lookup(char **input)
{
	char j=0;
	int rows;

	while( (input[0][j])!=0 )
	{	
		if( (input[0][j]) <48 || (input[0][j]) >57 )
		{
			return UID_NA;
		}
		j++;
	}
	

	char *command;

	const char *params[2];

	if(input[2][0]=='s')
	{
		command="select * from students where stud_id=$1::bigint";
	}
	else
	{
		command="select * from interviewers where interviewers_id=$1::bigint";
	}

	params[0]=input[0];

	res=PQexecParams(con,(const char*)command,1,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_TUPLES_OK)
	{
		err="Query execution failed fun:db_lookup()\n";
		logg(err);
		logg(PQerrorMessage(con));
		return VALUES_NA;
	}

	if( (rows=PQntuples(res))==0)
	{
		return UID_NA;
	}
	
	if(input[2][0]=='s')
	{
		command="select * from students where stud_id=$1::bigint and stud_password=$2";
	}
	else
	{
		command="select * from interviewers where interviewers_id=$1::bigint and interviewers_password=$2";
	}

	params[1]=input[1];

	res=PQexecParams(con,(const char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_TUPLES_OK)
	{
		err="Query execution failed fun:db_lookup()\n";
		logg(err);
		return VALUES_NA;
	}

	if( (rows=PQntuples(res))==0)
	{
		return PASS_NA;
	}
		
	return VALUES_OK;
}

static enum erno create_session(unsigned char nonce[])
{
	if(sodium_init()==-1)
	{
		err="sodium initialized failed fun:send_session()\n";
		logg(err);
		return SESSION_NA;
	}

	randombytes_buf(nonce,Len);

	int i=0;
	while(i<Len)
	{
		nonce[i]= 48 + (nonce[i]%range);
		i++;
	}
	nonce[Len]=0;

	logg("session id :");
	logg((char*) nonce);
	logg("\n");

	return SESSION_OK;
}

static enum erno send_page(char *input , unsigned char *nonce,int sockfd)
{
	FILE* fp = fopen("page","w+");
	if(fp==NULL)
	{
		err="failed to open page\n";
		logg(err);
		return PAGE_NA;
	}

	fprintf(fp,"<html>\n<head>\n<title>Welcome</title>\n<link rel=\"stylesheet\" href=\"/css-bin/csssnehal.css\">\n</head>\n<body>\n<p><b>WELCOME</b> : %s</p><br>\n<p><b>Session Id :</b> %s</p><br>\n<p><a href=\"#\" onclick=\"upload()\">Click here to Upload Files</a></p>\n<p><a href=\"#\" onclick=\"viewuploads()\">Click here to view Uploaded Files</a></p>\n<p><a href=\"/login.html\">Click here to Logout</a></p>\n",nonce,input);

	fprintf(fp,"<script>\nfunction upload() {\n var form = document.createElement('form');\nform.method = 'POST';\nform.action = '/cgi-bin/upload.cgi';\nform.style.display='none'\nvar session=document.createElement('input');\nsession.type='hidden';\nsession.name='sessionid';\nsession.value='%s';\nform.appendChild(session);\ndocument.body.appendChild(form);\nform.submit();\n}\n",nonce);

	fprintf(fp,"</script>\n</body>\n</html>");

	rewind(fp);

	char buffer[CAPACITY],lc=1;
	int n=fread((void*)buffer,sizeof(char),CAPACITY,fp);
	
	int counter= 0,nb;

	while(lc!=0 && n>0)
	{
		counter+=n;

		if(n<CAPACITY)
		{
			lc=0;
		}

		nb=send(sockfd,buffer,n,0);
		if( nb < 0 )
		{
			err="Failed to send page fun:send_page()\n";
			logg(err);
			return PAGE_NA;
		}
	
		n=fread((void*)buffer,sizeof(char),CAPACITY,fp);
	}

	fclose(fp);

	return PAGE_OK;
}

enum erno update_session(const char* nonce,char *userid , char* type)
{
	char * command;
	const char * params[3];

	command="insert into sessions values ( $1 , $2::bigint ,$3)";
	
	params[0]=nonce;
	params[1]=userid;
	params[2]=type;

	res=PQexecParams(con,(const char*)command,3,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_COMMAND_OK)
	{
		err="Query execution failed fun:update_session()\n";
		logg(err);
		logg(PQerrorMessage(con));
		return UPDATE_NA;
	}
	
	return UPDATE_OK;
}

void send_error(enum erno er,int sockfd)
{
	char buffer[1];
	if(er==PASS_NA)
	{
		buffer[0]='p';
	}
	else if(er==UID_NA)
	{
		buffer[0]='u';
	}
	else
	{
		buffer[0]='d';
	}

	int n=send(sockfd,(void*)buffer,1,0);
	if( n < 0)
	{
		err="failed to send error fun:send_error\n";
		logg(err);
	}
}

int main(void)
{
	enum erno er;
	logp=fopen(log ,"a");
	if ( logp == NULL)
	{
		perror("Failed to open log\n");
		return EXIT_FAILURE;
	}

	con=PQconnectdb("dbname=pucsd_hackerrank user=postgres password=1234 port=5432");
	if(PQstatus(con)!=CONNECTION_OK)
	{
		logg(PQerrorMessage(con));
		err="Database connection faile\n";
		logg(err);
		return EXIT_FAILURE;
	}

	char *input[INPUT_MAX];
	
	unsigned char nonce[Len+1];

	struct sockaddr_in senaddr;
	senaddr.sin_family=AF_INET;
	senaddr.sin_port=htons(portown);
	senaddr.sin_addr.s_addr=INADDR_ANY;

	socklen_t LEN = sizeof(senaddr);

	int sockfd,cfd,flow;

	if( (sockfd=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		err="Socket syscall failed\n";
		logg(err);
		return EXIT_FAILURE;
	}

	if( bind(sockfd,(const struct sockaddr*)&senaddr,LEN) <0)
	{
		err="Binding failed \n";
		logg(err);
		return EXIT_FAILURE;
	}

	if( listen(sockfd,9999999) != 0)
	{
		err="cannot listen\n";
		logg(err);
		return EXIT_FAILURE;
	}
	
	char loop=1;
	
	while(loop!=0)
	{
		flow=0;
		cfd = accept(sockfd,(struct sockaddr*)&senaddr,(socklen_t*) &LEN);
		
		if(cfd!=-1)
		{
//			printf("connected\n");
			if( (getinput(input,cfd)!=INPUT_OK) )
			{
				send_error(DATA_F,cfd);
				flow=1;
			}

//			printf("input\n");

			er=db_lookup(input);
			if( (flow==0) && (er != VALUES_OK) )
			{
				send_error(er,cfd);
				flow=1;
			}
//			printf("db done\n");

			if((flow==0) && (create_session(nonce)!=SESSION_OK)  )
			{
				send_error(DATA_F,cfd);
				flow=1;	
			}
//			printf("crea done\n");

			if( (flow==0) && (update_session((const char*)nonce,input[0],input[2])!=UPDATE_OK))
			{
				send_error(DATA_F,cfd);
				flow=1;
			}
			
//			printf("upd done\n");
			if( (flow==0) && (send_page(input[0],(unsigned char*)nonce,cfd)!=PAGE_OK))
			{
				send_error(DATA_F,cfd);
				flow=1;
			}
//			printf("pg done\n");
		}
		close(cfd);
	}

	PQfinish(con);
	fclose(logp);

	return 0;
}
