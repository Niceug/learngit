

/*
//1.��ɲ�������Ϸ�� 
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //�õ���time���� 

int main()
{
	int trueNum;
	int myNum;
	int selection = 1;
	srand((unsigned)time(NULL));
	while(1)
	{
		printf("***********��������Ϸ************\n");
		printf("*********************************\n");
		printf("*****	1.Play   0.�˳�     *****\n");
		printf("*********************************\n");
		trueNum = rand()%101;
		scanf("%d", &selection);
		if(selection == 1)
		{
			while( trueNum != myNum)
			{
				printf("������0��100֮�������\n");
				scanf("%d", &myNum);
				if(myNum<trueNum)
				{
					printf("С�ˣ�\n");
				}
				else if(myNum>trueNum)
				{
					printf("���ˣ�\n");
				}
				else
				{
					printf("��ȷ\n");
				}
			}
		}
		else
			break;
	}
	return 0;
}
//
*/


/*
//2.д����������������������в�����Ҫ�����֣��ҵ��˷����±꣬�Ҳ�������-1.���۰���ң� 
#include<stdio.h>
int main()
{
	int arr[] = {1, 8, 2, 98, 45, 78, 65, 12, 65, 69};
	int left = 0;
	int right = sizeof(arr)/sizeof(arr[0])-1;
	int myNum = 0;
	int mid = 0;
	printf("��������ҵ�����:\n");
	scanf("%d", &myNum);
	while(left <= right)
	{
		mid = left + (right - left)/2;
		if(myNum == arr[mid])
		{
			printf("�ҵ���������ĵ�%d��λ��\n", mid);
			break;
		}
		if(myNum<arr[mid])
		{
			right = mid - 1;
		}
		else if(myNum>arr[mid])
		{
			left = mid + 1;
		}
	}
	printf("û�ҵ�\n");
	return 0;
}

*/

/*

//3.��д����ģ��������������ĳ����� 
//����������������룬������ȷ����ʾ����¼�ɹ���,
//������󣬿����������룬
//����������Ρ����ξ�������ʾ�˳����� 
//��������
#include<stdio.h>
#include<string.h>
int main()
{
	int i = 0;
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
		if(i > 2)
		{
			printf("���������,");
			return 0;
		}
	}
	printf("����");
	return 0;
}
*/

//4.��дһ�����򣬿���һֱ���ռ����ַ���
//�����Сд�ַ��������Ӧ�Ĵ�д�ַ���������յ��Ǵ�д�ַ���
//�������Ӧ��Сд�ַ�����������ֲ������
#include<stdio.h>

int main()
{
	int ch;
	while((ch = getchar()) != EOF)
	{
		if(ch<'0' ||ch>'9')
		{
			if(ch>=97)
			{
				putchar(ch-32);
			}
			else if(ch<97)
			{
				putchar(ch+32);
			}	
		}
	}
	return 0;
}