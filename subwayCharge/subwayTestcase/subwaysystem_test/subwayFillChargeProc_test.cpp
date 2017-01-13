#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"
#include "subwayLine.h"
#include "../../subwayCommand/subwayCmdProc/include/subwayFillChargeProc.h"

using namespace testing;

class subwayFillChargeProcTest : public testing::Test
{
public:
	//�����׼����¼�
	//�ڲ������а�������������ǰ����һ��
	static void SetUpTestCase()
	{
		cout << " -----------��ʼ���У�subwayFillChargeProcTest-----------------" << endl;
		InitSubwayLine();
		SetDefaultLine();
	}

	//�ڲ������а�������������ȫ�����н���������һ��
	static void TearDownTestCase()
	{
		cout << " -----------�������У�subwayFillChargeProcTest-----------------" << endl;
		//		DeleteAllCardInfo();
	}

	//��������������¼�
	//�������е�ÿ��������ʼ����ǰ����һ��
	void SetUp()
	{
		DeleteAllCardInfo();
		InitCardQueue();
	}

	//��������ÿ����������������һ��
	void TearDown()
	{
		//�ɽ���һЩ��̬�ڴ���ͷŲ���
	}
};
//��ͨ����ֵ 100Ԫ
TEST_F(subwayFillChargeProcTest, subwayFillChargeProcTest_NormalSucessTest) {

	unsigned int pre_balance= 100;  //ԭ���
	unsigned int charge = 100;    //��ֵ���
	unsigned int cardNo;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int current_balance;
	EN_CARD_TYPE current_cardType;
	AssignCard(cardNo, enCardType, pre_balance);

	UN_CMD unCmd;
	unCmd.stCmdFillCharge.cardCharge = charge;
	unCmd.stCmdFillCharge.cardNo = cardNo;
	unCmd.stCmdFillCharge.cmd[0] = 'F';
    char returnStr[MAX_SEND_BUFFER_LENGTH];


	ProcFillChargeCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string expectStr = "�˳�����ֵ<�ɹ�><����=0><������=��ͨ��><���=200>";
	EXPECT_EQ(expectStr, resultStr);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
	GetCardInfo(cardNo, current_balance, current_cardType);
	EXPECT_EQ(200, current_balance);
	EXPECT_EQ(EN_CARD_TYPE_NOMAL, current_cardType);
}

//���̿����ܳ�ֵ
TEST_F(subwayFillChargeProcTest, subwayFillChargeProcTest_SingleCardCantRechangeTest) {

	unsigned int pre_balance = 5;  //ԭ���
	unsigned int charge = 100;    //��ֵ���
	unsigned int cardNo;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_SINGLE;
	unsigned int current_balance;
	EN_CARD_TYPE current_cardType;
	AssignCard(cardNo, enCardType, pre_balance);

	UN_CMD unCmd;
	unCmd.stCmdFillCharge.cardCharge = charge;
	unCmd.stCmdFillCharge.cardNo = cardNo;
	unCmd.stCmdFillCharge.cmd[0] = 'F';
	char returnStr[MAX_SEND_BUFFER_LENGTH];

	
	ProcFillChargeCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string expectStr = "�˳�����ֵ<ʧ��><����=0><������=���̿�><ʧ��ԭ��=���̿����ܳ�ֵ>";
	EXPECT_EQ(expectStr, resultStr);
	GetCardInfo(cardNo,current_balance,current_cardType);
	EXPECT_EQ(5,current_balance);
	EXPECT_EQ(EN_CARD_TYPE_SINGLE, current_cardType);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
}
//��Ч�Ŀ�����
TEST_F(subwayFillChargeProcTest, subwayFillChargeProcTest_ValidCardTest) {

	unsigned int pre_balance = 5;  //ԭ���
	unsigned int charge = 100;    //��ֵ���
	unsigned int cardNo;

	UN_CMD unCmd;
	unCmd.stCmdFillCharge.cardCharge = charge;
	unCmd.stCmdFillCharge.cardNo = 100;
	unCmd.stCmdFillCharge.cmd[0] = 'F';
	char returnStr[MAX_SEND_BUFFER_LENGTH];

	ProcFillChargeCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string expectStr = "�˳�����ֵ<ʧ��><����=100><������=��Ч������><ʧ��ԭ��=��Ч�ĵ�����>";
	EXPECT_EQ(expectStr, resultStr);

	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
}
//��ֵ��������
TEST_F(subwayFillChargeProcTest, subwayFillChargeProcTest_OutOfMoneyTest) {

	unsigned int pre_balance = 100;  //ԭ���
	unsigned int charge = 900;    //��ֵ���
	unsigned int cardNo;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int current_balance;
	EN_CARD_TYPE current_cardType;
	AssignCard(cardNo, enCardType, pre_balance);

	UN_CMD unCmd;
	unCmd.stCmdFillCharge.cardCharge = charge;
	unCmd.stCmdFillCharge.cardNo = cardNo;
	unCmd.stCmdFillCharge.cmd[0] = 'F';
	char returnStr[MAX_SEND_BUFFER_LENGTH];


	ProcFillChargeCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string expectStr = "�˳�����ֵ<ʧ��><����=0><������=��ͨ��><ʧ��ԭ��=�쿨���ֵ������������>";
	EXPECT_EQ(expectStr, resultStr);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
	GetCardInfo(cardNo, current_balance, current_cardType);
	EXPECT_EQ(100, current_balance);
	EXPECT_EQ(EN_CARD_TYPE_NOMAL, current_cardType);
}

#endif