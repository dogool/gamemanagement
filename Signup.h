#ifndef SIGNUP_H
#define SIGNUP_H

#include <mysql.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "define.h"
//#include <windows.h>

#define DB_HOST "127.0.0.1"
#define DB_USER "root"
#define DB_PASS "tjs12589*"
#define DB_NAME "Gamemanager_db"
//#define CHOP(x) x[strlen(x) - 1] = ' '

typedef struct GameInfo {
	char name[20];
	float price;
	char genre[50];
	int downloadCount;
	float score;
	char seller[50];
	char introduce[200];
	char reviews[200];
	char patchUpdate[200];
	int id;
} gInfo;

typedef struct UserInfo {
	char name[20];
	char birth[30];
	char id[20];
	char password[20];
	char nickName[20];
	float wallet;
	int level;
	int gameList;
} uInfo;

/*****************************************************************************************************************************************************
작성자    : 이구협
작성일    : 2016.10.17
변수 설명 : MySQL에서 데이터 가져오기, 데이터 삽입 등을 수행하기 위해 사용하는 변수들이다.
*****************************************************************************************************************************************************/
MYSQL *connection = NULL, conn;
MYSQL_RES *sql_result;
MYSQL_ROW sql_row;
int query_stat;
char query[255];
/*****************************************************************************************************************************************************
*   작성자    : 이구협
*   작성일    : 2016.10.17
*   변수 설명 : 테이블에서 가져온 결과셋의 개수(column의 개수)를 가져와 int형 num_fields에 저장한다.
*****************************************************************************************************************************************************/
int num_rows;
/*****************************************************************************************************************************************************
*   작성자    : 이구협
*   작성일    : 2016.10.17
*   변수 설명 : 전역 변수로 선언하고, uInfo형으로 정의한 구조체 UserInfo의 데이터를 MySQL내에 구현된 Gamemanager_db의 table UserInfo에서 가져온
data들을 저장하기 위하여 구조체 포인터 uInfo *userData를 선언하고 동적할당하였다.
동적할당 시의 크기는 num_fields이다.
*****************************************************************************************************************************************************/
uInfo *userData;
int i = 0, j = 0, k = 0;

/*****************************************************************************************************************************************************
*   작성자    : 이구협
*   작성일    : 2016.10.17
*   함수명    : idDuplicationCheck
*   매개변수  : char *id
*   함수 설명 : 매개변수로 넘겨진 char *형(이하 string이라 칭한다) id를 MySQL내에 구현된 Gamemanager_db의 table UserInfo테이블에서 가져온 data ID를
string.h에 구현된 strcmp()함수를 이용하여 id에 중복이 있는지 확인한다.
Id가 중복인 경우 1을 return하고, 중복이 아닌 경우 0을 return한다.
*****************************************************************************************************************************************************/
int idDuplicationCheck(char *id, uInfo *userData, int indexSize) {
	int duplicationCheck = 0;
	int i;
	/*
	매개변수로 넘겨진 id와 userDataId가 완전히 같은 경우 중복이므로 1을 return한다.
	*/
	for (i = 0; i < indexSize; i++) {
		if (strcmp(id, userData[i].id) == 0) {
			duplicationCheck = 1;
		}
		else {
			duplicationCheck = 0;
		}
	}
	return duplicationCheck;
}

/*****************************************************************************************************************************************************
작성자    : 이구협
작성일    : 2016.10.17
함수명    : loginCheck
매개변수  : char *id, char *password, char *userDataId, char *userDataPassword
함수 설명 : login을 처리하는 함수이다. 매개변수로 넘겨진 id, password값이 uInfo형 배열 userData내의 id와 password값이 일치하는지 판단하여
사용자가 확인되면 1을 return하고, 확인되지 않으면 0을 return한다.
*****************************************************************************************************************************************************/
int loginCheck(char *id, char *password, uInfo *userData, int indexSize) {
	int idCheck = 0;
	int passwdCheck = 0;
	int i;

	/*
	indexSize만큼 반복된다.
	*/
	for (i = 0; i < indexSize; i++) {
		/*
		id의 값이 userData[i].id의 값과 같은 경우 idCheck의 값을 1로 설정한다.
		*/
		if (strcmp(id, userData[i].id) == 0) {
			idCheck = 1;
		}
		else if (strcmp(id, "admin") == 0) {
			idCheck = 3;
			if (strcmp(password, "admin") == 0) {
				passwdCheck = 3;
			}
			if (idCheck == 3 && passwdCheck == 3) {
				printf("\nYou are admin!!\n");
				Sleep(2000);
				return 3;
			}
		}
		/*
		그렇지 않은 경우 idCheck의 값을 0으로 설정한다.
		*/
		else {
			idCheck = 0;
		}
		/*
		idCheck의 값이 1인 경우 password를 검사한다.
		*/
		if (idCheck == 1) {
			/*
			password의 값이 userData[i].password의 값과 같은 경우 passwdCheck의 값을 1로 설정한다.
			그리고 break;를 통해 반복문을 종료시킨다.
			*/
			if (strcmp(password, userData[i].password) == 0) {
				passwdCheck = 1;
				break;
			}
			/*
			password의 값이 userData[i].password의 값과 다른 경우 passwdCheck의 값을 0으로 설정한다.
			그리고 break;를 통해 반복문을 종료시킨다.
			*/
			else {
				passwdCheck = 0;
				break;
			}
		}
	}
	/*
	idCheck의 값과 passwdCheck의 값이 모두 1인 경우 로그인에 성공했음을 출력하고 1을 return한다.
	*/
	if (idCheck == 1 && passwdCheck == 1) {
		system("cls");
		gotoxy(x + 5, y + 2);   printf("\nLogin Success!!\nWelcome!! %S", id);

		Sleep(2000);
		return 1;
	}
	/*
	idCheck의 값이 1이고 passwdCheck의 값이 0인 경우 id에 대한 비밀번호 입력이 잘못된 경우이다.
	따라서, password를 잘못 입력하였다는 구문을 출력한 뒤, 0을 return한다.
	*/
	else if (idCheck == 1 && passwdCheck == 0) {
		printf("\nIncorrect password, please retry...\n");
		Sleep(2000);
		return 0;
	}
	/*
	나머지 경우는 idCheck의 값이 0인 경우이다.
	id가 존재하지 않으므로 id가 틀렸음을 출력한다.
	그리고 회원가입을 권유한다.
	마지막으로 -1을 return한다.
	*/
	else {
		printf("\nIncorrect ID\nAre you not a member? membership please!!!");
		Sleep(2000);
		return -1;
	}
}

/*
작성자    : 이구협
작성일    : 2016.10.18
함수명    :
매개변수  :
함수 설명 :
*/
int initiate() {
	// strtof()함수의 매개변수로 넘겨짐.
	char *junk = (char *)calloc(100, sizeof(char));

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if (connection == NULL) {
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		return 1;
	}

	query_stat = mysql_query(connection, "select * from UserInfo");

	if (query_stat != 0) {
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		return 1;
	}

	sql_result = mysql_store_result(connection);

	/*****************************************************************************************************************************************************
	*   작성자    : 이구협
	*   작성일    : 2016.10.17
	*   변수 설명 : 테이블에서 가져온 결과셋의 개수(column의 개수)를 가져와 int형 num_fields에 저장한다.
	*****************************************************************************************************************************************************/
	num_rows = mysql_num_rows(sql_result);
	/*****************************************************************************************************************************************************
	*   작성자    : 이구협
	*   작성일    : 2016.10.17
	*   변수 설명 : 전역 변수로 선언하고, uInfo형으로 정의한 구조체 UserInfo의 데이터를 MySQL내에 구현된 Gamemanager_db의 table UserInfo에서 가져온
	data들을 저장하기 위하여 구조체 포인터 uInfo *userData를 선언하고 동적할당하였다.
	동적할당 시의 크기는 num_fields이다.
	*****************************************************************************************************************************************************/
	userData = (uInfo *)calloc(num_rows, sizeof(uInfo));

	/*****************************************************************************************************************************************************
	작성자    : 이구협
	작성일    : 2016.10.17
	코드 설명 :
	*****************************************************************************************************************************************************/
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		for (i = 0; i < num_rows; i++) {
			strcpy(userData[i].name, sql_row[j++]);
			strcpy(userData[i].birth, sql_row[j++]);
			strcpy(userData[i].id, sql_row[j++]);
			strcpy(userData[i].password, sql_row[j++]);
			strcpy(userData[i].nickName, sql_row[j++]);
			userData[i].wallet = strtof(sql_row[j++], NULL);
			userData[i].level = atoi(sql_row[j++]);
			userData[i].gameList = atoi(sql_row[j++]);
			j = 0;
		}
	}

	mysql_free_result(sql_result);

	mysql_close(connection);
}

/************************************************************************************************************************************************************************
작성자    : 이구협
작성일    : 2016.11.02
함수명    : createAccount
매개변수  : void
함수 설명 : 사용자의 계정을 생성하는 코드이다. 처음에 ID를 입력받은 후, idDuplicationCheck()함수를 호출하여 이미 생성된 아이디가 있는지 중복검사를 수행한다.
중복이 아닌 경우, password를 입력받는다. 나머지 계정 정보를 전부 입력받은 뒤, MySQL의 gamemanager_db에 존재하는 userInfo테이블에 데이터를 삽입한다.
************************************************************************************************************************************************************************/
void createAccount() {
	uInfo newUser;
	char* PW;
	PW = (char*)malloc(sizeof(char) * 20);

	setcursortype(NORMALCURSOR);//visible console cursor
	gotoxy(x + 15, y + 6); scanf("%s", newUser.id);

	if(idDuplicationCheck(newUser.id, userData, num_rows) == 1) {
		system("cls");
		gotoxy(x + 10, y + 6); printf("ID duplicated!!\tPlease retype ID");
		flag = 0;
		return;
	}

	gotoxy(x + 15, y + 8); PW = Password();
	strcpy(newUser.password, PW);
	
	gotoxy(x + 16, y + 10); scanf("%s", newUser.name);
	gotoxy(x + 18, y + 12); scanf("%s", newUser.birth);
	gotoxy(x + 20, y + 14);scanf("%s", newUser.nickName);

	setcursortype(NOCURSOR);//unvisible console cursor
	newUser.level = 0;
	newUser.wallet = 10.0;
	newUser.gameList = 0;

	mysql_init(&conn);

	connection = mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 3306, (char *)NULL, 0);

	if (connection == NULL)
	{
		fprintf(stderr, "Mysql connection error : %s", mysql_error(&conn));
		exit(1);
	}

	query_stat = mysql_query(connection, "select * from userinfo");
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		exit(1);
	}

	sql_result = mysql_store_result(connection);

	mysql_free_result(sql_result);

	sprintf(query, "insert into userinfo values " "('%s', '%s', '%s', '%s', '%s', '%f', '%d', '%d')", newUser.name, newUser.birth, newUser.id, newUser.password, newUser.nickName, newUser.wallet, newUser.level, newUser.gameList);

	query_stat = mysql_query(connection, query);
	if (query_stat != 0)
	{
		fprintf(stderr, "Mysql query error : %s", mysql_error(&conn));
		exit(1);
	}

	mysql_close(connection);

}

#endif