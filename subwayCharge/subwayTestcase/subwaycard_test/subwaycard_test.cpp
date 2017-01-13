#if _SUBWAY_LLT
#include <gtest/gtest.h>
#include "mockcpp/mockcpp.hpp"
#include "subwayCard.h"

using namespace testing;

class subwayCardTest : public testing::Test
{
public:
  
    static void SetUpTestCase()     
    {
		cout <<" -----------��ʼ���У�subwayCardTest-----------------"<< endl;
		//��ʼ������Ϣ
//		InitCardManagerInfo();
    }   
    static void TearDownTestCase()
    {
//		DeleteAllCardInfo();
//		InitCardQueue(cardNumQueue);
		cout << " -----------�������У�subwayCardTest-----------------" << endl;
    }   
    void SetUp()
    {
		DeleteAllCardInfo();
		InitCardQueue();
    }

    
    void TearDown()
    {
         
     }
};


/*---------------�쿨��������1-2-----------------------*/
//��������1������ϵͳ������<100   
//��Σ����̿�  3  
//���أ�{,,,,,,}

TEST_F(subwayCardTest, AssignCard_CardMostNumTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	int charge = 3;
	unsigned int cardNo;
	EN_RETURN_CODE code;

	//ǰ100�ųɹ��쿨

	for (int i = 0; i < 100; i++) {
		code = AssignCard(cardNo, enCardType, charge);		
		EXPECT_EQ(code, EN_RETURN_SUCC);
	}
	//100�ź��޷�����
	for (int i = 0; i < 5; i++) {		
		code = CheckAvailCard();
		EXPECT_EQ(code, EN_RETURN_CARD_OVERLOW);
	}
}
//��������2�����̿� ���ŷ��䡢��ֵ����Ƿ���ȷ��   
//��Σ����̿�  5  
//���أ�{,,,,,,}
TEST_F(subwayCardTest, AssignCard_SucessSingleCardTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_SINGLE;
	unsigned int charge = 5;

	unsigned int cardNo;
	unsigned int current_balance;
	EN_CARD_TYPE currentCardType;

	EN_RETURN_CODE success_code = AssignCard(cardNo, enCardType, charge);  //�쿨

	EXPECT_EQ(success_code, EN_RETURN_SUCC);    //��������ȷ��
	EXPECT_TRUE(cardNo >= 0 && cardNo <= 99);      //���俨����ȷ��	

	GetCardInfo(cardNo, current_balance, currentCardType);   //��ֵ��Ŀ���������
	EXPECT_EQ(current_balance, charge);	       //��ֵ����Ƿ���ȷ
	EXPECT_EQ(currentCardType,enCardType);	   //���俨�����Ƿ���ȷ

}
//��������3����ͨ�� ���ŷ��䡢��ֵ����Ƿ���ȷ��   
//��Σ����̿� 100  
//���أ�{,,,,,,}
TEST_F(subwayCardTest, AssignCard_SucessNormalCardTest) {

	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	unsigned int charge = 100;

	unsigned int cardNo;
	unsigned int current_balance;
	EN_CARD_TYPE currentCardType;

	EN_RETURN_CODE success_code = AssignCard(cardNo, enCardType, charge);  //�쿨

	EXPECT_EQ(success_code, EN_RETURN_SUCC);    //��������ȷ��
	EXPECT_TRUE(cardNo >= 0 && cardNo <= 99);      //���俨����ȷ��	

	GetCardInfo(cardNo, current_balance, currentCardType);   //��ֵ��Ŀ���������
	EXPECT_EQ(current_balance, charge);	       //��ֵ����Ƿ���ȷ
	EXPECT_EQ(currentCardType, enCardType);	   //���俨�����Ƿ���ȷ

}

/*---------------��ͨ����ֵ��������1-4-----------------------*/
//��������1�� ��ȷ���г�ֵ
//��Σ�cardNo  recharge
//����ֵ��EN_RETURN_SUCC

TEST_F(subwayCardTest, RechargeCard_SuccessTest) {

	unsigned int cardNo;
	unsigned int current_balance;
	unsigned int charge = 100;
	unsigned int recharge = 100;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	EN_CARD_TYPE enCard;

	AssignCard(cardNo, enCardType, charge);  //�쿨
	EN_RETURN_CODE success_code = RechargeCard(cardNo, recharge);    //��ֵ100Ԫ	
	EXPECT_TRUE(EN_RETURN_SUCC == success_code);  //�������Ƿ���ȷ
	GetCardInfo(cardNo, current_balance, enCard);   //��ֵ��Ŀ����
	EXPECT_TRUE(200 == current_balance);	   //��ֵ����Ƿ���ȷ

}


//��������4�����Գ�ֵ�ܽ�� 0-999

TEST_F(subwayCardTest, RechargeCard_reChargeMoneyTest) {

	unsigned int cardNo;
	unsigned int current_balance;
	unsigned int charge = 100;
	unsigned int recharge = 100;
	EN_CARD_TYPE enCardType = EN_CARD_TYPE_NOMAL;
	EN_RETURN_CODE code;

	AssignCard(cardNo, enCardType, charge);  //�쿨 100

	code = RechargeCard(cardNo, 10);   //����ֵ   110
	EXPECT_EQ(EN_RETURN_SUCC, code);
	code = RechargeCard(cardNo,20);   //����ֵ   130
	EXPECT_EQ(EN_RETURN_SUCC, code);
	code = RechargeCard(cardNo, 100);   //����ֵ   230
	EXPECT_EQ(EN_RETURN_SUCC, code);
	code = RechargeCard(cardNo, 900);   //����ֵ   1130
	EXPECT_EQ(EN_RETURN_RECHARGE_OVERFLOW, code);
}

/*-----------------------��ѯ����Ϣ��������1-3-------------------------------*/

//��������1�� ��ȷ������ȷ��Ϣ����ͨ����  
//��Σ�cardNo  
//���Σ���� balance   ������  cardtype
TEST_F(subwayCardTest, GetCardInfo_SuccessNomalTest) {

	
	unsigned int cardNo;
	unsigned int expect_balance= 10;
	unsigned int balance;
	EN_CARD_TYPE enCard;

	AssignCard(cardNo, EN_CARD_TYPE_NOMAL, expect_balance);	
	EN_RETURN_CODE success_code = GetCardInfo(cardNo, balance, enCard);

	EXPECT_TRUE(success_code == EN_RETURN_SUCC);    //����ֵ�Ƿ���ȷ
	EXPECT_TRUE(enCard == EN_CARD_TYPE_NOMAL);       //�������Ƿ���ȷ
	EXPECT_TRUE(balance == expect_balance);         //����Ƿ���ȷ
}

//��������2�� ��ȷ������ȷ��Ϣ�����̿���  
//��Σ�cardNo  
//���Σ���� balance   ������  cardtype
TEST_F(subwayCardTest, GetCardInfo_SuccessSingleTest) {

	unsigned int cardNo;
	unsigned int expect_balance = 3;
	AssignCard(cardNo, EN_CARD_TYPE_SINGLE, expect_balance);

	unsigned int balance;
	EN_CARD_TYPE enCard;
	EN_RETURN_CODE success_code = GetCardInfo(cardNo, balance, enCard);

	EXPECT_TRUE(success_code == EN_RETURN_SUCC);    //����ֵ�Ƿ���ȷ
	EXPECT_TRUE(enCard == EN_CARD_TYPE_SINGLE);       //�������Ƿ���ȷ
	EXPECT_TRUE(balance == expect_balance);         //����Ƿ���ȷ
}

//��������3�� ���뿨������  
//��Σ�cardNo  
//���Σ���� balance   ������  cardtype

TEST_F(subwayCardTest, GetCardInfo_ValidCardTest) {

	unsigned int cardNo = 120;
	unsigned int balance;
	EN_CARD_TYPE enCard = EN_CARD_TYPE_SINGLE;

	EN_RETURN_CODE fail_code = GetCardInfo(cardNo, balance, enCard);
	EXPECT_EQ(EN_RETURN_INVALID_CARD, fail_code);
}


/*-----------------------�۷ѹ��ܲ�������1-3-------------------------------*/

//��������1�� ��ͨ����ȷ���п۷� ,��������ȷ��Ϣ���� 
//��Σ� cardNo,����;
//         card, ������; 
//  deductPrice, �۷�Ʊ��   
//����: balance, �۷Ѻ�����
TEST_F(subwayCardTest, DeductCard_NomalSuccessTest) {

	//�������
	unsigned int cardNo;
	unsigned int balance = 100;  //�����
	unsigned int deductPrice = 5;   //�۷�5
	EN_CARD_TYPE enCard= EN_CARD_TYPE_BUTT;
	AssignCard(cardNo, EN_CARD_TYPE_NOMAL, balance);

	//�ڴ��۷Ѻ����
	unsigned int expect_balance = 95;
	//�۷Ѻ���������
	unsigned int return_balance=0;
	//ʵ�ʲ�ѯ�Ŀ۷Ѻ����
	unsigned int current_balance=0;

	EN_RETURN_CODE success_code = DeductCard(cardNo, enCard, deductPrice, balance);   //�۷�
	GetCardInfo(cardNo, current_balance, enCard); //��ȡ�۷Ѻ���Ϣ

	EXPECT_EQ(success_code, EN_RETURN_SUCC);     //�������Ƿ���ȷ
	EXPECT_EQ(current_balance, expect_balance);     //  �Ƿ���ȷ�޸Ŀ����	
}

////��������2�� ���̿���ȷ���п۷� ,��������ȷ��Ϣ���� 
////��Σ� cardNo,����;
////         card, ������; 
////  deductPrice, �۷�Ʊ��   
////����: balance, �۷Ѻ�����
//
TEST_F(subwayCardTest, DeductCard_SingleSuccessTest) {

//�������
unsigned int cardNo;
unsigned int balance = 5;  //�۷�ǰ�����
unsigned int deductPrice = 5;   //�۷�5Ԫ
EN_CARD_TYPE enCard;
AssignCard(cardNo, EN_CARD_TYPE_SINGLE, balance);

//�ڴ��۷Ѻ����
unsigned int expect_balance = 0;

//ʵ�ʲ�ѯ�Ŀ۷Ѻ����
unsigned int current_balance;

GetCardInfo(cardNo, balance, enCard);   //��ȡԭʼ����Ϣ
EN_RETURN_CODE success_code = DeductCard(cardNo, enCard, deductPrice, balance);   //�۷�
GetCardInfo(cardNo, current_balance, enCard); //��ȡ�۷Ѻ���Ϣ

EXPECT_EQ(EN_RETURN_SUCC, success_code);     //�������Ƿ���ȷ
//EN_RETURN_BALANCE_TOO_LOW
EXPECT_EQ(current_balance, expect_balance);     //  �Ƿ���ȷ�޸Ŀ����
}
//
//��������3�� ��ͨ����������  1Ԫ
//��Σ� cardNo,����;
//         card, ������; 
//  deductPrice, �۷�Ʊ��   
//����: balance, �۷Ѻ�����

TEST_F(subwayCardTest, DeductCard_NOMALShortOfMoneyTest) {

	unsigned int cardNo;
	unsigned int balance = 0;  //�۷�ǰ�����
	unsigned int deductPrice = 5;   //�۷�5Ԫ
	EN_CARD_TYPE enCard = EN_CARD_TYPE_BUTT;
	unsigned int current_balance;  //ʵ�ʲ�ѯ�Ŀ۷Ѻ����
	AssignCard(cardNo, EN_CARD_TYPE_NOMAL, balance);
	
	EN_RETURN_CODE fail_code = DeductCard(cardNo, enCard, deductPrice, balance);   //�۷�
	GetCardInfo(cardNo, current_balance, enCard); //��ȡ�۷Ѻ���Ϣ

	EXPECT_EQ(EN_RETURN_BALANCE_NOT_ENOUGH, fail_code);     //�������Ƿ���ȷ
	EXPECT_EQ(current_balance, 0);     //  �Ƿ���ȷ�޸Ŀ����
}


//��������4�� ���̿���������  1Ԫ
//��Σ� cardNo,����;
//         card, ������; 
//  deductPrice, �۷�Ʊ��   
//����: balance, �۷Ѻ�����

TEST_F(subwayCardTest, DeductCard_SingleShortOfMoneyTest) {

	unsigned int cardNo;
	unsigned int balance = 0;  //�۷�ǰ�����
	unsigned int deductPrice = 5;   //�۷�5Ԫ
	EN_CARD_TYPE enCard = EN_CARD_TYPE_BUTT;
	unsigned int current_balance;  //ʵ�ʲ�ѯ�Ŀ۷Ѻ����
	AssignCard(cardNo, EN_CARD_TYPE_SINGLE, balance);

	EN_RETURN_CODE fail_code = DeductCard(cardNo, enCard, deductPrice, balance);   //�۷�
	GetCardInfo(cardNo, current_balance, enCard); //��ȡ�۷Ѻ���Ϣ

	EXPECT_EQ(EN_RETURN_BALANCE_NOT_ENOUGH, fail_code);     //�������Ƿ���ȷ
	EXPECT_EQ(current_balance, 0);     //  �Ƿ���ȷ�޸Ŀ����

}

#endif