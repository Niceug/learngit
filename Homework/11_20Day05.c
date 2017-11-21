

/*
//1.完成猜数字游戏。 
#include <stdio.h>
#include <stdlib.h>
#include <time.h> //用到了time函数 

int main()
{
	int trueNum;
	int myNum;
	int selection = 1;
	srand((unsigned)time(NULL));
	while(1)
	{
		printf("***********猜数字游戏************\n");
		printf("*********************************\n");
		printf("*****	1.Play   0.退出     *****\n");
		printf("*********************************\n");
		trueNum = rand()%101;
		scanf("%d", &selection);
		if(selection == 1)
		{
			while( trueNum != myNum)
			{
				printf("请输入0到100之间的数：\n");
				scanf("%d", &myNum);
				if(myNum<trueNum)
				{
					printf("小了！\n");
				}
				else if(myNum>trueNum)
				{
					printf("大了！\n");
				}
				else
				{
					printf("正确\n");
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
//2.写代码可以在整型有序数组中查找想要的数字，找到了返回下标，找不到返回-1.（折半查找） 
#include<stdio.h>
int main()
{
	int arr[] = {1, 8, 2, 98, 45, 78, 65, 12, 65, 69};
	int left = 0;
	int right = sizeof(arr)/sizeof(arr[0])-1;
	int myNum = 0;
	int mid = 0;
	printf("请输入查找的数字:\n");
	scanf("%d", &myNum);
	while(left <= right)
	{
		mid = left + (right - left)/2;
		if(myNum == arr[mid])
		{
			printf("找到了在数组的第%d个位置\n", mid);
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
	printf("没找到\n");
	return 0;
}

*/

/*

//3.编写代码模拟三次密码输入的场景。 
//最多能输入三次密码，密码正确，提示“登录成功”,
//密码错误，可以重新输入，
//最多输入三次。三次均错，则提示退出程序。 
//输入密码
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
		printf("请输入6位密码：");
		scanf("%s", mypassword);
		if(strcmp(mypassword, password) == 0)
		{
			printf("密码正确");
			break;
		}
		if(i > 2)
		{
			printf("输错了三次,");
			return 0;
		}
	}
	printf("进入");
	return 0;
}
*/

//4.编写一个程序，可以一直接收键盘字符，
//如果是小写字符就输出对应的大写字符，如果接收的是大写字符，
//就输出对应的小写字符，如果是数字不输出。
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