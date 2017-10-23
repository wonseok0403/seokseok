#pragma once
#include"User.h"
using namespace std;
class Chat {
/**
*	Chat Class ( Linked-List )
*
*	@author �����
*	@date 2017/10/11
*/
private:

	/**
	*	@brief	ä���� �������� �޽����� ���� �����
	*	@pre	Chat �Լ��� ���������� ȣ��� ���
	*/
	MemberType* writter;

	/**
	*	@brief	ä���� �������� �޽����� �޴� ���
	*	@pre	Chat �����ڰ� ȣ��Ǿ�� ��
	*/
	MemberType* getter;
	string message; // �޽��� ����
	int id; // seq
public:

	/**
	*	@brief	ä���� ���� ����� MemberType�� return
	*	@return	�ش� ������ �ּҰ�
	*/
	MemberType* getWritter() { return writter; }

	/**
	*	@brief	ä���� �޴� ����� Member Type�� reutrn
	*	@return	ä���� �޴� ����� �ּҰ�
	*/
	MemberType* getGetter() { return getter; }
	string getMsg() { return message; }


	/**
	*	@brief	Chat Class�� ������
	*	@pre	���� �����ڿ��� ������
	*	@post	Writter�� Getter�� pointer �̹Ƿ� ����
	*/
	Chat() {
		writter = new MemberType;
		getter = new MemberType;
	}
	int getId() {
		return id;
	}

	/**
	*	@brief	����ڷκ��� ä�� ������ �Է¹��� �� ��ü�� set
	*/
	void setting(int _id, MemberType* _wtr, MemberType* gtr, string _msg) {
		id = _id, writter = _wtr, getter = gtr, message = _msg;
	}
};