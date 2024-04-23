#include"headers.c"
#include<libpq-fe.h>
#include<ctype.h>

#define portown 1235
#define CAPACITY 1024
#define INPUT_MAX 4

enum erno{INPUT_OK,INPUT_NA,INSERT_OK,INSERT_NA,FILE_PRES,PASS_NA,DATA_F,SESSION_OK,SESSION_NA,PAGE_OK,PAGE_NA,UPDATE_NA,UPDATE_OK};

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
		if( (len=recv(sockfd,input[i],CAPACITY,0))<0)
		{
			err="Failed to recieve inputs from kcgi fun:getinput()\n";
			logg(err);
			return INPUT_NA;
		}
		input[i][len]=0;
		i++;
	}
	printf("%s,%s,%s,%s\n",input[0],input[1],input[2],input[3]);
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
	int rows;

	char *command;

	const char *params[4];

/*	if(input[2][0]=='s')
	{
		command="select * from students where stud_id=$1::bigint";
	}
	else*/
	{
		command="select * from ifiles where fname=$1";
	}

	params[0]=input[0];

	res=PQexecParams(con,(const char*)command,1,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_TUPLES_OK)
	{
		err="Query execution failed fun:db_lookup()\n";
		logg(err);
		printf("%s\n",PQerrorMessage(con));
		return INSERT_NA;
	}
	

	if( (rows=PQntuples(res))>0)
	{
		return FILE_PRES;
	}

/*	if(input[2][0]=='s')
	{
		command="select * from students where stud_id=$1::bigint and stud_password=$2";
	}
	else*/
	{
		command="insert into ifiles values ($1,$2,$3,$4::bigint)";
	}

	params[1]=input[1];
	params[2]=input[2];
	params[3]=input[3];

	res=PQexecParams(con,(const char*)command,4,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_COMMAND_OK)
	{
		err="Query execution failed fun:db_lookup()\n";
		logg(err);
		printf("%s\n",PQerrorMessage(con));
		return INSERT_NA;
	}
	
	return INSERT_OK;
}

static enum erno send_page(int sockfd)
{

	FILE* fp = fopen("/root/website/programs/second/upload.html","r");
	if(fp==NULL)
	{
		err="failed to open page\n";
		logg(err);
		printf("%s\n",err);
		return PAGE_NA;
	}

	char buffer[CAPACITY],lc=1;
	int n=fread((void*)buffer,sizeof(char),CAPACITY,fp);
	
	n=send(sockfd,buffer,n,0);
	if( n < 0 )
	{
		printf("pagena\n");
		return PAGE_NA;
	}

	fclose(fp);

	return PAGE_OK;
}


void send_error(enum erno er,int sockfd)
{
	char buffer[1];
	if(er==INSERT_NA)
	{
		buffer[0]='u';
	}
	else if(er==INPUT_NA)
	{
		buffer[0]='i';
	}
	else if(er==FILE_PRES)
	{
		buffer[0]='f';
	}
	else if(er==PAGE_NA)
	{
		buffer[0]='p';
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
		printf("Failed to open log\n");
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
			printf("connected\n");
			if( (getinput(input,cfd)!=INPUT_OK) )
			{
				send_error(DATA_F,cfd);
				flow=1;
			}

		/*	er=db_lookup(input);
			if( (flow==0) && (er != INSERT_OK) )
			{
				send_error(er,cfd);
				flow=1;
			}
			
			if( (flow==0) && (send_page(cfd)!=PAGE_OK))
			{
				send_error(DATA_F,cfd);
				flow=1;
			}*/
		}
		close(cfd);
	}

	PQfinish(con);
	fclose(logp);

	return 0;
}
