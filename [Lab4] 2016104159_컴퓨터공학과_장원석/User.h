#pragma once
#include<iostream>
#include<string>
#include"FriendList.h"
#include"DoublyList.h"
#include"UserInterface.h"
#include"DoublyList.cpp"
using namespace std;
/**
*	MemberType Class ( Linked-List )
*
*	@author 장원석
*	@date 2017/10/11
*/

class MemberType {
private:
	int id; // 유저를 구분하는 최소 단위
	string pn; //유저의 전화번호
	string pw; // 유저의 비밀번호
	string name; // 유저의 이름
	string msg; // 유저의 대화명
	int birth; // min 991231 max 19970403 < 2147483647
	string background; // non developed
	/**
	*	@brief	한 유저가 관리하는 친구 목록
	*	@pre	User들이 모두 불러와져 있어야 한다.
	*/
	DoublyList<FriendList> Friendlists;
public:
	DoublyList<FriendList>* getFriendlists() { return &Friendlists; }
	/**
	*	@brief	유저의 생성자, 해당 정보를 함께 넣어 생성할 경우 자동으로 넣어진다.
	*/
	MemberType(string _name, string _pn, int _id, string _pw, string _msg) {
		name = _name; pn = _pn; pw = _pw; msg = _msg; id = _id;
	}

	/**
	*	@brief	유저의 기본 생성자, 특별한 내용은 없음.
	*/
	MemberType() {
		bought_emot_num = 0;
		bingPoint = 0;
	}
	/**
	*	@brief	Id의 Get함수
	*/
	int getId() { return id; }

	/**
	*	@brief	Pw의 Get함수
	*/
	string getPw() { return pw; }

	/**
	*	@brief	Id를 출력하여 주는 함수
	*/
	void displayId() {cout << id;}

	/**
	*	@brief	 비밀번호를 출력해주는 함수
	*/
	void displayPw() { cout << pw;}

	/**
	*	@brief	User Interface와 연동되어 전체 정보를 출력하여 주는 함수
	*	@post	mode가 0일 경우 친구모드로, 비밀번호를 제외한 모든 정보를 출력하여 준다.
	*/
	void displayMemberInfo(int mode) { PrintDetailsOfUser(id, pn, pw, name, msg, mode); }
	/**
	*	@brief	전화번호를 return해주는 get 함수
	*/
	string getPn() { return pn; }
	/**
	*	@brief	대화명을 return해주는 get 함수
	*/
	string getMsg() { return msg; }
	/**
	*	@brief	이름을 return해주는 get 함수
	*/
	string getName() { return name; }
	/**
	*	@brief	ID를 입력받아 set 해주는 함수
	*/
	void ReadId() { int _id; cin >> _id; setId(_id); }
	void ReadPW() { string _pw; cin >> _pw; setPw(_pw); }
	void setId(int _id) { id = _id; }
	void setPw(string _pw) { pw = _pw; }
	void setName(string _name) { name = _name; }
	/**
	*	@brief	name, pn, password, msg를 바로 넣어줄 수 있는 set 함수
	*/
	void setNPIPM(string _name, string _pn, int _id, string _pw, string _msg) {
		name = _name; pn = _pn; pw = _pw; msg = _msg; id = _id;
	}
	string emot[10];
	int bought_emot_num;
	int bingPoint;
};