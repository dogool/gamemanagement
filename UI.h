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

char *ID, *PW; // �α��� ���̵� �н�����

/*������ MyPage �ӽ�*/
void MyPage() {
	int usernum;
	for (int i = 0; i < num_rows_user; i++) // ���̵�Ȯ��
	{
		if (strcmp(ID, userData[i].id) == 0)
			usernum = i; // usernum�� ���° db�� ����Ǿ��ִ��� Ȯ��.
	}
	COORD Cur;
	BasePrint();
	gotoxy(x + 10, y + 2); printf("MyPage"); Sleep(500);
	system("cls");
	gotoxy(x - 20, y - 4); printf(" MyPage");
	gotoxy(x - 23, y - 3); printf("��������������������������������������");
	gotoxy(x - 23, y); printf("Name"); printf(" : %s", userData[usernum].name);
	gotoxy(x - 23, y + 2); printf("ID"); printf(" : %s", userData[usernum].id);
	gotoxy(x - 23, y + 4); printf("Nickname"); printf(" : %s", userData[usernum].nickName);
	gotoxy(x - 23, y + 6); printf("Mywallet");  printf(" : %f", userData[usernum].wallet);
	gotoxy(x - 23, y + 8); printf("Level"); printf(" : %d", userData[usernum].level);
	gotoxy(x + 15, y); printf("GameLIst");

	gotoxy(x - 20, y + 14); printf("��Modify");
	gotoxy(x + 5, y + 14); printf("��Charge");
	gotoxy(x + 30, y + 14); printf("��Quit");
	gotoxy(x - 18, y + 14);//cursor location initialization

						   /*arrow key menu*/
	while (TRUE) {
		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case LEFT:
			if (Cur.X <= x - 18) break;//�޴� ���� ����⿡�� �� �̻� �ö��� �ʵ���
			gotoxy(x - 20, y + 14); printf("��Modify");
			gotoxy(x + 5, y + 14); printf("��Charge");
			gotoxy(x + 30, y + 14); printf("��Quit");
			gotoxy(Cur.X - 27, y + 14); printf("��");
			break;
		case RIGHT:
			if (Cur.X > x + 30) break;//�޴� ���� ���������� �� �̻� �������� �ʵ���
			gotoxy(x - 20, y + 14); printf("��Modify");
			gotoxy(x + 5, y + 14); printf("��Charge");
			gotoxy(x + 30, y + 14); printf("��Quit");
			gotoxy(Cur.X + 23, y + 14); printf("��");
			
			break;
		case SPACE:
			if (Cur.X >= x + 30){
				flag = 0;
				return;
				}
			/*      case SPACE://���� ����� DB���� ������������ Ȯ���ϴ� �ڵ尡 ���� ���� ���� ���� �ǰų� ���ʿ� �ڽ��� �������Ӹ� ���̵��� ����
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
	gotoxy(x - 23, y - 3); printf("��������������������������������������");

	gotoxy(13, 20); printf("��GameSelect");
	gotoxy(65, 20); printf("��Quit");
	

	for (int i = 0; i < num_rows_game; i++)
	{
		if(x+(row*25)==85)
		{
			y += 2;
			row = 0;
		}
		gotoxy(x - 23 + (25 * row), y); printf("��"); printf("%s", gameData[i].name);
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
			if (Cur.X <= x - 18) break;//�޴� ���� ����⿡�� �� �̻� �ö��� �ʵ���
			gotoxy(x - 22, y + 14); printf("��GameSelect");
			gotoxy(x + 30, y + 14); printf("��Quit");
			gotoxy(Cur.X - 54, y + 14); printf("��");
			break;
		case RIGHT:
			if (Cur.X > x + 30) break;//�޴� ���� ���������� �� �̻� �������� �ʵ���
			gotoxy(x - 22, y + 14); printf("��GameSelect");
			gotoxy(x + 30, y + 14); printf("��Quit");
			gotoxy(Cur.X + 50, y + 14); printf("��");

			break;
		case SPACE:
			if (Cur.X >= x + 30) {
				flag = 0;
				return;
			}
			else
			{
				//���Ӽ���,���� �κ�
			}
		}
	}
	
}

void AdminMain() {
	COORD Cur;
	BasePrint();
	gotoxy(x + 10, y + 2); printf("Admin Main"); Sleep(100);

	gotoxy(x + 10, y + 6); printf("��Game Edit \n");
	gotoxy(x + 10, y + 8); printf("��User Into Edit \n");
	gotoxy(x + 10, y + 10); printf("��Quit");
	gotoxy(x + 10, y + 6);//cursor location initialization

	/*arrow key menu*/
	while (TRUE) {


		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("����������������");
			gotoxy(x, y + 1); printf("�����  ����    ������");
			gotoxy(x, y + 2); printf("�������    ��������");
			gotoxy(x, y + 3); printf("������  ��  ��  ������");
			gotoxy(x, y + 4); printf("���  �������������");
			gotoxy(x + 10, y + 2); printf("Admin Main"); Sleep(100);

			gotoxy(x + 10, y + 6); printf("��Game Edit \n");
			gotoxy(x + 10, y + 8); printf("��User Into Edit \n");
			gotoxy(x + 10, y + 10); printf("��Quit");
			gotoxy(x + 10, y + 6);//cursor location initialization

			flag = 1;
		}

		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case UP:
			if (Cur.Y <= y + 6) break;//�޴� ���� ����⿡�� �� �̻� �ö��� �ʵ���
			gotoxy(x + 10, y + 6); printf("��Game Edit \n");
			gotoxy(x + 10, y + 8); printf("��User Into Edit \n");
			gotoxy(x + 10, y + 10); printf("��Quit");
			gotoxy(x + 10, Cur.Y - 2); printf("��");
			break;
		case DOWN:
			if (Cur.Y > y + 8) break;//�޴� ���� ���������� �� �̻� �������� �ʵ���
			gotoxy(x + 10, y + 6); printf("��Game Edit \n");
			gotoxy(x + 10, y + 8); printf("��User Into Edit \n");
			gotoxy(x + 10, y + 10); printf("��Quit");
			gotoxy(x + 10, Cur.Y + 2); printf("��");
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

	gotoxy(x + 10, y + 6); printf("��Game List \n");
	gotoxy(x + 10, y + 8); printf("��My Page \n");
	gotoxy(x + 10, y + 10); printf("��Quit");
	gotoxy(x + 10, y + 6);//cursor location initialization

	/*arrow key menu*/
	while (TRUE) {

		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("����������������");
			gotoxy(x, y + 1); printf("�����  ����    ������");
			gotoxy(x, y + 2); printf("�������    ��������");
			gotoxy(x, y + 3); printf("������  ��  ��  ������");
			gotoxy(x, y + 4); printf("���  �������������");


			gotoxy(x + 10, y + 2); printf("Main"); Sleep(100);

			gotoxy(x + 10, y + 6); printf("��Game List \n");
			gotoxy(x + 10, y + 8); printf("��My Page \n");
			gotoxy(x + 10, y + 10); printf("��Quit");
			gotoxy(x + 10, y + 6);//cursor location initialization
			flag = 1;
		}

		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case UP:
			if (Cur.Y <= y + 6) break;//�޴� ���� ����⿡�� �� �̻� �ö��� �ʵ���
			gotoxy(x + 10, y + 6); printf("��Game List \n");
			gotoxy(x + 10, y + 8); printf("��My Page \n");
			gotoxy(x + 10, y + 10); printf("��Quit");
			gotoxy(x + 10, Cur.Y - 2); printf("��");
			break;
		case DOWN:
			if (Cur.Y > y + 8) break;//�޴� ���� ���������� �� �̻� �������� �ʵ���
			gotoxy(x + 10, y + 6); printf("��Game List \n");
			gotoxy(x + 10, y + 8); printf("��My Page \n");
			gotoxy(x + 10, y + 10); printf("��Quit");
			gotoxy(x + 10, Cur.Y + 2); printf("��");
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
	gotoxy(x + 2, y + 16); printf("��SignUp");
	gotoxy(x + 12, y + 16); printf("��Quit");
	gotoxy(x, y + 18); printf("left <��>   right <��>   click <spacebar>");
	gotoxy(x + 2, y + 12);//cursor location initialization
	
	/*arrow key menu*/
	while (TRUE) {
		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("����������������");
			gotoxy(x, y + 1); printf("�����  ����    ������");
			gotoxy(x, y + 2); printf("�������    ��������");
			gotoxy(x, y + 3); printf("������  ��  ��  ������");
			gotoxy(x, y + 4); printf("���  �������������");


			gotoxy(x + 5, y + 2); printf("Account SignUp");

			gotoxy(x + 10, y + 6); printf("ID : \n");
			gotoxy(x + 10, y + 8); printf("PW : \n");
			gotoxy(x + 10, y + 10); printf("Name : \n");
			gotoxy(x + 10, y + 12); printf("Birth : \n");
			gotoxy(x + 10, y + 14); printf("NickName : \n");
			gotoxy(x + 2, y + 16); printf("��SignUp");
			gotoxy(x + 12, y + 16); printf("��Quit");
			gotoxy(x, y + 15); printf("left <��>   right <��>   click <spacebar>");
			gotoxy(x + 2, y + 12);//cursor location initialization
			flag = 1;
		}

		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case LEFT:
			if (Cur.X >= x + 12) {
				gotoxy(x + 2, y + 12); printf("��SignUp");
				gotoxy(x + 12, y + 12); printf("��Quit");
				gotoxy(x + 2, y + 12); printf("��");
			}
			break;
		case RIGHT:
			if (Cur.X >= x + 2) {
				gotoxy(x + 2, y + 12); printf("��SignUp");
				gotoxy(x + 12, y + 12); printf("��Quit");
				gotoxy(x + 12, y + 12); printf("��");
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
//ID�� PASSWORD
	ID = (char*)malloc(sizeof(char) * 20);
	PW = (char*)malloc(sizeof(char) * 20);
	COORD Cur;//Console cursor

	BasePrint();
	gotoxy(x + 10, y + 2); printf("Login"); Sleep(100);

	gotoxy(x+10,y+6); printf("ID : \n");
	gotoxy(x+10,y+8); printf("PW : \n");
	gotoxy(x+2,y+10); printf("��Login");
	gotoxy(x+12,y+10); printf("��Quit");
	gotoxy(x, y + 15); printf("left <��>   right <��>   click <spacebar>");
	gotoxy(x + 2, y + 10);//cursor location initialization
	while (TRUE) {
		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("����������������");
			gotoxy(x, y + 1); printf("�����  ����    ������");
			gotoxy(x, y + 2); printf("�������    ��������");
			gotoxy(x, y + 3); printf("������  ��  ��  ������");
			gotoxy(x, y + 4); printf("���  �������������");


			gotoxy(x + 5, y + 2); printf("Login");


			gotoxy(x + 10, y + 6); printf("ID : \n");
			gotoxy(x + 10, y + 8); printf("PW : \n");
			gotoxy(x + 2, y + 10); printf("��Login");
			gotoxy(x + 12, y + 10); printf("��Quit");
			gotoxy(x, y + 15); printf("left <��>   right <��>   click <spacebar>");
			gotoxy(x + 2, y + 10);//cursor location initialization

			flag = 1;
		}

		int cursor = 0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();

		switch (cursor) {
		case LEFT:
			if (Cur.X >= x + 12) {
				gotoxy(x + 2, y + 10); printf("��Login");
				gotoxy(x + 12, y + 10); printf("��Quit");
				gotoxy(x + 2, y + 10); printf("��");
			}
			break;
		case RIGHT:
			if (Cur.X >= x + 2) {
				gotoxy(x + 2, y + 10); printf("��Login");
				gotoxy(x + 12, y + 10); printf("��Quit");
				gotoxy(x + 12, y + 10); printf("��");
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
				if(DB�� �ִ� ID�� PW��)<= int ������ �޾ƿ� int check(char *ID, char *PW) FALSE ���� X TRUE ���� O ADMIN ������
				mysql�� �ִ� ������ ���̽����� �ڷ���� �޾ƿ� hash table�� �۾Ƴ��� �Լ�
				�� �� id�� pw�� ���� ���� �α��� �ǰ� �ƴ� ���� �ٽ� �ݺ�
				�� bool check(char* ID,char *PW)
				- ���� key�� �����Ͽ� ID�� key���� ���, ���� mysql���� �޾ƿ� �ؽ� ���̺�� 
				�� �� ID�� PW�� ���ÿ� �����ϴ� ��찡 ���� ��� �� �� ��ȯ
				���� ���� ��ȯ�Ǹ� Main(�α��� �� �� �������� ����)
				������ ��ȯ�Ǹ� �α����Ҷ� �� ���ڸ� �����.*/


				//(�ӽ�) ���н�
				//gotoxy(x + 15, y + 6); printf("                          ");
			//	gotoxy(x + 15, y + 8); printf("                          ");
				//(�ӽ�) ������
				/**********************************************************************************
				�ۼ���    : �̱���, �ּ���
				�ۼ���    : 2016.10.18
				�ڵ� ���� :
				**********************************************************************************/
				/*
					�����ؾ���
				*/
				//UserMain();//�������� �ӽ�
				int loginCheckTemp = loginCheck(ID, PW, userData, num_rows_user);
				if (loginCheckTemp == 3) {
					AdminMain();
				}
				else if (loginCheckTemp == 1) {
					UserMain();//�ӽ÷� ������ usermain ���� ��
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

	BasePrint();// �⺻ Ʋ�� �׸��� �Լ�
	gotoxy(x + 5, y + 2); printf("GAME MANAGEMENT SYSTEM"); Sleep(100);
	
	gotoxy(x + 7, y + 6); printf("��Login");
	gotoxy(x + 7, y + 8); printf("��Sign up");
	gotoxy(x + 7, y + 10); printf("��Quit");
	gotoxy(x , y + 15); printf("up <��>   down <��>   click <spacebar>");
	gotoxy(x + 7, y + 6);//cursor location initialization
	
	/*arrow key menu*/
	while (TRUE) {
		/*�ڷ� ����� repaint(���� â���� QUIT�� ������ ��� repaint�Ѵ�)*/
		if (flag == 0) {
			system("cls");
			gotoxy(x, y + 0); printf("����������������");
			gotoxy(x, y + 1); printf("�����  ����    ������");
			gotoxy(x, y + 2); printf("�������    ��������");
			gotoxy(x, y + 3); printf("������  ��  ��  ������");
			gotoxy(x, y + 4); printf("���  �������������");

			gotoxy(x + 5, y + 2); printf("GAME MANAGEMENT SYSTEM");

			gotoxy(x + 7, y + 6); printf("��Login");
			gotoxy(x + 7, y + 8); printf("��Sign up");
			gotoxy(x + 7, y + 10); printf("��Quit");
			gotoxy(x, y + 15); printf("up <��>   down <��>   click <spacebar>");

			gotoxy(x + 7, y + 6);//cursor location initialization
			flag = 1;
		}
		
		int cursor=0;//arrow menu select
		Cur = getXY();//get Cursor location
		cursor = getch();
		
		switch (cursor) {
			case UP:
				if (Cur.Y <= y + 6) break;//�޴� ���� ����⿡�� �� �̻� �ö��� �ʵ���
				gotoxy(x + 7, y + 6); printf("��Login");
				gotoxy(x + 7, y + 8); printf("��Sign up");
				gotoxy(x + 7, y + 10); printf("��Quit");
				gotoxy(x + 7, Cur.Y -2); printf("��");
				break;
			case DOWN:
				if (Cur.Y > y + 8) break;//�޴� ���� ���������� �� �̻� �������� �ʵ���
				gotoxy(x + 7, y + 6); printf("��Login");
				gotoxy(x + 7, y + 8); printf("��Sign up");
				gotoxy(x + 7, y + 10); printf("��Quit");
				gotoxy(x + 7, Cur.Y + 2); printf("��");
				break;
			case SPACE:
				if (Cur.Y == y + 6) {//Login ���� �� Login page�� �ҷ���
					Login();
				}
				else if (Cur.Y == y + 8)//AccountSignUp ���� �� AccountSignUp�� �ҷ���
					AccountSignUp();
				else if (Cur.Y == y + 10) {//Quit ���� �� ���α׷� ����
					system("cls");
					gotoxy(x + 7, y + 6); printf("THANK YOU.");
					return;
				}
			}
		}
}
