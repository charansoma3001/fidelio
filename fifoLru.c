#include <stdio.h>
#include<stdlib.h>

void FIFO(char s[], char F[], int l, int f)
{
	int i, k, j=0, flag=0, cnt=0;
	printf("page \t frames \t\t faults \n");
	for(i=0; i<l; i++)
	{
		for(k=0; k<f; k++)
		{
			if(F[k]==s[i])
			{
				flag=1;
				break;
			}
		}
		printf("%c\t ", s[i]);
		if(flag==0)
		{
			F[j]=s[i];
			j++;
			for(k=0; k<f; k++)
				printf("   %c", F[k]);
			printf("\t\tPage fault %d\n ", cnt);
			cnt++;
		}
		else
		{
			for(k=0; k<f; k++)
				printf("   %c", F[k]);
			printf("\t\tno fault\n");
			flag=0;
		}
		if(j==f)
			j=0;
	}
}


void LRU(char s[], char F[], int l, int f)
{
	int i, j=0, k, m, flag=0, cnt=0, top=0;
	printf("page \t frames \t\t faults \n");
	for(i=0; i<l; i++)
	{	
		for(k=0; k<f; k++)
		{
			if(F[k]==s[i])
			{
				flag=1;
				break;
			}
		}
		printf("%c\t", s[i]);
		if(j!=f && flag!=1)
		{
			F[top]=s[i];
			j++;
			if(j!=f)
				top++;
		}
		else
		{
			if(flag!=1)
			{
				for(k=0; k<top; k++)
					F[k]=F[k+1];
				F[top]=s[i];
			}
			
			if(flag==1)
			{
				for(m=k; m<top; m++)
					F[m]=F[m+1];
				F[top]=s[i];
			}
		}
		for(k=0; k<f; k++)
			printf("    %c", F[k]);
		if(flag==0)
		{
			printf("\t\tpage-fault %d\n", cnt);
			cnt++;
		}
		else
			printf("\t\tno fault\n");
		flag=0;
	}
}

int main()
{
	int i, ch, yn, l, f, k, j;
	char s[25], F[10];
	printf("Enter the number of empty frames : ");
	scanf("%d", &f);
	printf("Enter the length of the string : ");
	scanf("%d", &l);
	printf("Enter the string : ");
	scanf("%s", s);
	for(k=0; k<f; k++)
		F[k]=-1;
	do
	{
		printf("\n---MENU---\n1.FIFO \n2.LRU \n3.exit ");
		printf("Enter your choice : ");
		scanf("%d", &ch);
		switch(ch)
		{
			case 1: for(k=0; k<f; k++)
					F[k]=-1;
				FIFO(s, F, l, f);
				break;
						
			case 2: for(k=0; k<f; k++)
					F[k]=-1;
				LRU(s, F, l, f);
				break;
			case 3: exit(0);
		}

		printf("Enter 1 to continue or 0 to exit : ");
		scanf("%d", &yn);
	} while(yn==1);
	return 0;
}
		

