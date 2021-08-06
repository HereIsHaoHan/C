# include <stdio.h>
# include <windows.h>

int setUart (HANDLE hCom)
{
	COMMTIMEOUTS timeouts;		//设置一个COMMTIMEOUTS结构体以自定义超时信息
	DCB dcb;					//设置一个DCB结构以获得和设置串口信息
	//对COMMTIMEOUTS timeouts进行自定义	
	//读超时
	timeouts.ReadIntervalTimeout = 1000;			//读操作时两个字符间的间隔超时
	timeouts.ReadTotalTimeoutMultiplier = 500;		//读操作在读取每个字符时的超时
	timeouts.ReadTotalTimeoutConstant = 5000;		//读操作的固定超时
	//写超时
	timeouts.WriteTotalTimeoutMultiplier = 0;		//写操作在每个字符时的超时
	timeouts.WriteTotalTimeoutConstant = 2000;		//写操作的固定超时

	SetCommTimeouts (hCom,&timeouts);				//调用SetCommTimeouts将timeouts设置为串口读写超时时间

	//设置输入输出缓冲区的大小
	SetupComm (hCom,500,500);						//串口句柄，输入缓冲区大小，输出缓冲区大小

	//设置串口参数
	if (GetCommState (hCom, &dcb) == 0)				//获得当前串口配置信息
	{
		return -1;
	}

	dcb.BaudRate = CBR_9600;	//波特率
	dcb.ByteSize = 8;			//数据位数
	dcb.Parity   = NOPARITY;	//校验位
	dcb.StopBits = ONESTOPBIT;	//停止位

	if (SetCommState(hCom,&dcb) == 0)				//调用进行串口配置
	{
		return -1;
	}

	return 0;

}


int main ()
{
	int i;
	HANDLE hCom;		//定义串口句柄
	int count = 20;
	char rbuf[501] = {0}, wbuf[501] = {0};
	DWORD rsize = 0, wsize = 0;
	
	//打开串口 CreateFile函数
	hCom = CreateFile ("COM1", GENERIC_READ |GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	/*
	CreateFile函数打开串口,该函数包括7个部分,括号内按顺序配置，分别为：1、COM1为串口名（文件名lpFileName）；	2、访问方式dwDesiredAccess：
	GENERIC_READ，GENERIC_WRITE分别为读访问，写访问；	3、共享方式dwShareMode:0表示该文件不能被共享,打开串口时应该为0,串口为独占方式；	4、安全属性：NULL表示指针悬空，相当于0；
	5、dwCreationDisposition指创建或打开文件时的动作：OPEN_EXISTING表示打开文件，文件若不存在则会失败，串口必须存在；	6、文件标志属性dwFlagsAttributes
	7、hTemplateFile文件句柄

	通过调用CreateFile函数打开串口，执行成功时返回串口句柄给hCom,若不成功则返回INVALID_HANDLE_VALUE，再执行下面的if语句
	*/
	
	if (hCom != INVALID_HANDLE_VALUE)
		printf ("串口打开成功！\n");
	else
		printf ("串口打开失败！\n");		//通过if语句对串口打开情况进行判断，对应成功与失败

	//进行配置串口
	if (setUart (hCom) == -1)				//进行if语句时，先调用setUart函数，以hCom为实参赋给形参，
		if (INVALID_HANDLE_VALUE != hCom)	//当返回值为0时该语句不执行
			CloseHandle (hCom);				//关闭串口

	//读写串口
	printf ("开始读取串口数据\n");
	while (1)
	{
		if (INVALID_HANDLE_VALUE != hCom)	
		{
			ReadFile (hCom, rbuf, count, &rsize, NULL);			//开始数据获取
			//读取：串口句柄，缓冲区保存数据，读取字节，实际读取字节，无异步操作
			//printf ("数据值：")；
			for (i = 0; i < rsize; i++)							//输出数据
				printf ("%c",rbuf[i]);
			printf("\n");

		}

	}

	return 0;
}







