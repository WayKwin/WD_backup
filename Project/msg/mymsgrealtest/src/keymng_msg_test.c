#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "keymng_msg.h"

void Msg_ResTESt()
{
	int ret;
	MsgKey_Res mrs;
	MsgKey_Res* DeMrs;
	int				iType = 0;
	mrs.rv = 1;
	strcpy(mrs.clientId, "1234");
	strcpy(mrs.serverId, "4567");
	strcpy(mrs.r2, "90");
	mrs.seckeyid = 12;
	unsigned char	*myout = NULL;
	int				myoutlen = 0;

	ret = MsgEncode(&mrs, ID_MsgKey_Res, &myout, &myoutlen);


	if (ret != 0)
	{
		printf("error\n");
	}
	ret = MsgDecode(myout, myoutlen, &DeMrs, &iType);



	if (mrs.rv == DeMrs->rv &&
		(strcmp(mrs.clientId, DeMrs->clientId) == 0)
		&& (strcmp(mrs.serverId, DeMrs->serverId) == 0) && (strcmp(mrs.r2, DeMrs->r2) == 0))
	{
		printf("编码结果成功\n");
	}
	MsgMemFree((void **)&myout, 0); //释放内存块
	MsgMemFree((void **)&DeMrs, ID_MsgKey_Res); //释放老师结构体
}

void Msg_ReqTESt()
{
	int ret;
	MsgKey_Req mrq;
	MsgKey_Req* DeMrq;
	int				iType = 0;

	mrq.cmdType = 1;
	strcpy(mrq.clientId, "1234");
	strcpy(mrq.AuthCode, "4567");
	strcpy(mrq.serverId, "89");
	strcpy(mrq.r1, "zz");
	unsigned char	*myout = NULL;
	int				myoutlen = 0;

	ret = MsgEncode(&mrq, ID_MsgKey_Req, &myout, &myoutlen);


	if (ret != 0)
	{
		printf("error\n");
	}
	ret = MsgDecode(myout, myoutlen, &DeMrq, &iType);




	if (mrq.cmdType == DeMrq->cmdType &&
		(strcmp(mrq.clientId, DeMrq->clientId) == 0)
		&& (strcmp(mrq.serverId, DeMrq->serverId) == 0) && (strcmp(mrq.r1, DeMrq->r1) == 0))
	{
		printf("编码结果成功\n");
	}
	//MsgMemFree((void **)&myout, 0); //释放内存块
	//MsgMemFree((void **)&DeMrq, ID_MsgKey_Req); //释放老师结构体
}


int main()
{
	Msg_ResTESt();
	Msg_ReqTESt();
	int				ret = 0; //变量的本质: 
		Teacher			t1;
		unsigned char	*myout = NULL;
		int				myoutlen = 0;
		Teacher			*myTeacher = NULL;
		int				iType = 0;
	
	
		memset(&t1, 0, sizeof(Teacher));
	
		strcpy(t1.name, "myname");
		t1.age = 32;
		//指针变量 和 指针所在的内存空间 是两个不同的概念 
		t1.p = (char *)malloc(100);
		strcpy(t1.p, "aaaaaafgfff");
		t1.plen = strlen("aaaaaafgfff");
	
	
		//编码
		ret = MsgEncode(&t1, ID_MsgKey_Teacher, &myout, &myoutlen);
		if (ret != 0)
		{
			printf("func MsgEncode() err:%d \n", ret);
			goto End;
		}
	
		//解码
		ret = MsgDecode(myout, myoutlen, &myTeacher, &iType);
		if (ret != 0)
		{
			printf("func MsgDecode() err:%d \n", ret);
			goto End;
		}
			printf("指针 p  %p\n", myTeacher->p);
	
		//校验
		if (strcmp(t1.name, myTeacher->name) == 0 &&
			t1.age == myTeacher->age)
		{
			printf("编码和解码结果 ok\n");
		}
		else
		{
			printf("编码和解码结果 err\n");
		}
	
	End:
		if (t1.p != NULL) free(t1.p);
	
		MsgMemFree((void **)&myout, 0); //释放内存块
		MsgMemFree((void **)&myTeacher, ID_MsgKey_Teacher); //释放老师结构体
	return 0;
}
