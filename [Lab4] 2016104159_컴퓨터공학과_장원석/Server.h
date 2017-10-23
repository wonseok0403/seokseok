#pragma once
#include"User.h"
#include"DoublyList.h"
#include"Chat.h"
/**
*	Server Class ( Linked-List )
*
*	@author �����
*	@date 2017/10/11
*/
class server {
private:

	/**
	*	@brief	���� ������ ����� DB�� �ҷ��� �����ϴ� ����
	*/
	DoublyList<MemberType> UserDB;

	/**
	*	@brief	ChatDB.txt �κ��� ä�� ������ �ҷ��� �����ϴ� ����
	*/
	DoublyList<Chat> ChatDB;

public:

	/**
	*	@brief	����ڷκ��� �̸��� �Է¹޾� ���� ������ ã�� �Լ�
	*	@pre	Client���� �α����� �ؾ���.
	*	@post	UserInterface.cpp�� ����Ǿ� �ִ� �Է� �Լ��� ȣ���Ͽ� ����� ������ �Է��� �� ã��.
	*	@return	��� �� ���� ȣ�� ��η� return
	*/
	void retrieveByName();


	/**
	*	@brief	< ���� ������Ʈ ���� ���� - �� ���� >.
	*/
	void receiveMessage();

	/**
	*	@brief	< ���� ������Ʈ ���� ���� - �� ���� >.
	*/
	void sendMessage();

	/**
	*	@brief	Client���� UserDB�� ������ �� �ֵ��� �����ϴ� �Լ�.
	*	@pre	loadDB �Լ��� ���� �����ؾ� ��(Server�� �����ڿ��� �����).
	*	@post	UserDB�� ��ó�� �ּҰ� ��ȯ
	*	@return	UserDB�� ��ó�� �ּҰ� ��ȯ
	*/
	DoublyList<MemberType> * getUserDB() { return &UserDB; }
	
	/**
	*	@brief	ä�� ������ �����ϰ� �ִ� ChatDB�� ������ �� �ֵ��� ���ִ� �Լ�
	*	@pre	loadDB �Լ��� ���� �����ؾ� ��(Server�� �����ڿ��� �����).
	*	@post	ChatDB�� ��ó�� �ּҰ� ��ȯ
	*	@return	ChatDB�� ��ó�� �ּҰ� ��ȯ
	*/
	DoublyList<Chat> * getChatDB() { return &ChatDB; }

	/**
	*	@brief	Server Class�� �⺻ �Լ�. LoadDB �Լ��� ȣ���.
	*/
	server();

	/**
	*	@brief	Client���� �α����� �� �� �ֵ��� �˻��ϴ� �Լ�
	*	@pre	Client�� loginedUser�� �����Ǿ� ���;� �Ѵ�.
	*	@post	_user�� id, password�� UserDB�� �ִ��� Ȯ���Ͽ� ���� ��� �ش� user ������ _user�� �ְ� return
	*	@return	�α��ο� �������� ��� 1��, �ƴ� ��� 0�� return
	*/
	bool login(MemberType* & _user); // true is succeed zero is failed
	
									 /**
	*	@brief	ChatDB, FriendListDB, UserDB�� �ҷ����� �Լ�
	*	@pre	�����ڰ� ���� ȣ��Ǿ�� �Ѵ�.
	*	@post	User�� ���� �����ϰ�, Friend�� ������ ���� Chat�� ������
	*/
	void loadDB(); // load user and chat
	
	/**
	*	@brief	Client�� �α׾ƿ��� ���� ��� �������ִ� �Լ� (��� Ŭ���̾�Ʈ�� �־ �ȴ�.)
	*	@pre	Client���� loginedUser�� �Է��Ͽ� �־��־�� �ϳ�.
	*	@post	_user�� nullptr�� �ƴ� ��� new user ����.
	*	@return	�α׾ƿ� ���� ���̽�(������ �־��� ��� ���� ��) 1�� return, �ƴϸ� 0�� return
	*/
	bool logout(MemberType* & _user); // true is succeed zero is failed

	void saveDB(); // ģ�� ���踦 ������ �� �� ���� �� ����
	void signin(); // ȸ�� ���踦 ������ �� �� ���� ����
	/*
	bool SearchUserByID(User& _user); // same as login and logout
	bool SearchUserByName(User& _user); // same as login and logout
	void FixUser(User& _user); // ���� ������ �����ϴ� DB
	*/
};