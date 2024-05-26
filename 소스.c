#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "김준서 헤더파일.h"
#pragma warning(disable:4996)

#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define green SetConsoleTextAttribute(col, 0x0002);
#define wine SetConsoleTextAttribute(col, 0x0005);
#define white SetConsoleTextAttribute(col, 0x000f);
#define yellow SetConsoleTextAttribute(col, 0x000e);
#define blue SetConsoleTextAttribute(col, 0x0001);
#define sky SetConsoleTextAttribute(col, 0x000b);

#define _START_MONEY 1000000 //초기 플레이어 금액 지정
#define _PURCHASE_LAND_SCALE 2 //땅 매입할 때 몇 배로 구매할 지의 배수

void main_2(); //게임이 구동되는 함수
char map_name_user1(int x); //사용자1의 위치를 나타내는 함수
char map_name_user2(int x); //사용자2의 위치를 나타내는 함수
void play(int x);  //케이스문
void chance(int x); //찬스카드
void blackhole(int x, int y); //블랙홀
void ddang(int x, int y,int z, int w); //그 땅에 갔을 때의 상황 출력
void buying(int x, int y,int z); //사는 과정
void buying2(int x, int y); //사는 과정 추가한부분
void gotoxy(int x, int y);
void size();//유저들의 땅의 갯수를 나타내는 함수
void size_s();//실험함수
void price();//출발지점 월급 함수
void service();//자신의 땅에 도착시 일정 금액을 주는 함수
void service1();
void service2();
int land[23] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //
int cityland[23] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //땅의 소유권 표시
int country_money[23] = { 30000, 35000, 50000, 60000, 65000, 70000, 20000, 10000, 25000, 40000, 80000, 95000, 100000, 25000, 40000, 80000, 95000, 110000, 120000, 125000, 140000, 150000, 155000 };//각 지역들의 돈
int city_money[23] = { 3000, 3500, 5000, 6000, 6500, 7000, 2000, 1000, 2500, 4000, 8000, 9500, 10000, 2500, 4000, 8000, 9500, 11000, 12000, 12500, 14000, 15000, 15500 };//각 주택들의 돈 추가한부분
int user_site[2] = { 0, 0 }, i, t; //유저들의 위치
int user_money[2] = { _START_MONEY, _START_MONEY };//{ 1500000, 1500000 }; //유저들의 시작하는 돈 150만원
int isMuindo[2] = { 0, 0 }; //무인도인지 아닌지 검사하는 변수(최초초기화). 0이면 해당없음, 1이면 1턴쉼.
int* score;//점수
int a; //편의상 선언
void rank(int mode, int score);//순위
void move();//말의 이동
void map(int x);//맵
char user_name1[20];//유저이름
char user_name2[20];//유저이름

////////////////////////////////////////////////////////////////////////////////  
void main()///////////////////////////////////////////////////////////메인함수
{

	int no;
	system("mode con  cols=80 lines=50");////////////////////////콘솔창 크기


a:
	printf("\n\n\n\n\n\n\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 06);////////////이광은 추가사항 1번: 제목 변경 및 색깔 추가
	printf("\t\t\tThe Hongik Blue Marble!\n");
	printf("\n");
	printf("\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
	printf("\t플레이어 둘이서 벌이는 부루마블 게임입니다!\n");
	printf("\t\t1. 게임시작을 원하시면 1번을 눌러주세요\n");
	printf("\t\t2. 랭킹을 확인하고 싶다구요? 2번을 눌러주세요\n");
	printf("\t\t3. 아쉽지만 여기서 끝내고 싶으면 3번을ㅠㅠ\n");
	printf("\n\n\n\t\t\t숫자를 입력하세요 : ");
	scanf("%d", &no);

	if (no == 1)
		main_2();
	else if (no == 2)
	{
		rank(0, 0); //순위표 열람
		system("cls");
		goto a;
	}
	//순위 함수
	else if (no == 3)
		exit(0);
	else {
		system("cls");
		goto a;
	}
}
////////////////////////////////////////////////////////////////////////////////
void main_2()////////////////////////////////////////////////////////////////////////////////게임이 주요하게 굴러가는 함수
{


	system("cls");


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 02);
	printf("\n\n\n\n\n\t\t사용자1의 이름을 입력하세요 : ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
	scanf("%s", user_name1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 05);
	printf("\n\n\n\n\n\t\t사용자2의 이름을 입력하세요 : ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
	scanf("%s", user_name2);
	system("cls");

	printf("사용자1의 땅 : 1 // 사용자 2의 땅 : 2\n");


	for (i = 0; i < 500; i++) {           //턴 수 제한
		int sub_dice = 0;

		if (isMuindo[i % 2] == 0) //해당 플레이어가 무인도에 갇힌지 검사
		{//안갇힘
			sky
				printf("현재 %d번째 턴입니다.\n", (i / 2) + 1);
			white
				printf("주사위를 굴립니다. 아무키나 입력해주세요(user%d 턴) : \n", (i % 2) + 1);
			while (1) {
				printf("%d", sub_dice);
				if (kbhit()) {//키보드히트
					break;
				}
				sub_dice = (sub_dice + 1) % 5;
				if (sub_dice == 0)
					sub_dice++;
				printf("\b");
			}

			getch();
			user_site[(i % 2)] += sub_dice;
		}
		else
		{//갇힘
			sky
				printf("현재 %d번째 턴입니다.\n", (i / 2) + 1);
			white
				printf("user%d은 무인도에 있으므로 1턴 쉽니다.\n\n", (i % 2) + 1);
			isMuindo[i % 2] = 0;
			continue;//수행중인 반복문을 여기서 중단하고 바로 다음 반복문을 수행.
		}
		system("cls");

		//유저들의 위치 표시
	

		map(sub_dice);

		move();
		size_s();

		switch (user_site[i % 2] % 26) {
		case 0:
			if (i != (0 || 1)) {                                 //처음에 시작할 때 돈이 추가되지 않기 위함
				price();
			}
			break;
		case 1:
			a = 0;
			ddang(a, country_money[a],city_money[a], i % 2);
			break;
		case 2:
			a = 1;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 3:
			a = 2;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 4:
			a = 3;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 5:
			a = 4;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 6:
			a = 5;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 7:
			isMuindo[i % 2] = 1;
			printf("무인도에 갇혔습니다!\n");
			printf("다음 턴으로 넘깁니다.\n\n");
			break;
		case 8:
			a = 6;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 9:
			a = 7;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 10:
			a = 8;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 11:
			chance(i % 2);
			break;
		case 12:
			a = 9;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 13:
			a = 10;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 14:
			a = 11;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 15:
			a = 12;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 16:
			a = 13;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 17:
			a = 14;
			//ddang(a, country_money[a], i % 2);
			blackhole(i % 2, sub_dice);
			break;
		case 18:
			a = 15;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 19:
			a = 16;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 20:
			a = 17;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 21:
			a = 18;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 22:
			a = 19;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 23:
			a = 20;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 24:
			a = 21;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;
		case 25://대한민국
			a = 22;
			ddang(a, country_money[a], city_money[a], i % 2);
			break;

		}
		if (user_money[0] <= 0) {    //유저들의 돈이 0밑으로 내려가면 게임 종료
			int i;
			for (i = 0; i < 10; i++)////////////이광은 추가사항 4번: 승리자 발생 시 승리 멘트에 여러 색깔이 일정 주기로 바뀌는 기믹 적용
			{
				system("cls");
				printf("%s님이 승리하였습니다!\n", user_name2);
				printf("%7s의 최종 금액 : %8d\n", user_name2, user_money[1]);
				system("color 0d");
				Sleep(300);
				system("cls");
				printf("%s님이 승리하였습니다!\n", user_name2);
				printf("%7s의 최종 금액 : %8d\n", user_name2, user_money[1]);
				system("color 0e");
				Sleep(300);
				system("cls");
				printf("%s님이 승리하였습니다!\n", user_name2);
				printf("%7s의 최종 금액 : %8d\n", user_name2, user_money[1]);
				system("color 0c");
				Sleep(300);
				system("cls");
				printf("%s님이 승리하였습니다!\n", user_name2);
				printf("%7s의 최종 금액 : %8d\n", user_name2, user_money[1]);
				system("color 0b");
				Sleep(300);
			}
			score = &user_money[1];
			rank(2, *score);//유저 2가 승리
			exit(0);
		}
		else if (user_money[1] <= 0) {
			int i;
			for (i = 0; i < 10; i++)
			{
				system("cls");
				printf("%s님이 승리하였습니다!\n", user_name1);
				printf("%7s의 최종 금액 : %8d\n", user_name1, user_money[0]);
				system("color 0d");
				Sleep(300);
				system("cls");
				printf("%s님이 승리하였습니다!\n", user_name1);
				printf("%7s의 최종 금액 : %8d\n", user_name1, user_money[0]);
				system("color 0e");
				Sleep(300);
				system("cls");
				printf("%s님이 승리하였습니다!\n", user_name1);
				printf("%7s의 최종 금액 : %8d\n", user_name1, user_money[0]);
				system("color 0c");
				Sleep(300);
				system("cls");
				printf("%s님이 승리하였습니다!\n", user_name1);
				printf("%7s의 최종 금액 : %8d\n", user_name1, user_money[0]);
				system("color 0b");
				Sleep(300);
			}
			score = &user_money[0];
			rank(1, *score);//유저 1이 승리
			exit(0);
		}
	}
}




////////////////////////////////////////////////////////////////////////////////
char map_name_user1(int x)////////////////////////////////////////////////////////////////////////////////user1의 위치를 나타내는 함수
{

	int city_num = 0;

	city_num = x % 26;


	switch (city_num)
	{
	case 0:
		printf("      %s의 위치: 출발", user_name1);
		break;
	case 1:
		printf("      %s의 위치: 인도", user_name1);
		break;
	case 2:
		printf("      %s의 위치: 캄보디아", user_name1);
		break;
	case 3:
		printf("      %s의 위치: 파키스탄", user_name1);
		break;
	case 4:
		printf("      %s의 위치: 중국", user_name1);
		break;
	case 5:
		printf("      %s의 위치: 타이완", user_name1);
		break;
	case 6:
		printf("      %s의 위치: 일본", user_name1);
		break;
	case 7:
		printf("      %s의 위치: 무인도", user_name1);
		break;
	case 8:
		printf("      %s의 위치: 소말리아", user_name1);
		break;
	case 9:
		printf("      %s의 위치: 탄자니아", user_name1);
		break;
	case 10:
		printf("      %s의 위치: 남아공", user_name1);
		break;
	case 11:
		printf("      %s의 위치: 찬스", user_name1);
		break;
	case 12:
		printf("      %s의 위치: 이집트", user_name1);
		break;
	case 13:
		printf("      %s의 위치: 그리스", user_name1);
		break;
	case 14:
		printf("      %s의 위치: 이탈리아", user_name1);
		break;
	case 15:
		printf("      %s의 위치: 독일", user_name1);
		break;
	case 16:
		printf("      %s의 위치: 영국", user_name1);
		break;
	case 17:
		printf("      %s의 위치: 블랙홀", user_name1);
		break;
	case 18:
		printf("      %s의 위치: 루마니아", user_name1);
		break;
	case 19:
		printf("      %s의 위치: 프랑스", user_name1);
		break;
	case 20:
		printf("      %s의 위치: 러시아", user_name1);
		break;
	case 21:
		printf("      %s의 위치: 미국", user_name1);
		break;
	case 22:
		printf("      %s의 위치: 멕시코", user_name1);
		break;
	case 23:
		printf("      %s의 위치: 브라질", user_name1);
		break;
	case 24:
		printf("      %s의 위치: 콜롬비아", user_name1);
		break;
	case 25:
		printf("      %s의 위치: 대한민국", user_name1);
		break;
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
char map_name_user2(int x)////////////////////////////////////////////////////////////////////////////////user2의 위치를 나타내는 함수
{

	int city_num = 0;

	city_num = x % 26;

	switch (city_num)
	{
	case 0:
		printf("%s의 위치: 출발\n", user_name2);
		break;
	case 1:
		printf("%s의 위치: 인도\n", user_name2);
		break;
	case 2:
		printf("%s의 위치: 캄보디아\n", user_name2);
		break;
	case 3:
		printf("%s의 위치: 파키스탄\n", user_name2);
		break;
	case 4:
		printf("%s의 위치: 중국\n", user_name2);
		break;
	case 5:
		printf("%s의 위치: 타이완\n", user_name2);
		break;
	case 6:
		printf("%s의 위치: 일본\n", user_name2);
		break;
	case 7:
		printf("%s의 위치: 무인도\n", user_name2);
		break;
	case 8:
		printf("%s의 위치: 소말리아\n", user_name2);
		break;
	case 9:
		printf("%s의 위치: 탄자니아\n", user_name2);
		break;
	case 10:
		printf("%s의 위치: 남아공\n", user_name2);
		break;
	case 11:
		printf("%s의 위치: 찬스\n", user_name2);
		break;
	case 12:
		printf("%s의 위치: 이집트\n", user_name2);
		break;
	case 13:
		printf("%s의 위치: 그리스\n", user_name2);
		break;
	case 14:
		printf("%s의 위치: 이탈리아\n", user_name2);
		break;
	case 15:
		printf("%s의 위치: 독일\n", user_name2);
		break;
	case 16:
		printf("%s의 위치: 영국\n", user_name2);
		break;
	case 17:
		printf("%s의 위치: 블랙홀\n", user_name2);
		break;
	case 18:
		printf("%s의 위치: 루마니아\n", user_name2);
		break;
	case 19:
		printf("%s의 위치: 프랑스\n", user_name2);
		break;
	case 20:
		printf("%s의 위치: 러시아\n", user_name2);
		break;
	case 21:
		printf("%s의 위치: 미국\n", user_name2);
		break;
	case 22:
		printf("%s의 위치: 멕시코\n", user_name2);
		break;
	case 23:
		printf("%s의 위치: 브라질\n", user_name2);
		break;
	case 24:
		printf("%s의 위치: 콜롬비아\n", user_name2);
		break;
	case 25:
		printf("%s의 위치: 대한민국\n", user_name2);
		break;
	}
	return 0;
}
////////////////////////////////////////////////////////////////////////////////
void buying(int a, int country_money, int city_money)////////////////////////////////////////////////////////////////////////////////땅을 구매하는 함수
{
	int agree;

	if (land[a] == 0) {
		
		printf("이 땅의 가격은 %d원입니다\n구매하시겠습니까?(예1/아니오2) ", country_money);
		scanf("%d", &agree);
		if (agree == 1) {
			//user[i%2]에게는 땅을 매입할 여건이 충분한가?
			if (country_money <= user_money[i % 2])
			{
				user_money[i % 2] -= country_money;

				printf("땅이 정상적으로 구매되었습니다!\n\n");
				land[a]++;
				buying2(a, city_money);

			}
			else {
				printf("땅을 매입할 돈이 부족합니다!\n\n");
			}
			
			
		
			
		}
		else
			printf("다음 턴으로 넘깁니다.\n\n");
	}
}

void buying2(int a, int city_money)
{
	int agree;

	if (cityland[a] == 0) {

		printf("이 주택의 가격은 %d원입니다\n구매하시겠습니까?(예1/아니오2) ", city_money);
		scanf("%d", &agree);
		if (agree == 1) {
			//user[i%2]에게는 땅을 매입할 여건이 충분한가?
			if (city_money <= user_money[i % 2])
			{
				user_money[i % 2] -= city_money;

				printf("주택이 정상적으로 구매되었습니다!\n\n");
				cityland[a]++;
			}

			else {
				printf("주택을 매입할 돈이 부족합니다!\n\n");
			}
			
		}
		
	}
	
}
////////////////////////////////////////////////////////////////////////////////추가한부분
void blackhole(int player_turn, int dice)////////////////////////////////////////////////////////////////////////////////블랙홀 함수
{
	int num = rand() % 26;
	user_site[player_turn] = num;

	system("cls");
	map_name_user1(user_site[0]);
	printf("\t\t\t");
	map_name_user2(user_site[1]);

	map(dice);

	move();

	if (num != 17)//랜덤으로 돌린 숫자가 블랙홀 위치면 출력안함
		printf("당신은 블랙홀에 빠졌습니다! 아무 장소로 이동합니다.\n");

	switch (num)
	{
	case 0:
		sky
			printf("출발로 이동합니다.\n");
		white
			printf("블랙홀로 이동하여 한바퀴 수당을 받지 않습니다.\n");
		break;
	case 1:
		a = 0;
		sky
			printf("인도로 이동합니다.\n");
		white
			ddang(a, country_money[a],city_money[a], player_turn);
		break;
	case 2:
		a = 1;
		sky
			printf("캄보디아로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 3:
		a = 2;
		sky
			printf("파키스탄으로 이동합니다.\n");
		white
			ddang(a, country_money[a],city_money[a], player_turn);
		break;
	case 4:
		a = 3;
		sky
			printf("중국으로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 5:
		a = 4;
		sky
			printf("타이완으로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 6:
		a = 5;
		sky
			printf("일본으로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 7:
		isMuindo[player_turn] = 1;
		sky
			printf("무인도로 이동합니다.\n");
		white
			printf("무인도에 갇혔습니다!\n");
		printf("다음 턴으로 넘깁니다.\n\n");
		break;
	case 8:
		a = 6;
		sky
			printf("소말리아로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 9:
		a = 7;
		sky
			printf("탄자니아로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 10:
		a = 8;
		sky
			printf("남아공으로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 11:
		sky
			printf("찬스로 이동합니다.\n");
		white
			chance(player_turn);
		break;
	case 12:
		a = 9;
		sky
			printf("이집트로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 13:
		a = 10;
		sky
			printf("그리스로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 14:
		a = 11;
		sky
			printf("이탈리아로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 15:
		a = 12;
		sky
			printf("독일로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 16:
		a = 13;
		sky
			printf("영국으로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 17:
		blackhole(player_turn, dice); //재귀호출
		break;
	case 18:
		a = 15;
		sky
			printf("루마니아로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 19:
		a = 16;
		sky
			printf("프랑스로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 20:
		a = 17;
		sky
			printf("러시아로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 21:
		a = 18;
		sky
			printf("미국으로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 22:
		a = 19;
		sky
			printf("멕시코로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 23:
		a = 20;
		sky
			printf("브라질로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 24:
		a = 21;
		sky
			printf("콜롬비아로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;
	case 25:
		a = 22;
		sky
			//이스터에그
			printf("지옥 불반도 헬 조선 대한민국으로 이동합니다.\n");
		white
			ddang(a, country_money[a], city_money[a], player_turn);
		break;

	}
}
////////////////////////////////////////////////////////////////////////////////
void ddang(int ddang_number, int coun_money,int cit_money ,int player_turn)///////////////////////////////////////////////////그 땅에 갔을때
{
	int agree;

	if (land[ddang_number] == 0) {
		if ((player_turn) == 0) {
			buying(ddang_number, coun_money, cit_money);
		}
		else if ((player_turn) == 1) {
			buying(ddang_number, coun_money, cit_money);
			if (land[ddang_number] > 0)
				land[ddang_number]++;
		}
		//플레이어2의 소유권 표시
	}
	//플레이어2가 플레이어 1의 땅에 들어갔을때(주택 x 땅만소유)

	else if (land[ddang_number] == 1 && cityland[ddang_number] == 0) {
		if ((player_turn) == 1) {
			int purchase_money = coun_money * (_PURCHASE_LAND_SCALE);

			user_money[1] -= 2 * country_money[ddang_number];
			user_money[0] += 2 * country_money[ddang_number];
			printf("남의 땅입니다. 돈을 %d원 지불해야합니다.\n", 2 * country_money[ddang_number]);
			//상대에게 땅 매입하기
			printf("혹시 이 땅을 구매하실 생각이 있으신가요? \n대신 가격은 원래 땅의 두배로 지불하셔야 합니다.!\n매입할 경우 가격은 %d원입니다. 구매하시겠습니까?(예1/아니오2) ", purchase_money);
			scanf("%d", &agree);
			if (agree == 1) {
				//user[b]에게는 땅을 매입할 여건이 충분한가?
				if (purchase_money <= user_money[player_turn])
				{
					user_money[player_turn] -= purchase_money;

					printf("땅이 정상적으로 구매되었습니다!\n\n");
					land[ddang_number] = 2;
				}
				else
					printf("땅을 매입할 돈이 부족합니다!\n\n");
			}
		}
		else if ((player_turn) == 0)
		{
			printf("자신의 땅입니다.\n\n");
			service1();
		}
		//플레이어2가 플레이어 1의 땅에 들어갔을때(주택소유)
	}

	else if (land[ddang_number] == 1 && cityland[ddang_number] == 1) {
		if ((player_turn) == 1) {
			int purchase_money = (cit_money + coun_money) * (_PURCHASE_LAND_SCALE);

			user_money[1] -= 2 * country_money[ddang_number];
			user_money[0] += 2 * country_money[ddang_number];
			printf("남의 땅입니다 주택까지 지어져있습니다. 돈을 %d원 지불해야합니다.\n", 2 * country_money[ddang_number]);
			//상대에게 땅 매입하기
			printf("혹시 이 땅과 주택을 구매하실 생각이 있으신가요? \n대신 가격은 원래 땅+주택의 두배로 지불하셔야 합니다.!\n매입할 경우 가격은 %d원입니다. 구매하시겠습니까?(예1/아니오2) ", purchase_money);
			scanf("%d", &agree);
			if (agree == 1) {
				//user[b]에게는 땅을 매입할 여건이 충분한가?
				if (purchase_money <= user_money[player_turn])
				{
					user_money[player_turn] -= purchase_money;

					printf("땅과 주택이 정상적으로 구매되었습니다!\n\n");
					land[ddang_number] = 2;
				}
				else
					printf("땅과 주택을 매입할 돈이 부족합니다!\n\n");
			}
		}

		else if ((player_turn) == 0)
			printf("자신의 땅입니다.\n\n");
	}

		//플레이어1가 플레이어 2의 땅에 들어갔을때(주택 x 땅만소유)
	else if (land[ddang_number] == 2 && cityland[ddang_number] == 0) {
		if ((player_turn) == 0) {
			int purchase_money = coun_money * (_PURCHASE_LAND_SCALE);

			user_money[0] -= 2 * country_money[ddang_number];
			user_money[1] += 2 * country_money[ddang_number];
			printf("남의 땅입니다. 돈을 %d원 지불합니다.\n\n", 2 * country_money[ddang_number]);
			//상대에게 땅 매입하기
			printf("혹시 이 땅을 구매하실 생각이 있으신가요? \n대신 가격은 원래 땅의 두배로 지불하셔야 합니다.!\n매입할 경우 가격은 %d원입니다. 구매하시겠습니까?(예1/아니오2) ", purchase_money);
			scanf("%d", &agree);
			if (agree == 1) {
				//user[b]에게는 땅을 매입할 여건이 충분한가?
				if (purchase_money <= user_money[player_turn])
				{
					user_money[player_turn] -= purchase_money;

					printf("땅이 정상적으로 구매되었습니다!\n\n");
					land[ddang_number] = 1;
				}
				else
					printf("땅을 매입할 돈이 부족합니다!\n\n");
			}
		}
		else if ((player_turn) == 1)
		{
			printf("자신의 땅입니다.\n\n");
			service2();
		}
		//플레이어2가 플레이어 1의 땅에 들어갔을때(주택소유)
	}
	else if (land[ddang_number] == 2 && cityland[ddang_number] == 1) {
		if ((player_turn) == 1) {
			int purchase_money = (cit_money + coun_money) * (_PURCHASE_LAND_SCALE);

			user_money[1] -= 2 * country_money[ddang_number];
			user_money[0] += 2 * country_money[ddang_number];
			printf("남의 땅입니다 주택까지 지어져있습니다. 돈을 %d원 지불해야합니다.\n", 2 * country_money[ddang_number]);
			//상대에게 땅 매입하기
			printf("혹시 이 땅과 주택을 구매하실 생각이 있으신가요? \n대신 가격은 원래 땅의 두배로 지불하셔야 합니다.!\n매입할 경우 가격은 %d원입니다. 구매하시겠습니까?(예1/아니오2) ", purchase_money);
			scanf("%d", &agree);
			if (agree == 1) {
				//user[b]에게는 땅을 매입할 여건이 충분한가?
				if (purchase_money <= user_money[player_turn])
				{
					user_money[player_turn] -= purchase_money;

					printf("땅과 주택이 정상적으로 구매되었습니다!\n\n");
					land[ddang_number] = 2;
				}
				else
					printf("땅과 주택을 매입할 돈이 부족합니다!\n\n");
			}
		}

		else if ((player_turn) == 1)
			printf("자신의 땅입니다.\n\n");
			service2();
	}

}


////////////////////////////////////////////////////////////////////////////////
void chance(int x)///////////////////////////////////////////////////////////////////////찬스카드
{
	int chance_num = 0;

	srand(time(NULL));
	chance_num = rand() % 11;

	switch (chance_num)///이광은 추가사항 5번: 찬스 발생 시 자신이 무슨 찬스에 걸렸는지 명확히 알기 위해 'Sleep' 기능 추가
	{
	case 1:
		printf("핵전쟁이 일어났습니다. 가지고 있는 돈이 반으로 줄어듭니다\n");
		Sleep(5000);
		user_money[x] /= 2;
		break;
	case 2:
		printf("상대편의 은행을 인수했습니다. 돈 20000원 획득\n");
		Sleep(5000);
		user_money[x] += 20000;
		break;
	case 3:
		printf("거대 해일로 인해 모든 영토와 재산을 잃어버렸습니다.\n");///이광은 추가사항 3번: 찬스 목록 중 '꽝'을 '파산'으로 변경
		Sleep(5000);
		user_money[x] *= 0;;
		break;
	case 4:
		printf("수출액이 증가했습니다. 돈 30000원 획득\n");
		Sleep(5000);
		user_money[x] += 30000;
		break;
	case 5:
		printf("IMF가 터졌습니다. 돈의 50%가 사라집니다\n");
		Sleep(5000);
		user_money[x] /= 2;
		break;
	case 6:
		printf("아프리카에 에볼라가 발생했습니다, 복지예산 증가. 돈 50000원 지출\n");
		Sleep(5000);
		user_money[x] -= 50000;
		break;
	case 7:
		printf("다음 월드컵 개최지로 선정되었습니다. 보유액이 1.5배가 됩니다\n");
		Sleep(5000);
		user_money[x] *= 1.5;
		break;
	case 8:
		printf("제2의 지구를 찾았습니다. 보유액이 2배로 늘어납니다\n");
		Sleep(5000);
		user_money[x] *= 2;
		break;
	case 9:
		printf("고령화시대가 도달했습니다. 복지예산은 30000원입니다\n");
		Sleep(5000);
		user_money[x] += 30000;
		break;
	case 10:
		printf("전쟁에서 이겼습니다. 돈 100000원 획득\n");
		Sleep(5000);
		user_money[x] += 100000;
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////
void rank(int mode, int score)///////////////////////////////////////////////랭킹 구현
{
	int win;
	int lose;
	int rate1, rate2;
	int score1, score2;
	int sum;

	FILE* fp = NULL;

	switch (mode)//0 : 순위만 표시, 1,2 : 각각 플레이어1,2 승리하고 전적 갱신
	{
	case 0://순위 표시
		fp = fopen("rank.txt", "r");//파일 호출
		if (fp == NULL)
		{
			printf("파일을 읽어오는데 실패하였습니다.\n");
			exit(0);
		}
		fscanf(fp, "%d %d %d %d", &win, &lose, &score1, &score2);
		fclose(fp);//파일 닫기

		//승률 계산
		sum = win + lose;
		if (sum == 0)
			rate1 = (win == 0) ? 0 : 100;
		else
			rate1 = 100 * win / sum;
		sum = win + lose;
		if (sum == 0)
			rate2 = (lose == 0) ? 0 : 100;
		else
			rate2 = 100 * lose / sum;

		//프린트문 출력
		printf("\n\n\n");
		printf("\t─────┬──────────┬────┬──────\n");
		printf("\t Player   │\tWin\tLose\t│ Winrate│ Best Score\n");
		printf("\t─────┼──────────┼────┼──────\n");
		printf("\t user1    │\t %d\t %d\t│ %d\t%% │ %d\n", win, lose, rate1, score1);
		printf("\t user2    │\t %d\t %d\t│ %d\t%% │ %d\n", lose, win, rate2, score2);
		printf("\t─────┴──────────┴────┴──────\n");
		printf("\n\n\n확인이 끝나셨으면 아무 키나 눌러주세요.");
		while (1) {
			if (kbhit()) {//키보드히트
				break;
			}
		}
		break;
	case 1: //플레이어1 승리 추가 및 플레이어2 패배 추가
		fp = fopen("rank.txt", "r");//파일 호출
		if (fp == NULL)
		{
			printf("파일을 읽어오는데 실패하였습니다.\n");
			exit(0);
		}
		fscanf(fp, "%d %d %d %d", &win, &lose, &score1, &score2);
		fclose(fp);//파일 닫기

		win++;
		if (score1 < score)
			score1 = score;

		fp = fopen("rank.txt", "w");//파일 호출
		if (fp == NULL)
		{
			printf("파일을 읽어오는데 실패하였습니다.\n");
			exit(0);
		}
		fprintf(fp, "%d %d %d %d\n", win, lose, score1, score2);
		fclose(fp);//파일 닫기

		printf("전적 갱신이 성공적으로 완료되었습니다.\n");
		break;
	case 2: //플레이어1 패배 추가 및 플레이어2 승리 추가
		fp = fopen("rank.txt", "r");//파일 호출
		if (fp == NULL)
		{
			printf("파일을 읽어오는데 실패하였습니다.\n");
			exit(0);
		}
		fscanf(fp, "%d %d %d %d", &win, &lose, &score1, &score2);
		fclose(fp);//파일 닫기

		lose++;
		if (score2 < score)
			score2 = score;

		fp = fopen("rank.txt", "w");//파일 호출
		if (fp == NULL)
		{
			printf("파일을 읽어오는데 실패하였습니다.\n");
			exit(0);
		}
		fprintf(fp, "%d %d %d %d\n", win, lose, score1, score2);
		fclose(fp);//파일 닫기

		printf("전적 갱신이 성공적으로 완료되었습니다.\n");
		break;
	}
}



void gotoxy(int x, int y)//gotoxy선언
{//gotoxy시작

	COORD Pos = { x - 1, y - 1 };//
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);//

}//gotoxy종료
/////////////////////////////////////////////////////////////////////////////////////////////
void move()
{
	int z;
	z = user_site[1] % 26;
	if (z == 0)//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		gotoxy(69, 31);
		wine
			printf("★\n\n\n\n\n\n");
		white
	}
	else if (z == 1)
	{
		gotoxy(59, 31);
		wine
			printf("★\n\n\n\n\n\n");
		white
	}
	else if (z == 2)
	{
		gotoxy(49, 31);
		wine
			printf("★\n\n\n\n\n\n");
		white
	}
	else if (z == 3)
	{
		gotoxy(39, 31);
		wine
			printf("★\n\n\n\n\n\n");
		white
	}
	else if (z == 4)
	{
		gotoxy(29, 31);
		wine
			printf("★\n\n\n\n\n\n");
		white
	}
	else if (z == 5)
	{
		gotoxy(19, 31);
		wine
			printf("★\n\n\n\n\n\n");
		white
	}
	else if (z == 6)
	{
		gotoxy(9, 31);
		wine
			printf("★\n\n\n\n\n\n");
		white
	}
	else if (z == 7)
	{
		gotoxy(9, 27);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 8)
	{
		gotoxy(9, 23);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 9)
	{
		gotoxy(9, 19);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 10)
	{
		gotoxy(9, 15);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 11)
	{
		gotoxy(9, 11);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 12)
	{
		gotoxy(9, 7);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 13)
	{
		gotoxy(9, 3);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 14)
	{
		gotoxy(19, 3);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 15)
	{
		gotoxy(29, 3);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 16)
	{
		gotoxy(39, 3);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 17)
	{
		gotoxy(49, 3);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 18)
	{
		gotoxy(59, 3);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 19)
	{
		gotoxy(69, 3);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 20)
	{
		gotoxy(69, 7);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 21)
	{
		gotoxy(69, 11);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 22)
	{
		gotoxy(69, 15);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 23)
	{
		gotoxy(69, 19);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 24)
	{
		gotoxy(69, 23);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 25)
	{
		gotoxy(69, 27);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (z == 26)
	{
		gotoxy(69, 31);
		wine
			printf("★\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}



	int c = 1;
	c = user_site[0] % 26;
	if (c == 0)//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		gotoxy(65, 31);
		green
			printf("●\n\n\n\n\n\n");
		white
	}
	else if (c == 1)
	{
		gotoxy(55, 31);
		green
			printf("●\n\n\n\n\n\n");
		white
	}
	else if (c == 2)
	{
		gotoxy(45, 31);
		green
			printf("●\n\n\n\n\n\n");
		white
	}
	else if (c == 3)
	{
		gotoxy(35, 31);
		green
			printf("●\n\n\n\n\n\n");
		white
	}
	else if (c == 4)
	{
		gotoxy(25, 31);
		green
			printf("●\n\n\n\n\n\n");
		white
	}
	else if (c == 5)
	{
		gotoxy(15, 31);
		green
			printf("●\n\n\n\n\n\n");
		white
	}
	else if (c == 6)
	{
		gotoxy(5, 31);
		green
			printf("●\n\n\n\n\n\n");
		white
	}
	else if (c == 7)
	{
		gotoxy(5, 27);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 8)
	{
		gotoxy(5, 23);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 9)
	{
		gotoxy(5, 19);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 10)
	{
		gotoxy(5, 15);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 11)
	{
		gotoxy(5, 11);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 12)
	{
		gotoxy(5, 7);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 13)
	{
		gotoxy(5, 3);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 14)
	{
		gotoxy(15, 3);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 15)
	{
		gotoxy(25, 3);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 16)
	{
		gotoxy(35, 3);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 17)
	{
		gotoxy(45, 3);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 18)
	{
		gotoxy(55, 3);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 19)
	{
		gotoxy(65, 3);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 20)
	{
		gotoxy(65, 7);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 21)
	{
		gotoxy(65, 11);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 22)
	{
		gotoxy(65, 15);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 23)
	{
		gotoxy(65, 19);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 24)
	{
		gotoxy(65, 23);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 25)
	{
		gotoxy(65, 27);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
	else if (c == 26)
	{
		gotoxy(65, 31);
		green
			printf("●\n\n\n\n\n\n\n\n\n\n\n\n");
		white
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void map(int sub_dice)
{
	
	char house[4] = "H ";
	char str[20] = "│  [";
	char str3[5] = "] ";
	char str2[2] = { 0 };
	//글자들
	
	printf("┌────┬────┬────┬────┬────┬────┬────┐\n");
	printf("│        │        │        │        │        │        │        │\n");
	printf("│ 그리스 │이탈리아│  독일  │  영국  │ 블랙홀 │루마니아│ 프랑스 │\n");

	if (land[10] == 0)/////////////////////////////////////////////////////그리스
	{
		printf("│  [%d]   ", land[10]);
		
	}
	else if (land[10] == 1)
	{
		
		
		green
			if (cityland[10] == 1)
			{
				itoa(land[10], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[10]);
			}
		
		
		white
	}
	else if (land[10] == 2)
	{
		wine
		if (cityland[10] == 1)
		{

			itoa(land[10], str2, 10);
			strcat(str, str2); //|  [숫자
			strcat(str, str3);
			strcat(str, house);//|  [숫자]h
			printf(str);
		}
		else
		{
			printf("│  [%1d]   ", land[10]);
		}
		
		white
	}
	//////////////////////////////////////////////

	if (land[11] == 0)////////////////////////////////////////////////////이탈리아
	{
		printf("│  [%d]   ", land[11]);
	}

	else if (land[11] == 1)
	{

		char str[20] = "│  [";
		green
			if (cityland[11] == 1)
			{
				itoa(land[11], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[11]);
			}


		white
	}
	else if (land[11] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[11] == 1)
			{

				itoa(land[11], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[11]);
			}

		white
	}
	//////////////////////////////////////////////


	if (land[12] == 0)//////////////////////////////////////////////////////독일
		printf("│  [%d]   ", land[12]);
	else if (land[12] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[12] == 1)
			{
				itoa(land[12], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%d]   ", land[11]);
			}


		white
	}
	else if (land[12] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[12] == 1)
			{

				itoa(land[12], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[12]);
			}

		white
	}
	//////////////////////////////////////////////


	if (land[13] == 0)//////////////////////////////////////////////////////영국
		printf("│  [%1d]   ", land[13]);
	else if (land[13] == 1)
	{

		char str[20] = "│  [";
		green
			if (cityland[13] == 1)
			{
				itoa(land[13], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[13]);
			}


		white
	}
	else if (land[13] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[13] == 1)
			{

				itoa(land[13], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[13]);
			}

		white
	}
	//////////////////////////////////////////////

	printf("│        ", land[14]);//블랙홀 위치

	if (land[15] == 0)//////////////////////////////////////////////////////루마니아
		printf("│  [%1d]   ", land[15]);
	else if (land[15] == 1)
	{

		char str[20] = "│  [";
		green
			if (cityland[15] == 1)
			{
				itoa(land[15], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[15]);
			}


		white
	}
	else if (land[15] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[15] == 1)
			{

				itoa(land[15], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[15]);
			}

		white
	}
	//////////////////////////////////////////////


	if (land[16] == 0)//////////////////////////////////////////////////////프랑스
		printf("│  [%1d]   ", land[16]);
	else if (land[16] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[16] == 1)
			{
				itoa(land[16], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[16]);
			}


		white
	}
	else if (land[16] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[16] == 1)
			{

				itoa(land[16], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[16]);
			}

		white
	}
	//////////////////////////////////////////////

	printf("│\n");



	printf("├────┼────┴────┴──ㅡ─┴────┴────┼────┤\n");
	printf("│        │                                                │        │\n");


	printf("│ 이집트 │  ");


	yellow
		printf("%7s의 돈 = %8d                       ", user_name1, user_money[0]);
	white


		printf("│ 러시아 │\n");


	if (land[9] == 0)//////////////////////////////////////////////////////이집트
		printf("│  [%1d]   ", land[9]);
	else if (land[9] == 1)
	{

		char str[20] = "│  [";
		green
			if (cityland[9] == 1)
			{
				itoa(land[9], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[9]);
			}


		white
	}
	else if (land[9] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[9] == 1)
			{

				itoa(land[9], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[9]);
			}

		white
	}
	//////////////////////////////////////////////
	printf("│");


	yellow////////////////////////////////////////////////////////////////////////////사용자돈
		printf("  %7s의 돈 = %8d                       ", user_name2, user_money[1]);
	white


		if (land[17] == 0)//////////////////////////////////////////////////////러시아
			printf("│  [%1d]   ", land[17]);
		else if (land[11] == 1)
		{

			char str[20] = "│  [";
			green
				if (cityland[17] == 1)
				{
					itoa(land[17], str2, 10);
					strcat(str, str2); //|  [숫자
					strcat(str, str3);
					strcat(str, house);//|  [숫자]h
					printf(str);
				}
				else {
					printf("│  [%1d]   ", land[17]);
				}


			white
		}
		else if (land[17] == 2)
		{
			char str[20] = "│  [";
			wine
				if (cityland[17] == 1)
				{

					itoa(land[17], str2, 10);
					strcat(str, str2); //|  [숫자
					strcat(str, str3);
					strcat(str, house);//|  [숫자]h
					printf(str);
				}
				else
				{
					printf("│  [%d]   ", land[17]);
				}

			white
		}
	//////////////////////////////////////////////
	printf("│\n");


	printf("├────┤                                                ├────┤\n");
	printf("│        │                                                │        │\n");
	printf("│  찬스  │                                                │  미국  │\n");
	printf("│        │                                                ");
	if (land[18] == 0)//////////////////////////////////////////////////////미국
		printf("│  [%1d]   ", land[18]);
	else if (land[18] == 1)
	{

		char str[20] = "│  [";
		green
			if (cityland[18] == 1)
			{
				char str[20] = "│  [";
				itoa(land[18], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[18]);
			}


		white
	}
	else if (land[18] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[18] == 1)
			{

				itoa(land[18], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[18]);
			}

		white
	}
	//////////////////////////////////////////////
	printf("│\n");



	printf("├────┤                                                ├────┤\n");
	printf("│        │                                                │        │\n");
	printf("│ 남아공 │                  ┌───┬──┐              │ 멕시코 │\n");
	if (land[8] == 0)//////////////////////////////////////////////////////남아공
		printf("│  [%1d]   ", land[8]);
	else if (land[8] == 1)
	{

		char str[20] = "│  [";
		green
			if (cityland[8] == 1)
			{
				itoa(land[8], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[8]);
			}


		white
	}
	else if (land[8] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[8] == 1)
			{

				itoa(land[8], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[8]);
			}

		white
	}
	//////////////////////////////////////////////
	printf("│         ");


	printf("         │주사위│ %d  │              ", sub_dice);
	if (land[19] == 0)//////////////////////////////////////////////////////멕시코
		printf("│  [%1d]   ", land[19]);
	else if (land[9] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[9] == 1)
			{
				itoa(land[9], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[9]);
			}


		white
	}
	else if (land[9] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[9] == 1)
			{

				itoa(land[9], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[9]);
			}

		white
	}
	//////////////////////////////////////////////
	printf("│\n");


	printf("├────┤                  └───┴──┘              ├────┤\n");
	printf("│        │                                                │        │\n");
	printf("│탄자니아│                                                │ 브라질 │\n");


	if (land[7] == 0)//////////////////////////////////////////////////////탄자니아
		printf("│  [%1d]   ", land[7]);
	else if (land[7] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[7] == 1)
			{
				itoa(land[7], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[7]);
			}


		white
	}
	else if (land[7] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[7] == 1)
			{

				itoa(land[7], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[7]);
			}

		white
	}
	//////////////////////////////////////////////
	printf("│                                                ");


	if (land[20] == 0)//////////////////////////////////////////////////////브라질
		printf("│  [%1d]   ", land[20]);
	else if (land[20] == 1)
	{

		char str[20] = "│  [";
		green
			if (cityland[20] == 1)
			{
				itoa(land[20], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[20]);
			}


		white
	}
	else if (land[20] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[20] == 1)
			{

				itoa(land[20], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[20]);
			}

		white
	}
	//////////////////////////////////////////////
	printf("│\n");


	printf("├────┤                                                ├────┤\n");
	printf("│        │                                                │        │\n");
	printf("│소말리아│                                                │콜롬비아│\n");


	if (land[6] == 0)//////////////////////////////////////////////////////소말리아
		printf("│  [%1d]   ", land[6]);
	else if (land[6] == 1)
	{

		char str[20] = "│  [";
		green
			if (cityland[6] == 1)
			{
				itoa(land[6], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[6]);
			}


		white
	}
	else if (land[6] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[6] == 1)
			{

				itoa(land[6], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[6]);
			}

		white
	}
	//////////////////////////////////////////////
	printf("│                                                ");


	if (land[21] == 0)//////////////////////////////////////////////////////콜롬비아
		printf("│  [%1d]   ", land[21]);
	else if (land[21] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[21] == 1)
			{
				itoa(land[21], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[21]);
			}


		white
	}
	else if (land[21] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[21] == 1)
			{

				itoa(land[21], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[21]);
			}

		white
	}
	//////////////////////////////////////////////
	printf("│\n");



	printf("├───ㅡ┤                                                ├────┤\n");
	printf("│        │                                                │        │\n");
	printf("│ 무인도 │                                                │대한민국│\n");
	printf("│        │                                                ");
	if (land[22] == 0)//////////////////////////////////////////////////////대한민국
		printf("│  [%1d]   ", land[22]);
	else if (land[22] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[22] == 1)
			{
				itoa(land[22], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[2]);
			}


		white
	}
	else if (land[22] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[22] == 1)
			{

				itoa(land[22], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[22]);
			}

		white
	}
	//////////////////////////////////////////////
	printf("│\n");



	printf("├────┼────┬────┬────┬──ㅡ─┬────┼────┤\n");
	printf("│        │        │        │        │        │        │        │\n");
	printf("│  일본  │ 타이완 ㅣ  중국  │파키스탄│캄보디아│  인도  │  출발  │\n");



	if (land[5] == 0)/////////////////////////////////////////////////////일본
		printf("│  [%d]   ", land[5]);
	else if (land[5] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[5] == 1)
			{
				itoa(land[5], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[5]);
			}


		white
	}
	else if (land[5] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[5] == 1)
			{

				itoa(land[5], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[5]);
			}

		white
	}
	//////////////////////////////////////////////

	if (land[4] == 0)////////////////////////////////////////////////////타이완
		printf("│  [%1d]   ", land[4]);
	else if (land[4] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[4] == 1)
			{
				itoa(land[4], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[4]);
			}


		white
	}
	else if (land[4] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[4] == 1)
			{

				itoa(land[4], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[4]);
			}

		white
	}
	//////////////////////////////////////////////


	if (land[3] == 0)//////////////////////////////////////////////////////중국
		printf("│  [%1d]   ", land[3]);
	else if (land[3] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[3] == 1)
			{
				itoa(land[3], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[3]);
			}


		white
	}
	else if (land[3] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[3] == 1)
			{

				itoa(land[3], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[3]);
			}

		white
	}
	//////////////////////////////////////////////


	if (land[2] == 0)//////////////////////////////////////////////////////파키스탄
		printf("│  [%1d]   ", land[2]);
	else if (land[2] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[2] == 1)
			{
				itoa(land[2], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[2]);
			}


		white
	}
	else if (land[2] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[2] == 1)
			{

				itoa(land[2], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[2]);
			}

		white
	}
	//////////////////////////////////////////////


	if (land[1] == 0)//////////////////////////////////////////////////////캄보디아
		printf("│  [%1d]   ", land[1]);
	else if (land[1] == 1)
	{

		char str[20] = "│  [";
		green
			if (cityland[1] == 1)
			{
				itoa(land[1], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[1]);
			}


		white
	}
	else if (land[1] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[1] == 1)
			{

				itoa(land[1], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[1]);
			}

		white
	}
	//////////////////////////////////////////////


	if (land[0] == 0)//////////////////////////////////////////////////////인도
		printf("│  [%1d]   ", land[0]);
	else if (land[0] == 1)
	{
		char str[20] = "│  [";

		green
			if (cityland[0] == 1)
			{
				itoa(land[0], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else {
				printf("│  [%1d]   ", land[0]);
			}


		white
	}
	else if (land[0] == 2)
	{
		char str[20] = "│  [";
		wine
			if (cityland[0] == 1)
			{

				itoa(land[0], str2, 10);
				strcat(str, str2); //|  [숫자
				strcat(str, str3);
				strcat(str, house);//|  [숫자]h
				printf(str);
			}
			else
			{
				printf("│  [%d]   ", land[0]);
			}

		white
	}
	//////////////////////////////////////////////



	printf("│        ㅣ\n");
	printf("└────┴────┴────┴────┴────┴────┴────┘\n\n\n");


	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 02);
	map_name_user1(user_site[0]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
	printf("\t\t\t");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 05);
	map_name_user2(user_site[1]);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 07);
}