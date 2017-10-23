#pragma once
#include<iostream>
#include"User.h"
#include"Server.h"
#include"Chat.h"
#include"DoublyList.h"
using namespace std;

/**
*	Client Class ( Linked-List )
*
*	@author �����
*	@date 2017/10/11
*/
class client {
public:

	/**
	*	@brief	Server Class
	*	@pre	run �Լ��� ȣ��ȴ�.
	*/
	server OreoServer;
	
	/**
	*	@brief	���α׷� �������̽��� �����ϴ� �Լ�
	*	@pre	Client�� ������ ���� ����
	*/
	void run();

	/**
	*	@brief	����ڰ� �α����� ���� ģ�� �˻�, ä�� ���� �� �� �ְ� ���ִ� �Լ�
	*	@pre	loginedUser ������ �ִ��� Ȯ���Ѵ�. (�α��� ���� �˾Ƽ� ����ȴ�.)
	*	@post	�α��� ���� ����ڰ� �� �� �ִ� ���� ���񽺸� �����ش�.
	*/
	void afterLogin();

	/**
	*	@brief	����ڿ� ����Ǿ� �ִ� ģ�� ������ ������ִ� �Լ�.
	*	@pre	ģ�� ������ ��ϵǾ� �־�� �Ѵ�. 123/wonseok���� �α��� �ϸ� 456�� ����Ǿ� ������ �� �� ����.
	*	@post	ģ�� ������ �ҷ��� ����Ͽ� �ش�. userinterface�� ���� �����.
	*/
	void ShowFriendList();
	
	/**
	*	@brief	����ڰ� ä���� ���� �� �� �� �ֵ��� �����ִ� �Լ�. ���� �����Ǿ� ���� �ʴ�.
	*/
	void GoToChat(MemberType* _user);

	/**
	*	@brief	Client�� �⺻ ������.
	*	@post	loginedUser�� new User�� �Ͽ��ش�.
	*/
	client();
	
	/**
	*	@brief	���� �� ����ڰ� �α����� �������� Ȯ���Ѵ�.
	*	@pre	�α����� �ߵ� ���ߵ� �������� ����.
	*	@post	loginedUser�� id, pw�� "" ������ Ȯ���Ѵ�.
	*	@return	�α��� ������� True, �ƴ� ��� False return.
	*/
	bool isLogin();

	/**
	*	@brief	�ش� id�� loginedUser�� ģ������ Ȯ���Ѵ�. ģ���ϰ�� _user�� �ش� ģ�� ������ �־��ش�.
	*	@pre	ã��;��ϴ� ���� ������ �Է����־�� �Ѵ�.
	*	@post	�ش� _id�� loginedUser�� ģ������ Ȯ���Ѵ�. ģ���� ��� �ش� ������ ������ _user�� �־��ְ� 1�� return.
	*	@return	�� id�� ģ���� ��� 1��, �ƴ� ��� 0�� return �Ѵ�.
	*/
	bool isFriendById(MemberType*& _user, int _id);

	/**
	*	@brief	< ���� ������Ʈ ���� ���� - �� ���� >
	*/
	Chat* sendMessage();
	
	/**
	*	@brief	< ���� ������Ʈ ���� ���� - �� ���� >
	*/
	void receiveMessage(Chat* _Msg);

	bool FindUserByName(MemberType*& _user, string _name);
	void GoToShop();
	void updateShop();
private:
	/**
	*	@brief	����ڰ� �α����� �����̴�.
	*/
	MemberType* CurrentUser;

	/**
	*	@brief	������ ���� �ִ� ChatDB���� receive �� ��� �����صδ� �����̴�.
	*	@pre	�������� ChatDB�� �����;� �ϴµ�, �������� send�Լ��� ȣ�����־�� �Ѵ�.
	*/
	DoublyList<Chat> ChatList;

	// chat in this list and update in server
	// when logout, chatlist is saved in PC
};