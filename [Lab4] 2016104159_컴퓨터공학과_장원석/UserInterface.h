#pragma once
#include<string>
using namespace std;

/**
*	Interface ( Linked-List )
*
*	@author 장원석
*	@date 2017/10/11
*/



/**
*	@brief	친구에 대해 알고싶다고 했을 때 유저로부터 입력받는 함수
*/
int PrintAfterFriendList();

/**
*	@brief	프로그램 시작한 이후 출력하는 인터페이스
*/
void PrintStartScreen();

/**
*	@brief	유저의 아이디와 비밀번호를 입력받기 위해 출력되는 인터페이스
*/
void PrintUserId(int& id, string& pw);

/**
*	@brief	프로그램 시작 이후 로그인, 로그아웃, 회원가입 등 원하는 화면으로 이동시켜주는 함수
*	@post	1부터 5, 순서대로 로그인, 로그아웃, 회원가입, 선물숍, 저장/나가기 이다. 구현되지 않았을 경우 끝에(x)가 표시되어 있음.
*/
int PrintUserMenu();

/**
*	@brief	로그인 화면을 출력해준다.
*/
void PrintLoginMenu(int& tmp_id, string& tmp_pw);

/**
*	@brief	로그아웃 화면을 출력하여 준다.
*/
bool PrintLogoutMenu(string _name);

/**
*	@brief	로그인 이후 유저가 할 수 있는 기능들을 출력해주는 함수
*/
int PrintAfterLoginUserMenu();

/**
*	@brief	친구 목록을 표시할 때 맨 위에 표시되는 타이틀
*/
void PrintFriendListTitle();

/**
*	@brief	파라미터로 받은 id, phone number, password, name, msg를 mode에 따라 출력해주는 함수
*	@post	mode값이 0일 경우 friend mode라 하여 pw를 제외한 모든 정보 출력
*/
void PrintDetailsOfUser(int _id, string _pn, string _pw, string _name, string _msg, int mode);
// mode 1 = friend mode


/**
*	@brief	유저로부터 id를 입력받는 메뉴를 출력하여 준다.
*	@return	유저로부터 입력받은 id를 return 해준다.
*/
int InputIdByUser();

/**
*	@brief	파라미터로 넣은 값(id, name, msg)를 갖는 친구를 출력하여 주는 함수
*/
void PrintFriendOnList(int _id, string _name, string _msg);

/**
*	@brief	유저가 채팅을 원하는지 확인하는 함수.
*/
bool chkToGoChat();

/**
*	@brief	친구 찾기 메뉴를 띄워준다.
*/
int PrintFriendSearchMenu();

/**
*	@brief	유저가 찾고 싶어 하는 이름을 검색받는 메뉴를 띄워준다.
*/
string InputNameToSearch();

/**
*	@brief	유저가 채팅을 하고싶어 채팅 메뉴에 접속을 시도했으나 임시 채팅 저장 리스트가 비어있을 경우 호출한다.
*/
void NoChatList();

/**
*	@brief	유저가 채팅을 하고 싶거나 채팅 리스트를 보고싶을 경우 임시 채팅 저장 리스트 데이터를 호출하기 위한 기본 레이아웃을 띄워준다.
*/
void DisplayTmpChatList();

/**
*	@brief	채팅을 할 때 메시지를 보내고 엔터를 쳤을 때 윗 줄을 삭제하여 인터페이스를 깔끔히 할 수 있도록 도와준다.
*/
void ClearLineBeforeChat();

/**
*	@brief	채팅 정보들을 보여주기 위해 _name을 보여주고 _name이 채팅하는 내역을 저장받아 돌려준다.
*/
string getChatByUser(string _name);

/**
*	@brief	stdHandle의 가로 해상도 크기만큼 '='을 출력한다.
*/
void PrintHiponOneline();

/**
*	@brief	채팅 내용을 보여주는 함수. Getter가 있을 경우 writter->getter 형식으로, Getter가 없을 경우 Writter만의 메시지를 보여준다.
*/
void DisplayChatContent(string writter, string getter, string content, bool isCurrentUserWritten);

/**
*	@brief	채팅 내용을 보여주는 함수. Getter가 있을 경우 writter->getter 형식으로, Getter가 없을 경우 Writter만의 메시지를 보여준다.
*/
void DisplayChatContent(string writter, string content, bool isCurrentUserWritten);

void AfterLogout();
void InputforSignin(int& id, string& name, string& pn, string& pw, string& msg);
void PrintLoginInterface(string n);
int PrintShopInterface(int money);
void PrintRecentItems();