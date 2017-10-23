#pragma once
#include<string>
using namespace std;

/**
*	Interface ( Linked-List )
*
*	@author �����
*	@date 2017/10/11
*/



/**
*	@brief	ģ���� ���� �˰�ʹٰ� ���� �� �����κ��� �Է¹޴� �Լ�
*/
int PrintAfterFriendList();

/**
*	@brief	���α׷� ������ ���� ����ϴ� �������̽�
*/
void PrintStartScreen();

/**
*	@brief	������ ���̵�� ��й�ȣ�� �Է¹ޱ� ���� ��µǴ� �������̽�
*/
void PrintUserId(int& id, string& pw);

/**
*	@brief	���α׷� ���� ���� �α���, �α׾ƿ�, ȸ������ �� ���ϴ� ȭ������ �̵������ִ� �Լ�
*	@post	1���� 5, ������� �α���, �α׾ƿ�, ȸ������, ������, ����/������ �̴�. �������� �ʾ��� ��� ����(x)�� ǥ�õǾ� ����.
*/
int PrintUserMenu();

/**
*	@brief	�α��� ȭ���� ������ش�.
*/
void PrintLoginMenu(int& tmp_id, string& tmp_pw);

/**
*	@brief	�α׾ƿ� ȭ���� ����Ͽ� �ش�.
*/
bool PrintLogoutMenu(string _name);

/**
*	@brief	�α��� ���� ������ �� �� �ִ� ��ɵ��� ������ִ� �Լ�
*/
int PrintAfterLoginUserMenu();

/**
*	@brief	ģ�� ����� ǥ���� �� �� ���� ǥ�õǴ� Ÿ��Ʋ
*/
void PrintFriendListTitle();

/**
*	@brief	�Ķ���ͷ� ���� id, phone number, password, name, msg�� mode�� ���� ������ִ� �Լ�
*	@post	mode���� 0�� ��� friend mode�� �Ͽ� pw�� ������ ��� ���� ���
*/
void PrintDetailsOfUser(int _id, string _pn, string _pw, string _name, string _msg, int mode);
// mode 1 = friend mode


/**
*	@brief	�����κ��� id�� �Է¹޴� �޴��� ����Ͽ� �ش�.
*	@return	�����κ��� �Է¹��� id�� return ���ش�.
*/
int InputIdByUser();

/**
*	@brief	�Ķ���ͷ� ���� ��(id, name, msg)�� ���� ģ���� ����Ͽ� �ִ� �Լ�
*/
void PrintFriendOnList(int _id, string _name, string _msg);

/**
*	@brief	������ ä���� ���ϴ��� Ȯ���ϴ� �Լ�.
*/
bool chkToGoChat();

/**
*	@brief	ģ�� ã�� �޴��� ����ش�.
*/
int PrintFriendSearchMenu();

/**
*	@brief	������ ã�� �;� �ϴ� �̸��� �˻��޴� �޴��� ����ش�.
*/
string InputNameToSearch();

/**
*	@brief	������ ä���� �ϰ�;� ä�� �޴��� ������ �õ������� �ӽ� ä�� ���� ����Ʈ�� ������� ��� ȣ���Ѵ�.
*/
void NoChatList();

/**
*	@brief	������ ä���� �ϰ� �Ͱų� ä�� ����Ʈ�� ������� ��� �ӽ� ä�� ���� ����Ʈ �����͸� ȣ���ϱ� ���� �⺻ ���̾ƿ��� ����ش�.
*/
void DisplayTmpChatList();

/**
*	@brief	ä���� �� �� �޽����� ������ ���͸� ���� �� �� ���� �����Ͽ� �������̽��� ����� �� �� �ֵ��� �����ش�.
*/
void ClearLineBeforeChat();

/**
*	@brief	ä�� �������� �����ֱ� ���� _name�� �����ְ� _name�� ä���ϴ� ������ ����޾� �����ش�.
*/
string getChatByUser(string _name);

/**
*	@brief	stdHandle�� ���� �ػ� ũ�⸸ŭ '='�� ����Ѵ�.
*/
void PrintHiponOneline();

/**
*	@brief	ä�� ������ �����ִ� �Լ�. Getter�� ���� ��� writter->getter ��������, Getter�� ���� ��� Writter���� �޽����� �����ش�.
*/
void DisplayChatContent(string writter, string getter, string content, bool isCurrentUserWritten);

/**
*	@brief	ä�� ������ �����ִ� �Լ�. Getter�� ���� ��� writter->getter ��������, Getter�� ���� ��� Writter���� �޽����� �����ش�.
*/
void DisplayChatContent(string writter, string content, bool isCurrentUserWritten);

void AfterLogout();
void InputforSignin(int& id, string& name, string& pn, string& pw, string& msg);
void PrintLoginInterface(string n);
int PrintShopInterface(int money);
void PrintRecentItems();