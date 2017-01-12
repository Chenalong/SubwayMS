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
@ ��ѯ������
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcQueryLineCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    //��ѯ���е����� GetLineInfo
	string output;
	GetLineInfo(output);
	int length = output.length();
	int copyLength = MinValue(length, MAX_SEND_BUFFER_LENGTH);//ʵ��string copy�ķ�����copy����Ϊ���泤����string���ȵĽ�Сֵ
	output.copy(returnStr, copyLength, 0);
    return;
}