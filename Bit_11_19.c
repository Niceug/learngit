/*#include<stdio.h>
#include<math.h>
int main()
{
	
	int i = 0;
	int j = 0;
	int temp = 0;
	int count = 1;
	double sum = 0.0;
	for(i = 0; i<10000000; i++)
	{
		int sum = 0;
		temp = i;	
		while(temp>9)
		{
			count++;
			temp = temp/10;
		}
		temp = i;
		while(count)
		{
			temp = temp%(int)pow(10.0, count);
			sum += (pow(temp, 3));
			count--;
		}
		if(sum == i)
			printf("%lf", i);
	}
	
	return 0;
}
*/

/*
#include<stdio.h>
#include<math.h>
int main()
{
	//file * f = fopen("C:\Users\hasee\Desktop\�½��ļ���\test.c");
	int count = 0;
	int ch = fgate(f);
	while((ch = getchar()) != EOF)
	{
		if(ch == '{')
			count++;
		else if(ch == '}')
			count--;
		if(count<0)
		{
			printf("��ƥ��");
			return 0;
		}
	}

	if(count == 0)
		printf("ƥ��\n");
	else
		printf("��ƥ��\n");
	return 0;
}
*/

/*
//��������
#include<stdio.h>
#include<string.h>
int main()
{
	int i = 0;
	int arrTest[] = {1, 2, 4, 5};
	char password[] = "123456";
	char mypassword[(sizeof(password)-1)] = {'0'};
	printf("%d",strlen(password));
	for(i = 0; i<3; i++)
	{
		printf("������6λ���룺");
		scanf("%s", mypassword);
		if(strcmp(mypassword, password) == 0)
		{
			printf("������ȷ");
			break;
		}
		if(i == 2)
		{
			printf("���������");
			return 0;
		}
	}
	printf("����");
	return 0;
}
*/
#include<stdio.h>
int main()
{
	
	return 0;
}