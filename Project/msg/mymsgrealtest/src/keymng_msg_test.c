﻿#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../incl/keymng_msg.h"

void Msg_ResTESt(unsigned char** pMsgKeyResData,int* iMsgKeyResDataLen)
{
  int ret;
	/*MsgKey_Res mrs;*/
  MsgKey_Res* DeMrs = NULL;
  int				iType = 0;
	/*mrs.rv = 1;*/
	/*strcpy(mrs.clientId, "1234");*/
	/*strcpy(mrs.serverId, "4567");*/
	/*strcpy((char*)mrs.r2,"90");*/
	/*mrs.seckeyid = 12;*/
	/*unsigned char	*myout = NULL;*/
	/*int				myoutlen = 0;*/

	/*ret = MsgEncode(&mrs, ID_MsgKey_Res, &myout, &myoutlen);*/

  int i = 0;
  MsgKey_Res msgRes;
  msgRes.rv = 0;
    msgRes.seckeyid= 0;
      strcpy(msgRes.clientId,"1111");
        strcpy(msgRes.serverId,"1111");
          printf("msgRes.clientId:%s\n",msgRes.clientId);
            printf("msgRes.serverId:%s\n",msgRes.serverId);
              for(i = 0; i < 1; i++)
              {
                    msgRes.r2[i] = 'a' + i;
                      
              }
          ret = MsgEncode(&msgRes,ID_MsgKey_Res,pMsgKeyResData,iMsgKeyResDataLen);
            printf("over MsgEncode\n");



	/*if (ret != 0)*/
	/*{*/
		/*printf("error\n");*/
	/*}*/
  ret = MsgDecode(*pMsgKeyResData, *iMsgKeyResDataLen, (void**)&DeMrs, &iType);
  printf("once DsgDecode\n");
  ret = MsgDecode(*pMsgKeyResData, *iMsgKeyResDataLen, (void**)&DeMrs, &iType);
  printf("Twice DsgDecode\n");
  ret = MsgDecode(*pMsgKeyResData, *iMsgKeyResDataLen, (void**)&DeMrs, &iType);
  printf("Thrid DsgDecode\n");



  if (msgRes.rv == DeMrs->rv &&
    (strcmp(msgRes.clientId, DeMrs->clientId) == 0)
    && (strcmp(msgRes.serverId, DeMrs->serverId) == 0) && (strcmp((char*)msgRes.r2, (char*)DeMrs->r2) == 0))
  {
    printf("aa编码结果成功aaa\n");
  }
	/*MsgMemFree((void **)&myout, 0); //释放内存块*/
	/*MsgMemFree((void **)&DeMrs, ID_MsgKey_Res); //释放老师结构体*/
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
  printf("%s\n",DeMrq->clientId);
  ret = MsgDecode(myout, myoutlen, &DeMrq, &iType);
  printf("%s\n",DeMrq->clientId);
  ret = MsgDecode(myout, myoutlen, &DeMrq, &iType);
  printf("%s\n",DeMrq->clientId);
  ret = MsgDecode(myout, myoutlen, &DeMrq, &iType);
  printf("%s\n",DeMrq->clientId);
  ret = MsgDecode(myout, myoutlen, &DeMrq, &iType);
  printf("%s\n",DeMrq->clientId);
  ret = MsgDecode(myout, myoutlen, &DeMrq, &iType);
  printf("%s\n",DeMrq->clientId);
  ret = MsgDecode(myout, myoutlen, &DeMrq, &iType);
  printf("%s\n",DeMrq->clientId);




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
  unsigned char* s = NULL;
  int len = 0;

	/*Msg_ResTESt(&s,&len);*/
  Msg_ReqTESt();
#if 0
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
#endif
}
