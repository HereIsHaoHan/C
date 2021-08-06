# include <stdio.h>
# include <windows.h>

int setUart (HANDLE hCom)
{
	COMMTIMEOUTS timeouts;		//����һ��COMMTIMEOUTS�ṹ�����Զ��峬ʱ��Ϣ
	DCB dcb;					//����һ��DCB�ṹ�Ի�ú����ô�����Ϣ
	//��COMMTIMEOUTS timeouts�����Զ���	
	//����ʱ
	timeouts.ReadIntervalTimeout = 1000;			//������ʱ�����ַ���ļ����ʱ
	timeouts.ReadTotalTimeoutMultiplier = 500;		//�������ڶ�ȡÿ���ַ�ʱ�ĳ�ʱ
	timeouts.ReadTotalTimeoutConstant = 5000;		//�������Ĺ̶���ʱ
	//д��ʱ
	timeouts.WriteTotalTimeoutMultiplier = 0;		//д������ÿ���ַ�ʱ�ĳ�ʱ
	timeouts.WriteTotalTimeoutConstant = 2000;		//д�����Ĺ̶���ʱ

	SetCommTimeouts (hCom,&timeouts);				//����SetCommTimeouts��timeouts����Ϊ���ڶ�д��ʱʱ��

	//������������������Ĵ�С
	SetupComm (hCom,500,500);						//���ھ�������뻺������С�������������С

	//���ô��ڲ���
	if (GetCommState (hCom, &dcb) == 0)				//��õ�ǰ����������Ϣ
	{
		return -1;
	}

	dcb.BaudRate = CBR_9600;	//������
	dcb.ByteSize = 8;			//����λ��
	dcb.Parity   = NOPARITY;	//У��λ
	dcb.StopBits = ONESTOPBIT;	//ֹͣλ

	if (SetCommState(hCom,&dcb) == 0)				//���ý��д�������
	{
		return -1;
	}

	return 0;

}


int main ()
{
	int i;
	HANDLE hCom;		//���崮�ھ��
	int count = 20;
	char rbuf[501] = {0}, wbuf[501] = {0};
	DWORD rsize = 0, wsize = 0;
	
	//�򿪴��� CreateFile����
	hCom = CreateFile ("COM1", GENERIC_READ |GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	/*
	CreateFile�����򿪴���,�ú�������7������,�����ڰ�˳�����ã��ֱ�Ϊ��1��COM1Ϊ���������ļ���lpFileName����	2�����ʷ�ʽdwDesiredAccess��
	GENERIC_READ��GENERIC_WRITE�ֱ�Ϊ�����ʣ�д���ʣ�	3������ʽdwShareMode:0��ʾ���ļ����ܱ�����,�򿪴���ʱӦ��Ϊ0,����Ϊ��ռ��ʽ��	4����ȫ���ԣ�NULL��ʾָ�����գ��൱��0��
	5��dwCreationDispositionָ��������ļ�ʱ�Ķ�����OPEN_EXISTING��ʾ���ļ����ļ������������ʧ�ܣ����ڱ�����ڣ�	6���ļ���־����dwFlagsAttributes
	7��hTemplateFile�ļ����

	ͨ������CreateFile�����򿪴��ڣ�ִ�гɹ�ʱ���ش��ھ����hCom,�����ɹ��򷵻�INVALID_HANDLE_VALUE����ִ�������if���
	*/
	
	if (hCom != INVALID_HANDLE_VALUE)
		printf ("���ڴ򿪳ɹ���\n");
	else
		printf ("���ڴ�ʧ�ܣ�\n");		//ͨ��if���Դ��ڴ���������жϣ���Ӧ�ɹ���ʧ��

	//�������ô���
	if (setUart (hCom) == -1)				//����if���ʱ���ȵ���setUart��������hComΪʵ�θ����βΣ�
		if (INVALID_HANDLE_VALUE != hCom)	//������ֵΪ0ʱ����䲻ִ��
			CloseHandle (hCom);				//�رմ���

	//��д����
	printf ("��ʼ��ȡ��������\n");
	while (1)
	{
		if (INVALID_HANDLE_VALUE != hCom)	
		{
			ReadFile (hCom, rbuf, count, &rsize, NULL);			//��ʼ���ݻ�ȡ
			//��ȡ�����ھ�����������������ݣ���ȡ�ֽڣ�ʵ�ʶ�ȡ�ֽڣ����첽����
			//printf ("����ֵ��")��
			for (i = 0; i < rsize; i++)							//�������
				printf ("%c",rbuf[i]);
			printf("\n");

		}

	}

	return 0;
}







