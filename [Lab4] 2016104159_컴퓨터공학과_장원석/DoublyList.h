#pragma once
#include<iostream>
using namespace std;
template <typename T>

/**
*	DoublyList Class ( Linked-List )
*
*	@author �����
*	@date 2017/10/11
*/
class DoublyList {
private:
	/**
	*	@brief	����Ʈ�� ����� ���� List ������ ��
	*	@pre	this�� ������ �־�� �Ѵ�.
	*/
	DoublyList * next;

	/**
	*	@brief	����Ʈ�� ����� ���� List ������ ��
	*	@pre	this�� ������ �־�� �Ѵ�.
	*/
	DoublyList * before;
	
	/**
	*	@brief	����Ʈ ��ü�� �� Ʋ�� �� ó�� �ּ�
	*	@pre	����Ʈ�� 1�� �̻� �־�� �Ѵ�
	*/
	static DoublyList* first;

	/**
	*	@brief	����Ʈ ��ü�� �� Ʋ�� �� ������ �ּ�
	*	@pre	����Ʈ�� 1�� �̻� �־�� �Ѵ�.
	*/
	static DoublyList* last;

	/**
	*	@brief	Template���� �����Ǵ� ������ ���� �ִ� ����
	*	@pre	this�� �����Ǵ� �ܰ迡�� ����
	*/
	T Item;

	/**
	*	@brief	��ü list�� ũ��
	*	@pre	1���� �ƴϿ��� ��� ����
	*/
	static int size;

public:
	/**
	*	@brief	Template���� �����Ǵ� ���� ������ ����Ͽ� �ش�. �ѹ��� ������ �� �����Ƿ� �ּҰ� return
	*	@pre	T ���� �־�� �Ѵ�.
	*	@post	this->T�� return
	*	@return	this->item
	*/
	T* getItem() { return &Item; }

	/**
	*	@brief	now�� ���� �Ķ������ next�� �־��ְ� return
	*	@pre	now�� �Է¹޾ƾ� �Ѵ�
	*	@post	now�� next�� nullptr���� Ȯ��
	*	@return	nullptr �ϰ�� 0�� �ƴ� ��� 1�� return.
	*/
	bool GetNextList(DoublyList*& now) {
		if (now->next == nullptr) { return 0; }
		else { now = now->next; 
		return true;

		}
	}
	/**
	*	@brief	��ü ����Ʈ�� �� ó�� �ּҸ� return���ִ� �Լ�
	*	@pre	����Ʈ�� 1�� �̻� �־�� �Ѵ�.
	*	@post	����Ʈ�� �� ó�� ����
	*	@return	return first
	*/
	DoublyList* GetFirstList() { return first; }

	/**
	*	@brief	��ü ����Ʈ�� �� ������ �ּҸ� return ���ִ� �Լ�
	*	@pre	����Ʈ�� 1�� �̻� �־�� �Ѵ�.
	*	@post	����Ʈ�� ������ return
	*	@return	Last
	*/
	DoublyList* GetLastList() { return last; }

	/**
	*	@brief	DoublyList�� �⺻ ������, size�� 0���� �Ѵ�.
	*	@pre	�ְ��� �ϴ� template�� id�� �־�� �Ѵ�.(SortedList �̱� ������)
	*	@post	size = 0, first = this
	*/
	DoublyList();

	/**
	*	@brief	size ������ static type ���� size�� 1 ���������ִ� �Լ�
	*/
	static void sizeplus() {
		size++;
	}

	/**
	*	@brief	�������� �ְ� ������ ���� �� ȣ�����ִ� �Լ�
	*	@pre	�������� id�� ���� �־�� �Ѵ�.
	*/
	DoublyList<T>(T* _T) {
		Item = *_T;
	}

	/**
	*	@brief	list�� item�� �߰��ϰ� ���� �� ȣ���ϴ� �Լ�
	*	@pre	list�� �ϴ� �����ؾ� �Ѵ�. item�� id�� ���� �־�� �Ѵ�.
	*	@post	�������� id�� �������� ���� ��ġ�� ������ ���� item�� �߰��Ѵ�.
	*/
	void addItem(T* Item);
	
	/**
	*	@brief	ID�� �������� ������ �˻��ϴ� �Լ�. DoublyLinkedList �̱� ������ Left���� �˻��� ���������� ���� �������� �ʾҴ�.
	*	@pre	List�� 1�� �̻� �־�� �Ѵ�.
	*	@post	List�� �� ó������ �����Ͽ� id�� ��ġ�ϴ� ������ return ���ش�.
	*	@return	ã���� 1, �ƴϸ� 0�� return
	*/
	bool ToRightFindUserByID(T* & _user, int id);
	
	/**
	*	@brief	���ϴ� ������ �����ϰ� ���� �� ȣ���Ѵ�.
	*	@pre	Item�� ��� ������ ��ġ�ϴ��� Ȯ���Ѵ�.
	*	@post	��ġ�� ��� �ش� �������� �����ϰ� ������ before�� next�� �̾��ش�.
	*/
	void delItem(T* Item);

	/**
	*	@brief	���� list�� ���� �ִ� item�� �ٲٰ� ���� �� ȣ���Ѵ�.
	*	@pre	������ list�� item�� ���������� ���� �־�� �Ѵ�.
	*	@post	item = _item
	*/
	void setItem(T* _Item) { Item = *_Item; }
	/*
	T * sortItem(T* Item);
	T * getNextItem(T* Item);
	T * getBeforeItem(T* Item);
	*/

	/**
	*	@brief	this�� before�� ������ setting �Ѵ�.
	*/
	void setbefore(DoublyList* _item) {
		before = _item;
	}

	/**
	*	@brief	this�� next�� ������ setting �Ѵ�.
	*/
	void setnext(DoublyList* _Item) {
		next = _Item;
	}

	//bool searchItem(T& Item);
	int getsize() { return size; }
	void setsize(int _s) { size = _s; }

	/**
	*	@brief	���� ����Ʈ�� ���� �ִ� ��Ͽ��� ���� ������ list�� id�� return.
	*	@pre	����Ʈ�� item�� 1�� �̻� ���� �ְ� last�� �������̾�� �Ѵ�.
	*	@post	Getnextlist�� ���������� ȣ��.
	*	@return	Last list�� id���� ���.
	*/
	int GetLastId();
};