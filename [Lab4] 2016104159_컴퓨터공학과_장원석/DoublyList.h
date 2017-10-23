#pragma once
#include<iostream>
using namespace std;
template <typename T>

/**
*	DoublyList Class ( Linked-List )
*
*	@author 장원석
*	@date 2017/10/11
*/
class DoublyList {
private:
	/**
	*	@brief	리스트와 연결된 다음 List 포인터 값
	*	@pre	this의 정보가 있어야 한다.
	*/
	DoublyList * next;

	/**
	*	@brief	리스트와 연결된 이전 List 포인터 값
	*	@pre	this의 정보가 있어야 한다.
	*/
	DoublyList * before;
	
	/**
	*	@brief	리스트 전체를 통 틀어 맨 처음 주소
	*	@pre	리스트가 1개 이상 있어야 한다
	*/
	static DoublyList* first;

	/**
	*	@brief	리스트 전체를 통 틀어 맨 마지막 주소
	*	@pre	리ㅡ트가 1개 이상 있어야 한다.
	*/
	static DoublyList* last;

	/**
	*	@brief	Template으로 관리되는 정보를 갖고 있는 변수
	*	@pre	this가 생성되는 단계에서 생성
	*/
	T Item;

	/**
	*	@brief	전체 list의 크기
	*	@pre	1개가 아니여도 상관 없음
	*/
	static int size;

public:
	/**
	*	@brief	Template으로 관리되는 변수 내용을 출력하여 준다. 한번에 관리할 수 없으므로 주소값 return
	*	@pre	T 값이 있어야 한다.
	*	@post	this->T를 return
	*	@return	this->item
	*/
	T* getItem() { return &Item; }

	/**
	*	@brief	now로 받은 파라미터의 next를 넣어주고 return
	*	@pre	now를 입력받아야 한다
	*	@post	now의 next가 nullptr인지 확인
	*	@return	nullptr 일경우 0을 아닐 경우 1을 return.
	*/
	bool GetNextList(DoublyList*& now) {
		if (now->next == nullptr) { return 0; }
		else { now = now->next; 
		return true;

		}
	}
	/**
	*	@brief	전체 리스트의 맨 처음 주소를 return해주는 함수
	*	@pre	리스트가 1개 이상 있어야 한다.
	*	@post	리스트의 맨 처음 리턴
	*	@return	return first
	*/
	DoublyList* GetFirstList() { return first; }

	/**
	*	@brief	전체 리스트의 맨 마지막 주소를 return 해주는 함수
	*	@pre	리스트가 1개 이상 있어야 한다.
	*	@post	리스트의 마지막 return
	*	@return	Last
	*/
	DoublyList* GetLastList() { return last; }

	/**
	*	@brief	DoublyList의 기본 생성자, size를 0으로 한다.
	*	@pre	넣고자 하는 template에 id가 있어야 한다.(SortedList 이기 때문임)
	*	@post	size = 0, first = this
	*/
	DoublyList();

	/**
	*	@brief	size 변수가 static type 여서 size를 1 증가시켜주는 함수
	*/
	static void sizeplus() {
		size++;
	}

	/**
	*	@brief	아이템을 넣고 생성을 원할 때 호출해주는 함수
	*	@pre	아이템이 id를 갖고 있어야 한다.
	*/
	DoublyList<T>(T* _T) {
		Item = *_T;
	}

	/**
	*	@brief	list에 item을 추가하고 싶을 때 호출하는 함수
	*	@pre	list가 일단 존재해야 한다. item이 id를 갖고 있어야 한다.
	*	@post	아이템의 id를 기준으로 넣을 위치를 결정한 이후 item을 추가한다.
	*/
	void addItem(T* Item);
	
	/**
	*	@brief	ID를 기준으로 유저를 검색하는 함수. DoublyLinkedList 이기 때문에 Left에서 검색이 가능하지만 아직 구현하지 않았다.
	*	@pre	List가 1개 이상 있어야 한다.
	*	@post	List의 맨 처음부터 조사하여 id가 일치하는 정보를 return 해준다.
	*	@return	찾으면 1, 아니면 0을 return
	*/
	bool ToRightFindUserByID(T* & _user, int id);
	
	/**
	*	@brief	원하는 정보를 삭제하고 싶을 때 호출한다.
	*	@pre	Item의 모든 정보가 일치하는지 확인한다.
	*	@post	일치할 경우 해당 아이템을 삭제하고 삭제된 before와 next를 이어준다.
	*/
	void delItem(T* Item);

	/**
	*	@brief	현재 list가 갖고 있는 item을 바꾸고 싶을 때 호출한다.
	*	@pre	지금의 list가 item을 정상적으로 갖고 있어야 한다.
	*	@post	item = _item
	*/
	void setItem(T* _Item) { Item = *_Item; }
	/*
	T * sortItem(T* Item);
	T * getNextItem(T* Item);
	T * getBeforeItem(T* Item);
	*/

	/**
	*	@brief	this의 before을 새로이 setting 한다.
	*/
	void setbefore(DoublyList* _item) {
		before = _item;
	}

	/**
	*	@brief	this의 next를 새로이 setting 한다.
	*/
	void setnext(DoublyList* _Item) {
		next = _Item;
	}

	//bool searchItem(T& Item);
	int getsize() { return size; }
	void setsize(int _s) { size = _s; }

	/**
	*	@brief	현재 리스트가 갖고 있는 목록에서 가장 마지막 list의 id를 return.
	*	@pre	리스트가 item을 1개 이상 갖고 있고 last가 정상적이어야 한다.
	*	@post	Getnextlist를 지속적으로 호출.
	*	@return	Last list의 id값을 출력.
	*/
	int GetLastId();
};