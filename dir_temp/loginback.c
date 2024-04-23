#include"headers.c"
#include<libpq-fe.h>
#include<sodium.h>
#include<ctype.h>

#define portown 1235
#define portnum 1236
#define CAPACITY 1024
#define Len 32
#define range 63
#define INPUT_MAX 3

enum erno{INPUT_OK,INPUT_NA,VALUES_OK,VALUES_NA,UID_NA,PASS_NA,DATA_F,SESSION_OK,SESSION_NA,PAGE_OK,PAGE_NA,UPDATE_NA,UPDATE_OK};

struct sockaddr_in recvaddr[2],senaddr;
int sockfd[2],setup;
PGconn* con;
PGresult* res;

static enum erno getinput( char **input)
{
	int len;
	socklen_t LEN;
	char i=0;

	input[0]=(char*) malloc (sizeof(char)*CAPACITY);
	input[1]=(char*) malloc (sizeof(char)*CAPACITY);
	input[2]=(char*) malloc (sizeof(char)*CAPACITY);

	if((sockfd[0]=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		err="Socket syscall failed fun:getinput()\n";
		logg(err);
		return INPUT_NA;
	}

	memset(&recvaddr[0],0,sizeof(recvaddr[0]));
	memset(&senaddr,0,sizeof(senaddr));

	recvaddr[0].sin_family=AF_INET;
	recvaddr[0].sin_port=htons(portown);
	recvaddr[0].sin_addr.s_addr=INADDR_ANY;

	LEN=sizeof(senaddr);

	if( bind(sockfd[0],(const struct sockaddr*)&recvaddr[0],sizeof(recvaddr[0]))<0)
	{
		err="Binding failed in fun:getinput()\n";
		logg(err);
		return INPUT_NA;
	}

	while(i<INPUT_MAX)
	{
		if( (len=recvfrom(sockfd[0],(void*)input[i],CAPACITY,MSG_WAITALL,(struct sockaddr*)&senaddr,&LEN))<0)
		{
			err="Failed to recieve inputs from kcgi fun:getinput()\n";
			logg(err);
			return INPUT_NA;
		}
		input[i][len]='\0';
		i++;
	}

	logg(input[0]);
	logg("\n");
	logg(input[1]);
	logg("\n");
	logg(input[2]);
	logg("\n");

	return INPUT_OK;
}

static enum erno db_lookup(char **input)
{
	char j=0;
	while( (input[0][j])!=0 )
	{	
		if( (input[0][j]) <48 || (input[0][j]) >57 )
		{
			return UID_NA;
		}
		j++;
	}

	con=PQconnectdb("dbname=pucsd_hackerrank user=postgres password=1234 port=5432");
	if(PQstatus(con)!=CONNECTION_OK)
	{
		logg(PQerrorMessage(con));
		err="Database connection failed fun:db_lookup()\n";
		logg(err);
		return VALUES_NA;
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

	int rows;

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
		logg(PQerrorMessage(con));
		return VALUES_NA;
	}

	if( (rows=PQntuples(res))==0)
	{
		return PASS_NA;
	}

	return VALUES_OK;
}

//unsigned char nonce[Len+1];
static enum erno send_session(unsigned char nonce[])
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
		nonce[i]= 63 + (nonce[i]%range);
		i++;
	}
	nonce[Len]=0;

	logg((char*) nonce);

	logg("\n");

	if((sockfd[1]=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		err="socket syscall failed fun:send_session()\n";
		logg(err);
		return SESSION_NA;
	}

	memset(&recvaddr[1],0,sizeof(recvaddr[1]));

	recvaddr[1].sin_port=htons(portnum);
	recvaddr[1].sin_family=AF_INET;
	recvaddr[1].sin_addr.s_addr=INADDR_ANY;


	setup=1;

	if( sendto(sockfd[1],(void*)nonce,Len,0,(const struct sockaddr*)&recvaddr[1],sizeof(recvaddr[1])) < 0)
	{
		err="failed to send session id fun:send_session\n";
		logg(err);
		return SESSION_NA;
	}

	return SESSION_OK;
}

static enum erno send_page(char *input , unsigned char *nonce)
{
	FILE* fp = fopen("page","w+");
	if(fp==NULL)
	{
		err="failed to open page\n";
		logg(err);
		return PAGE_NA;
	}

	fprintf(fp,"<html>\n<head>\n<title>Welcome</title>\n<link rel=\"stylesheet\" href=\"/csssnehal.css\">\n</head>\n<body>\n<p><b>WELCOME</b> : %s</p><br>\n<p><b>Session Id :</b> %s</p><br>\n<form action=\"/cgi-bin/update.cgi\" method=\"post\">\n<label for=\"value\">Enter the value:</label>\n<input type=\"text\" id=\"value\" name=\"val\" ",input,nonce);

	char* command="select last_data from data where user_id = $1 ::bigint";
	char* params[1];
	params[0]=input;

	res=PQexecParams(con,(const char*)command,1,NULL,(const char* const*)params,NULL,NULL,0);
	
	if(PQresultStatus(res)!=PGRES_TUPLES_OK)
	{
		printf("here\n");
		err="Query execution failed fun:db_lookup()\n";
		logg(err);
		logg(PQerrorMessage(con));
		return PAGE_NA;
	}

	if( PQntuples(res)>0)
	{
		printf("here2\n");
		char *val = PQgetvalue(res,0,0);
		fprintf(fp,"value= \"%s\" ",val);
	}


	fprintf(fp,"required><br>\n<input type=\"text\" id=\"xyz\" name=\"id\" value=\"%s\">\n<button> Submit </button><br>\n</form>\n<p><a href=\"/login.html\">Click here to Logout</a></p>\n</body>\n</html>",input);

	rewind(fp);

	char buffer[CAPACITY],lc=1;
	int n=fread((void*)buffer,sizeof(unsigned char),CAPACITY,fp);
	int counter= 0;

	while(lc!=0 && n>0)
	{
		counter+=n;

		if(n<CAPACITY)
		{
			lc=0;
		}

		if(sendto(sockfd[1],(void*)buffer,n,0,(const struct sockaddr*)&recvaddr[1],sizeof(recvaddr[1]))<0)
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

enum erno update_session(const char* nonce)
{
	char *command="insert into sessions values ( $1 , $2 )";

	const char * params[2];
	params[0]=nonce;
	params[1]="welcome";

	res=PQexecParams(con,(const char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_COMMAND_OK)
	{
		err="Query execution failed fun:update_session()\n";
		logg(err);
		logg(PQerrorMessage(con));
		return UPDATE_NA;
	}

	return UPDATE_OK;
}

void send_error(enum erno er)
{
	char *buffer;
	if(er==PASS_NA)
	{
		buffer="p";
	}
	else if(er==UID_NA)
	{
		buffer="u";
	}
	else
	{
		buffer="d";
	}

	if(setup!=1)
	{
		if((sockfd[1]=socket(AF_INET,SOCK_DGRAM,0))<0)
		{	
			err="socket syscall failed fun:send_error()\n";
			logg(err);
		}

		memset(&recvaddr[1],0,sizeof(recvaddr[1]));

		recvaddr[1].sin_port=htons(portnum);
		recvaddr[1].sin_family=AF_INET;
		recvaddr[1].sin_addr.s_addr=INADDR_ANY;
	}

	if( sendto(sockfd[1],(void*)buffer,1,0,(const struct sockaddr*)&recvaddr[1],sizeof(recvaddr[1])) < 0)
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

	int flow;
	char *input[INPUT_MAX];
	unsigned char nonce[Len+1];

	while(1)
	{
		flow=0;
		setup=0;

		if( (getinput(input)!=INPUT_OK) && (flow==0))
		{
			//	err="Failed to get input fun:input!!\n";
			//	logg(err);
			send_error(DATA_F);
			flow=1;
			//return EXIT_FAILURE;
		}
		else
		{
			printf("conn\n");
		}

		er=db_lookup(input);
		if( (er != VALUES_OK) && (flow==0))
		{
			//	err="Failed to process values from database fun:db_lookup\n";
			//	logg(err);
			send_error(er);
			flow=1;
			//return EXIT_FAILURE;
		}

		if( (send_session(nonce)!=SESSION_OK)  && (flow==0))
		{
			//	err="Failed to create session fun:send_session\n";
			//	logg(err);
			send_error(DATA_F);
			flow=1;	
			//return EXIT_FAILURE;
		}

		if( (update_session((const char*)nonce)!=UPDATE_OK)  && (flow==0))
		{
			//	err=("Failed to log session into database fun:update_session()\n");
			//	logg(err);
			send_error(DATA_F);
			flow=1;
		}

		sleep(10);

		if( (send_page(input[0],(unsigned char*)nonce)!=PAGE_OK)  && (flow==0))
		{
			//	err="Failed to send page fun:send_page\n";
			//	logg(err);
			send_error(DATA_F);
			//return EXIT_FAILURE;
			flow=1;
		}

		close(sockfd[1]);
		close(sockfd[0]);
		PQfinish(con);
	}

	fclose(logp);

	return 0;
}
