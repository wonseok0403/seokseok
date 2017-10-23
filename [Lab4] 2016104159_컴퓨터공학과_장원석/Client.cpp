#include"Client.h"
#include"UserInterface.h"
#include<fstream>
#include"DoublyList.h"
using namespace std;
extern void PrintStartScreen();

bool client::isLogin() {
	if (CurrentUser->getName() == "" && CurrentUser->getId() == 0) {
		return false;
	}
	else return true;
}
client::client() {
	CurrentUser = new MemberType;
}
void client::ShowFriendList() {
	while (1) {
		PrintFriendListTitle();
		DoublyList<FriendList>* tmp;
		MemberType* UserTmp = new MemberType;
		tmp = CurrentUser->getFriendlists();
		for (;;) {
			OreoServer.getUserDB()->GetFirstList()->ToRightFindUserByID(UserTmp, tmp->getItem()->getId());
			if (UserTmp->getId() == 0 && UserTmp->getMsg() == "") {
				cout << "OreoTalk	OreoServices		I'm your friend!" << endl;
				cout << "=====================================================================" << endl;
				return;
			}
			PrintFriendOnList(UserTmp->getId(), UserTmp->getName(), UserTmp->getMsg());
			if (!tmp->GetNextList(tmp)) {
				PrintHiponOneline();
				return;
			}
		}
	}
}
bool client::isFriendById(MemberType * & _User, int _id) {
	FriendList* tmp = new FriendList;
	MemberType* tmp_user;
	if (CurrentUser->getFriendlists()->ToRightFindUserByID(tmp, _id)) {
		OreoServer.getUserDB()->GetFirstList()->ToRightFindUserByID(tmp_user, tmp->getId());
		_User = tmp_user;
		return true;
	}
	else return false;
}
string changeContentToEmot(string _s) {
	if (_s == "(Catmoticon)") {
		return "1_emot.txt";
	}
	else if (_s == "(Ryonticon)") {
		return "2_emot.txt";
	}
	else return _s;
}
void client::GoToChat(MemberType* _user) {
	// loading user own's chat list
	// tmp loading go to chat
	DoublyList<Chat>* tmo_ChatDB = new DoublyList<Chat>;
	DoublyList<Chat>* tmp_ChatDB = OreoServer.getChatDB();
	DoublyList<Chat>* User_ChatDB = new DoublyList<Chat>;
	while (1) {
		// loginedUser가 메시지를 보낸 경우
		if (tmp_ChatDB->getItem()->getWritter()->getId() == CurrentUser->getId() && tmp_ChatDB->getItem()->getGetter()->getId() == _user->getId()) {
			User_ChatDB->addItem(tmp_ChatDB->getItem());
		}
		else if (tmp_ChatDB->getItem()->getWritter()->getId() == _user->getId() && tmp_ChatDB->getItem()->getGetter()->getId() == CurrentUser->getId()) {
			User_ChatDB->addItem(tmp_ChatDB->getItem());
		}
		if (!tmp_ChatDB->GetNextList(tmp_ChatDB)) {
			break;
		}
	}
	tmp_ChatDB = User_ChatDB;
	if (tmp_ChatDB != nullptr) {
		while (1) {
			if (tmp_ChatDB->getItem()->getWritter()->getId() == CurrentUser->getId()) {
				// 로그인한 유저가 보낸 메시지 = 오른쪽
				DisplayChatContent(CurrentUser->getName(), tmp_ChatDB->getItem()->getMsg(), 1);
			}
			else {
				// 상대방이 보낸 메시지 = 왼쪽
				DisplayChatContent(tmp_ChatDB->getItem()->getWritter()->getName(), tmp_ChatDB->getItem()->getMsg(), 0);
			}
			if (!tmp_ChatDB->GetNextList(tmp_ChatDB)) {
				break;
			}
		}
	}
	cout<<"------- You've seen it all the way down here. -------------" << endl;

	// 채팅 시작
	string tmp_Content;
	Chat* tmp_Chat;
	char tmp_c[400];
	cin.getline(tmp_c, sizeof(tmp_c));
	while (1) {
		tmp_Chat = new Chat;
		tmp_Content = getChatByUser(CurrentUser->getName());
		if (tmp_Content == "") {
			cout << endl;
			cout << "Stop to Chat!" << endl << endl;
			break;
		}
		for (int i = 0; i < CurrentUser->bought_emot_num; i++) {
			//이모티콘
			if (CurrentUser->emot[i] == changeContentToEmot(tmp_Content)) {
				string a, b;
				ifstream input;
				input.open(CurrentUser->emot[i]);
				input >> a >> b;
				char tmp_emot[400];
				input.getline(tmp_emot, 400, '\n');
				input.getline(tmp_emot, 400, '\n');
				tmp_Content = tmp_emot;
			}
		}
		ClearLineBeforeChat();
		DisplayChatContent(CurrentUser->getName(), tmp_Content, 1);
		tmp_Chat->setting(OreoServer.getChatDB()->GetLastId()+1, CurrentUser, _user, tmp_Content);
		OreoServer.getChatDB()->addItem(tmp_Chat);
		ChatList.addItem(tmp_Chat);
	}
	cout << "Return to before menu~ " << endl;
	// 채팅 불러온거 임시 저장
	// 채팅한 내역 출력
	// 채팅 내역 입력 유도
	// 입력한 내역 서버에 저장
	// 저장 이후 창에 표시
	// call back
}
void client::afterLogin() {
	MemberType* tmpUser = new MemberType;
	DoublyList<Chat> *tmp_ChatDB = new DoublyList<Chat>;
	MemberType* tmp_usr;
	string tmp_str;
	while (isLogin()) {
		switch (PrintAfterLoginUserMenu()) {
		case 1: // go friend List
			ShowFriendList();
			switch (PrintAfterFriendList()) {
			case 1: // details of friend
				if (isFriendById(tmpUser, InputIdByUser())) {
					PrintDetailsOfUser(tmpUser->getId(), tmpUser->getPn(), tmpUser->getPw(), tmpUser->getName(), tmpUser->getMsg(), 1); // 1 = friend mode
					if (chkToGoChat()) {
						GoToChat(tmpUser);
					}
					else {
						cout << "Go other Menu ~ " << endl << endl;
						cin.get(); cin.get();
						system("pause");
						break;
					}
				}
				else {
					cout << "I can't find User" << endl;
					system("pause");
				}
				break;
			case 2: // Go chatting List
				if (ChatList.getItem() == nullptr) {
					NoChatList();
					break;
				}
				else if (ChatList.getItem()->getWritter()->getMsg() == "") {
					NoChatList();
				}
				else {
					system("cls");
					DoublyList<Chat> *tmp_ChatList = new DoublyList<Chat>;
					tmp_ChatList = &ChatList;
					while (1) {
						if (tmp_ChatList->getItem()->getWritter()->getId() == CurrentUser->getId()) {
							// 로그인한 유저가 보낸 메시지 = 오른쪽
							DisplayChatContent(CurrentUser->getName(),tmp_ChatList->getItem()->getGetter()->getName(), tmp_ChatList->getItem()->getMsg(), 1);
						}
						if (!tmp_ChatList->GetNextList(tmp_ChatList)) {
							break;
						}
					}
					DisplayTmpChatList();
				}
				break;
			case 3: // Go 1:1 Chat!
				if (isFriendById(tmpUser, InputIdByUser())) {
					if (chkToGoChat()) {
						GoToChat(tmpUser);
					}
					else {
						cout << "Go other Menu ~ " << endl << endl;
						cin.get(); cin.get();
						system("pause");
						break;
					}
				}
				else {
					cout << "I can't find User" << endl;
					system("pause");
				}
				break;
			case 0: // return to menu
				break;
			}
			break;
		case 2://  search friend
			OreoServer.retrieveByName();
			break;
		case 3: // Chatting List
			system("cls");
			tmp_ChatDB = OreoServer.getChatDB();
			PrintHiponOneline();
			while (1) {
				if (tmp_ChatDB->getItem()->getWritter()->getId() == CurrentUser->getId()) {
					// 로그인한 유저가 보낸 메시지 = 오른쪽
					DisplayChatContent(CurrentUser->getName(), tmp_ChatDB->getItem()->getGetter()->getName(), tmp_ChatDB->getItem()->getMsg(), 1);
				}
				if (!tmp_ChatDB->GetNextList(tmp_ChatDB)) {
					break;
				}
			}
			PrintHiponOneline(); cout << endl << endl;
			system("pause");
			break;
		case 4: // go 1:1 chat
			// CurrentUser 말고 채팅하고자 하는 사람의 아이디를 넣어주어야 함
	
			tmp_usr = new MemberType;
			while (1) {
				system("cls");
				PrintHiponOneline();
				cout << endl;
				cout << "You can chat with people who is not your friend!" << endl << endl;
				PrintHiponOneline(); cout << endl << endl;
				if (FindUserByName(tmp_usr, tmp_str)) {
					GoToChat(tmp_usr);
				}
				else {
					// 친구를 찾지 못했을 때
					cout << "I can't find that name in Server Database!" << endl;
				}
				cout << "Do you want to stop? (1/0)" << endl;
				// 그만할지 입력받고 그만할거면 중단
				bool chk; cin >> chk;
				if (chk) break;
			}
			break;

		case 5:
			OreoServer.saveDB(); // save
			OreoServer.logout(CurrentUser);
			AfterLogout();
			system("cls");
			break;

		case 6: // 빙수, 기프트 숍
			PrintLoginInterface(CurrentUser->getName());
			GoToShop();
			break;
		}

	}
}
void client::GoToShop() {
	ifstream inputBingsu;
	ifstream inputEmot;
	string dirBingsu="";
	string nick_emot;
	int money;
	int money_emot; string name_emot;
	int idx; char tmp[400];

	string t = to_string(CurrentUser->getId());
	dirBingsu = t + "_Bingsu";
	inputBingsu.open(dirBingsu + ".txt");
	if (inputBingsu.is_open() == false) { money = 0; }
	else { inputBingsu >> money; }
	int chosen;
	while (1) {
		chosen = PrintShopInterface(money);
		t = to_string(chosen) + "_emot.txt";
		inputEmot.open(t);
		if (inputEmot.is_open() == false) {
			cout << "InputError" << endl;
		}
		inputEmot >> name_emot >> money_emot;
		cout << name_emot << " : " << money_emot << "Bingsu! " << endl;
		while (!inputEmot.eof() && inputEmot.is_open()) {
			inputEmot.getline(tmp, 400, '\n');
			cout << tmp << endl;
		}
		cout << "Do you want to buy? (1/0)" << endl;
		bool chk;
		cin >> chk; if (chk) {
			// emoticon buy
			if (CurrentUser->bingPoint < money_emot) {
				cout << "You have less Bingsu..." << endl;
				system("pause");
				break;
			}
			CurrentUser->emot[CurrentUser->bought_emot_num++] = t;
			ofstream output;
			output.open(to_string(CurrentUser->getId()) + "_Bought.txt");
			output << CurrentUser->bought_emot_num << endl;
			for (int i = 0; i < CurrentUser->bought_emot_num; i++) {
				output << CurrentUser->emot[i] << endl;
			}
			output.close();

			output.open(to_string(CurrentUser->getId()) + "_Bingsu.txt");
			output << CurrentUser->bingPoint - money_emot;
			output.close();

			CurrentUser->bingPoint -= money_emot;
			break;
		}
		inputEmot.close();
	}
}
bool client::FindUserByName(MemberType*& _user, string _name) {
	DoublyList<MemberType> *tmp_DB = new DoublyList<MemberType>;
	tmp_DB = OreoServer.getUserDB();
	cout << "Input name which you want to search!" << endl;
	_name = InputNameToSearch();
	while (1) {
		if (tmp_DB->getItem()->getName() == _name) {
			_user = tmp_DB->getItem();
			return true;
		}
		else if (!tmp_DB->GetNextList(tmp_DB)) {
			break;
		}
	}
	return false;
}
void client::updateShop() {
	ifstream input;
	input.open(to_string(CurrentUser->getId()) + "_Bingsu.txt");
	input >> CurrentUser->bingPoint;
	input.close();

	input.open(to_string(CurrentUser->getId()) + "_Bought.txt");
	if (input.is_open() == false) return;
	int n;
	input >> n;
	CurrentUser->bought_emot_num = n;
	for (int i = 0; i < n; i++) {
		input >> CurrentUser->emot[i];
	}
}
void client::run() {
	int tmp_id;
	string tmp_pw;
	for (;;) {
		PrintStartScreen();
		cin.get();
		system("cls");
		switch (PrintUserMenu()) {
		case 1: // log in
			while (1) {
				if (isLogin()) {
					cout << CurrentUser->getName() << "! you already logined!\ndo you want to logout? (1/0) " << endl;
					bool chk;
					cin >> chk;
					if (chk) {
						if (OreoServer.logout(CurrentUser)) {
							cout << "You successfully loged out!" << endl;
							system("pause");
						}
						else {
							cout << "Your account may have some wrongs" << endl;
							cout << "Please contact : 010 6253 1685" << endl;
							system("pause");
							break;
						}
					}
					else {
						break;
					}
				}
				PrintLoginMenu(tmp_id, tmp_pw);
				CurrentUser->setId(tmp_id);
				CurrentUser->setPw(tmp_pw);
				if (OreoServer.login(CurrentUser)) {
					cout << "『" << CurrentUser->getName() << "』Login Succeed!" << endl;
					updateShop();
					system("pause");
					afterLogin();
					break;
				}
				else {
					CurrentUser = new MemberType;
					cout << "Login Failed!" << endl;
					cout << "Do you want to retry to login? (1/0)" << endl;
					bool chk; cin >> chk;
					if (!chk) {
						break;
					}
				}
			}
			break;
		case 2: // log out
			while (1) {
				if (isLogin() == true) {
					if (PrintLogoutMenu(CurrentUser->getName())) {
						CurrentUser = new MemberType;
					}
					else {
						cout << "Okay! Let's think other way!" << endl;
					}
					system("pause");
					break;
				}
				else {
					cout << "You must do log-in first!" << endl;
					system("pause");
					break;
				}
			}
			break;
		case 3: // sign in
			OreoServer.signin();
			system("cls");
			break;

		case 4:
			cout << "Program End." << endl;
			exit(10);
			break;
		}
	}
}