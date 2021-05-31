#pragma once

#include <conio.h>
#include <vector>
#include <Windows.h>
#include "User.h"
#include "Board.h"
#include "Post.h"
#include "Mail.h"
#include "Comment.h"
#include "BoardType.h"

using std::vector;

class BoardManager
{
private:
	static vector<User*> users;
	static vector<Board*> boards;
	static vector<Mail*> mails;
	static vector<BoardType*> boardtypes;
	static vector<Comment*> comments;
	static User* current_User;
	static HANDLE hOut;
	static CONSOLE_SCREEN_BUFFER_INFO csbi;

public:
	static void Start();
	static void Loop();

	static void Login(User* login_User);
	static void Logout();

};