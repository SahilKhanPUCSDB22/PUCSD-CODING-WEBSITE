#include"headers.c"
#include<libpq-fe.h>
#include<ctype.h>

#define portown 1237
#define CAPACITY 1024
#define INPUT_MAX 5
#define USR_DETS 3
#define UTYPE_LEN 4

PGconn* con;
PGresult* res;

enum erno{INPUT_OK,INPUT_NA,SAN_OK,SAN_NA,FILE_OK,FILE_NA};

int seggregate(char *stream,char **input)
{
	int i=0,j=0,k;

	int size[]={SESSION_LEN,UTYPE_LEN,FNAME_LEN,FTYPE_LEN,FSIZE_LEN};

	while(i<INPUT_MAX)
	{
		input[i]=(char*)malloc(sizeof(char)*(size[i]+1));
		i++;
	}

	i=0;

	while(i<INPUT_MAX)
	{
		k=0;
		while(stream[j]!=10)
		{
			input[i][k]=stream[j];
			k++;
			j++;
		}
		input[i][k]=0;
		i++;
		j++;
	}
	
//	printf("%s\n%s\n%s\n%s\n%s\n",input[0],input[1],input[2],input[3],input[4]);

	return 1;
}

enum erno getinput(int sockfd,char **input)
{
	int len,size;
	char INP_STREAM[size=(SESSION_LEN+UTYPE_LEN+FNAME_LEN+FTYPE_LEN+FSIZE_LEN+INPUT_MAX+1)];

	if( (len=recv(sockfd,INP_STREAM,size,0))<0)
	{
		err="Failed to recieve inputs from kcgi fun:getinput()\n";
		logg(err);
		return INPUT_NA;
	}

	INP_STREAM[len]=0;
	
	if(seggregate(INP_STREAM,input)<0)
	{
		return INPUT_NA;
	}

	return INPUT_OK;
}

int new(char** input,char **udetails)
{
	char *usertype = udetails[1];
	char *command,*command2;

	if(usertype[0]=='s')
	{
		command="delete from sfiles where owner=$1::bigint and fname=$2";
		command2="insert into sfiles values($1,$2,$3::bigint,0,$4::bigint)";
	}
	else
	{
		command="delete from ifiles where owner=$1::bigint and fname=$2";
		command2="insert into ifiles values($1,$2,$3::bigint,0,$4::bigint)";
	}
	char *params[4];

	params[0]=udetails[0];
	params[1]=input[2];

	res=PQexecParams(con,(const char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_COMMAND_OK)
	{
		err="Query execution failed fun:db_lookup()\n";
		logg(err);
		logg(PQerrorMessage(con));
		return -1;
	}	


	params[0]=input[2];  //fname
	params[1]=input[3]; //ftype
	params[2]=input[4]; //fsize
	params[3]=udetails[0]; //userid


	res=PQexecParams(con,(const char*)command2,4,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_COMMAND_OK)
	{
		err="Query execution failed fun:db_lookup()\n";
		logg(err);
		logg(PQerrorMessage(con));
		return -1;
	}

	udetails[2]="0";

	return 0;
}

int old(char** input,char** udetails)
{
	int rows;
	char* params[3],*command;

	char* usertype=udetails[1];

	if(usertype[0]=='s')
	{
		command="select * from sfiles where owner=$1::bigint and fname=$2";
	}
	else
	{
		command="select * from ifiles where owner=$1::bigint and fname=$2";
	}

	params[0]=(char*)udetails[0];
	params[1]=(char*)input[2];

	res=PQexecParams(con,(const char*)command,2,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_TUPLES_OK)
	{
		err="Query execution failed fun:db_lookup()\n";
		logg(err);
		logg(PQerrorMessage(con));
		return -1;
	}

	if((rows=PQntuples(res))>0)
	{
		udetails[2]=PQgetvalue(res,0,3);
		return 1;
	}
	else
	{
		return -1;
	}

}

enum erno sanitize(char** input,char** udetails)
{
	//sanitize db and retrieve partnois

	char * command;
	char *params[1];

	char *utype = input[1];

	command="select userid,usertype from sessions where session_id=$1";

	params[0]=input[0];

	res=PQexecParams(con,(char*)command,1,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_TUPLES_OK)
	{
		logg(PQerrorMessage(con));
		return SAN_NA;
	}

	int rows=PQntuples(res),cols=PQnfields(res);

	if(cols>0 && rows >0)
	{
		udetails[0]=(char*)PQgetvalue(res,0,0);
		udetails[1]=PQgetvalue(res,0,1);
	}
	else
	{
		err="Userid , Type fetch failure\n";
		logg(err);
		return SAN_NA;
	}

	if( utype[0]=='o' )
	{
		if( old(input,udetails)<0)
		{
			return SAN_NA;
		}
	}
	else
	{
		if( new(input,udetails)<0)
		{
			return SAN_NA;
		}
	}
	//retrieve parts
	return SAN_OK;
}

enum erno getfile(int sockfd ,char **input , char **userdetails)
{
	char *params[3],*command,*command2; //params command
	char *usertype=userdetails[1]; //tyype of user
	
	char filename[CAPACITY*2];
	filename[0]=0;
	
	strcat(strcat(strcat(strcat(filename,userfiles),userdetails[0]),userdetails[1]),input[2]);
		
	char parts[CAPACITY]; //no of parts for query
	
	int n= myatoi(userdetails[2]);  //no of parts for loop
	int fsize = myatoi( (char*)input[4]);  //sizeof file
	int max = MAX_SEG(fsize);  //max no of segments
	int r,flag=0,x; 

	FILE* fp;
	char *utype = input[1];


	if( (x=send(sockfd,userdetails[2],strlen(userdetails[2]),0)) < 0 )
	{
		logg("Failed to send parts\n");
		return FILE_NA;
	}
	
	printf("Send %s %d %s\n",userdetails[2],x,filename);

	if(utype[0]=='o')
	{
		printf("opened in append\n");
		fp=fopen(filename,"a+");
		if(fp==NULL)
		{
			logg("Error Failure opening temp file\n");
			return FILE_NA;
		}
	}
	else
	{
		printf("opened in new\n");
		fp=fopen(filename,"w+");
		if(fp==NULL)
		{
			logg("Error Failure opening temp file\n");
			return FILE_NA;
		}
	}

//	fseek(fp,(n*SEG_SIZE),SEEK_SET);

	int buflen=0;
	int left= fsize - (n*SEG_SIZE);

	char buffer[SEG_SIZE*2];

	while(n<max && (flag==0))
	{
		if(left<SEG_SIZE)
		{
			buflen=left;
		}
		else
		{
			buflen=SEG_SIZE;
		}

		if( (r=recv(sockfd,(void*)buffer,buflen,0)) < 0 )
		{
			logg("File rec failed");
			flag=1;
		}

		if(r==buflen)
		{
			r=fwrite((void*)buffer,sizeof(char),r,fp);
			left-=buflen;
			n++;
		}
		else
		{
			flag=1;
		}
	}
	
//	printf("prec%d left%d totp%d\n",n,left,max);

	myitoa(n,parts);

	params[0]=parts;
	params[1]=userdetails[0];
	params[2]=input[2];
		
	if(usertype[0]=='s')
	{	
		command="update sfiles set parts = $1::bigint where owner = $2::bigint and fname= $3";
		command2="update sfiles set filedata = $1 where owner = $2::bigint and fname=$3"; 	
	}	
	else	
	{
		command="update ifiles set parts = $1::bigint where owner=$2::bigint and fname=$3";
		command2="update ifiles set filedata = $1 where owner = $2::bigint and fname=$3"; 	
	}
	
	res=PQexecParams(con,(const char*)command,3,NULL,(const char* const*)params,NULL,NULL,0);

	if(PQresultStatus(res)!=PGRES_COMMAND_OK)
	{
		err="Query execution failed fun:parts Inclusion\n";
		logg(err);
		logg(PQerrorMessage(con));
		fclose(fp);
		return FILE_NA;
	}
	else
	{
		printf("Parts updated\n");
	}
	
	if(n==max)
	{
		fseek(fp,0,SEEK_SET);
		char tmpbuf[fsize+1];
		int red = fread((void*)tmpbuf,sizeof(char),fsize,fp);
		printf("Read num %d\n",red);
		tmpbuf[red]=0;
		params[0]=(char*)tmpbuf;
		fclose(fp);

		res=PQexecParams(con,(const char*)command2,3,NULL,(const char* const*)params,NULL,NULL,0);
		if(PQresultStatus(res)!=PGRES_COMMAND_OK)
		{
			err="Query execution failed fun:data insertion\n";
			logg(err);
			logg(PQerrorMessage(con));
			return FILE_NA;
		}
		else
		{
			printf("Filedata Inserted\n");
		}

	}
	else
	{
		fclose(fp);
		return FILE_NA;
	}
	return FILE_OK;
}

int main()
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
	char *udetails[USR_DETS];

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

			if((flow==0) && (er=getinput(cfd,input)!=INPUT_OK))
			{
				flow=1;
			}

			if((flow==0) && (sanitize(input,udetails))!=SAN_OK)
			{
				flow=1;
			}

			printf("%s %s %s\n",udetails[0],udetails[1],udetails[2]);

			if((flow==0) && (er=getfile(cfd,input,udetails))!=FILE_OK)
			{
				flow=1;
			}
			close(cfd);
		}
	}

	PQfinish(con);
	fclose(logp);
	return 0;
}
