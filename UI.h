#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "define.h"
#include "Game.h"
#include "Signup.h"

void MainConsole();
void AccountSignUp();
void Login();
void UserMain();
void AdminMain();
void GameList();
void MyPage();

char *ID, *PW; // 로그인 아이뒤 패스워드

/*유저의 MyPage 임시*/
void MyPage() {
	int usernum;
	for (int i = 0; i < num_rows_user; i++) // 아이디확인
	{
		if (strcmp(ID, userData[i].id) == 0)
			usernum = i; // usernum에 몇번째 db에 저장되어있는지 확인.
	}
	COORD Cur;
	BasePrint();
	gotoxy(x + 10, y + 2); printf("MyPage"); Sleep(500);
	system("cls");
	gotoxy(x - 20, y - 4); printf(" MyPage");
	gotoxy(x - 23, y - 3); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");
	gotoxy(x - 23, y); printf("Name"); printf(" : %s", userData[usernum].name);
	gotoxy(x - 23, y + 2); printf("ID"); printf(" : %s", userData[usernum].id);
	gotoxy(x - 23, y + 4); printf("Nickname"); printf(" : %s", userData[usernum].nickName);
	gotoxy(x - 23, y + 6); printf("Mywallet");  printf(" : %f", userData[usernum].wallet);
	gotoxy(x - 23, y + 8); printf("Level"); printf(" : %d", userData[usernum].level);
	gotoxy(x + 15, y); printf("GameLIst");

	gotoxy(x - 20, y + 14); printf("▷Modify");
	gotoxy(x + 5, y + 14); printf("□Charge");
	gotoxy(x + 30, y + 14); printf("□Quit");
	gotoxy(x - 18, y + 14);//cursor location initialization

						   /*arrow key menu*/
	while (TRUE) {
		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case LEFT:
			if (Cur.X <= x - 18) break;//메뉴 선택 꼭대기에서 더 이상 올라가지 않도록
			gotoxy(x - 20, y + 14); printf("□Modify");
			gotoxy(x + 5, y + 14); printf("□Charge");
			gotoxy(x + 30, y + 14); printf("□Quit");
			gotoxy(Cur.X - 27, y + 14); printf("▷");
			break;
		case RIGHT:
			if (Cur.X > x + 30) break;//메뉴 선택 마지막에서 더 이상 내려가지 않도록
			gotoxy(x - 20, y + 14); printf("□Modify");
			gotoxy(x + 5, y + 14); printf("□Charge");
			gotoxy(x + 30, y + 14); printf("□Quit");
			gotoxy(Cur.X + 23, y + 14); printf("▷");
			
			break;
		case SPACE:
			if (Cur.X >= x + 30){
				flag = 0;
				return;
				}
			/*      case SPACE://게임 실행시 DB에서 보유게임인지 확인하는 코드가 게임 실행 전에 삽입 되거나 애초에 자신의 보유게임만 보이도록 설정
			if (Cur.Y == y + 6) {
			system("cls");
			TETRIS();
			}
			else if (Cur.Y == y + 8) {
			system("cls");
			TETRIS();
			}
			else if (Cur.Y == y + 10) {
			system("cls");
			TETRIS();
			}
			else if (Cur.Y == y + 12) {
			UserMain();
			}
			}*/
		}

	}
}

void GameList() {
	COORD Cur;
	BasePrint();
	int row = 0;
	gotoxy(x + 10, y + 2); printf("GameList"); Sleep(500);
	system("cls");
	gotoxy(x - 20, y - 4); printf(" MyPage");
	gotoxy(x - 23, y - 3); printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■");

	gotoxy(13, 20); printf("▷GameSelect");
	gotoxy(65, 20); printf("□Quit");
	

	for (int i = 0; i < num_rows_game; i++)
	{
		if(x+(row*25)==85)
		{
			y += 2;
			row = 0;
		}
		gotoxy(x - 23 + (25 * row), y); printf("□"); printf("%s", gameData[i].name);
		row++;
	}
	
	gotoxy(15, 20);//cursor location initialization

	/*arrow key menu*/
	
	while (TRUE) {
		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case LEFT:
			if (Cur.X <= x - 18) break;//메뉴 선택 꼭대기에서 더 이상 올라가지 않도록
			gotoxy(x - 22, y + 14); printf("□GameSelect");
			gotoxy(x + 30, y + 14); printf("□Quit");
			gotoxy(Cur.X - 54, y + 14); printf("▷");
			break;
		case RIGHT:
			if (Cur.X > x + 30) break;//메뉴 선택 마지막에서 더 이상 내려가지 않도록
			gotoxy(x - 22, y + 14); printf("□GameSelect");
			gotoxy(x + 30, y + 14); printf("□Quit");
			gotoxy(Cur.X + 50, y + 14); printf("▷");

			break;
		case SPACE:
			if (Cur.X >= x + 30) {
				flag = 0;
				return;
			}
			else
			{
				//게임선택,실행 부분
			}
		}
	}
	
}

void AdminMain() {
	COORD Cur;
	BasePrint();
	gotoxy(x + 10, y + 2); printf("Admin Main"); Sleep(100);

	gotoxy(x + 10, y + 6); printf("▷Game Edit \n");
	gotoxy(x + 10, y + 8); printf("□User Into Edit \n");
	gotoxy(x + 10, y + 10); printf("□Quit");
	gotoxy(x + 10, y + 6);//cursor location initialization

	/*arrow key menu*/
	while (TRUE) {


		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■");
			gotoxy(x, y + 1); printf("■■■□  ■□□    ■■□□■");
			gotoxy(x, y + 2); printf("□□□■■■    □□□□□■■");
			gotoxy(x, y + 3); printf("■■□■■  □  ■  □□■□□");
			gotoxy(x, y + 4); printf("■■  ■□□□■■■□■■□□");
			gotoxy(x + 10, y + 2); printf("Admin Main"); Sleep(100);

			gotoxy(x + 10, y + 6); printf("▷Game Edit \n");
			gotoxy(x + 10, y + 8); printf("□User Into Edit \n");
			gotoxy(x + 10, y + 10); printf("□Quit");
			gotoxy(x + 10, y + 6);//cursor location initialization

			flag = 1;
		}

		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case UP:
			if (Cur.Y <= y + 6) break;//메뉴 선택 꼭대기에서 더 이상 올라가지 않도록
			gotoxy(x + 10, y + 6); printf("□Game Edit \n");
			gotoxy(x + 10, y + 8); printf("□User Into Edit \n");
			gotoxy(x + 10, y + 10); printf("□Quit");
			gotoxy(x + 10, Cur.Y - 2); printf("▷");
			break;
		case DOWN:
			if (Cur.Y > y + 8) break;//메뉴 선택 마지막에서 더 이상 내려가지 않도록
			gotoxy(x + 10, y + 6); printf("□Game Edit \n");
			gotoxy(x + 10, y + 8); printf("□User Into Edit \n");
			gotoxy(x + 10, y + 10); printf("□Quit");
			gotoxy(x + 10, Cur.Y + 2); printf("▷");
			break;
		case SPACE:
			if (Cur.Y == y + 6) {//Select Game Edit
				GameList();
			}
			else if (Cur.Y == y + 8)//Select Userinfo
				MyPage();
			else if (Cur.Y == y + 10) {//Select Quit
				flag = 0;
				return;
			}
		}
	}
}
void UserMain() {
	COORD Cur;
	BasePrint();
	gotoxy(x + 10, y + 2); printf("Main"); Sleep(100);

	gotoxy(x + 10, y + 6); printf("▷Game List \n");
	gotoxy(x + 10, y + 8); printf("□My Page \n");
	gotoxy(x + 10, y + 10); printf("□Quit");
	gotoxy(x + 10, y + 6);//cursor location initialization

	/*arrow key menu*/
	while (TRUE) {

		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■");
			gotoxy(x, y + 1); printf("■■■□  ■□□    ■■□□■");
			gotoxy(x, y + 2); printf("□□□■■■    □□□□□■■");
			gotoxy(x, y + 3); printf("■■□■■  □  ■  □□■□□");
			gotoxy(x, y + 4); printf("■■  ■□□□■■■□■■□□");


			gotoxy(x + 10, y + 2); printf("Main"); Sleep(100);

			gotoxy(x + 10, y + 6); printf("▷Game List \n");
			gotoxy(x + 10, y + 8); printf("□My Page \n");
			gotoxy(x + 10, y + 10); printf("□Quit");
			gotoxy(x + 10, y + 6);//cursor location initialization
			flag = 1;
		}

		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case UP:
			if (Cur.Y <= y + 6) break;//메뉴 선택 꼭대기에서 더 이상 올라가지 않도록
			gotoxy(x + 10, y + 6); printf("□Game List \n");
			gotoxy(x + 10, y + 8); printf("□My Page \n");
			gotoxy(x + 10, y + 10); printf("□Quit");
			gotoxy(x + 10, Cur.Y - 2); printf("▷");
			break;
		case DOWN:
			if (Cur.Y > y + 8) break;//메뉴 선택 마지막에서 더 이상 내려가지 않도록
			gotoxy(x + 10, y + 6); printf("□Game List \n");
			gotoxy(x + 10, y + 8); printf("□My Page \n");
			gotoxy(x + 10, y + 10); printf("□Quit");
			gotoxy(x + 10, Cur.Y + 2); printf("▷");
			break;
		case SPACE:
			if (Cur.Y == y + 6) {//Select GameList
				GameList();
			}
			else if (Cur.Y == y + 8)//Select MyPage
				MyPage();
			else if (Cur.Y == y + 10) {//Select Quit
				flag = 0;
				return;
			}
		}
	}
}

void AccountSignUp() {
	char* ID;
	char* PW;
	char* checkPW;
	COORD Cur;

	ID = (char*)malloc(sizeof(char) * 20);
	PW = (char*)malloc(sizeof(char) * 20);
	checkPW = (char*)malloc(sizeof(char) * 20);

	BasePrint();
	gotoxy(x + 10, y + 2); printf("Account SignUp"); Sleep(100);

	gotoxy(x + 10, y + 6); printf("ID : \n");
	gotoxy(x + 10, y + 8); printf("PW : \n");
	gotoxy(x + 10, y + 10); printf("Name : \n");
	gotoxy(x + 10, y + 12); printf("Birth : \n");
	gotoxy(x + 10, y + 14); printf("NickName : \n");
	gotoxy(x + 2, y + 16); printf("▷SignUp");
	gotoxy(x + 12, y + 16); printf("□Quit");
	gotoxy(x, y + 18); printf("left <←>   right <→>   click <spacebar>");
	gotoxy(x + 2, y + 12);//cursor location initialization
	
	/*arrow key menu*/
	while (TRUE) {
		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■");
			gotoxy(x, y + 1); printf("■■■□  ■□□    ■■□□■");
			gotoxy(x, y + 2); printf("□□□■■■    □□□□□■■");
			gotoxy(x, y + 3); printf("■■□■■  □  ■  □□■□□");
			gotoxy(x, y + 4); printf("■■  ■□□□■■■□■■□□");


			gotoxy(x + 5, y + 2); printf("Account SignUp");

			gotoxy(x + 10, y + 6); printf("ID : \n");
			gotoxy(x + 10, y + 8); printf("PW : \n");
			gotoxy(x + 10, y + 10); printf("Name : \n");
			gotoxy(x + 10, y + 12); printf("Birth : \n");
			gotoxy(x + 10, y + 14); printf("NickName : \n");
			gotoxy(x + 2, y + 16); printf("▷SignUp");
			gotoxy(x + 12, y + 16); printf("□Quit");
			gotoxy(x, y + 15); printf("left <←>   right <→>   click <spacebar>");
			gotoxy(x + 2, y + 12);//cursor location initialization
			flag = 1;
		}

		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case LEFT:
			if (Cur.X >= x + 12) {
				gotoxy(x + 2, y + 12); printf("□SignUp");
				gotoxy(x + 12, y + 12); printf("□Quit");
				gotoxy(x + 2, y + 12); printf("▷");
			}
			break;
		case RIGHT:
			if (Cur.X >= x + 2) {
				gotoxy(x + 2, y + 12); printf("□SignUp");
				gotoxy(x + 12, y + 12); printf("□Quit");
				gotoxy(x + 12, y + 12); printf("▷");
				break;
			}
		case SPACE:
			if (Cur.X >= x + 12) {//select Quit
				flag = 0;
				return;
			}
			else if (Cur.X >= x + 2) {//Select SignUp
				createAccount();
				
				
			}
		}
	}
}





void Login() {
//ID와 PASSWORD
	ID = (char*)malloc(sizeof(char) * 20);
	PW = (char*)malloc(sizeof(char) * 20);
	COORD Cur;//Console cursor

	BasePrint();
	gotoxy(x + 10, y + 2); printf("Login"); Sleep(100);

	gotoxy(x+10,y+6); printf("ID : \n");
	gotoxy(x+10,y+8); printf("PW : \n");
	gotoxy(x+2,y+10); printf("▷Login");
	gotoxy(x+12,y+10); printf("□Quit");
	gotoxy(x, y + 15); printf("left <←>   right <→>   click <spacebar>");
	gotoxy(x + 2, y + 10);//cursor location initialization
	while (TRUE) {
		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■");
			gotoxy(x, y + 1); printf("■■■□  ■□□    ■■□□■");
			gotoxy(x, y + 2); printf("□□□■■■    □□□□□■■");
			gotoxy(x, y + 3); printf("■■□■■  □  ■  □□■□□");
			gotoxy(x, y + 4); printf("■■  ■□□□■■■□■■□□");


			gotoxy(x + 5, y + 2); printf("Login");


			gotoxy(x + 10, y + 6); printf("ID : \n");
			gotoxy(x + 10, y + 8); printf("PW : \n");
			gotoxy(x + 2, y + 10); printf("▷Login");
			gotoxy(x + 12, y + 10); printf("□Quit");
			gotoxy(x, y + 15); printf("left <←>   right <→>   click <spacebar>");
			gotoxy(x + 2, y + 10);//cursor location initialization

			flag = 1;
		}

		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case LEFT:
			if (Cur.X >= x + 12) {
				gotoxy(x + 2, y + 10); printf("□Login");
				gotoxy(x + 12, y + 10); printf("□Quit");
				gotoxy(x + 2, y + 10); printf("▷");
			}
			break;
		case RIGHT:
			if (Cur.X >= x + 2) {
				gotoxy(x + 2, y + 10); printf("□Login");
				gotoxy(x + 12, y + 10); printf("□Quit");
				gotoxy(x + 12, y + 10); printf("▷");
				break;
			}
		case SPACE:
			if (Cur.X >= x + 12) {//select Quit
				flag = 0;
				return;
			}
			else if (Cur.X >= x+2) {//select Login
				setcursortype(NORMALCURSOR);//visible console cursor
				gotoxy(x + 15, y + 6); scanf("%s", ID);
				gotoxy(x + 15, y + 8);PW = Password();
				setcursortype(NOCURSOR);//unvisible console cursor			
				
				/*
				if(DB에 있는 ID와 PW비교)<= int 형으로 받아옴 int check(char *ID, char *PW) FALSE 승인 X TRUE 승인 O ADMIN 관리자
				mysql에 있는 데이터 베이스에서 자료들을 받아와 hash table에 밖아놓는 함수
				그 뒤 id와 pw가 맞을 경우는 로그인 되고 아닐 경우는 다시 반복
				즉 bool check(char* ID,char *PW)
				- 변수 key를 선언하여 ID의 key값을 계산, 그후 mysql에서 받아온 해쉬 테이블과 
				비교 후 ID와 PW가 동시에 만족하는 경우가 있을 경우 참 을 반환
				만약 참이 반환되면 Main(로그인 된 후 페이지로 간다)
				거짓이 반환되면 로그인할때 쓴 글자를 지운다.*/


				//(임시) 실패시
				//gotoxy(x + 15, y + 6); printf("                          ");
			//	gotoxy(x + 15, y + 8); printf("                          ");
				//(임시) 성공시
				/**********************************************************************************
				작성자    : 이구협, 최선욱
				작성일    : 2016.10.18
				코드 설명 :
				**********************************************************************************/
				/*
					수정해야함
				*/
				//UserMain();//지워야함 임시
				int loginCheckTemp = loginCheck(ID, PW, userData, num_rows_user);
				if (loginCheckTemp == 3) {
					AdminMain();
				}
				else if (loginCheckTemp == 1) {
					UserMain();//임시로 무조건 usermain 으로 감
				}
				else {
					return;
				}
			}
		}
	}
}

void MainConsole() {
	
	COORD Cur;//Console cursor

	BasePrint();// 기본 틀을 그리는 함수
	gotoxy(x + 5, y + 2); printf("GAME MANAGEMENT SYSTEM"); Sleep(100);
	
	gotoxy(x + 7, y + 6); printf("▷Login");
	gotoxy(x + 7, y + 8); printf("□Sign up");
	gotoxy(x + 7, y + 10); printf("□Quit");
	gotoxy(x , y + 15); printf("up <↑>   down <↓>   click <spacebar>");
	gotoxy(x + 7, y + 6);//cursor location initialization
	
	/*arrow key menu*/
	while (TRUE) {
		/*뒤로 가기용 repaint(다음 창에서 QUIT을 눌렀을 경우 repaint한다)*/
		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■");
			gotoxy(x, y + 1); printf("■■■□  ■□□    ■■□□■");
			gotoxy(x, y + 2); printf("□□□■■■    □□□□□■■");
			gotoxy(x, y + 3); printf("■■□■■  □  ■  □□■□□");
			gotoxy(x, y + 4); printf("■■  ■□□□■■■□■■□□");

			gotoxy(x + 5, y + 2); printf("GAME MANAGEMENT SYSTEM");

			gotoxy(x + 7, y + 6); printf("▷Login");
			gotoxy(x + 7, y + 8); printf("□Sign up");
			gotoxy(x + 7, y + 10); printf("□Quit");
			gotoxy(x, y + 15); printf("up <↑>   down <↓>   click <spacebar>");

			gotoxy(x + 7, y + 6);//cursor location initialization
			flag = 1;
		}
		
		int cursor=0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();
		
		switch (cursor) {
			case UP:
				if (Cur.Y <= y + 6) break;//메뉴 선택 꼭대기에서 더 이상 올라가지 않도록
				gotoxy(x + 7, y + 6); printf("□Login");
				gotoxy(x + 7, y + 8); printf("□Sign up");
				gotoxy(x + 7, y + 10); printf("□Quit");
				gotoxy(x + 7, Cur.Y -2); printf("▷");
				break;
			case DOWN:
				if (Cur.Y > y + 8) break;//메뉴 선택 마지막에서 더 이상 내려가지 않도록
				gotoxy(x + 7, y + 6); printf("□Login");
				gotoxy(x + 7, y + 8); printf("□Sign up");
				gotoxy(x + 7, y + 10); printf("□Quit");
				gotoxy(x + 7, Cur.Y + 2); printf("▷");
				break;
			case SPACE:
				if (Cur.Y == y + 6) {//Login 선택 시 Login page를 불러옴
					Login();
				}
				else if (Cur.Y == y + 8)//AccountSignUp 선택 시 AccountSignUp을 불러옴
					AccountSignUp();
				else if (Cur.Y == y + 10) {//Quit 선택 시 프로그램 종료
					system("cls");
					gotoxy(x + 7, y + 6); printf("THANK YOU.");
					return;
				}
			}
		}
}
