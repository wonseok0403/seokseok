#include<iostream>
#include<iomanip>
#include<string>
#include<Windows.h>
#include<stdio.h>
#include"UserInterface.h"
using namespace std;


CONSOLE_SCREEN_BUFFER_INFO ScrBuf;
void PrintStartScreen() {
	system(" mode con lines=30 cols=80 ");
	cout << "                        ┏━━━━━━━━━━━━━━┓" << endl;
	cout << "                        ┃                           -┃" << endl;
	cout << "                        ┃                        O  -┃" << endl;
	cout << "                        ┃                       RE  -┃" << endl;
	cout << "                        ┃                     OTAL  -┃" << endl;
	cout << "                        ┃                    OTERK  -┃" << endl;
	cout << "                        ┃                 O   REOT  -┃" << endl;
	cout << "                        ┃         O    ORTKORE ORE  -┃" << endl;
	cout << "                        ┃        OORE OETLAKOREOTA  -┃" << endl;
	cout << "                        ┃      EOTALKOREOREOTALKRE  -┃" << endl;
	cout << "                        ┃    OREOTREOTAKREEETALKRE  -┃" << endl;
	cout << "                        ┃                           -┃" << endl;
	cout << "                        ┃         OREO TALK         -┃" << endl;
	cout << "                        ┃                     V0.9  -┃" << endl;
	cout << "                        └━━━━━━━━━━━━━━┘" << endl;

	cout << "                             ! ENTER TO CONTINUE !" << endl << endl;
	cout << " :: Patch Note :: " << endl;
	cout << "    0.4v (10/19) Program will get the size of console. " << endl;
	cout << "    0.41v (10/20) Program can chat with other people." << endl;
	cout << "    0.5v (10/21) Program officially support chat-mode." << endl;
	cout << "    0.55v (10/21) You can send any message to anyone." << endl;
	cout << "    0.6v (10/22) Some errors are fixed" << endl;
	cout << "    0.61v (10/22) You can send your chat to anyone in server" << endl;
	cout << "    0.7v (10/23) Program can save data" << endl;
	cout << "    0.8v (10/23) You can signin" << endl;
	cout << "    0.9v (10/23) We support you < Oreo shop > " << endl;
	cout << "    0.91v(Not yet) You can chat with many people" << endl;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ScrBuf);

}

void PrintUserId(int& id, string& pw) {
	cout << "ID : "; cin >> id;
	cout << "PW : "; cin >> pw;
}
void PrintLoginMenu(int& id, string& pw) {
	system("cls");
	cout << " Thank you for using OREO TALK! " << endl;
	cout << " Please type your information down! " << endl;
	cout << " ID : "; cin >> id;
	cout << " PW : "; cin >> pw;
	return;
}
void PrintFriendOnList(int _id, string _name, string _msg) {
	cout << _id << "\t\t" << _name << "\t\t" << _msg << endl;
}
void PrintFriendListTitle() {
	system("cls");
	PrintHiponOneline();
	cout << "ID		Name				Message" << endl;
	PrintHiponOneline();
}
int PrintAfterLoginUserMenu() {
	while (1) {
		system("cls");
		cout << "┏━━━━━━━━━━━━━━┓" << endl;
		cout << "┃- ! Welcome Oreotalk ?     -┃" << endl;
		cout << "┃--- 1. Go Friend List!     -┃" << endl;
		cout << "┃--- 2. Search Friend!      -┃" << endl;
		cout << "┃--- 3. Go Server Chat list -┃" << endl;
		cout << "┃--- 4. Go 1:1 Chat!        -┃" << endl;
		cout << "┃--- 5. Save & exit         -┃" << endl;
		cout << "┃--- 6. Gift shop!          -┃" << endl;
		cout << "┃--- 0. Refresh!            -┃" << endl;
		cout << "└━━━━━━━━━━━━━━┘" << endl;
		int chk;
		cout << "  -> "; cin >> chk;
		if (chk < 1 || chk >6) {
			cout << "Do you want to return?(1/0" << endl;
			bool Rechk;
			cin >> Rechk;
			if (Rechk) return 0;
		}
		else {
			return chk;
		}
	}
}
bool PrintLogoutMenu(string _name) {
	cout << "======================================" << endl;
	cout << "  " << _name << "! Do you want to logout?" << endl;
	cout << "If you want, type 1! else, 0!" << endl;
	cout << "======================================" << endl;
	bool chk;
	cin >> chk;
	return chk;
}
void PrintDetailsOfUser(int _id, string _pn, string _pw, string _name, string _msg, int mode) {
	cout << endl << endl;
	if (mode == 1) { // User - Friend Mode
		cout << "About User * ----------------------------------" << endl;
		cout << "ID    : " << _id << endl;
		cout << "Name  : " << _name << endl;
		cout << "Phone : " << _pn << endl;
		cout << "Msg   : " << _msg << endl;
		cout << "End -------------------------------------------" << endl;
		cin.get(); cin.get();
	}
	if (mode == 2) {
		cout << "About User * -----------------------------------" << endl;
		cout << "ID    : " << _id << endl;
		cout << "Name  : " << _name << endl;
		cout << "Phone : " << "Not friend" << endl;
		cout << "Msg   : " << _msg << endl;
		cout << "End -------------------------------------------" << endl;
	}
}
// loginMenu
int InputIdByUser() {
	int tmp;
	cout << "┌━━━━━━━━━━━━━━━━━" << endl;
	cout << "┣ Input ID you want to search -> ";
	cin >> tmp;
	return tmp;
}
bool chkToGoChat() {
	cout << "Do you want to chat with him/her ? (1/0)" << endl;
	bool chk; cin >> chk;
	return chk;
}
int PrintAfterFriendList() {
	cout << endl;
	cout << "    ┌━━━━━━━━━━━━━━━┐" << endl;
	cout << "┏━┴  1. Details of friend      ━┤" << endl;
	cout << "┣━━  2. Go recent Chat List!   ━┤" << endl;
	cout << "┣━━  3. Go 1:1 Chat!           ━┤" << endl;
	cout << "└━━  0. Return to menu         ━┘" << endl;
	int chk;
	cout << "  -> "; cin >> chk;
	if (chk < 1 || chk >5) {
		cout << "Do you want to return?(1/0)" << endl;
		bool Rechk;
		cin >> Rechk;
		if (Rechk) return 0;
	}
	else {
		return chk;
	}
}
string InputName() {
	string tmp;
	cin >> tmp;
	return tmp;
}
string InputNameToSearch() {
	cout << "-----User Find Menu!------" << endl;
	cout << "-> ";
	return InputName();
}
int PrintFriendSearchMenu() {
	system("cls");
	cout << "┏━━━━━━━━━━━━┓" << endl;
	cout << "┃- Searching friend     -┃" << endl;
	cout << "┃--- 1. By name         -┃" << endl;
	cout << "┃--- 2. By ID           -┃" << endl;
	cout << "┃--- 0. Exit            -┃" << endl;
	cout << "└━━━━━━━━━━━━┘" << endl;
	int k;
	cin >> k;
	if (k < 1 || k>2) {
		cout << "Do you want to exit? (1/0)" << endl;
		bool chk; cin >> chk;
		if (chk) return 0;
		else {
			cout << "Try again!" << endl;
			cin.get(); cin.get();
			return 3;
		}
	}
	else {
		return k;
	}
}
int PrintUserMenu() {
	int k;
	while (1) {
		system("cls");
		cout << "┏━━━━━━━━━━━━━┓" << endl;
		cout << "┃- ! What do you want ?   -┃" << endl;
		cout << "┃--- 1. Log in            -┃" << endl;
		cout << "┃--- 2. Log out           -┃" << endl;
		cout << "┃--- 3. Sign in           -┃" << endl;
		cout << "┃--- 4. Exit              -┃" << endl;
		cout << "└━━━━━━━━━━━━━┘" << endl;
		cout << "   -->"; cin >> k;
		if (k < 0 || k>5) {
			cout << "INPUT ERROR!" << endl;
			cout << "Please re-enter what you want to do!" << endl;
			system("pause");
		}
		else {
			return k;
		}
	}
	return 1;
}

void DisplayChatContent(string writter,string getter, string content, bool isCurrentUserWritten) {

		// 오른쪽
		cout << setw(ScrBuf.dwSize.X - 12 - getter.size()) << right << writter << " -> " << getter << endl;
		cout << setw(ScrBuf.dwSize.X - 8) << right << content << endl << endl;
}
void DisplayChatContent(string writter, string content, bool isCurrentUserWritten) {

	if (isCurrentUserWritten) {
		// 오른쪽
		cout << setw(ScrBuf.dwSize.X - 8) << right << writter << endl;
		cout << setw(ScrBuf.dwSize.X - 8) << right << content << endl << endl;
	}
	else {
		// 왼쪽
		cout << "        " << writter << endl;
		cout << "        " << content << endl << endl;
	}
}

string getChatByUser(string _name) {
	char tmp_c[400];
	cout << "<Press just enter to stop to chat" << endl;
	for (int i = 0; i < ScrBuf.dwSize.X; i++) {
		cout << "=";
	}	
	cout << endl;
	cout << "  " << _name << endl;
	cout << "-> ";
	cin.getline(tmp_c, 350);
	return tmp_c;
}
void gotoxy(int x, int y) {
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void ClearLineBeforeChat() {
	cout << "\b";
	for (int y = 1; y <= 4; y++) {
		cout << "\r";
		for (int x = 0; x < ScrBuf.dwSize.X; x++) {
			cout << " ";
		}
		cout << "\r\b";
	}
}
void NoChatList() {
	// 표시할 임시 채팅 내역이 없을 경우
	system("cls");
	for (int x = 0; x < ScrBuf.dwSize.X; x++) {
		cout << "=";
	}
	cout << endl << "No chats are in here at this session!" << endl << endl;
	for (int x = 0; x < ScrBuf.dwSize.X; x++) {
		cout << "=";
	}
	system("pause");
}
void DisplayTmpChatList() {
	// 표시할 채팅 내역이 있을 경우
	for (int x = 0; x < ScrBuf.dwSize.X; x++) {
		cout << "=";
	}
	cout << " Here are you have chatted! " << endl << endl;
	cout << " Press any key to return before menu " << endl;
	cin.get(); cin.get();
}

void PrintHiponOneline() {
	for (int x = 0; x < ScrBuf.dwSize.X; x++) {
		cout << "=";
	}
}
void AfterLogout() {
	cout << "┌━━━━━━━━━━━━━━━━☆" << endl;
	cout << "┣ Good Bye ~ Let's meet again~	 " << endl;
	cout << "└━━━━━━━━━━━━━━" << endl;
	cout << endl;
	cin.get(); cin.get();
}
void InputforSignin(int& id, string& name, string& pn, string& pw, string& msg) {
	cout << "┏━━━━━━━━━━━━┓" << endl;
	cout << "┃- User sign-in menu    -┃" << endl;
	cout << "┃--- 1. ID              -┃" << endl;
	cout << "┃--- 2. name            -┃" << endl;
	cout << "┃--- 3. PN              -┃" << endl;
	cout << "┃--- 4. PW              -┃" << endl;
	cout << "┃--- 5. MSG             -┃" << endl;
	cout << "└━━━━━━━━━━━━┘" << endl;
	cout << "  Caution : If you input ID already in here, you have to write this form again! " << endl << endl;
	cout << "Input ID : "; cin >> id;
	cout << "Input name : "; cin >> name;
	cout << "Input PN : "; cin >> pn;
	cout << "Input PW : "; cin >> pw;
	char tmp[400];
	cout << "Input msg : ";
	cin.getline(tmp, 400, '\n');
	cin.getline(tmp, 400, '\n');
	msg = tmp;
	return;
}
void PrintLoginInterface(string n) {
	system("cls");
	string tmp = "Welcome to Kakao Shop! : " + n;
	cout << setw(ScrBuf.dwSize.X - 4) << right << tmp << endl;
	for (int x = 0; x < ScrBuf.dwSize.X; x++) {
		cout << "=";
	}
	cout << endl << endl;
}
// 서버로 이동시키는게 좋을 수 있음.
void PrintRecentItems() {
	cout << "Recent Hot items! " << endl;
	cout << "1. Cat emoticon" << endl;
	cout << "2. Lion emoticon" << endl;
	cout << endl;
}
void PrintPastItems() {
	cout << "Past items : " << endl;
	cout << "   ... " << endl;
}
int PrintShopInterface(int money) {
	string tmp = "Bingsu : " + to_string(money);
	while (1) {
		cout << setw(ScrBuf.dwSize.X - 4) << right << tmp << endl;
		cout << endl;
		PrintRecentItems();
		PrintPastItems();
		cout << "What do you want to see? " << endl;
		int n;
		cin >> n;
		if (n < 0 || n>2) {
			cout << "Input err!" << endl;
			bool chk;
			cout << "Do you want to exit(1/0)?" << endl;
			cin >> chk; if (chk) break;
			else {
				continue;
				system("cls");
			}
		}
		return n;
	}
}