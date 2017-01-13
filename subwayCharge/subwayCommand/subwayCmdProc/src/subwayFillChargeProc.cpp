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
@ ��ֵ����
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcFillChargeCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{

	unsigned int balance = 0;
	EN_CARD_TYPE enCard = EN_CARD_TYPE_BUTT;

	//��ȡ����Ϣ
	EN_RETURN_CODE returnCode = GetCardInfo(unCmd.stCmdFillCharge.cardNo, balance, enCard);
	//����Ч�ж�
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, unCmd.stCmdFillCharge.cardNo, enCard, balance, returnStr);
		return;
	}
	//�������ж�
	if (EN_CARD_TYPE_SINGLE == enCard)
	{
		returnCode = EN_RETURN_SINGLE_CARD_CANNOT_RECHARGE;
		GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, unCmd.stCmdFillCharge.cardNo, enCard, balance, returnStr);
		return;
	}

	//���г�ֵ��������ֵ��Χ���Լ�������Χ�жϣ���ֵ�ɹ�����¿����
	returnCode = RechargeCard(unCmd.stCmdFillCharge.cardNo, unCmd.stCmdFillCharge.cardCharge);

	//���ݳ�ֵ��Ŀ���Ϣ  GetCardInfo
	GetCardInfo(unCmd.stCmdFillCharge.cardNo, balance, enCard);
	//����ַ���
	//GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, pCmdCharge->cardNo, enCard, balance, returnStr);
	GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, unCmd.stCmdFillCharge.cardNo, enCard, balance, returnStr);

	return;
}