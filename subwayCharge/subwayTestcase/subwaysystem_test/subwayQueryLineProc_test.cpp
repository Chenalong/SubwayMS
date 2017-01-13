#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"

#include "../../subwayCommand/subwayCmdProc/include/subwayQueryLineProc.h"
#include "subwayLine.h"

using namespace testing;

class subwayQueryLineProcTest : public testing::Test
{
public:
	//�����׼����¼�
	//�ڲ������а�������������ǰ����һ��
	static void SetUpTestCase()
	{
		cout << " -----------��ʼ���У�subwayQueryLineProc_test-----------------" << endl;
		InitSubwayLine();
		SetDefaultLine();
	}

	//�ڲ������а�������������ȫ�����н���������һ��
	static void TearDownTestCase()
	{
		cout << " -----------�������У�subwayQueryLineProc_test-----------------" << endl;
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


//��������1:   ��ѯ������·  ProcQueryLineCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])

TEST_F(subwayQueryLineProcTest, ProcQueryLineCmd_SucessTest) {

	char result[MAX_SEND_BUFFER_LENGTH];
	string expectStr="������·��S0<->S1<->S2<->S3<->S4<->S5<->S6<->S7<->S8<->S9<->S10<->S11<->S12<->S13<->S14<->S15<->S16";
	UN_CMD unCmd;
	unCmd.stCmdQueryLine.cmd[0] = 'L';

	//ProcQueryLineCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
	ProcQueryLineCmd(unCmd, result);
	string resultStr(&result[0], &result[99]);
	EXPECT_EQ(expectStr, resultStr);
	cout << "------------------expectStr=" << expectStr << endl;
	cout << "------------------resultStr=" << resultStr << endl;


}


#endif