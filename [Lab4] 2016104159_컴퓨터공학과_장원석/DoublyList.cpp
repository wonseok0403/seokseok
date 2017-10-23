#include"DoublyList.h"
using namespace std;


template<typename T>
int DoublyList<T>::size = 0;

template<typename T>
DoublyList<T>* DoublyList<T>::first = new DoublyList<T>;

template<typename T>
DoublyList<T> * DoublyList<T>::last = new DoublyList<T>;

template <typename T>
void DoublyList<T>::addItem(T* _Item) {
	int i;
	if (size == 0 || Item.getId() == 0) {
		setItem(_Item);
		first = this;
		size = 1;
	}
	else if (next == nullptr) {
		DoublyList* adding = new DoublyList(_Item);
		next = adding;
		last = next;
		adding->setbefore(this);
	}
	else {
		// 1 2 3 4
		if (Item.getId() > _Item->getId() && before != nullptr) {
			DoublyList* tmpNext = next;
			DoublyList* tmpBefore = before;
			DoublyList* adding = new DoublyList(_Item);
			before->setnext(adding);
			adding->setbefore(before);
			adding->setnext(this);
			before = adding;
			last = this;
		}
		else {
			next->addItem(_Item);
		}
	}
}
template<typename T>
bool DoublyList<T>::ToRightFindUserByID(T* & _user, int _id) {
	if (Item.getId() == _id) {
		_user = &(this->Item);
		return true;
	}
	else {
		if (next == nullptr) {
			return false;
		}
		else {
			next->ToRightFindUserByID(_user, _id);
		}
	}
}
template <typename T>
void DoublyList<T>::delItem(T* Item) {

}

template <typename T>
DoublyList<T>::DoublyList() {
}

template <typename T>
int DoublyList<T>::GetLastId() {
		if (next == nullptr) {
			return Item.getId();
		}
		else {
			next->GetLastId();
		}
}


