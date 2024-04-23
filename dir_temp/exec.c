#include<unistd.h>
#include<stdio.h>

int main(void)
{
	char *args[2];

	args[0]="loginback.cgi";
	args[1]=NULL;

	if(fork()==0)
	{
		if( execv((const char*)args[0],(char* const*)args) < 0)
		{
			printf("Failed to run script\n");
			return 1;
		}
	}
	return 0;
}
