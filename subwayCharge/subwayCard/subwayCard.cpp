#include "stdafx.h"
#include <iostream>
#include "list.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
using namespace std;


CARD *cardInfoArray[100];
int cardCount = 0;
queue<unsigned int> cardNumQueue;


/*
@ ��ʼ�����п���Ϣ
@ ����ֵ: ��
*/
void InitCardManagerInfo()
{
	InitCardQueue(cardNumQueue);
}

/*
@ ���������俨�źͿ���Ϣ
@ ��Σ�enCard,������; charge: ��ֵ
@ ����: cardNo, ����Ŀ���
@ ����ֵ: EN_RETURN_SUCC������ɹ�; EN_RETURN_CARD_OVERLOW, ����ʧ��;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge)
{
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	CARD *card = new CARD(cardNo, enCard, charge);
	returnCode = GetAssignedCardNum(cardNo);
	if (EN_RETURN_SUCC != returnCode)
	{
		return returnCode;
	}

	cardInfoArray[cardNo] = card;//������ϣ����������Ŀ�����

	return EN_RETURN_SUCC;
}

/*
@ ��ֵ
@ ��Σ�cardNo,����; recharge: ��ֵ
@ ����: ��
@ ����ֵ: EN_RETURN_SUCC���ɹ�; ����, ʧ��;
*/
EN_RETURN_CODE RechargeCard(unsigned int cardNo, unsigned int recharge)
{

	return EN_RETURN_SUCC;
}

/*
@ ��ȡ�����
@ ��Σ�cardNo,����;
@ ����: balance: ���
		enCard:  ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, ʧ��;
*/
EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard)
{

	return EN_RETURN_SUCC;
}

/*
@ ���۷�
@ ��Σ�cardNo,����; enCard, ������; deductPrice, �۷�Ʊ��
@ ����: balance, �۷Ѻ�����
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, EN_RETURN_BALANCE_NOT_ENOUGH, ʧ��;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance)
{

	return EN_RETURN_SUCC;
}

/*
@ ɾ������Ϣ
@ ��Σ�cardNo,����;
@ ����: ��
@ ����ֵ: 0���ɹ�; -1, ʧ��;
*/
int DeleteCard(unsigned int cardNo)
{

	return 0;
}

/*
@ ��ȡ�������ַ���
@ ��Σ�enCard,������;
@ ����: ��
@ ����ֵ: �������ַ���;
*/
char* GetCardTypeStr(EN_CARD_TYPE enCard)
{
	switch (enCard)
	{
		case   EN_CARD_TYPE_SINGLE:
			return "���̿�";
			break;
		case   EN_CARD_TYPE_ELDER:
			return "���꿨";
			break;
		case   EN_CARD_TYPE_NOMAL:
			return "��ͨ��";
			break;
		default:
			return nullptr;
	}

}

/*
@ ���ݿ������ַ���, ʶ������
@ ��Σ�cardType,      �������ַ���;
@ ����: enCard,        ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INPUT_INVALID_CARDTYPE, ʧ��;
*/
EN_RETURN_CODE GetCardType(char cardType[], EN_CARD_TYPE &enCard)
{


	return EN_RETURN_SUCC;
}

void InitCardQueue(queue<unsigned int> &cardNumQueue)
{
	int index = 0;
	for (; index < CARDNUM; ++index)
	{
		cardNumQueue.push(index);
	}
}

EN_RETURN_CODE GetAssignedCardNum(unsigned int &cardNo)
{
	//�����зǿգ��Ž��п��ŷ���
	if (cardNumQueue.size() < 1)
		return EN_RETURN_CARD_OVERLOW;
	else
	{
		cardNo = cardNumQueue.front();
		cardNumQueue.pop();
		return EN_RETURN_SUCC;
	}
}