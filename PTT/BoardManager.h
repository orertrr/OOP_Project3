#pragma once

#include <iostream>
#include <conio.h>
#include <vector>
#include <stack>
#include <string>
#include <Windows.h>
#include "User.h"
#include "Board.h"
#include "Post.h"
#include "Mail.h"
#include "Comment.h"
#include "BoardType.h"
#include "LoginViewer.h"
#include "HomeViewer.h"

#define ESC "\x1b"
#define CSI "\x1b["

using std::vector;
using std::stack;
using std::cout;

class BoardManager
{
	friend class HomeViewer;
	friend class LoginViewer;

private:
	static vector<User*> users;
	static vector<Board*> boards;
	static vector<Mail*> mails;
	static vector<BoardType*> boardtypes;
	static vector<Comment*> comments;
	static User* current_User;
	static stack<Viewer*> viewers;
	static int console_width;

	static void EnableVTR();

	static void Send(int key, Viewer* currentViewer);
	static void Forward(Viewer* nextViewer);
	static void Back();

	static void Login();
	static void Logout();
	
public:
	static void Start();
	
};