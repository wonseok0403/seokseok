#pragma once
#include<iostream>
using namespace std;
class FriendList {
public:
	int getId() { return id; }
	bool isFriend() { return Friend; }
	FriendList(int _id, bool chk) {
		id = _id;
		Friend = chk;
	}
	void setting(int _id, bool _chk) {
		id = _id;
		Friend = _chk;
	}
	FriendList() {}
private:
	int id;
	bool Friend;
};