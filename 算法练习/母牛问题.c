/*
#include<stdio.h>
int main()
{
	int M = 5;
	int N = 6;
	int i = 0;
	int sum = 0;
	for(i = 1; i <= 6; ++i)
	{
		sum += M/i;
	}
	printf("%d\n", sum);
}
*/



//Сţ4�곤��ĸţ��ĸţÿ�������1ֻСţ����������ĸţһֱ����
//��n���ж���ֻСţ(0< n <55)
#include<stdio.h>
int main()
{
	int year_n = 0;
	int arrxiaoNiu[55] = {0};//���Сţ
	int arrmuNiu[55] = {0};//���ĸţ
	int arrniuSum[55] = {0};//���ţ������
	int i = 0;
	printf("����������->");
	scanf("%d", &year_n);
	printf("n�� ĸţ Сţ ţ��\n");
	//ǰ����
	for(i = 0; i<3; ++i)
	{
		if(i == 0)
		{
			arrxiaoNiu[i] = 0;
			arrmuNiu[i] = 1;
			arrniuSum[i] = 1;		
		}
		else if(i == 1)
		{
			arrxiaoNiu[i] = 1;
			arrmuNiu[i] = 1;
			arrniuSum[i] = 2;
		}
		else if(i == 2)
		{
			arrxiaoNiu[i] = 2;
			arrmuNiu[i] = 1;
			arrniuSum[i] = 3;
		}
		printf("%d�� %dͷ %dͷ %dͷ\n", i, arrmuNiu[i], arrxiaoNiu[i], arrniuSum[i]);
	}
	//���������
	while(1)
	{
		
		if(i>year_n)
		{
			break;
		}
		arrxiaoNiu[i] = arrxiaoNiu[i-1]+arrmuNiu[i-1];
		arrmuNiu[i] = arrniuSum[i-3];
		arrniuSum[i] = arrxiaoNiu[i] + arrmuNiu[i];
		printf("%d�� %dͷ %dͷ %dͷ\n", i, arrmuNiu[i], arrxiaoNiu[i], arrniuSum[i]);
		++i;
	}
	return 0;
}

/*
#include<stdio.h>
int main()
{
	
}*/