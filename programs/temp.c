#include"headers.c"
#include<libpq-fe.h>
#include<ctype.h>
#include<kcgi.h>

#define portown 1235
#define CAPACITY 1024
#define INPUT_MAX 4
#define MAX_SEG fsize/1024+( (fsize%1024)/fsize/1024)

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
	//	printf("%s,%s,%s,%s\n",input[0],input[1],input[2],input[3]);
	logg(input[0]);
	logg("\n");
	logg(input[1]);
	logg("\n");
	logg(input[2]);
	logg("\n");

	return INPUT_OK;
}
char *callcommand(int flg){
	char *command;
	if(flg == 0){
		command = "update ifile set no_of_seg=$3::bigint where usrid=$1 and f_name=$2";
	}
	else{
		command = "update sfile set no_of_seg=$3::bigint where usrid=$1 and f_name=$2";	
	}
	return command;
}


static enum erno db_lookup(char **input)
{
	char j=0;
	int rows;
	int usr_id;
	char *type;
	char *command;

	FILE *fp;
	fp=fopen(input[1],"w+");

	const char *params[4];

	// Searching user_id and user_type in session Id table

	command="select * from session where session_id=$1";

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
		usr_id = PQgetvalues(res,0,1);
		type = PQgetvalues(res,0,2);	

		int flg;

		// Searching weather file is present in database

		if(type[0]=='s')
		{
			command="select * from sfile where user_id=$1 and f_name=$2";
			flg=1;
		}
		else{
			command="select * from ifile where user_id=$1 and f_name=$2";
			flg=0;
		}

		params[0]= usr_id ;
		params[1]= input[1];


		res=PQexecParams(con,(const char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);

		if(PQresultStatus(res)!=PGRES_COMMAND_OK)
		{
			err="Query execution failed fun:db_lookup()\n";
			logg(err);
			printf("%s\n",PQerrorMessage(con));
			return INSERT_NA;
		}	

		// If filedetails are Present

		if( (rows=PQntuples(res))>0)
		{
			int nos = PQgetvalues(res,0,4);
			int size = PQgetvalues(res,0,2);
			int fsize =  myatoi(input[2]); 

			if(size == fsize && nos == MAX_SEG ){
				buf="0";
				send(cfd,buf,100,MSG_WAITALL);
				return PRESENT;
			}	
			else if( size == fsize && nos < MAX_SEG  ){
				buf="2";
				send(cfd,buf,100,MSG_WAITALL);
				recv(cfd,buf,100,MSG_WAITALL);
				if(buf[0] == '0'){
				//restart
					if(flg == 0){
						command="insert into ifiles values ($1,$2,$3,$4::bigint,0)";
					}
					else{
						command="insert into sfiles values ($1,$2,$3,$4::bigint,0)";
					}
					params[0]= usrid;
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
					nos=0;
				}
				command = callcommand(flg);
			}
				
			else if( (size == fsize && nos > MAX_SEG) || (fsize != size) ){
				//restart uploading
				buf="2";
				send(cfd,buf,100,MSG_WAITALL);
				if(flg == 0){
						command="insert into ifiles values ($1,$2,$3,$4::bigint,0)";
					}
					else{
						command="insert into sfiles values ($1,$2,$3,$4::bigint,0)";
					}
					params[0]= usrid;
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
					command = callcommand(flg);
					n=0;
					lseek(fp,0,SEEK_END);

				}
		}
			else
				{
					if(flg == 0){
					command="insert into ifile values ($1,$2,$3,$4::bigint,0)";
					}else{
					
					command="insert into sfile values ($1,$2,$3,$4::bigint,0)";
					}
					params[0]=usrid;
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
					command = callcommand(flg);
					nos=0;

				}

			params[0] = usrid;
			params[1] = input[1];
			params[2] = nos;
			while(nos < MAX_SEG){
			
			res=PQexecParams(con,(const char*)command,3,NULL,(const char* const*)params,NULL,NULL,0);

			if(PQresultStatus(res)!=PGRES_COMMAND_OK)
			{
				err="Query execution failed fun:db_lookup()\n";
				logg(err);
				printf("%s\n",PQerrorMessage(con));
				return INSERT_NA;
			}
			nos++;
			params[2] = nos;
			recv(cfd,buf,1024,MSG_WAITALL);
			fprintf(fp,buf,1024);
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

						er=db_lookup(input);
						if( (flow==0) && (er != INSERT_OK) )
						{
							send_error(er,cfd);
							flow=1;
						}

						if( (flow==0) && (send_page(cfd)!=PAGE_OK))
						{
							send_error(DATA_F,cfd);
							flow=1;
						}
					}
					close(cfd);
				}

				PQfinish(con);
				fclose(logp);

				return 0;
			}
