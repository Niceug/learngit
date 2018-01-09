#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define ROUTNUM 10 //7个路由器
typedef struct {
	int dis;
	int from;
}RoutNode;
//初始化路由表
void initDis(RoutNode routNode[ROUTNUM][ROUTNUM])
{
	int rout_a, rout_b;
	//初始化路由表为-1和0， -1表示不可达，0表示到当前路由
	for (int i = 0; i<ROUTNUM; ++i)
	{
		for (int j = 0; j<ROUTNUM; ++j)
		{
			if (i == j)
			{
				routNode[i][j].dis = 0;
				routNode[i][j].from = 0;
			}
			else
			{
				routNode[i][j].dis = -1;
				routNode[i][j].from = -1;
			}

		}
	}

	//路由距离随机赋值
	for (int i = 0; i<ROUTNUM; ++i)
	{
		while (1)
		{
			rout_a = rand() % ROUTNUM;
			rout_b = rand() % ROUTNUM;
			int rout_dis = rand() % 9;
			rout_dis++;
			if (rout_a != rout_b)
			{
				routNode[rout_a][rout_b].dis = rout_dis;
				routNode[rout_b][rout_a].dis = rout_dis;
				routNode[rout_a][rout_b].from = rout_a;
				routNode[rout_b][rout_a].from = rout_b;
				break;
			}
		}
	}

}

//输出路由表
void outputRouter(RoutNode routNode[ROUTNUM][ROUTNUM])
{
	printf("输出路由表:\n");
	printf("   ");
	for (int i = 0; i<ROUTNUM; ++i)
	{
		printf("%c   ", 65 + i);
	}
	printf("\n");
	for (int i = 0; i<ROUTNUM; ++i)
	{
		printf("%c:", 65 + i);
		for (int j = 0; j<ROUTNUM; ++j)
		{
			if (routNode[i][j].dis < 0)
				printf("%d, ", routNode[i][j].dis);
			else if(routNode[i][j].dis >= 10)
				printf("%d, ", routNode[i][j].dis);
			else
			{
				printf(" %d, ", routNode[i][j].dis);

			}
		}
		printf("\n");
	}
	printf("\n");
}

//把j的路由表赋值给i
void exchangeAB(RoutNode routNode[ROUTNUM][ROUTNUM], int dis, int src)
{
	if (routNode[dis][src].from>0)//表示src到dis有直接相连,可以赋值
	{
		for (int i = 0; i<ROUTNUM; ++i)
		{
			if (routNode[src][i].dis>0 && routNode[dis][i].dis<0)//
			{
				routNode[dis][i].dis = routNode[dis][src].dis + routNode[src][i].dis;
				routNode[dis][i].from = src;
			}
			else if (routNode[src][i].dis>0 && routNode[dis][i].dis>0)
			{
				if (routNode[dis][i].dis > routNode[dis][src].dis + routNode[src][i].dis)
				{
					routNode[dis][i].dis = routNode[dis][src].dis + routNode[src][i].dis;
					routNode[dis][i].from = src;
				}
			}
		}

	}
}

//路由表交换
void exchangeRouter(RoutNode routNode[ROUTNUM][ROUTNUM])
{
	for (int i = 0; i<ROUTNUM; ++i)
	{
		for (int j = 0; j<ROUTNUM; ++j)
		{
			if (routNode[i][j].dis>0)//表示路由i和j有直连，就交换路由表
			{
				exchangeAB(routNode, i, j);//把j的路由表赋值给i
			}
		}
	}
}

//路由路径查找
void searchRouter(RoutNode routNode[ROUTNUM][ROUTNUM])
{
	printf("输入查找的路由(范围为0-%d 如0 1代表A到B):\n", ROUTNUM-1);
	int input_a;
	int input_b;
	while (1)
	{
		scanf("%d%d", &input_a, &input_b);
		if (input_a >= 0 && input_a < ROUTNUM)
		{
			if (input_b >= 0 && input_b < ROUTNUM)
			{
				break;
			}
		}
		printf("必须输入0到%d之间的数\n", ROUTNUM - 1);
	}

	if (routNode[input_a][input_b].dis>0)
	{
		printf("%c-->%c-->%c\n", input_a + 65, routNode[input_a][input_b].from + 65, input_b + 65);
		printf("%c到%c的距离为%d\n", input_a + 65, input_b + 65, routNode[input_a][input_b].dis);
		return;
	}
	else if (routNode[input_a][input_b].dis == 0)
	{
		printf("\n输入了同一路由名字距离为0!\n");
		return;
	}
	else if(routNode[input_a][input_b].dis == -1)
	{
		for (int i = 0; i < ROUTNUM; i++)
		{
			for (int j = 0; j < ROUTNUM; j++)
			{
				if (routNode[input_a][i].from == 1)
				{
					if (routNode[i][input_b].dis != -1)
					{
						int distination = routNode[input_a][i].dis + routNode[i][input_b].dis;
						printf("-1的时候的路由%d\n", distination);
						return;
					}
				}
			}
		}
	}
	printf("路由不可达!\n");
	return;
}


int main()
{
	srand((unsigned int)time(NULL));
	RoutNode routNode[ROUTNUM][ROUTNUM];
	initDis(routNode);//初始化路由表
	outputRouter(routNode);//输出路由表
	exchangeRouter(routNode);//路由交换
	printf("路由交换之后:\n");
	outputRouter(routNode);//输出路由表
	searchRouter(routNode);//查找路由
	return 0;
}