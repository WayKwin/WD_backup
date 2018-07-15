
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "keymng_msg.h"
#include "itcastderlog.h"
#include "itcast_asn1_der.h"
/*

Debug   ��Encode �� ��*outdata  ���ٿռ�, û�н� (seqence)poutdata->pDatalen ��ֵ��outdata

ע��malloc ��ǵ�memcpy
memcpy֮��
���� �����\0
*/
int TeacherEncode(Teacher* pstruct, ITCAST_ANYBUF **out)
{
	int ret = 0;

	ITCAST_ANYBUF *tmp = NULL;
	ITCAST_ANYBUF *head = NULL;
	ITCAST_ANYBUF *cur = head;
	ITCAST_ANYBUF*  outdata = NULL;
	int tmpoutlen = 0;


	ret = DER_ITCAST_String_To_AnyBuf(&outdata, pstruct->name, strlen(pstruct->name));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s%d\n", __FUNCTION__, __LINE__);
		return ret;
	}

	ret = DER_ItAsn1_WritePrintableString(outdata, &head);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(head);
		DER_ITCAST_FreeQueue(outdata);
		printf("%s%d\n", __FUNCTION__, __LINE__);
		return ret;
	}

	cur = head;
	// �ͷŵ�ת���õ�tmp
	DER_ITCAST_FreeQueue(outdata);

	DER_ItAsn1_WriteInteger(pstruct->age, &(cur->next));
	if (ret != 0)
	{
		printf("%s%d\n", __FUNCTION__, __LINE__);
		DER_ITCAST_FreeQueue(head);
		return ret;
	}
	cur = cur->next;
	//����P
	ret = EncodeChar(pstruct->p, pstruct->plen, &(cur->next));
	if (ret != 0)
	{
		printf("%s%d\n", __FUNCTION__, __LINE__);
		DER_ITCAST_FreeQueue(head);
		return ret;
	}
	cur = cur->next;
	ret = DER_ItAsn1_WriteInteger(pstruct->plen, &cur->next);
	if (ret != 0)
	{
		printf("%s%d\n", __FUNCTION__, __LINE__);
		DER_ITCAST_FreeQueue(head);
		return ret;
	}



	// ������� ���� ���һ���µ� any_buf
	// ��ô outdata-> pdata  Ӧ���ǽ� ������ÿ�� any_buff ��������(���һƬ�������ڴ�ռ�)
	ret = DER_ItAsn1_WriteSequence(head, &outdata);
	if (ret != 0)
	{
		printf("%s%d\n", __FUNCTION__, __LINE__);
		DER_ITCAST_FreeQueue(head);
		return ret;
	}
	//   
	DER_ITCAST_FreeQueue(head);
	*out = outdata;


	//*out = (unsigned char*)malloc(outdata->dataLen);

	//memcpy(*out, outdata->pData, outdata->dataLen);
	//*outlen = outdata->dataLen;

	// ����֮���ɾ��data
	//DER_ITCAST_FreeQueue(outdata);

	return ret;
}

int TeacherDecode(unsigned char *in, int len, Teacher** pStruct)
{

	int ret = 0;
	ITCAST_ANYBUF *pTmp = NULL, *pHead = NULL;
	ITCAST_ANYBUF *pTmpDABuf = NULL;
	ITCAST_ANYBUF *pOutData = NULL;
	ITCAST_ANYBUF *inAnyBuf = NULL;
	int tempNum = 0;
	Teacher *pTmpStru = NULL;
	// �Ѷ����������� ��ԭΪanybuf;
	inAnyBuf = malloc(sizeof(ITCAST_ANYBUF));
	inAnyBuf->next = NULL;

	if (!inAnyBuf)
	{
		return 3;
	}
	memset(inAnyBuf, 0, sizeof(inAnyBuf));
	inAnyBuf->pData = (unsigned char *)malloc(len);
	memset(inAnyBuf->pData, 0, sizeof(inAnyBuf));
	if (!inAnyBuf->pData)
	{
		DER_ITCAST_FreeQueue(inAnyBuf);
		return 3;
	}
	memcpy(inAnyBuf->pData, in, len);
	inAnyBuf->dataLen = len;
	//read  inAnyBuf ���� sequence ,��� ����ͷ��  ��������anybuf->pdata ��Ϊ��ɢ���ڴ�(����)
	DER_ItAsn1_ReadSequence(inAnyBuf, &pTmp);
	if (ret != 0)
	{
		//free(inAnyBuf->pData);
		DER_ITCAST_FreeQueue(inAnyBuf);
		DER_ITCAST_FreeQueue(pHead);
		return ret;
	}
	//free(inAnyBuf->pData); // ����ĺ����Ѿ�������һ��
	DER_ITCAST_FreeQueue(inAnyBuf);

	pTmpStru = (Teacher*)malloc(sizeof(Teacher));
	memset(pTmpStru, 0, sizeof(Teacher));
	if (!pTmpStru)
	{
		DER_ITCAST_FreeQueue(pHead);
		return ret;
	}

	//����name
	DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);
	//pTmpStru->name[pTmp->dataLen] = 0;
	//name������
	memcpy(pTmpStru->name, pTmpDABuf->pData, pTmpDABuf->dataLen);

	pTmp = pTmp->next;

	ret = DER_ItAsn1_ReadInteger(pTmp, &pTmpStru->age);

	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		return ret;
	}
	pTmp = pTmp->next;
	//ָ��p
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &pTmpDABuf);

	if (ret != 0)
	{
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		return ret;
	}
	//pTmpStru->p = malloc(sizeof(pTmpDABuf->dataLen + 1));
	pTmpStru->p = malloc(pTmpDABuf->dataLen + 1);


	if (!pTmpStru->p)
	{
		printf("%s %d\n", __FUNCTION__, __LINE__);
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
	}
	memset(pTmpStru->p, 0, pTmpStru->plen);
	memcpy(pTmpStru->p, pTmpDABuf->pData, pTmpDABuf->dataLen);
	printf(" ָ��p %p\n", pTmpStru->p);

	pTmpStru->p[pTmpDABuf->dataLen] = 0;

	pTmp = pTmp->next;

	ret = DER_ItAsn1_ReadInteger(pTmp, &pTmpStru->plen);
	if (ret != 0)
	{
		free(pTmpStru->p);
		free(pTmpStru);
		DER_ITCAST_FreeQueue(pHead);
		return ret;
	}

	*pStruct = pTmpStru;

	DER_ITCAST_FreeQueue(pHead);
	return ret;
}
int MsgKey_ResEncode(MsgKey_Res* pStruct, ITCAST_ANYBUF** pp_outData)
{
	ITCAST_ANYBUF* pHeadBuf = NULL, *pTmp = NULL;
	ITCAST_ANYBUF* outdata = NULL;
	int ret = 0;
	// rv
	ret = DER_ItAsn1_WriteInteger(pStruct->rv, &pHeadBuf);
	if (ret != 0)
	{
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;
	}
	pTmp = pHeadBuf;
	//clinetId
	ret = DER_ITCAST_String_To_AnyBuf(&outdata, pStruct->clientId, strlen(pStruct->clientId));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}
	ret = DER_ItAsn1_WritePrintableString(outdata, &pTmp->next);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}

	memset(outdata, 0, sizeof(outdata));
	ret = DER_ITCAST_String_To_AnyBuf(&outdata, pStruct->serverId, strlen(pStruct->serverId));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}
	//serid
	pTmp = pTmp->next;
	ret = DER_ItAsn1_WritePrintableString(outdata, &pTmp->next);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}

	memset(outdata, 0, sizeof(outdata));
	ret = DER_ITCAST_String_To_AnyBuf(&outdata, pStruct->r2, strlen(pStruct->r2));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;
	}

	//R2

	pTmp = pTmp->next;
	ret = DER_ItAsn1_WritePrintableString(outdata, &pTmp->next);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}


	DER_ITCAST_FreeQueue(outdata);
	//seckeyid
	pTmp = pTmp->next;
	ret = DER_ItAsn1_WriteInteger(pStruct->seckeyid, &pTmp->next);
	if (ret != 0)
	{
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;
	}

	//����pTmpӦ����NULL
	pTmp = pTmp->next;
	int i = 0;
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &outdata);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;
	}
	*pp_outData = outdata;

	DER_ITCAST_FreeQueue(pHeadBuf);

}
int MsgKey_ResDecode(unsigned char* indata, int len, MsgKey_Res** ppStruct)
{
	int ret = 0;
	ITCAST_ANYBUF *pHeadBuf = NULL, *pTmp = NULL;
	//�����ṹ��
	ITCAST_ANYBUF* OutSequence = NULL;

	ITCAST_ANYBUF* CharBuf = NULL;


	OutSequence = (ITCAST_ANYBUF*)malloc(sizeof(ITCAST_ANYBUF));
	if (OutSequence == NULL)
	{
		ret = KeyMng_MallocErr;
		printf(" malloc error %d\n", __LINE__);
		return ret;
	}
	memset(OutSequence, 0, sizeof(ITCAST_ANYBUF)); //����Ҫ

	OutSequence->pData = (unsigned char*)malloc(len);
	memcpy(OutSequence->pData, indata, len);
	OutSequence->dataLen = len;
	if (OutSequence->pData == NULL)
	{
		ret = KeyMng_MallocErr;
		printf(" malloc error %d\n", __LINE__);
		return ret;
	}

	OutSequence->next = NULL;
	ret = DER_ItAsn1_ReadSequence(OutSequence, &pHeadBuf);
	if (ret != 0)
	{
		printf(" %s %d\n ", __FUNCTION__, __LINE__);
		DER_ITCAST_FreeQueue(OutSequence);
		return ret;
	}
	//������free��
	DER_ITCAST_FreeQueue(OutSequence);

	//���� Res �ṹ����ڴ濪ʼ����
	*ppStruct = (MsgKey_Res*)malloc(sizeof(MsgKey_Res));
	if (*ppStruct == NULL)
	{
		ret = KeyMng_MallocErr;
		printf(" malloc error %d\n", __LINE__);
		return ret;
	}

	MsgKey_Res * pStruct = *ppStruct;
	ret = DER_ItAsn1_ReadInteger(pHeadBuf, &(pStruct->rv));
	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}

	pTmp = pHeadBuf->next;
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &CharBuf);
	memcpy(pStruct->clientId, CharBuf->pData, CharBuf->dataLen);
	//��ס�����\0
	pStruct->clientId[CharBuf->dataLen] = 0;
	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}

	pTmp = pTmp->next;
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &CharBuf);
	memcpy(pStruct->serverId, CharBuf->pData, CharBuf->dataLen);
	pStruct->serverId[CharBuf->dataLen] = 0;

	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}

	pTmp = pTmp->next;
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &CharBuf);
	memcpy(pStruct->r2, CharBuf->pData, CharBuf->dataLen);
	pStruct->r2[CharBuf->dataLen] = 0;
	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}

	pTmp = pTmp->next;
	ret = DER_ItAsn1_ReadInteger(pTmp, &(pStruct->seckeyid));
	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}
	return ret;
}

int MsgKey_ReqEncode(MsgKey_Req* pStruct, ITCAST_ANYBUF** pp_outData)
{
	ITCAST_ANYBUF* pHeadBuf = NULL, *pTmp = NULL;
	ITCAST_ANYBUF* outdata = NULL;
	int ret = 0;
	// rv
	ret = DER_ItAsn1_WriteInteger(pStruct->cmdType, &pHeadBuf);
	if (ret != 0)
	{
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;
	}
	pTmp = pHeadBuf;
	//clinetId
	ret = DER_ITCAST_String_To_AnyBuf(&outdata,
		pStruct->clientId, strlen(pStruct->clientId));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}
	ret = DER_ItAsn1_WritePrintableString(outdata, &pTmp->next);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}

	memset(outdata, 0, sizeof(outdata));
	ret = DER_ITCAST_String_To_AnyBuf(&outdata, pStruct->AuthCode,
		strlen(pStruct->AuthCode));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}
	pTmp = pTmp->next;
	ret = DER_ItAsn1_WritePrintableString(outdata, &pTmp->next);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}

	memset(outdata, 0, sizeof(outdata));
	//serverId
	ret = DER_ITCAST_String_To_AnyBuf(&outdata, pStruct->serverId,
		strlen(pStruct->serverId));
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;
	}

	//R2
	pTmp = pTmp->next;
	ret = DER_ItAsn1_WritePrintableString(outdata, &pTmp->next);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(outdata);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;

	}

	memset(outdata, 0, sizeof(outdata));
	ret = DER_ITCAST_String_To_AnyBuf(&outdata, pStruct->r1,
		strlen(pStruct->r1));

	// r1
	pTmp = pTmp->next;
	ret = DER_ItAsn1_WritePrintableString(outdata, &pTmp->next);
	if (ret != 0)
	{
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;
	}

	DER_ITCAST_FreeQueue(outdata);
	//����pTmpӦ����NULL
	pTmp = pTmp->next;
	int i = 0;
	ret = DER_ItAsn1_WriteSequence(pHeadBuf, &outdata);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadBuf);
		printf("%s %d error\n", __FUNCTION__, __LINE__);
		return ret;
	}
	*pp_outData = outdata;

	DER_ITCAST_FreeQueue(pHeadBuf);

}

int MsgKey_ReqDecode(unsigned char* indata, int len, MsgKey_Req** ppStruct)
{
	int ret = 0;
	ITCAST_ANYBUF *pHeadBuf = NULL, *pTmp = NULL;
	//�����ṹ��
	ITCAST_ANYBUF* OutSequence = NULL;

	ITCAST_ANYBUF* CharBuf = NULL;


	OutSequence = (ITCAST_ANYBUF*)malloc(sizeof(ITCAST_ANYBUF));
	if (OutSequence == NULL)
	{
		ret = KeyMng_MallocErr;
		printf(" malloc error %d\n", __LINE__);
		return ret;
	}
	memset(OutSequence, 0, sizeof(ITCAST_ANYBUF)); //����Ҫ

	OutSequence->pData = (unsigned char*)malloc(len);
	memcpy(OutSequence->pData, indata, len);
	OutSequence->dataLen = len;
	if (OutSequence->pData == NULL)
	{
		ret = KeyMng_MallocErr;
		printf(" malloc error %d\n", __LINE__);
		return ret;
	}

	OutSequence->next = NULL;
	ret = DER_ItAsn1_ReadSequence(OutSequence, &pHeadBuf);
	if (ret != 0)
	{
		printf(" %s %d\n ", __FUNCTION__, __LINE__);
		DER_ITCAST_FreeQueue(OutSequence);
		return ret;
	}
	//������free��
	DER_ITCAST_FreeQueue(OutSequence);

	//���� Res �ṹ����ڴ濪ʼ����
	*ppStruct = (MsgKey_Req*)malloc(sizeof(MsgKey_Res));
	if (*ppStruct == NULL)
	{
		ret = KeyMng_MallocErr;
		printf(" malloc error %d\n", __LINE__);
		return ret;
	}

	MsgKey_Req * pStruct = *ppStruct;
	ret = DER_ItAsn1_ReadInteger(pHeadBuf, &(pStruct->cmdType));
	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}

	pTmp = pHeadBuf->next;
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &CharBuf);
	memcpy(pStruct->clientId, CharBuf->pData, CharBuf->dataLen);
	//��ס�����\0
	pStruct->clientId[CharBuf->dataLen] = 0;
	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}

	pTmp = pTmp->next;
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &CharBuf);
	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}
	memcpy(pStruct->AuthCode, CharBuf->pData, CharBuf->dataLen);
	pStruct->serverId[CharBuf->dataLen] = 0;

	pTmp = pTmp->next;
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &CharBuf);
	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}
	memcpy(pStruct->serverId, CharBuf->pData, CharBuf->dataLen);
	pStruct->serverId[CharBuf->dataLen] = 0;

	pTmp = pTmp->next;
	ret = DER_ItAsn1_ReadPrintableString(pTmp, &CharBuf);
	if (ret != 0)
	{
		MsgMemFree(ppStruct, ID_MsgKey_Res);
		DER_ITCAST_FreeQueue(pHeadBuf);
	}
	memcpy(pStruct->r1, CharBuf->pData, CharBuf->dataLen);
	pStruct->r1[CharBuf->dataLen] = 0;

	return ret;
}


int MsgEncode(
	void			*pStruct, /*in*/
	int				type,
	unsigned char	**outData, /*out*/
	int				*outLen)
{
	if (pStruct == NULL || type < 0 || outData == NULL || outLen == NULL)
	{
		printf(" paratemter error\n");
		return  KeyMng_Check;
	}
	ITCAST_ANYBUF *pHeadbuf = NULL, *pTmp = NULL;
	ITCAST_ANYBUF *pOutData = NULL;
	int ret = 0;

	//����type
	ret = DER_ItAsn1_WriteInteger(type, &pHeadbuf);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		printf("error writeInteger\n");
		return ret;
	}
	switch (type)
	{
	case ID_MsgKey_Teacher:
		// teacher ��д  ��� Ϊ anybuf  ��� head->buf
		ret = TeacherEncode((Teacher*)pStruct, &pTmp);
		if (ret != 0)
		{
			DER_ITCAST_FreeQueue(pHeadbuf);
			printf("error TeacherEncode\n");
			return ret;
		}
		break;
	case ID_MsgKey_Req:
		ret = MsgKey_ReqEncode((MsgKey_Req*)pStruct, &pTmp);
		if (ret != 0)
		{
			DER_ITCAST_FreeQueue(pHeadbuf);
			printf("error MsgKey_Req\n");
			return ret;
		}
		break;
		break;
	case ID_MsgKey_Res:
		// pTmp �����м���
		ret = MsgKey_ResEncode((MsgKey_Res*)pStruct, &pTmp);
		if (ret != 0)
		{
			DER_ITCAST_FreeQueue(pHeadbuf);
			printf("error MsgKey_Res\n");
			return ret;
		}
		break;
	default:
		printf("unkown type\n");
		return -1;
		break;
	}
	pHeadbuf->next = pTmp;
	ret = DER_ItAsn1_WriteSequence(pHeadbuf, &pOutData);
	if (ret != 0)
	{
		DER_ITCAST_FreeQueue(pHeadbuf);
		return ret;
	}

	*outData = (unsigned char*)malloc(pOutData->dataLen);

	memset(*outData, 0, sizeof(pOutData->dataLen));

	memcpy(*outData, pOutData->pData, pOutData->dataLen);

	*outLen = pOutData->dataLen;

	//printf("%s_%d_[][]%s\n", __FUNCTION__, __LINE__,*outData);

	DER_ITCAST_FreeQueue(pHeadbuf);
	DER_ITCAST_FreeQueue(pOutData);
	return ret;
}



int MsgDecode(
	unsigned char *inData,/*in*/
	int           inLen,
	void          **pStruct /*out*/,
	int           *type /*out*/)
{
	//printf("%s_%d_[][]%s\n", __FUNCTION__, __LINE__,inData);
	ITCAST_ANYBUF *pHeadBUf = NULL, *pTmp = NULL;
	int ret = 0;
	unsigned long itype = 0;
	if (inData == NULL || inLen < 0 || pStruct == NULL || type == NULL)
	{
		perror("Input Error \n");
		return 3;
	}
	pTmp = (ITCAST_ANYBUF*)malloc(sizeof(ITCAST_ANYBUF));
	if (pTmp == NULL)
	{
		ret = KeyMng_MallocErr;
		perror("mallc:\n");
		return 3;
	}

	memset(pTmp, 0, sizeof(ITCAST_ANYBUF));

	pTmp->pData = (unsigned char*)malloc(inLen);
	if (pTmp->pData == NULL)
	{
		ret = KeyMng_MallocErr;
		return ret;
	}
	memset(pTmp->pData, 0, pTmp->dataLen);
	memcpy(pTmp->pData, inData, inLen);
	pTmp->dataLen = inLen;

	ret = DER_ItAsn1_ReadSequence(pTmp, &pHeadBUf);
	if (ret != 0)
	{
		printf("%s_%d\n", __FUNCTION__, __LINE__);
		DER_ITCAST_FreeQueue(pHeadBUf);
		return ret;
	}
	DER_ITCAST_FreeQueue(pTmp);
	DER_ItAsn1_ReadInteger(pHeadBUf, &itype);
	//	DER_ITAsn1_ReadInteger(pHeadBUf, &itype);
	if (ret != 0)
	{
		printf("%s_%d\n", __FUNCTION__, __LINE__);
		DER_ITCAST_FreeQueue(pHeadBUf);
		return ret;
	}
	switch (itype)
	{
	case ID_MsgKey_Teacher:
		//pHeadBUf->next->pData; ������Ҫ���� anybuf���pData
		//pHeadBUf->next->dataLen;
		ret = TeacherDecode(pHeadBUf->next->pData,
			pHeadBUf->next->dataLen,
			(Teacher**)pStruct);
		if (ret != 0)
		{
			printf("%s_%d\n", __FUNCTION__, __LINE__);
			DER_ITCAST_FreeQueue(pHeadBUf);
			printf("error TeacherEncode\n");
			return ret;
		}
		break;
	case ID_MsgKey_Req:
		MsgKey_ReqDecode(pHeadBUf->next->pData,
			pHeadBUf->next->dataLen,
			(MsgKey_Res**)pStruct);
		break;
	case ID_MsgKey_Res:
		MsgKey_ResDecode(pHeadBUf->next->pData,
			pHeadBUf->next->dataLen,
			(MsgKey_Res**)pStruct);
		break;
	default:
		break;
	}
	*type = itype;
	DER_ITCAST_FreeQueue(pHeadBUf);
	return ret;
}


int FreeTeacher(Teacher**  ppThr)
{
	if (ppThr == NULL)
	{
		printf("%s %d: NULL INPUT\n", __FUNCTION__, __LINE__);
		return 0;
	}
	Teacher* pThr = *ppThr;
	if (pThr == NULL)
	{
		printf("%s %d: * NULL INPUT\n", __FUNCTION__, __LINE__);
		return 0;
	}
	if (pThr->p)
	{
		//printf("ָ�� p  %p\n", pThr->p);
		//printf("pThr-> p %s\n", pThr->p);
		free(pThr->p);
	}
	free(pThr);
	*ppThr = NULL;
	return 0;
}
int free_msgkey_res(MsgKey_Res** ppres)
{
	if (*ppres)
	{
		free(*ppres);
	}
	*ppres = NULL;
}
int free_msgkey_req(MsgKey_Req** ppreq)
{
	if (*ppreq)
	{
		free(*ppreq);
	}
	*ppreq = NULL;
}

// Free Struct
int MsgMemFree(void **point, int type)
{
	if (point == NULL)
	{
		printf("Empty Input\n");
		return 0;
	}
	if (type == 0)
	{
		if (*point)
		{
			free(*point);
		}
	}
	else
	{
		switch (type)
		{
		case ID_MsgKey_Teacher:
			FreeTeacher((Teacher**)point);
			break;
		case ID_MsgKey_Req:
			// TODO �����ṹ���ڱ���Ŀ���ͷŹ���һ��
			free_msgkey_res((MsgKey_Res**)point);
			break;
		case ID_MsgKey_Res:
			free_msgkey_req((MsgKey_Req**)point);
			break;
		default:
			printf("UnKown Type %s %d\n", __FUNCTION__, __LINE__);
			break;
		}
	}
	return 0;
}
