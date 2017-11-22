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



//小牛4年长成母牛，母牛每年年初生1只小牛，假设所有母牛一直不死
//第n年有多少只小牛(0< n <55)
#include<stdio.h>
int main()
{
	int year_n = 0;
	int arrxiaoNiu[55] = {0};//存放小牛
	int arrmuNiu[55] = {0};//存放母牛
	int arrniuSum[55] = {0};//存放牛的总数
	int i = 0;
	printf("请输入年数->");
	scanf("%d", &year_n);
	printf("n年 母牛 小牛 牛总\n");
	//前三年
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
		printf("%d年 %d头 %d头 %d头\n", i, arrmuNiu[i], arrxiaoNiu[i], arrniuSum[i]);
	}
	//后面的年数
	while(1)
	{
		
		if(i>year_n)
		{
			break;
		}
		arrxiaoNiu[i] = arrxiaoNiu[i-1]+arrmuNiu[i-1];
		arrmuNiu[i] = arrniuSum[i-3];
		arrniuSum[i] = arrxiaoNiu[i] + arrmuNiu[i];
		printf("%d年 %d头 %d头 %d头\n", i, arrmuNiu[i], arrxiaoNiu[i], arrniuSum[i]);
		++i;
	}
	return 0;
}

/*
#include<stdio.h>
int main()
{
	
}*/