/*
//1.дһ���������ز����������� 1 �ĸ��� 
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
	printf("������һ�� -65536��65535 ֮�������");
	scanf("%d", &num);
	printf("%d�Ķ���������%d��1\n", num, count_one_bits(num));
	return 0;
}
*/

/*
//
//2.��ȡһ�������������������е�ż��λ������λ���ֱ�������������С� 
#include<stdio.h>

void get_evenAndodd(int num)
{
	int tempeven = num>>1;//ż��λ
	int tempodd = num;//����λ
	int arreven[32] = {0};
	int arrodd[32] = {0};
	int i = 0;
	//����
	while(tempodd != 0)
	{
		arrodd[i] = tempodd&1;
		tempodd >>= 2;
		++i;
	}
	//ż��
	i = 0;
	while(tempeven != 0)
	{
		arreven[i] = tempeven&1;
		tempeven>>= 2;
		++i;
	}
	//�������λ����������
	printf("32λ��������\n" );
	for(i = sizeof(arrodd)/sizeof(arrodd[0]); i>=0; --i)
	{
		printf("%d", arrodd[i]);
	}
	printf("\n");
	//���ż��λ����������
	printf("32λż������\n" );
	for(i = sizeof(arreven)/sizeof(arreven[0]); i>=0; --i)
	{
		printf("%d", arreven[i]);
	}
	printf("\n");
	
}
int main()
{
	int num = 0;
	printf("������һ����: \n");
	scanf("%d", &num);
	get_evenAndodd(num);
	return 0;
}
*/
//


/*
//3. ���һ��������ÿһλ�� 
#include<stdio.h>
#include<math.h>
int main()
{
	int num = 0;
	int temp = 0;
	int count = 1;
	int i = 0;
	printf("������һ������");
	scanf("%d", &num);
	temp = num;
	//�ж�λ��
	while(num>9)
	{
		++count;
		temp /= 10;
	}
	printf("%d��%dλ��\n", num, count);
	temp = num;
	//���ÿһλ����
	for(i = count; i >= 0; --i)
	{
		printf("%d ",temp/(pow(10, i)) );
	}
	return 0;
}
*/



//4.���ʵ�֣� 
//����int��32λ������m��n�Ķ����Ʊ���У��ж��ٸ�λ(bit)��ͬ�� 
//��������: 
//1999 2299 
//�������:7
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
//5.д�����ܽ�C���Բ��������������ӷ����ң�������Ⱥ� 
http://write.blog.csdn.net/postedit/78598224