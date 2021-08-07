/************************************************************************************************
2021年8月7日 23:33:44
程序：数字的排序与求和
功能：从用户获取十个数据，将这十个数据进行排序与求和，并且输出
特点：数据的输入分隔方式不限

编者：吴浩瀚
************************************************************************************************/

# include <stdio.h>

//读入十个数据，数据之间不限分隔方式
void input (int* in)
{
	int i;
	char ch;

	for (i=0; i<10; ++i)
	{
		scanf ("%d", &in[i]);
		if( (ch = getchar()) != '\n' )
				continue;
	}

}

//对十个数据进行排序：冒泡排序法
void compare (int* com)
{
	int k, t, s;
	
	for (k=0; k<9; ++k)
		for (s=0; s<(9-k); ++s)
			if(com[s] > com[s+1])
			{
				t = com[s];
				com[s] = com[s+1];
				com[s+1] = t;
			}
	
}

//将排序后的十个数据输出，并且求和
void output (int* out)
{
	int j, sum=0;

	for (j=0; j<10; ++j)
	{
		printf ("%d ",out[j]);
		sum+=out[j];
	}
	printf ("\nsum=%d\n",sum);
}


int main()
{
	int a[10]; 

	input (a);			//输入
	compare (a);		//排序
	output (a);			//输出

	return 0;
}