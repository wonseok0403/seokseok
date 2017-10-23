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
*	@author 장원석
*	@date 2017/10/11
*/
class client {
public:

	/**
	*	@brief	Server Class
	*	@pre	run 함수가 호출된다.
	*/
	server OreoServer;
	
	/**
	*	@brief	프로그램 인터페이스를 관리하는 함수
	*	@pre	Client가 생성된 이후 시행
	*/
	void run();

	/**
	*	@brief	사용자가 로그인한 이후 친구 검색, 채팅 등을 할 수 있게 해주는 함수
	*	@pre	loginedUser 정보가 있는지 확인한다. (로그인 이후 알아서 진행된다.)
	*	@post	로그인 이후 사용자가 할 수 있는 여러 서비스를 보여준다.
	*/
	void afterLogin();

	/**
	*	@brief	사용자와 연결되어 있는 친구 내역을 출력해주는 함수.
	*	@pre	친구 정보가 등록되어 있어야 한다. 123/wonseok으로 로그인 하면 456과 연결되어 있음을 알 수 있음.
	*	@post	친구 정보를 불러와 출력하여 준다. userinterface를 통해 출력함.
	*/
	void ShowFriendList();
	
	/**
	*	@brief	사용자가 채팅을 원할 때 할 수 있도록 도와주는 함수. 아직 구현되어 있지 않다.
	*/
	void GoToChat(MemberType* _user);

	/**
	*	@brief	Client의 기본 생성자.
	*	@post	loginedUser에 new User을 하여준다.
	*/
	client();
	
	/**
	*	@brief	지금 이 사용자가 로그인한 상태인지 확인한다.
	*	@pre	로그인을 했든 안했든 관여하지 않음.
	*	@post	loginedUser의 id, pw가 "" 값인지 확인한다.
	*	@return	로그인 했을경우 True, 아닐 경우 False return.
	*/
	bool isLogin();

	/**
	*	@brief	해당 id가 loginedUser의 친구인지 확인한다. 친구일경우 _user에 해당 친구 정보를 넣어준다.
	*	@pre	찾고싶어하는 유저 정보를 입력해주어야 한다.
	*	@post	해당 _id가 loginedUser의 친구인지 확인한다. 친구일 경우 해당 유저의 정보를 _user에 넣어주고 1을 return.
	*	@return	이 id가 친구일 경우 1을, 아닐 경우 0을 return 한다.
	*/
	bool isFriendById(MemberType*& _user, int _id);

	/**
	*	@brief	< 다음 프로젝트 까지 개발 - 명세 내역 >
	*/
	Chat* sendMessage();
	
	/**
	*	@brief	< 다음 프로젝트 까지 개발 - 명세 내역 >
	*/
	void receiveMessage(Chat* _Msg);

	bool FindUserByName(MemberType*& _user, string _name);
	void GoToShop();
	void updateShop();
private:
	/**
	*	@brief	사용자가 로그인한 유저이다.
	*/
	MemberType* CurrentUser;

	/**
	*	@brief	서버가 갖고 있는 ChatDB에서 receive 할 경우 저장해두는 변수이다.
	*	@pre	서버에서 ChatDB를 가져와야 하는데, 서버에서 send함수를 호출해주어야 한다.
	*/
	DoublyList<Chat> ChatList;

	// chat in this list and update in server
	// when logout, chatlist is saved in PC
};