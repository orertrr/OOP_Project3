#include "BoardManager.h"

vector<User*> BoardManager::users;
vector<Board*> BoardManager::boards;
vector<Mail*> BoardManager::mails;
vector<BoardType*> BoardManager::boardtypes;
vector<Comment*> BoardManager::comments;
User* BoardManager::current_User;
HANDLE BoardManager::hOut;
CONSOLE_SCREEN_BUFFER_INFO BoardManager::csbi;

void BoardManager::Start()
{
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &csbi);
}
