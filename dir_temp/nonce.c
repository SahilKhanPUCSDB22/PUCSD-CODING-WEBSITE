#include<sodium.h>
#include<stdio.h>

int main()
{
	if(sodium_init()==-1)
	{}

	const int len = crypto_secretbox_NONCEBYTES;

	unsigned char nonce[len];
	randombytes_buf(nonce,len);
	int i=0;
	while(i<len)
	{
		printf("%c",nonce[i++]);
	}

	printf("\n");
	return 0;
}
