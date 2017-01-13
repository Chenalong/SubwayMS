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
@ ������ͨ��
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcCreateCardCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH]) // ��ͨ+ ����
{
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	EN_CARD_TYPE cardType = EN_CARD_TYPE_BUTT;


	//���ȼ����Ƿ��п��õĿ�
	returnCode = CheckAvailCard();
	if (returnCode != EN_RETURN_SUCC)
	{
		//TODO
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
		return;
	}


	//ʶ������ GetCardType
	returnCode = GetCardType(unCmd.stCmdCreateCard.cardType, cardType);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
		return;
	}
	//����ֵ����Ƿ�Ϸ�

	if (!CheckChargeValue(unCmd.stCmdCreateCard.cardCharge))
	{
		returnCode = EN_RETURN_RECHARGE_OVERFLOW;
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
		return;
	}


	//�쿨 AssignCard
	returnCode = AssignCard(cardNo, cardType, unCmd.stCmdCreateCard.cardCharge);
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
		return;
	}
	//����ַ���
	GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, cardType, unCmd.stCmdCreateCard.cardCharge, returnStr);
	return;
}