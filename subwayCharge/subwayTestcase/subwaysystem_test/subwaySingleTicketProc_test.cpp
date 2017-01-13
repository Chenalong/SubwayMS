#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"

#include "subwayLine.h"
#include "subwayCommand\subwayCmdProc\include\subwaySingleTicketProc.h"
using namespace testing;


class subwaySingleTicketProcTest : public testing::Test
{
public:
	//�����׼����¼�
	//�ڲ������а�������������ǰ����һ��
	static void SetUpTestCase()
	{
		cout << " -----------��ʼ���У�subwaySingleTicketProcTest-----------------" << endl;
		InitSubwayLine();
		SetDefaultLine();
		//DeleteAllCardInfo();

	}

	//�ڲ������а�������������ȫ�����н���������һ��
	static void TearDownTestCase()
	{
		cout << " -----------�������У�subwaySingleTicketProcTest-----------------" << endl;
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


//�����������ɹ����򵥳�Ʊ
// "r   s s0 s1";

TEST_F(subwaySingleTicketProcTest, ProcCreateSingleTicketCmd_StationSuccessTest) {


	UN_CMD unCmd;
	unCmd.stCmdSingleTicket.cmd[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[1] = '0';
	unCmd.stCmdSingleTicket.srcStation[2] = '0';
	unCmd.stCmdSingleTicket.srcStation[3] = '0';

	unCmd.stCmdSingleTicket.dstStation[0] = 'S';
	unCmd.stCmdSingleTicket.dstStation[1] = '0';
	unCmd.stCmdSingleTicket.dstStation[2] = '0';
	unCmd.stCmdSingleTicket.dstStation[3] = '1';

	char result[MAX_SEND_BUFFER_LENGTH];
	string expectStr = "���򵥳�Ʊ<�ɹ�><����=0><������=���̿�><���=2>";
	ProcCreateSingleTicketCmd(unCmd, result);
	string resultStr(&result[0], &result[strlen(result)]);
	//cout << "------------------expectStr="<< expectStr <<endl;
	//cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr, resultStr);
}

//�������������򵥳�Ʊʧ��  ����վ������
// "r   s s100 s1";

TEST_F(subwaySingleTicketProcTest, ProcCreateSingleTicketCmd_Station2NotExitTest) {

	UN_CMD unCmd;
	unCmd.stCmdSingleTicket.cmd[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[1] = '0';
	unCmd.stCmdSingleTicket.srcStation[2] = '0';
	unCmd.stCmdSingleTicket.srcStation[3] = '0';

	unCmd.stCmdSingleTicket.dstStation[0] = 'S';
	unCmd.stCmdSingleTicket.dstStation[1] = '1';
	unCmd.stCmdSingleTicket.dstStation[2] = '0';
	unCmd.stCmdSingleTicket.dstStation[3] = '1';

	char result[MAX_SEND_BUFFER_LENGTH];

	string expectStr = "���򵥳�Ʊ<ʧ��><ʧ��ԭ��=��Ч�ĵ���վ>";
	
	ProcCreateSingleTicketCmd(unCmd, result);
	string resultStr(&result[0], &result[strlen(result)]);
	//cout << "------------------expectStr=" << expectStr << endl;
	//cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr, resultStr);
}

//�������������򵥳�Ʊʧ��  ��������
// "r   s s100 s1";

TEST_F(subwaySingleTicketProcTest, ProcCreateSingleTicketCmd_Station1NotExitTest) {

	UN_CMD unCmd;
	unCmd.stCmdSingleTicket.cmd[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[1] = '1';
	unCmd.stCmdSingleTicket.srcStation[2] = '0';
	unCmd.stCmdSingleTicket.srcStation[3] = '0';

	unCmd.stCmdSingleTicket.dstStation[0] = 'S';
	unCmd.stCmdSingleTicket.dstStation[1] = '0';
	unCmd.stCmdSingleTicket.dstStation[2] = '0';
	unCmd.stCmdSingleTicket.dstStation[3] = '1';

	char result[MAX_SEND_BUFFER_LENGTH];

	string expectStr= "���򵥳�Ʊ<ʧ��><ʧ��ԭ��=��Ч�ĵ���վ>";
	ProcCreateSingleTicketCmd(unCmd, result);
	string resultStr(&result[0], &result[strlen(result)]);
	//cout << "------------------expectStr=" << expectStr << endl;
	//cout << "------------------resultStr=" << resultStr << endl;
	EXPECT_EQ(expectStr, resultStr);
}

TEST_F(subwaySingleTicketProcTest, ProcCreateSingleTicketOutOfRangeTest) {

	UN_CMD unCmd;
	unCmd.stCmdSingleTicket.cmd[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[0] = 'S';
	unCmd.stCmdSingleTicket.srcStation[1] = '0';
	unCmd.stCmdSingleTicket.srcStation[2] = '0';
	unCmd.stCmdSingleTicket.srcStation[3] = '2';

	unCmd.stCmdSingleTicket.dstStation[0] = 'S';
	unCmd.stCmdSingleTicket.dstStation[1] = '0';
	unCmd.stCmdSingleTicket.dstStation[2] = '0';
	unCmd.stCmdSingleTicket.dstStation[3] = '1';

	char result[MAX_SEND_BUFFER_LENGTH];	
	string expectStr = "���򵥳�Ʊ<ʧ��><ʧ��ԭ��=����Ŀ�����ϵͳ����>";

	ProcCreateSingleTicketCmd(unCmd, result);
	for (int i = 0; i < 200; i++)  ProcCreateSingleTicketCmd(unCmd, result);  //��100��
	ProcCreateSingleTicketCmd(unCmd, result);   //����100��
	string resultStr(&result[0], &result[strlen(result)]);
	/*cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;*/
	EXPECT_EQ(expectStr, resultStr);
}

#endif