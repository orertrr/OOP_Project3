#include "BoardManager.h"

vector<User*> BoardManager::users;
vector<Board*> BoardManager::boards;
vector<Mail*> BoardManager::mails;
vector<BoardType*> BoardManager::boardtypes;
vector<Comment*> BoardManager::comments;
User* BoardManager::current_User = nullptr;
stack<Viewer*> BoardManager::viewers;
int BoardManager::console_width;

void BoardManager::Start()
{
	EnableVTR();

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO scbi;
	GetConsoleScreenBufferInfo(hOut, &scbi);

	console_width = scbi.srWindow.Right + 1;

	char input;
	viewers.push(new LoginViewer());
	viewers.top()->print();
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

void BoardManager::Send(char key, Viewer* currentViewer)
{
	currentViewer->receive(key);
}

void BoardManager::Forward(Viewer* nextViewer)
{
	cout << CSI "0m";
	cout << CSI "0;0H";
	cout << CSI " J";

	viewers.push(nextViewer);
	nextViewer->print();
}

void BoardManager::Back()
{
	Viewer* v = viewers.top();
	viewers.pop();
	delete v;

	viewers.top()->print();
}

void BoardManager::Login()
{
	UserManager manager;
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
			User* login = manager.Get(account);

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

			if (login->getPassWorrd() == password)
				current_User = login;
		}
	} while (current_User == nullptr);

	cout << "Login successful.\n";
}

void BoardManager::Logout()
{
	current_User = nullptr;

	while (viewers.size() > 0)
	{
		delete viewers.top();
		viewers.pop();
	}

	viewers.push(new LoginViewer());
	viewers.top()->print();
}
