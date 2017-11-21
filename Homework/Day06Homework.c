/*
//1.写一个函数返回参数二进制中 1 的个数 
#include<stdio.h>
int count_one_bits(unsigned int value) 
{
	int count = 0;
	while(value != 0)
	{
		if(value&1 == 1)
		{
			++count;
		}
		value >>= 1;
	}
	return count;
}
int main()
{
	int num = 0;
	printf("请输入一个 -65536到65535 之间的数：");
	scanf("%d", &num);
	printf("%d的二进制中有%d个1\n", num, count_one_bits(num));
	return 0;
}
*/

/*
//
//2.获取一个数二进制序列中所有的偶数位和奇数位，分别输出二进制序列。 
#include<stdio.h>

void get_evenAndodd(int num)
{
	int tempeven = num>>1;//偶数位
	int tempodd = num;//奇数位
	int arreven[32] = {0};
	int arrodd[32] = {0};
	int i = 0;
	//奇数
	while(tempodd != 0)
	{
		arrodd[i] = tempodd&1;
		tempodd >>= 2;
		++i;
	}
	//偶数
	i = 0;
	while(tempeven != 0)
	{
		arreven[i] = tempeven&1;
		tempeven>>= 2;
		++i;
	}
	//输出奇数位二进制序列
	printf("32位奇数序列\n" );
	for(i = sizeof(arrodd)/sizeof(arrodd[0]); i>=0; --i)
	{
		printf("%d", arrodd[i]);
	}
	printf("\n");
	//输出偶数位二进制序列
	printf("32位偶数序列\n" );
	for(i = sizeof(arreven)/sizeof(arreven[0]); i>=0; --i)
	{
		printf("%d", arreven[i]);
	}
	printf("\n");
	
}
int main()
{
	int num = 0;
	printf("请输入一个数: \n");
	scanf("%d", &num);
	get_evenAndodd(num);
	return 0;
}
*/
//


/*
//3. 输出一个整数的每一位。 
#include<stdio.h>
#include<math.h>
int main()
{
	int num = 0;
	int temp = 0;
	int count = 1;
	int i = 0;
	printf("请输入一个数：");
	scanf("%d", &num);
	temp = num;
	//判断位数
	while(num>9)
	{
		++count;
		temp /= 10;
	}
	printf("%d是%d位数\n", num, count);
	temp = num;
	//输出每一位数字
	for(i = count; i >= 0; --i)
	{
		printf("%d ",temp/(pow(10, i)) );
	}
	return 0;
}
*/



//4.编程实现： 
//两个int（32位）整数m和n的二进制表达中，有多少个位(bit)不同？ 
//输入例子: 
//1999 2299 
//输出例子:7
#include<stdio.h>
int main()
{
	int m = 0;
	int n = 0;
	
	int temp_m = 0;
	int temp_n = 0;
	int count = 0;
	scanf("%d%d",&m, &n);
	while(1)
	{
		if(m == 0 && n == 0)
		{
			break;
		}
		temp_m = m&1;
		m >>= 1;

		temp_n = n&1;
		n >>= 1;
		if(temp_m != temp_n)
		{
			++count;
		}
	}
	printf("%d\n", count);
	return 0;
}	
//
//5.写博客总结C语言操作符，博客链接发给我，并分享到群里。 
http://write.blog.csdn.net/postedit/78598224