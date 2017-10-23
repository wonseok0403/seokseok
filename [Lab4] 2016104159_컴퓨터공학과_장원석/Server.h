#pragma once
#include"User.h"
#include"DoublyList.h"
#include"Chat.h"
/**
*	Server Class ( Linked-List )
*
*	@author 장원석
*	@date 2017/10/11
*/
class server {
private:

	/**
	*	@brief	유저 정보가 저장된 DB를 불러와 관리하는 변수
	*/
	DoublyList<MemberType> UserDB;

	/**
	*	@brief	ChatDB.txt 로부터 채팅 파일을 불러와 관리하는 변수
	*/
	DoublyList<Chat> ChatDB;

public:

	/**
	*	@brief	사용자로부터 이름을 입력받아 유저 정보를 찾는 함수
	*	@pre	Client에서 로그인을 해야함.
	*	@post	UserInterface.cpp에 연결되어 있는 입력 함수를 호출하여 사용자 정보를 입력한 후 찾음.
	*	@return	출력 후 이전 호출 경로로 return
	*/
	void retrieveByName();


	/**
	*	@brief	< 다음 프로젝트 까지 개발 - 명세 내역 >.
	*/
	void receiveMessage();

	/**
	*	@brief	< 다음 프로젝트 까지 개발 - 명세 내역 >.
	*/
	void sendMessage();

	/**
	*	@brief	Client에서 UserDB에 접근할 수 있도록 관리하는 함수.
	*	@pre	loadDB 함수를 먼저 시행해야 함(Server의 생성자에서 실행됨).
	*	@post	UserDB의 맨처음 주소값 반환
	*	@return	UserDB의 맨처음 주소값 반환
	*/
	DoublyList<MemberType> * getUserDB() { return &UserDB; }
	
	/**
	*	@brief	채팅 내역을 저장하고 있는 ChatDB에 접근할 수 있도록 해주는 함수
	*	@pre	loadDB 함수를 먼저 시행해야 함(Server의 생성자에서 실행됨).
	*	@post	ChatDB의 맨처음 주소값 반환
	*	@return	ChatDB의 맨처음 주소값 반환
	*/
	DoublyList<Chat> * getChatDB() { return &ChatDB; }

	/**
	*	@brief	Server Class의 기본 함수. LoadDB 함수가 호출됨.
	*/
	server();

	/**
	*	@brief	Client에서 로그인을 할 수 있도록 검사하는 함수
	*	@pre	Client의 loginedUser가 생성되어 들어와야 한다.
	*	@post	_user의 id, password가 UserDB에 있는지 확인하여 있을 경우 해당 user 정보를 _user에 넣고 return
	*	@return	로그인에 성공했을 경우 1을, 아닐 경우 0을 return
	*/
	bool login(MemberType* & _user); // true is succeed zero is failed
	
									 /**
	*	@brief	ChatDB, FriendListDB, UserDB를 불러오는 함수
	*	@pre	생성자가 먼저 호출되어야 한다.
	*	@post	User을 먼저 저장하고, Friend를 가져온 다음 Chat을 가져옴
	*/
	void loadDB(); // load user and chat
	
	/**
	*	@brief	Client가 로그아웃을 원할 경우 시행해주는 함수 (사실 클라이언트에 있어도 된다.)
	*	@pre	Client에서 loginedUser을 입력하여 넣어주어야 하낟.
	*	@post	_user가 nullptr이 아닐 경우 new user 해줌.
	*	@return	로그아웃 성공 케이스(유저가 있었을 경우 시행 후) 1을 return, 아니면 0을 return
	*/
	bool logout(MemberType* & _user); // true is succeed zero is failed

	void saveDB(); // 친구 관계를 돈독히 한 후 개발 할 예정
	void signin(); // 회원 관계를 돈독히 한 후 개발 예정
	/*
	bool SearchUserByID(User& _user); // same as login and logout
	bool SearchUserByName(User& _user); // same as login and logout
	void FixUser(User& _user); // 유저 정보를 고정하는 DB
	*/
};