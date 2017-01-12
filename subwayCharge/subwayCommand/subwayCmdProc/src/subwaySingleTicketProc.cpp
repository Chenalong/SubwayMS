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
@ ������Ʊ
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcCreateSingleTicketCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	unsigned int distance = 0;
	int basePrice = -2;
	//���ȼ����Ƿ��п��õĿ�
	returnCode = CheckAvailCard();
	if (returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);
		return;
	}


	//��ȡ����վ��������� GetSubwayStationDis
	returnCode = GetSubwayStationDis(unCmd.stCmdSingleTicket.srcStation, unCmd.stCmdSingleTicket.dstStation, distance);
	if (returnCode != EN_RETURN_SUCC)
	{
		//����ַ���
		GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);
		return;
	}

	 //��ȡ����վ���Ļ���Ʊ��  GetBasePrice
	basePrice = GetBasePrice(distance);
	if (basePrice < 0)   //����յ��ص����޷�����ʱ������ʾΪ�ڲ�����
	{
		returnCode = EN_RETURN_INNER_ERR;
		GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);
		return;
	}
	

	//�쵥�̿� AssignCard
	returnCode = AssignCard(cardNo, EN_CARD_TYPE_SINGLE, basePrice);

	//���۳ɹ���񶼻������Ϣ �ɹ�������returnCode������
	//����ַ���
	

	GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);

	return;
}