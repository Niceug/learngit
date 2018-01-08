#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int showMenu()
{
	int option;
	printf("*******************************\n");
	printf("****1.开始游戏   0.退出游戏****\n");
	printf("*******************************\n");
	printf("请输入您的选择>");
	scanf("%d", &option);
	return option;
}