#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <libpmemobj.h>

typedef struct My_Root{
	int saldo;
}test;

POBJ_LAYOUT_BEGIN(JaPHa);
POBJ_LAYOUT_ROOT(JaPHa,test);
POBJ_LAYOUT_END(JaPHa);

void Display(PMEMobjpool *pop)
{
	int total;
	TOID(test) root = POBJ_ROOT(pop,test);
	printf("%d\n",D_RO(root)->saldo);
	total = D_RO(root)->saldo;
	TX_BEGIN(pop){
		while(1)
		{
			total++;
			TX_MEMCPY(&(D_RW(root)->saldo),&total,sizeof(total));
		}
	}TX_END
}

int main(int argc,char *argv[])
{
	if(argc != 2)
	{
		printf("\nusage: %s new file-name\n\n",argv[0]);
		return 1;
	}
	PMEMobjpool *pop = pmemobj_create(argv[1],POBJ_LAYOUT_NAME(JaPHa),PMEMOBJ_MIN_POOL,0666);
	if(pop == NULL)
	{
		PMEMobjpool *pop = pmemobj_open(argv[1],POBJ_LAYOUT_NAME(JaPHa));
		if(pop == NULL)
		{
			perror("pmemobj_open");
			return 1;
		}
		printf("opened\n");
		Display(pop);
		pmemobj_close(pop);
		return 0;
	}
	else
	{
		TOID(test) root = POBJ_ROOT(pop,test);
		D_RW(root)->saldo = 100;
		printf("created\n");
		Display(pop);
		pmemobj_close(pop);
		return 0;
	}
}
