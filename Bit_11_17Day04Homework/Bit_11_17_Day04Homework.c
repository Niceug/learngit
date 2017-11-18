/*
//Day04 1.在屏幕上输出以下图案：
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	int n = 0;
	int m = 0;//行数
	printf("请输入行数:");
	scanf("%d", &m);
	n = m*2;
	for(i = 1; i<n; i+=2)
	{
		if(i<=n/2)
		{
			for(j = 0; j<i; j++)
			{
				printf("*");
			}
			printf("\n");
		}
		else
		{
			for(j = n-i; j>0; j--)
			{
				printf("*");
			}
			printf("\n");
		}
	}
	return 0;
}
*/


/*
//Day04 2.求出0～999之间的所有“水仙花数”并输出。 
#include<stdio.h>
#include<math.h>
int main()
{	
	int i = 0;
	int baiwei = 0;
	int shiwei = 0;
	int gewei = 0;
	for(i = 0; i<1000; i++)
	{
		baiwei = i/100;
		shiwei = i%100/10;
		gewei = i%10;
		if(i == (pow(baiwei, 3) + pow(shiwei, 3) + pow(gewei, 3)))
			printf("%d\n", i);
	}
}
*/

/*
//Day04 求Sn=a+aa+aaa+aaaa+aaaaa的前5项之和，其中a是一个数字，例如：2+22+222+2222+22222 
#include<stdio.h>
#include<math.h>
int main()
{
	int a = 0;
	int i = 0;
	scanf("%d", &a);
	printf("%d\n",a*5+10*a*4+100*a*3+1000*a*2+10000*a*1);
	return 0;
}*/


//Day04 4.编写一个程序，它从标准输入读取C源代码，并验证所有的花括号都正确的成对出现。
#include<stdio.h>
#include<string.h>
int main()
{
	char a = 0;
	int i = 0; 
	int j = 0;
	char source[1024] = {0};
	gets(source);
	printf("%s",source);
	for(i = 0; i<strlen(source); i++)
	{
			if(source[i] == '{')
			{
				j++;
				printf("j++的%d\n", j);
			}
			if(source[i] == '}')
			{
				j--;
				printf("j--的%d\n", j);
			}
	}
	printf("%d", j);
			if(j == 0)
				printf("花括号是匹配的\n");
			else
				printf("花括号不匹配\n");
	return 0;
}