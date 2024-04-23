#include<sodium.h>
#include<stdio.h>

int main(void)
{
	int len=32;
	unsigned char nonce[128];
	int range=126-32;

	if(sodium_init()==-1)
	{
		return 1;
	}

	randombytes_buf(nonce,len);

	int i=0;
	while(i<len)
	{
		nonce[i]= 32 + (nonce[i]%range);
		printf("%x %c %d\n",nonce[i],nonce[i],nonce[i]);
		i++;
	}
	nonce[i]='\0';
	printf("\n%s",nonce);
	printf("\n");

	return 0;
}


