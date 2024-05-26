#include <stdio.h>
#define _START_MONEY 1000000

void service1()
{
	int k;
	extern int user_site[2];
	extern int user_money[2];
	extern int land[23];
	extern int country_money[23];

	for (k = 0; k < 6; k++)
	{
		if ((user_site[0] % 26 == k + 1) && (land[k] == 1))
		{
			user_money[0] += country_money[k] / 5;
			printf("땅세를 받아 땅값의 20퍼센트에 해당하는 금액을 얻습니다. 획득금액: %d\n", country_money[k] / 5);
		}
	}
	for (k = 7; k < 10; k++)
	{
		if ((user_site[0] % 26 == k + 1) && (land[k - 1] == 1))
		{
			user_money[0] += country_money[k - 1] / 5;
			printf("땅세를 받아 땅값의 20퍼센트에 해당하는 금액을 얻습니다. 획득금액: %d\n", country_money[k - 1] / 5);
		}

	}
	for (k = 11; k < 25; k++)
	{
		if ((user_site[0] % 26 == k + 1) && (land[k - 2] == 1))
		{
			user_money[0] += country_money[k - 2] / 5;
			printf("땅세를 받아 땅값의 20퍼센트에 해당하는 금액을 얻습니다. 획득금액: %d\n", country_money[k - 2] / 5);
		}

	}





}
void service2()
{
	int k;
	extern int user_site[2];
	extern int user_money[2];
	extern int land[23];
	extern int country_money[23];

	for (k = 0; k < 6; k++)
	{
		if ((user_site[1] % 26 == k + 1) && (land[k] == 2))
		{
			user_money[1] += country_money[k] / 5;
			printf("땅세를 받아 땅값의 20퍼센트에 해당하는 금액을 얻습니다. 획득금액: %d\n", country_money[k] / 5);
		}
	}
	for (k = 7; k < 10; k++)
	{
		if ((user_site[1] % 26 == k + 1) && (land[k - 1] == 2))
		{
			user_money[1] += country_money[k - 1] / 5;
			printf("땅세를 받아 땅값의 20퍼센트에 해당하는 금액을 얻습니다. 획득금액: %d\n", country_money[k - 1] / 5);
		}
	}
	for (k = 11; k < 25; k++)
	{
		if ((user_site[1] % 26 == k + 1) && (land[k - 2] == 2))
		{
			user_money[1] += country_money[k - 2] / 5;
			printf("땅세를 받아 땅값의 20퍼센트에 해당하는 금액을 얻습니다. 획득금액: %d\n", country_money[k - 2] / 5);
		}
	}
}
void size_s()
{
	int a;
	int size1 = 0;
	int size2 = 0;
	int price1 = 0;
	int price2 = 0;
	extern int land[23];

	for (a = 0; a < 23; a++)
	{
		if (land[a] == 1)
			size1++;
		else if (land[a] == 2)
			size2++;
	}
	printf("사용자1의 땅의갯수는 %d \n", size1);
	printf("사용자2의 땅의갯수는 %d \n", size2);


}
void price()
{
	int a;
	int size1 = 0;
	int size2 = 0;
	int price1;
	int price2;
	extern int land[23];
	extern int user_money[2];
	extern int user_site[2];

	for (a = 0; a < 23; a++)
	{
		if (land[a] == 1)
			size1++;
		else if (land[a] == 2)
			size2++;
	}
	price1 = 50000 * size1;
	price2 = 50000 * size2;
	if ((user_site[0] % 26) == 0)
	{
		user_money[0] += price1;
		printf("출발지점 특혜! 땅하나당 5만원씩 추가됩니다. 획득금액: %d\n", price1);
	}
	else if ((user_site[1] % 26) == 0)
	{
		user_money[1] += price2;
		printf("출발지점 특혜! 땅하나당 5만원씩 추가됩니다. 획득금액: %d\n", price2);
	}
}