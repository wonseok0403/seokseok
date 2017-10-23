#include"Server.h"
#include<iostream>
#include<string>
#include"User.h"
#include"Chat.h"
#include"FriendList.h"
#include"UserInterface.h"
#include<fstream>
using namespace std;
/*
DoublyList<User> UserDB;
DoublyList<Chat> ChatDB;
User* FirstUserDB;
User* LastUserDB;
*/
server::server() {
	loadDB();
}
bool server::logout(MemberType* & _User) {
	if (_User->getId() != 0 && _User->getName() != "" && _User->getPw() != "") {
		_User = new MemberType;
		return true;
	}
	else {
		cout << "You have never loged in!" << endl;
		return false;
	}
}
bool server::login(MemberType* & _User) {
	MemberType* u;
	if (!UserDB.GetFirstList()->ToRightFindUserByID(u, _User->getId())) {
		cout << "Id you wrote down is not in DB" << endl;
		return 0;
	}
	else {
		if (_User->getPw() == u->getPw()) {
			_User = u;
			return true;
		}
		else {
			cout << "Password you wrote down is not same as DB" << endl;
			return false;
		}
	}
}
void server::retrieveByName() {
	MemberType* tmpUser = new MemberType;
	DoublyList<MemberType>* tmpUserDB = & UserDB;
	while (1) {
		switch (PrintFriendSearchMenu()) {
		case 1: // by name
			tmpUser->setName(InputNameToSearch());
			for (;;) {
				if (tmpUserDB->getItem()->getName() == tmpUser->getName()) {
					PrintDetailsOfUser(tmpUserDB->getItem()->getId(), tmpUserDB->getItem()->getPn(), tmpUserDB->getItem()->getPw(), tmpUserDB->getItem()->getName(), tmpUserDB->getItem()->getMsg(), 1);
					break;
				}
				else {
					if (tmpUserDB->GetNextList(tmpUserDB) == false) {
						cout << "I can't find that user! Sorry!" << endl;
						cin.get(); cin.get();
						break;
					}
				}
			}
			break;
		case 2: // by ID
			tmpUser->setId(InputIdByUser());
			for (;;) {
				if (tmpUserDB->getItem()->getId() == tmpUser->getId()) {
					PrintDetailsOfUser(tmpUserDB->getItem()->getId(), tmpUserDB->getItem()->getPn(), tmpUserDB->getItem()->getPw(), tmpUserDB->getItem()->getName(), tmpUserDB->getItem()->getMsg(), 1);
					break;
				}
				else {
					if (tmpUserDB->GetNextList(tmpUserDB) == false) {
						cout << "I can't find that user! Sorry!" << endl;
						cin.get(); cin.get();
						break;
					}
				}
			}
			break;
		case 0:
			return;
		}
	}
}
void server::signin() {
	MemberType* tmp_usr = new MemberType;
	MemberType* isUsr = new MemberType;
	int id;
	string name, pn, pw, msg;
	while (1) {
		InputforSignin(id, name, pn, pw, msg);
		tmp_usr->setNPIPM(name, pn, id, pw, msg);
		if (UserDB.ToRightFindUserByID(isUsr, id)) {
			cout << "User Id is already in here" << endl;
			cout << "Do you want to re-start? (1/0) " << endl;
			bool chk;
			cin >> chk;
			if (!chk) break;
		}
		else {
			UserDB.addItem(tmp_usr);
			cout << "Your sign-in has been done!" << endl;
			break;
		}
	}
}
void server::saveDB() {
	// userDB save
	// chatDB save
	ofstream output;
	DoublyList<Chat> *ChatTmpBox;
	DoublyList<MemberType> *UserTmpBox = new DoublyList<MemberType>;
	ChatTmpBox = new DoublyList<Chat>;
	ChatTmpBox = &ChatDB;
	output.open("UserDB.txt");
	UserTmpBox = &UserDB;
		while (1) {
			if (UserTmpBox->getItem() != nullptr) {
				output << UserTmpBox->getItem()->getName() << "\t" << UserTmpBox->getItem()->getPn() << "\t" << UserTmpBox->getItem()->getId() << "\t" << UserTmpBox->getItem()->getPw() << "\t" << UserTmpBox->getItem()->getMsg();
			}
			if (!UserTmpBox->GetNextList(UserTmpBox)) {
				break;
			}
			else { output << endl; }
		}


	output.close();
	output.open("ChatDB.txt");
	int i = 1;
	// chat save complete
	while (1) {
		if (ChatTmpBox->getItem() != nullptr) {
			output << i << "\t" << ChatTmpBox->getItem()->getWritter()->getId() << "\t\t" << ChatTmpBox->getItem()->getGetter()->getId() << "\t" << ChatTmpBox->getItem()->getMsg();
		}
		if (!ChatTmpBox->GetNextList(ChatTmpBox)) {
			break;
		}
		else { output << endl; i++; }
	}
	output.close();
	output.open("FriendListDB_t.txt");
	DoublyList<MemberType> *tmp_userBox = new DoublyList<MemberType>;
	tmp_userBox = &UserDB;
	DoublyList<FriendList> *tmp_fBox;
	bool flag = false;
	while (1) {
		if (tmp_userBox->getItem() != nullptr) {
			tmp_fBox = new DoublyList<FriendList>;
			tmp_fBox = tmp_userBox->getItem()->getFriendlists();
			
			while (1) {
				if (tmp_fBox->getItem() != nullptr) {
					if (tmp_userBox->getItem()->getId() > tmp_fBox->getItem()->getId()) {
						break;
					}
					else {
						if (flag) { output << endl; }
						flag = true;
						output << tmp_userBox->getItem()->getId() << "\t\t" << tmp_fBox->getItem()->getId();
					}
					if (!tmp_fBox->GetNextList(tmp_fBox)) {
						break;
					}
				}
			}
		}
		if (!tmp_userBox->GetNextList(tmp_userBox)) {
			break;
		}
	}
}
void server::loadDB() {
	// below is loading User DB
	ifstream input;
	string _name, _pn, _pw, _msg;
	int _id;
	MemberType* tmpUser = new MemberType;
	char msgBox[60];
	input.open("UserDB.txt");
	while (!input.eof() && input.is_open()) {
		input >> _name >> _pn >> _id >> _pw;
		input.getline(msgBox, 10, '\t');
		input.getline(msgBox, sizeof(msgBox), '\n');
		tmpUser->setNPIPM(_name, _pn, _id, _pw, msgBox);
		UserDB.addItem(tmpUser);
	}
	if (input.is_open() == false) {
		cout << "I can't load USER DB!" << endl;
	}

	// below is loading  DB
	input.close();
	input.open("ChatDB.txt");
	MemberType* _wtr = new MemberType;
	int _wtrId;
	char _tmpMsg[400];
	MemberType* _gtr = new MemberType;
	Chat* _chat = new Chat;
	int _gtrId;
	while (!input.eof() && input.is_open()) {
		_wtr = new MemberType;
		_gtr = new MemberType;
		_chat = new Chat;
		input >> _id >> _wtrId >> _gtrId;
		input.getline(_tmpMsg, sizeof(_tmpMsg), '\t');
		input.getline(_tmpMsg, 400, '\n');
		if (!UserDB.GetFirstList()->ToRightFindUserByID(_wtr, _wtrId)) {
			cout << "I can't find WritterID" << endl;
			break;
		}
		if (!UserDB.GetFirstList()->ToRightFindUserByID(_gtr, _gtrId)) {
			cout << "I can't find GetterID" << endl;
			break;
		}
		_chat->setting(_id, _wtr, _gtr, _tmpMsg);
		ChatDB.addItem(_chat);
	}
	if (input.is_open() == false) {
		cout << "I can't load Chat DB!" << endl;
	}

	// below is loading Friend List
	MemberType* _f1;
	MemberType* _f2;
	FriendList* tmpFriendList1;
	FriendList* tmpFriendList2;
	_f1 = new MemberType;
	_f2 = new MemberType;
	input.close();
	input.open("FriendListDB.txt");
	int _id1, _id2;
	int *tmpId1, *tmpId2;
	while (!input.eof() && input.is_open()) {
		_f1 = new MemberType;
		_f2 = new MemberType;
		input >> _id1 >> _id2;
		if (!UserDB.GetFirstList()->ToRightFindUserByID(_f1, _id1)) {
			cout << "I can't find Id : " << _id1 << endl;
			system("pause");
		}
		if (!UserDB.GetFirstList()->ToRightFindUserByID(_f2, _id2)) {
			cout << "I can't find Id : " << _id2 << endl;
			system("pause");
		}
		tmpFriendList1 = new FriendList;
		tmpFriendList1->setting(_f1->getId(), 1);

		tmpFriendList2 = new FriendList;
		tmpFriendList2->setting(_f2->getId(), 1);
		_f1->getFriendlists()->addItem(tmpFriendList2);
		_f2->getFriendlists()->addItem(tmpFriendList1);
		// friend list 다시 만들기
	}

	// below is loading preFriendList
	input.close();
	input.open("PreFriendListDB.txt");
	while (!input.eof() && input.is_open()) {
		_f2 = new MemberType;
		input >> _id1 >> _id2;
		if (!UserDB.GetFirstList()->ToRightFindUserByID(_f1, _id1)) {
			cout << "I can't find id : " << _id1 << endl;
			system("pause");
		}
		if (!UserDB.GetFirstList()->ToRightFindUserByID(_f2, _id2)) {
			cout << "I can't find id : " << _id2 << endl;
			system("pause");
		}
		tmpFriendList1 = new FriendList;
		tmpFriendList1->setting(_f1->getId(), 0);
		_f2->getFriendlists()->addItem(tmpFriendList1);
	}
}