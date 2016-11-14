#pragma once
#pragma once

#define LEFT 75 //좌로 이동    //키보드값들 
#define RIGHT 77 //우로 이동 
#define UP 72 //위로이동 
#define DOWN 80 //아래로이동
#define SPACE 32 //클릭
#define TRUE 1
#define FALSE 0
#define ADMIN 3


int flag = 1;//뒤로가기 역할을 하는 flag변수(flag==0이면 뒤로 자신의 화면을 끝냄)
int x = 35, y = 6;//위치를 용이하게 배치하기 위한 변수
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //커서숨기는 함수에 사용되는 열거형 

void setcursortype(CURSOR_TYPE c) { //커서숨기는 함수 

	CONSOLE_CURSOR_INFO CurInfo;
	switch (c) {
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void textColor(int colorNum) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorNum);
}

COORD getXY() {
	COORD Cur;
	CONSOLE_SCREEN_BUFFER_INFO a;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
	Cur.X = a.dwCursorPosition.X;
	Cur.Y = a.dwCursorPosition.Y;
	return Cur;
}

void BasePrint() {
	system("cls");
	gotoxy(x, y + 0); printf("■□□□■■■□□■■□□■■"); Sleep(100);
	gotoxy(x, y + 1); printf("■■■□  ■□□    ■■□□■"); Sleep(100);
	gotoxy(x, y + 2); printf("□□□■■■    □□□□□■■"); Sleep(100);
	gotoxy(x, y + 3); printf("■■□■■  □  ■  □□■□□"); Sleep(100);
	gotoxy(x, y + 4); printf("■■  ■□□□■■■□■■□□"); Sleep(100);

}

char* Password() {
	char* str, c = ' ';
	str = (char*)malloc(sizeof(char) * 20);
	int i = 0;

	while (i <= 20) {
		str[i] = getch();
		c = str[i];
		if (c == 13) break;
		else printf("*");
		i++;
	}
	str[i] = '\0';
	return str;
}
