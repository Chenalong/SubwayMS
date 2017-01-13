#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"
#include "subwayLine.h"
#include "../../subwayCommand/subwayCmdProc/include/subwayDeductProc.h";
#include "subwayPrice.h"

using namespace testing;

class subwayDeductProcTest : public testing::Test
{
public:
	//�����׼����¼�
	//�ڲ������а�������������ǰ����һ��
	static void SetUpTestCase()
	{
		cout << " -----------��ʼ���У�subwayDeductProcTest-----------------" << endl;
		InitSubwayLine();
		SetDefaultLine();
		DeleteAllCardInfo();

	}

	//�ڲ������а�������������ȫ�����н���������һ��
	static void TearDownTestCase()
	{
		cout << " -----------�������У�subwayDeductProcTest-----------------" << endl;
		DeleteAllCardInfo();
	}

	//��������������¼�
	//�������е�ÿ��������ʼ����ǰ����һ��
	void SetUp()
	{
		//Ϊ��С���Բ�����������֮���Ӱ�죬����ɽ���һЩ��ʼ������
		DeleteAllCardInfo();
		InitCardManagerInfo();
	}

	//��������ÿ����������������һ��
	void TearDown()
	{
		//�ɽ���һЩ��̬�ڴ���ͷŲ���
	}
};

//������ͨ���۷�
TEST_F(subwayDeductProcTest, subwayDeductProcTest_NormalSucessTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int charge = 100;
	unsigned int cardNo;
	unsigned int balance = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "�˳����۷�<�ɹ�><����=0><������=��ͨ��><���=98>";
     AssignCard(cardNo, enCardType, charge);  //�쿨

	UN_CMD un_Cmd;
	un_Cmd.stCmdDeduct.cmd[0] = 'C';
	un_Cmd.stCmdDeduct.enterStation[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[1] = '1';
	un_Cmd.stCmdDeduct.exitStation[0] = 'S';
	un_Cmd.stCmdDeduct.exitStation[1] = '0';
	un_Cmd.stCmdDeduct.cardNo = cardNo;
	un_Cmd.stCmdDeduct.enterTime.hour=11;
	un_Cmd.stCmdDeduct.enterTime.minutes=0;
	un_Cmd.stCmdDeduct.exitTime.hour=14;
	un_Cmd.stCmdDeduct.exitTime.minutes=0;
	ProcDeductCmd(un_Cmd, returnStr);
	//string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr,resultStr);
}
//������ͨ���۷�����
TEST_F(subwayDeductProcTest, subwayDeductProcTest_NormalLowBalanceFaliTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int charge = 3;
	unsigned int cardNo;
	unsigned int balance = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "�˳����۷�<ʧ��><����=0><������=��ͨ��><���=3><ʧ��ԭ��=����>";
	AssignCard(cardNo, enCardType, charge);  //�쿨

	UN_CMD un_Cmd;
	un_Cmd.stCmdDeduct.cmd[0] = 'C';
	un_Cmd.stCmdDeduct.enterStation[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[1] = '1';
	un_Cmd.stCmdDeduct.enterStation[2] = '6';
	un_Cmd.stCmdDeduct.exitStation[0] = 'S';
	un_Cmd.stCmdDeduct.exitStation[1] = '0';
	un_Cmd.stCmdDeduct.cardNo = cardNo;
	un_Cmd.stCmdDeduct.enterTime.hour = 11;
	un_Cmd.stCmdDeduct.enterTime.minutes = 0;
	un_Cmd.stCmdDeduct.exitTime.hour = 14;
	un_Cmd.stCmdDeduct.exitTime.minutes = 0;
	ProcDeductCmd(un_Cmd, returnStr);
	
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);
}
//���Ե��̿��۷�
TEST_F(subwayDeductProcTest, subwayDeductProcTest_SingleCardSucessTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_SINGLE;
	UN_CMD un_Cmd;
	unsigned int distance = 0;
	int basePrice = 2;
	unsigned int cardNo;
	AssignCard(cardNo, enCardType, basePrice);  //�쿨

	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "�˳����۷�<�ɹ�><����=0><������=���̿�><���=0>";

	un_Cmd.stCmdDeduct.cmd[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[1] = '1';
	un_Cmd.stCmdDeduct.exitStation[0] = 'S';
	un_Cmd.stCmdDeduct.exitStation[1] = '0';
	un_Cmd.stCmdDeduct.cardNo = cardNo;
	un_Cmd.stCmdDeduct.enterTime.hour = 11;
	un_Cmd.stCmdDeduct.enterTime.minutes = 0;
	un_Cmd.stCmdDeduct.exitTime.hour = 14;
	un_Cmd.stCmdDeduct.exitTime.minutes = 0;
	ProcDeductCmd(un_Cmd, returnStr);
	
	//string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);

	EXPECT_EQ(expectStr, resultStr);
}
//���Ե��̿��۷�����
TEST_F(subwayDeductProcTest, subwayDeductProcTest_SingleTicketLowBalanceFaliTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_SINGLE;
	UN_CMD un_Cmd;
	unsigned int distance = 0;
	int basePrice = 2;
	unsigned int cardNo;
	AssignCard(cardNo, enCardType, basePrice);  //�쿨

	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "�˳����۷�<ʧ��><����=0><������=���̿�><���=2><ʧ��ԭ��=����>";

	un_Cmd.stCmdDeduct.cmd[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[0] = 'S';
	un_Cmd.stCmdDeduct.enterStation[1] = '1';
	un_Cmd.stCmdDeduct.enterStation[2] = '6';
	un_Cmd.stCmdDeduct.exitStation[0] = 'S';
	un_Cmd.stCmdDeduct.exitStation[1] = '0';
	un_Cmd.stCmdDeduct.cardNo = cardNo;
	un_Cmd.stCmdDeduct.enterTime.hour = 11;
	un_Cmd.stCmdDeduct.enterTime.minutes = 0;
	un_Cmd.stCmdDeduct.exitTime.hour = 14;
	un_Cmd.stCmdDeduct.exitTime.minutes = 0;
	ProcDeductCmd(un_Cmd, returnStr);

	//string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	//cout << "------------------expectStr=" << expectStr << endl;
	//cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr, resultStr);
}

#endif
