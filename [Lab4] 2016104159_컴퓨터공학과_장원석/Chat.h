#pragma once
#include"User.h"
using namespace std;
class Chat {
/**
*	Chat Class ( Linked-List )
*
*	@author 장원석
*	@date 2017/10/11
*/
private:

	/**
	*	@brief	채팅의 구성에서 메시지를 보낸 당사자
	*	@pre	Chat 함수가 정상적으로 호출될 경우
	*/
	MemberType* writter;

	/**
	*	@brief	채팅의 구성에서 메시지를 받는 사람
	*	@pre	Chat 생성자가 호출되어야 함
	*/
	MemberType* getter;
	string message; // 메시지 내용
	int id; // seq
public:

	/**
	*	@brief	채팅을 보낸 사람의 MemberType을 return
	*	@return	해당 정보의 주소값
	*/
	MemberType* getWritter() { return writter; }

	/**
	*	@brief	채팅을 받는 사람의 Member Type을 reutrn
	*	@return	채팅을 받는 사람의 주소값
	*/
	MemberType* getGetter() { return getter; }
	string getMsg() { return message; }


	/**
	*	@brief	Chat Class의 생성자
	*	@pre	서버 생성자에서 생성됨
	*	@post	Writter와 Getter이 pointer 이므로 생성
	*/
	Chat() {
		writter = new MemberType;
		getter = new MemberType;
	}
	int getId() {
		return id;
	}

	/**
	*	@brief	사용자로부터 채팅 내용을 입력받을 때 전체를 set
	*/
	void setting(int _id, MemberType* _wtr, MemberType* gtr, string _msg) {
		id = _id, writter = _wtr, getter = gtr, message = _msg;
	}
};