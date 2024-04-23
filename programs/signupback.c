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

#define listenport 1237
#define INPUT_MAX 8

int main(){
	char *msg;
	char params[INPUT_MAX][100];
	int i=0,r;
	int rows,cols;

	//Socket connection

	int sockfd , cfd , b ;
	struct sockaddr_in sr_addr,clnt_addr;
	socklen_t clen=sizeof(clnt_addr);

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd<0)
	{
		printf("Socket failed\n");
		return 1;
	}

	memset(&sr_addr,'\0',sizeof(sr_addr));

	sr_addr.sin_family =AF_INET;
	sr_addr.sin_port=htons(listenport);
	sr_addr.sin_addr.s_addr = INADDR_ANY;

	b=bind(sockfd,(struct sockaddr*)&sr_addr,sizeof(sr_addr));
	if(b<0)
	{
		printf("Binding failed\n");
		return 1;
	}

	char *conninfo ="dbname=pucsd_hackerrank password=1234 user=postgres";

	PGconn *conn=PQconnectdb(conninfo);

	if ( PQstatus(conn) != CONNECTION_OK)
	{
		msg="0";
		printf("DBCONN failure\n");
		return 1;
	}
	else{
		listen(sockfd,5);
		while(1){	
			cfd=accept(sockfd,(struct sockaddr*)&clnt_addr,&clen);
			if(cfd > -1){
				printf("accepted\n");
				char * param[INPUT_MAX];
				while(i<INPUT_MAX){
					r=recv(cfd,(void *)params[i],100,MSG_WAITALL);
					param[i]=params[i];
					i++;
				}

				char *sql="insert into students values($1::bigint,$2,$3,$4,$5,$6,$7,$8::bigint)";

				PGresult *res;
				res=PQexecParams(conn,(const char*)sql,INPUT_MAX,NULL,(const char* const*)param,NULL,NULL,0);

				if(PQresultStatus(res) != PGRES_COMMAND_OK ){
					msg="1";
					printf("%s\n",PQerrorMessage(conn));
				}
				else
				{	
					msg="2";
				}
				PQclear(res);
				send(cfd,msg,1,0);
				cfd=-1;
			}
		}
	}
	close(sockfd);
	PQfinish(conn);
	return 1;
}

