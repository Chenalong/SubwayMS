#include "stdafx.h"
#include <iostream>
#include  <sstream>
#include "subwayMacro.h"
#include "include/basePrice.h"
using namespace std;

/*
@ ��ȡ����Ʊ��, ������վ�����վ��֮��������̷ּ�����
@ -1, ��ѯ����Ʊ��ʧ��; ����, ����Ʊ��
*/
int GetBasePrice(unsigned int meters)
{
	int price = -2;

	if (meters == 0)
		price = -1;
	else if (meters <= 3000)
		price = 2;
	else if (meters <= 5000)
		price = 3;
	else if (meters <= 10000)
		price = 4;
	else
		price = 5;

	return price;
}