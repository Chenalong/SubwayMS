#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"
#include "subwayLine.h"
#include "../../subwayCommand/subwayCmdProc/include/subwayCreateCardProc.h"

using namespace testing;


class subwayCreateCardProcTest : public testing::Test
{
public:
	//�����׼����¼�
	//�ڲ������а�������������ǰ����һ��
	static void SetUpTestCase()
	{
		cout << " -----------��ʼ���У�subwayCreateCardProcTest-----------------" << endl;
	}

	//�ڲ������а�������������ȫ�����н���������һ��
	static void TearDownTestCase()
	{
		cout << " -----------�������У�subwayCreateCardProcTest-----------------" << endl;
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

/*
@ ������ͨ��
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
//void ProcCreateCardCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH]);// ��ͨ+ ����

//��һ����ͨ��
TEST_F(subwayCreateCardProcTest, ProcQueryLineCmd_NormalSucessTest) {

	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	EN_CARD_TYPE cardType = EN_CARD_TYPE_BUTT;

	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr="����˳���<�ɹ�><����=0><������=��ͨ��><���=100>";

	UN_CMD unCmd ;
	unCmd.stCmdCreateCard.cmd[0] = 'B';
	unCmd.stCmdCreateCard.cardType[0] = 'C';
	unCmd.stCmdCreateCard.cardCharge = 100 ;	
	ProcCreateCardCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);


}

//�������ʹ���
TEST_F(subwayCreateCardProcTest, ProcQueryLineCmd_CardTypeFailTest) {

	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr= "����˳���<ʧ��><ʧ��ԭ��=���뿨���ʹ���>";

	UN_CMD unCmd;
	unCmd.stCmdCreateCard.cmd[0] = 'B';
	unCmd.stCmdCreateCard.cardType[0] = 'Z';
	unCmd.stCmdCreateCard.cardCharge = 100;
	ProcCreateCardCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);

}
//��ֵ������
TEST_F(subwayCreateCardProcTest, ProcQueryLineCmd_CardChargeFailTest) {

	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "����˳���<ʧ��><ʧ��ԭ��=�쿨���ֵ������������>";

	UN_CMD unCmd;
	unCmd.stCmdCreateCard.cmd[0] = 'B';
	unCmd.stCmdCreateCard.cardType[0] = 'C';
	unCmd.stCmdCreateCard.cardCharge = 1000;
	ProcCreateCardCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);

}
//�ﵽϵͳ����
TEST_F(subwayCreateCardProcTest, ProcQueryLineCmd_CardOutOfRangeTest) {

	EN_RETURN_CODE returnCode = EN_RETURN_SUCC;
	unsigned int cardNo = 0;
	char returnStr[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "����˳���<ʧ��><ʧ��ԭ��=����Ŀ�����ϵͳ����>";

	UN_CMD unCmd;
	unCmd.stCmdCreateCard.cmd[0] = 'B';
	unCmd.stCmdCreateCard.cardType[0] = 'C';
	unCmd.stCmdCreateCard.cardCharge = 100;
	for (int i = 0; i < 100; i++) ProcCreateCardCmd(unCmd, returnStr);  //��100��
	ProcCreateCardCmd(unCmd, returnStr);
	string resultStr(&returnStr[0], &returnStr[strlen(returnStr)]);
	EXPECT_EQ(expectStr, resultStr);

}
#endif