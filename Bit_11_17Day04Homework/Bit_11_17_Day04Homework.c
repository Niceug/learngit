/*
//Day04 1.����Ļ���������ͼ����
#include<stdio.h>
int main()
{
	int i = 0;
	int j = 0;
	int n = 0;
	int m = 0;//����
	printf("����������:");
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
//Day04 2.���0��999֮������С�ˮ�ɻ������������ 
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
//Day04 ��Sn=a+aa+aaa+aaaa+aaaaa��ǰ5��֮�ͣ�����a��һ�����֣����磺2+22+222+2222+22222 
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


//Day04 4.��дһ���������ӱ�׼�����ȡCԴ���룬����֤���еĻ����Ŷ���ȷ�ĳɶԳ��֡�
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
				printf("j++��%d\n", j);
			}
			if(source[i] == '}')
			{
				j--;
				printf("j--��%d\n", j);
			}
	}
	printf("%d", j);
			if(j == 0)
				printf("��������ƥ���\n");
			else
				printf("�����Ų�ƥ��\n");
	return 0;
}