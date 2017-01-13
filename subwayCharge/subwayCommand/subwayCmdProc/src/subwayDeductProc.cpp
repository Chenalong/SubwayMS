#include "stdafx.h"
#include <iostream>
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
#include "subwayline.h"
#include "subwayPrice.h"
#include "subwayCommon.h"
#include "subwayError.h"
#include "subwayCmdParse/subwayCmdParse.h"
#include "subwayOutput/subwayOutput.h"
using namespace std;

/*
@ ����۷�����
@ ��Σ�stCmdDeduct, ��������
@ ����: returnStr
@ ����ֵ: void
*/
void ProcDeductCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	EN_CARD_TYPE cardType = EN_CARD_TYPE_BUTT;
	unsigned int balance = 0;
	unsigned int distance = 0;
	unsigned int cost = 0;
	//���ݿ��Ż�ȡ����Ϣ  GetCardInfo
	returnCode = GetCardInfo(unCmd.stCmdDeduct.cardNo, balance, cardType);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}
	//���ʱ���ʽ  CHECK_TIME
	returnCode = CheckTime(unCmd.stCmdDeduct.enterTime, unCmd.stCmdDeduct.exitTime);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}

	//���������  GetSubwayStationDis
	returnCode = GetSubwayStationDis(unCmd.stCmdDeduct.enterStation, unCmd.stCmdDeduct.exitStation, distance);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}

	//����۷Ѽ۸� 
	returnCode = GetDeductPrice(cardType, balance, distance, unCmd.stCmdDeduct.enterTime, unCmd.stCmdDeduct.exitTime, cost);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}



	//�Գ˳������п۷� DeductCard
	returnCode = DeductCard(unCmd.stCmdDeduct.cardNo, cardType, cost, balance);
	if ((returnCode != EN_RETURN_SUCC)&&(returnCode != EN_RETURN_BALANCE_TOO_LOW))
	{
		GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
		return;
	}
	if (EN_CARD_TYPE_SINGLE == cardType)
	{
		DeleteCard(unCmd.stCmdDeduct.cardNo);
	}
	

	

	//����ַ���
	GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, cardType, balance, returnStr);
	return;
}