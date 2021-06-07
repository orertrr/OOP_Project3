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
#include "LoginViewer.h"
#include "HomeViewer.h"
#include "BoardTypeViewer.h"
#include "PostViewer.h"

#define ESC "\x1b"
#define CSI "\x1b["

using std::vector;
using std::stack;
using std::cout;

class BoardManager
{
	friend class HomeViewer;
	friend class LoginViewer;
	friend class BoardTypeViewer;
	friend class SelectBoardViewer;
	friend class BoardViewer;
	friend class PostViewer;
	friend class MailBoxViewer;
	friend class MailViewer;

private:
	static vector<User*> users;
	static vector<Board*> boards;
	static vector<Mail*> mails;
	static vector<BoardType*> boardtypes;
	static vector<Comment*> comments;
	static vector<Post*> posts;
	static User* current_User;
	static stack<Viewer*> viewers;
	static int console_width;

	static void EnableVTR();

	static void Send(int key, Viewer* currentViewer);
	static void Forward(Viewer* nextViewer);
	static void Back();

	static void Login();
	static void Logout();
	static void Create_comment(PostViewer* post);
	static void Create_mail();

	static void LoadData();
	
public:
	static void Start();
	
};