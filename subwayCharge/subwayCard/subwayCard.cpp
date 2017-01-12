#include "stdafx.h"
#include <iostream>
#include "list.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
#include "../subwayPrice/subwayPrice.h"
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

	GetAssignedCardNum(cardNo);

	CARD *card = new CARD(cardNo, enCard, charge);
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
	if (recharge > 999 || recharge <= 0)
		return EN_RETURN_RECHARGE_OVERFLOW;

	unsigned int totalSum = cardInfoArray[cardNo]->getBalance() + recharge;

	if (totalSum > 999 || totalSum <= 0)
		return EN_RETURN_RECHARGE_OVERFLOW;

	cardInfoArray[cardNo]->setBalance(totalSum);
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
	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	if (cardNo > 99)
	{
		return EN_RETURN_INVALID_CARD;
	}
	if (cardInfoArray[cardNo] == nullptr)
	{
		return EN_RETURN_INVALID_CARD;
	}
	enCard = cardInfoArray[cardNo]->getType();
	balance = cardInfoArray[cardNo]->getBalance();

	return EN_RETURN_SUCC;
}

///*
//@ ��ȡ�����
//@ ��Σ�cardNo,����;
//@ ����: balance: ���
//		enCard:  ������
//@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, ʧ��;
//*/
//EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard)
//{
//	//�滻������
//	if (cardNo > 99 || cardNo < 0)
//		return EN_RETURN_INVALID_CARD;
//	
//	balance = cardInfoArray[cardNo]->getBalance();
//	enCard = cardInfoArray[cardNo]->getType();
//
//	return EN_RETURN_SUCC;
//}

/*
@ ���۷�
@ ��Σ�cardNo,����; enCard, ������; deductPrice, �۷�Ʊ��
@ ����: balance, �۷Ѻ�����
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_BALANCE_NOT_ENOUGH, ʧ��;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance)
{
	if (balance < deductPrice)
	{
		return EN_RETURN_BALANCE_NOT_ENOUGH;
	}
	balance = balance - deductPrice;
	cardInfoArray[cardNo]->setBalance(balance);

	if (balance <= 20)
	{
		return EN_RETURN_BALANCE_TOO_LOW;
	}

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
		return "��Ч������";
		break;
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
	if (cardType[0] == 'C' || cardType[0] == 'c')
	{
		enCard = EN_CARD_TYPE_NOMAL;
	}
	else if (cardType[0] == 'B' || cardType[0] == 'b')
	{
		enCard = EN_CARD_TYPE_ELDER;
	}
	else
		return EN_RETURN_INPUT_INVALID_CARDTYPE;

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

void GetAssignedCardNum(unsigned int &cardNo)
{
	//�����зǿգ��Ž��п��ŷ���
	cardNo = cardNumQueue.front();
	cardNumQueue.pop();
	cardCount++;             //�����ÿ���+1
	return;

	//�������ڲ���ϵͳ�ڵĿ���������У�飬У�����ϲ�ͨ������CheckAvailCard()ʵ�֣�
}


EN_RETURN_CODE CheckAvailCard()
{
	if (cardNumQueue.size() <= 0)
	{
		return EN_RETURN_CARD_OVERLOW;
	}
	else
	{
		return EN_RETURN_SUCC;
	}
}


bool CheckChargeValue(int chargeValue)
{
	if ((chargeValue >= 0) && (chargeValue <= 999))
		return true;
	else
		return false;
}


EN_RETURN_CODE CheckTime(ST_SUBWAY_TIME enterTime, ST_SUBWAY_TIME exitTime)
{
	int enterHour = enterTime.hour;
	int enterMinutes = enterTime.minutes;
	int exitHour = exitTime.hour;
	int exitMinutes = exitTime.minutes;
	if ((enterHour < 0) || (enterHour >= 24)
		|| (exitHour < 0) || (exitHour >= 24)
		|| (enterMinutes < 0) || (enterMinutes >= 60)
		|| (exitMinutes < 0) || (exitMinutes >= 60))
	{
		return EN_RETURN_INVALID_TIME;
	}
	else if ((enterHour * 60 + enterMinutes) >= (exitHour * 60 + exitMinutes))
	{
		return EN_RETURN_INVALID_TIME;
	}
	else
		return EN_RETURN_SUCC;
}

unsigned int CalDurationTime(ST_SUBWAY_TIME enterTime, ST_SUBWAY_TIME exitTime)
{
	int enterHour = enterTime.hour;
	int enterMinutes = enterTime.minutes;
	int exitHour = exitTime.hour;
	int exitMinutes = exitTime.minutes;
	unsigned int durationTime = (exitHour * 60 + exitMinutes) - (enterHour * 60 + enterMinutes);
	return durationTime;
}
