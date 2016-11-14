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
�ۼ���    : �̱���
�ۼ���    : 2016.10.17
���� ���� : MySQL���� ������ ��������, ������ ���� ���� �����ϱ� ���� ����ϴ� �������̴�.
*****************************************************************************************************************************************************/
MYSQL *connection = NULL, conn;
MYSQL_RES *sql_result;
MYSQL_ROW sql_row;
int query_stat;
char query[255];
/*****************************************************************************************************************************************************
*   �ۼ���    : �̱���
*   �ۼ���    : 2016.10.17
*   ���� ���� : ���̺��� ������ ������� ����(column�� ����)�� ������ int�� num_fields�� �����Ѵ�.
*****************************************************************************************************************************************************/
int num_rows;
/*****************************************************************************************************************************************************
*   �ۼ���    : �̱���
*   �ۼ���    : 2016.10.17
*   ���� ���� : ���� ������ �����ϰ�, uInfo������ ������ ����ü UserInfo�� �����͸� MySQL���� ������ Gamemanager_db�� table UserInfo���� ������
data���� �����ϱ� ���Ͽ� ����ü ������ uInfo *userData�� �����ϰ� �����Ҵ��Ͽ���.
�����Ҵ� ���� ũ��� num_fields�̴�.
*****************************************************************************************************************************************************/
uInfo *userData;
int i = 0, j = 0, k = 0;

/*****************************************************************************************************************************************************
*   �ۼ���    : �̱���
*   �ۼ���    : 2016.10.17
*   �Լ���    : idDuplicationCheck
*   �Ű�����  : char *id
*   �Լ� ���� : �Ű������� �Ѱ��� char *��(���� string�̶� Ī�Ѵ�) id�� MySQL���� ������ Gamemanager_db�� table UserInfo���̺��� ������ data ID��
string.h�� ������ strcmp()�Լ��� �̿��Ͽ� id�� �ߺ��� �ִ��� Ȯ���Ѵ�.
Id�� �ߺ��� ��� 1�� return�ϰ�, �ߺ��� �ƴ� ��� 0�� return�Ѵ�.
*****************************************************************************************************************************************************/
int idDuplicationCheck(char *id, uInfo *userData, int indexSize) {
	int duplicationCheck = 0;
	int i;
	/*
	�Ű������� �Ѱ��� id�� userDataId�� ������ ���� ��� �ߺ��̹Ƿ� 1�� return�Ѵ�.
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
�ۼ���    : �̱���
�ۼ���    : 2016.10.17
�Լ���    : loginCheck
�Ű�����  : char *id, char *password, char *userDataId, char *userDataPassword
�Լ� ���� : login�� ó���ϴ� �Լ��̴�. �Ű������� �Ѱ��� id, password���� uInfo�� �迭 userData���� id�� password���� ��ġ�ϴ��� �Ǵ��Ͽ�
����ڰ� Ȯ�εǸ� 1�� return�ϰ�, Ȯ�ε��� ������ 0�� return�Ѵ�.
*****************************************************************************************************************************************************/
int loginCheck(char *id, char *password, uInfo *userData, int indexSize) {
	int idCheck = 0;
	int passwdCheck = 0;
	int i;

	/*
	indexSize��ŭ �ݺ��ȴ�.
	*/
	for (i = 0; i < indexSize; i++) {
		/*
		id�� ���� userData[i].id�� ���� ���� ��� idCheck�� ���� 1�� �����Ѵ�.
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
		�׷��� ���� ��� idCheck�� ���� 0���� �����Ѵ�.
		*/
		else {
			idCheck = 0;
		}
		/*
		idCheck�� ���� 1�� ��� password�� �˻��Ѵ�.
		*/
		if (idCheck == 1) {
			/*
			password�� ���� userData[i].password�� ���� ���� ��� passwdCheck�� ���� 1�� �����Ѵ�.
			�׸��� break;�� ���� �ݺ����� �����Ų��.
			*/
			if (strcmp(password, userData[i].password) == 0) {
				passwdCheck = 1;
				break;
			}
			/*
			password�� ���� userData[i].password�� ���� �ٸ� ��� passwdCheck�� ���� 0���� �����Ѵ�.
			�׸��� break;�� ���� �ݺ����� �����Ų��.
			*/
			else {
				passwdCheck = 0;
				break;
			}
		}
	}
	/*
	idCheck�� ���� passwdCheck�� ���� ��� 1�� ��� �α��ο� ���������� ����ϰ� 1�� return�Ѵ�.
	*/
	if (idCheck == 1 && passwdCheck == 1) {
		system("cls");
		gotoxy(x + 5, y + 2);   printf("\nLogin Success!!\nWelcome!! %S", id);

		Sleep(2000);
		return 1;
	}
	/*
	idCheck�� ���� 1�̰� passwdCheck�� ���� 0�� ��� id�� ���� ��й�ȣ �Է��� �߸��� ����̴�.
	����, password�� �߸� �Է��Ͽ��ٴ� ������ ����� ��, 0�� return�Ѵ�.
	*/
	else if (idCheck == 1 && passwdCheck == 0) {
		printf("\nIncorrect password, please retry...\n");
		Sleep(2000);
		return 0;
	}
	/*
	������ ���� idCheck�� ���� 0�� ����̴�.
	id�� �������� �����Ƿ� id�� Ʋ������ ����Ѵ�.
	�׸��� ȸ�������� �����Ѵ�.
	���������� -1�� return�Ѵ�.
	*/
	else {
		printf("\nIncorrect ID\nAre you not a member? membership please!!!");
		Sleep(2000);
		return -1;
	}
}

/*
�ۼ���    : �̱���
�ۼ���    : 2016.10.18
�Լ���    :
�Ű�����  :
�Լ� ���� :
*/
int initiate() {
	// strtof()�Լ��� �Ű������� �Ѱ���.
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
	*   �ۼ���    : �̱���
	*   �ۼ���    : 2016.10.17
	*   ���� ���� : ���̺��� ������ ������� ����(column�� ����)�� ������ int�� num_fields�� �����Ѵ�.
	*****************************************************************************************************************************************************/
	num_rows = mysql_num_rows(sql_result);
	/*****************************************************************************************************************************************************
	*   �ۼ���    : �̱���
	*   �ۼ���    : 2016.10.17
	*   ���� ���� : ���� ������ �����ϰ�, uInfo������ ������ ����ü UserInfo�� �����͸� MySQL���� ������ Gamemanager_db�� table UserInfo���� ������
	data���� �����ϱ� ���Ͽ� ����ü ������ uInfo *userData�� �����ϰ� �����Ҵ��Ͽ���.
	�����Ҵ� ���� ũ��� num_fields�̴�.
	*****************************************************************************************************************************************************/
	userData = (uInfo *)calloc(num_rows, sizeof(uInfo));

	/*****************************************************************************************************************************************************
	�ۼ���    : �̱���
	�ۼ���    : 2016.10.17
	�ڵ� ���� :
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
�ۼ���    : �̱���
�ۼ���    : 2016.11.02
�Լ���    : createAccount
�Ű�����  : void
�Լ� ���� : ������� ������ �����ϴ� �ڵ��̴�. ó���� ID�� �Է¹��� ��, idDuplicationCheck()�Լ��� ȣ���Ͽ� �̹� ������ ���̵� �ִ��� �ߺ��˻縦 �����Ѵ�.
�ߺ��� �ƴ� ���, password�� �Է¹޴´�. ������ ���� ������ ���� �Է¹��� ��, MySQL�� gamemanager_db�� �����ϴ� userInfo���̺� �����͸� �����Ѵ�.
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