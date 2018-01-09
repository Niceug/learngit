#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>
#define ROUTNUM 10 //7��·����
typedef struct {
	int dis;
	int from;
}RoutNode;
//��ʼ��·�ɱ�
void initDis(RoutNode routNode[ROUTNUM][ROUTNUM])
{
	int rout_a, rout_b;
	//��ʼ��·�ɱ�Ϊ-1��0�� -1��ʾ���ɴ0��ʾ����ǰ·��
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

	//·�ɾ��������ֵ
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

//���·�ɱ�
void outputRouter(RoutNode routNode[ROUTNUM][ROUTNUM])
{
	printf("���·�ɱ�:\n");
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

//��j��·�ɱ�ֵ��i
void exchangeAB(RoutNode routNode[ROUTNUM][ROUTNUM], int dis, int src)
{
	if (routNode[dis][src].from>0)//��ʾsrc��dis��ֱ������,���Ը�ֵ
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

//·�ɱ���
void exchangeRouter(RoutNode routNode[ROUTNUM][ROUTNUM])
{
	for (int i = 0; i<ROUTNUM; ++i)
	{
		for (int j = 0; j<ROUTNUM; ++j)
		{
			if (routNode[i][j].dis>0)//��ʾ·��i��j��ֱ�����ͽ���·�ɱ�
			{
				exchangeAB(routNode, i, j);//��j��·�ɱ�ֵ��i
			}
		}
	}
}

//·��·������
void searchRouter(RoutNode routNode[ROUTNUM][ROUTNUM])
{
	printf("������ҵ�·��(��ΧΪ0-%d ��0 1����A��B):\n", ROUTNUM-1);
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
		printf("��������0��%d֮�����\n", ROUTNUM - 1);
	}

	if (routNode[input_a][input_b].dis>0)
	{
		printf("%c-->%c-->%c\n", input_a + 65, routNode[input_a][input_b].from + 65, input_b + 65);
		printf("%c��%c�ľ���Ϊ%d\n", input_a + 65, input_b + 65, routNode[input_a][input_b].dis);
		return;
	}
	else if (routNode[input_a][input_b].dis == 0)
	{
		printf("\n������ͬһ·�����־���Ϊ0!\n");
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
						printf("-1��ʱ���·��%d\n", distination);
						return;
					}
				}
			}
		}
	}
	printf("·�ɲ��ɴ�!\n");
	return;
}


int main()
{
	srand((unsigned int)time(NULL));
	RoutNode routNode[ROUTNUM][ROUTNUM];
	initDis(routNode);//��ʼ��·�ɱ�
	outputRouter(routNode);//���·�ɱ�
	exchangeRouter(routNode);//·�ɽ���
	printf("·�ɽ���֮��:\n");
	outputRouter(routNode);//���·�ɱ�
	searchRouter(routNode);//����·��
	return 0;
}