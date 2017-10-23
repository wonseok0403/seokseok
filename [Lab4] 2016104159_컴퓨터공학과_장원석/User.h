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
*	@author �����
*	@date 2017/10/11
*/

class MemberType {
private:
	int id; // ������ �����ϴ� �ּ� ����
	string pn; //������ ��ȭ��ȣ
	string pw; // ������ ��й�ȣ
	string name; // ������ �̸�
	string msg; // ������ ��ȭ��
	int birth; // min 991231 max 19970403 < 2147483647
	string background; // non developed
	/**
	*	@brief	�� ������ �����ϴ� ģ�� ���
	*	@pre	User���� ��� �ҷ����� �־�� �Ѵ�.
	*/
	DoublyList<FriendList> Friendlists;
public:
	DoublyList<FriendList>* getFriendlists() { return &Friendlists; }
	/**
	*	@brief	������ ������, �ش� ������ �Բ� �־� ������ ��� �ڵ����� �־�����.
	*/
	MemberType(string _name, string _pn, int _id, string _pw, string _msg) {
		name = _name; pn = _pn; pw = _pw; msg = _msg; id = _id;
	}

	/**
	*	@brief	������ �⺻ ������, Ư���� ������ ����.
	*/
	MemberType() {
		bought_emot_num = 0;
		bingPoint = 0;
	}
	/**
	*	@brief	Id�� Get�Լ�
	*/
	int getId() { return id; }

	/**
	*	@brief	Pw�� Get�Լ�
	*/
	string getPw() { return pw; }

	/**
	*	@brief	Id�� ����Ͽ� �ִ� �Լ�
	*/
	void displayId() {cout << id;}

	/**
	*	@brief	 ��й�ȣ�� ������ִ� �Լ�
	*/
	void displayPw() { cout << pw;}

	/**
	*	@brief	User Interface�� �����Ǿ� ��ü ������ ����Ͽ� �ִ� �Լ�
	*	@post	mode�� 0�� ��� ģ������, ��й�ȣ�� ������ ��� ������ ����Ͽ� �ش�.
	*/
	void displayMemberInfo(int mode) { PrintDetailsOfUser(id, pn, pw, name, msg, mode); }
	/**
	*	@brief	��ȭ��ȣ�� return���ִ� get �Լ�
	*/
	string getPn() { return pn; }
	/**
	*	@brief	��ȭ���� return���ִ� get �Լ�
	*/
	string getMsg() { return msg; }
	/**
	*	@brief	�̸��� return���ִ� get �Լ�
	*/
	string getName() { return name; }
	/**
	*	@brief	ID�� �Է¹޾� set ���ִ� �Լ�
	*/
	void ReadId() { int _id; cin >> _id; setId(_id); }
	void ReadPW() { string _pw; cin >> _pw; setPw(_pw); }
	void setId(int _id) { id = _id; }
	void setPw(string _pw) { pw = _pw; }
	void setName(string _name) { name = _name; }
	/**
	*	@brief	name, pn, password, msg�� �ٷ� �־��� �� �ִ� set �Լ�
	*/
	void setNPIPM(string _name, string _pn, int _id, string _pw, string _msg) {
		name = _name; pn = _pn; pw = _pw; msg = _msg; id = _id;
	}
	string emot[10];
	int bought_emot_num;
	int bingPoint;
};