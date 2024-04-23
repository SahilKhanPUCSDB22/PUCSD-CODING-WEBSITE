#include"headers.c"
#include<libpq-fe.h>
#include<ctype.h>

#define portown 1236
#define CAPACITY 1024
#define INPUT_MAX 1

enum erno{INPUT_OK,INPUT_NA,FILE_OK,FILE_NA,NO_FILES,PAGE_OK,PAGE_NA};

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
		printf("%s\n",input[i]);
		i++;
	}
	logg(input[0]);
	logg("\n");

	printf("out\n");
	return INPUT_OK;
}

static enum erno db_lookup(char **input)
{
	printf("inside\n");
	char j=0;
	int rows,cols;

	char *command;

	const char *params[INPUT_MAX];

	/*	if(input[2][0]=='s')
		{
		command="select * from students where stud_id=$1::bigint";
		}
		else*/
	{		
		command="select fname,ftype,fsize from ifiles where owner=($1::bigint);";
	}

	params[0]=input[0];

	res=PQexecParams(con,(const char*)command,1,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_TUPLES_OK)
	{
		err="Query execution failed fun:db_lookup()\n";
		logg(err);
		printf("%s\n",PQerrorMessage(con));
		return FILE_NA;
	}


	if( (rows=PQntuples(res))==0)
	{
		return NO_FILES;
	}
	else
	{
		FILE* fp=fopen("/root/website/programs/files/uploaded","w+");
		if(fp==NULL)
		{
			err="file opening failed";
			printf("%s\n",err);
			logg(err);
		}

		rows=PQntuples(res);		
		cols=PQnfields(res);

		printf("%d %d\n",rows,cols);
		fprintf(fp,"<html>\n<body>\n<table border=\"1\">\n <tr>\n <th>File Name</th>\n<th>File Type</th>\n<th>File Size</th>\n</tr>");
		int i=0,j=0;
		while(i < rows) 
		{
			if(j==0)
			{
				fprintf(fp,"<tr>\n");
			}

			fprintf(fp,"<td> %s </td>",PQgetvalue(res,i,j));
			
			j++;

			if(j==cols)
			{
				fprintf(fp,"</tr>\n");
				j=0;
				i++;
			}
		}
		fprintf(fp," </table>\n</body>\n</html>\n");

		fclose(fp);
	}

	printf("file created\n");
	return FILE_OK;
}

static enum erno send_page(int sockfd)
{

	FILE* fp = fopen("/root/website/programs/files/uploaded","r");
	if(fp==NULL)
	{
		err="failed to open page\n";
		logg(err);
		printf("%s\n",err);
		return PAGE_NA;
	}

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
			printf("pagena\n");
			return PAGE_NA;
		}
		n=fread((void*)buffer,sizeof(char),CAPACITY,fp);
	}
	

	fclose(fp);

	return PAGE_OK;
}


void send_error(enum erno er,int sockfd)
{
	char buffer[1];
	if(er==FILE_NA)
	{
		buffer[0]='f';
	}
	else if(er==INPUT_NA)
	{
		buffer[0]='i';
	}
	else if(er==NO_FILES)
	{
		buffer[0]='a';
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
			if( (er=getinput(input,cfd)!=INPUT_OK) )
			{
				send_error(er,cfd);
				flow=1;
			}

			er=db_lookup(input);
			if( (flow==0) && (er != FILE_OK) )
			{
				send_error(er,cfd);
				flow=1;
			}

			if( (flow==0) && (er=send_page(cfd)!=PAGE_OK))
			{
				send_error(er,cfd);
				flow=1;
			}
		}
		close(cfd);
	}

	PQfinish(con);
	fclose(logp);

	return 0;
}
