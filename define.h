#pragma once
#pragma once

#define LEFT 75 //�·� �̵�    //Ű���尪�� 
#define RIGHT 77 //��� �̵� 
#define UP 72 //�����̵� 
#define DOWN 80 //�Ʒ����̵�
#define SPACE 32 //Ŭ��
#define TRUE 1
#define FALSE 0
#define ADMIN 3


int flag = 1;//�ڷΰ��� ������ �ϴ� flag����(flag==0�̸� �ڷ� �ڽ��� ȭ���� ����)
int x = 35, y = 6;//��ġ�� �����ϰ� ��ġ�ϱ� ���� ����
typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //Ŀ������� �Լ��� ���Ǵ� ������ 

void setcursortype(CURSOR_TYPE c) { //Ŀ������� �Լ� 

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
	gotoxy(x, y + 0); printf("����������������"); Sleep(100);
	gotoxy(x, y + 1); printf("�����  ����    ������"); Sleep(100);
	gotoxy(x, y + 2); printf("�������    ��������"); Sleep(100);
	gotoxy(x, y + 3); printf("������  ��  ��  ������"); Sleep(100);
	gotoxy(x, y + 4); printf("���  �������������"); Sleep(100);

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
