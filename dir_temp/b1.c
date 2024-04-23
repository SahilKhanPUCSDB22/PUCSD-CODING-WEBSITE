#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<libpq-fe.h>

#define listenport 1234

int main(){
	
	int r=0;
	char *params[8];
	char *msg;
	int sockfd=socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in rec_addr;

	memset(&rec_addr,0,sizeof(rec_addr));

	rec_addr.sin_family = AF_INET;
	rec_addr.sin_port = htons(listenport);
	rec_addr.sin_addr.s_addr=INADDR_ANY;

	if(connect(sockfd,(const struct sockaddr *)&rec_addr,sizeof(rec_addr))<0)
	{
		printf("Connection Failed \n");
		return 1;
	}
	char *conninfo ="dbname=pucsd_hackerrank password=1234 user=postgres";

	PGconn *conn=PQconnectdb(conninfo);

	if(PQstatus(conn)!=CONNECTION_OK)
	{
		 msg="0";
		printf("Connection Failed\n");
		send(sockfd,(const char *)msg,strlen(msg),0);
	}
	else{
		printf("IN\n");
		int i=1;
		while(r==0)
		{
			r=recv(sockfd,msg,100,0);
			if(r!=0)
			{
				msg[r]='\0';
				strcpy(params[0],msg);
				while(i<7){
					r=recv(sockfd,msg,100,0);
					msg[r]='\0';
					strcpy(params[i],msg);
					printf("%s\n",params[i]);
					i++;
				}
				char *sql="insert into students values($1::bigint,$2,$3,$4,$5,$6,$7);";
				
				PGresult *res=PQexecParams(conn,(const char*)sql,7,NULL,(const char* const*)params,NULL,NULL,0);
				
				if(PQresultStatus(res) != PGRES_COMMAND_OK ){
					msg="1";
					printf("Already Inserted\n");
					send(sockfd,(const char *)msg,strlen(msg),0);
				}
				else{	
					printf("Inserted\n");
					msg="2";
					send(sockfd,(const char *)msg,strlen(msg),0);
				}
			}
		}

	}
	PQfinish(conn);
	return 1;
}
