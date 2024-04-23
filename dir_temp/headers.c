#include<stdarg.h>
#include<stddef.h>
#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>

#define log "errlog"
#define klog "/usr/local/www/apache24/log/errlog"
FILE* logp;
char *err;

void logg(char *err)
{
	fwrite(err,sizeof(char),strlen(err),logp);
}

