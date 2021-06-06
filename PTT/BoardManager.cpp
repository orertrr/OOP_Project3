#include "BoardManager.h"

vector<User*> BoardManager::users;
vector<Board*> BoardManager::boards;
vector<Mail*> BoardManager::mails;
vector<BoardType*> BoardManager::boardtypes;
vector<Comment*> BoardManager::comments;
vector<Post*> BoardManager::posts;
User* BoardManager::current_User = nullptr;
stack<Viewer*> BoardManager::viewers;
int BoardManager::console_width;

void BoardManager::Start()
{
	LoadData();
	EnableVTR();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO scbi;
	GetConsoleScreenBufferInfo(hOut, &scbi);

	console_width = scbi.srWindow.Right + 1;

	int input;
	viewers.push(new LoginViewer());
	viewers.top()->print();

	cout << CSI "?12h";
	while (input = _getch())
	{
		Send(input, viewers.top());
	}
}

void BoardManager::EnableVTR()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);

	DWORD outMode, inMode;
	GetConsoleMode(hOut, &outMode);
	GetConsoleMode(hIn, &inMode);

	SetConsoleMode(hOut, outMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN);
	SetConsoleMode(hIn, inMode);
}

void BoardManager::Send(int key, Viewer* currentViewer)
{
	currentViewer->receive(key);
}

void BoardManager::Forward(Viewer* nextViewer)
{
	cout << CSI "0m";
	cout << CSI "0;0H";
	cout << CSI "J";

	viewers.push(nextViewer);
	nextViewer->print();
}

void BoardManager::Back()
{
	Viewer* v = viewers.top();
	viewers.pop();
	delete v;

	cout << CSI "0m";
	cout << CSI "0;0H";
	cout << CSI "J";
	viewers.top()->print();
}

void BoardManager::Login()
{
	UserController controller;
	string account;
	string password;

	cout << CSI "0m";

	do
	{
		cout << CSI "5;0H";
		cout << CSI "K";
		cout << CSI "6;0H";
		cout << CSI "K";
		cout << CSI "7;0H";
		cout << CSI "K";

		cout << CSI "5;0H";
		cout << "Enter your Account to login, enter Guest to visit, or enter new to register: ";

		getline(cin, account);

		if (account == "Guest");
		else if (account == "new");
		else
		{
			User* login = controller.Get(account);

			if (login == nullptr)
			{
				cout << CSI "6;0H";
				cout << "This Account is not exists.\n";
				cout << "Press any key to continue.";
				cin.get();

				continue;
			}

			cout << CSI "6;0H";
			cout << "Password: ";
			cin >> password;
			cin.get();

			if (login->getPassWorrd() == password)
			{
				if (current_User != nullptr)
				{
					delete current_User;
				}

				current_User = new User();
				*current_User = *login;
			}
		}
	} while (current_User == nullptr);

	Forward(new HomeViewer());
}

void BoardManager::Logout()
{
	cout << CSI "J";
	current_User = nullptr;

	while (viewers.size() > 0)
	{
		delete viewers.top();
		viewers.pop();
	}

	Forward(new LoginViewer());
}

void BoardManager::Create_comment(PostViewer* post)
{
	string comment;

	cout << CSI + std::to_string(console_width - 1) << ";0H";
	cout << "Type your comment here: ";
	cout << CSI "47;30";
	cout << CSI + std::to_string(console_width) + "@";
	cin >> comment;

	cout << CSI + std::to_string(console_width) + "@";
	cout << "(1)Push (2)Pull (3)None";

	int kind = 0;
	bool has_pushed_or_pulled = false;

	for (auto e : post->comments)
	{
		if (!e->getBeDelete() && e->getUserAccount() == current_User->getAccount() && (e->getKind() == 1 || e->getKind() == -1))
		{
			has_pushed_or_pulled = true;
			break;
		}
	}

	if (!has_pushed_or_pulled)
	{
		do
		{
			kind = _getch();
		} while (kind != '1' || kind != '2' || kind != '3');

		if (kind == '1')
			kind = 1;
		else if (kind == '2')
			kind = 0;
		else if (kind == '3')
			kind = -1;
	}

	Comment new_comment(comment, current_User->getAccount(), post->p->getPostID(), kind);
	CommentController().Insert(new_comment);

	LoadData();

	// Reflash Viewers
	auto board = BoardController().Get(post->p->getBoardID());
	auto p = post->p;

	Back();
	Back();
	Forward(new BoardViewer(board));
	Forward(new PostViewer(p));
}

void BoardManager::LoadData()
{
	for (auto element : users)
		delete element;
	for (auto element : boards)
		delete element;
	for (auto element : posts)
		delete element;
	for (auto element : comments)
		delete element;
	for (auto element : boardtypes)
		delete element;
	for (auto element : mails)
		delete element;

	users = UserController().GetAll();
	boards = BoardController().GetAll();
	posts = PostController().GetAll();
	comments = CommentController().GetAll();
	boardtypes = BoardTypeController().GetAll();
	mails = MailController().GetAll();
}
