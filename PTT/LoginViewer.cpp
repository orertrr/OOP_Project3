#include "LoginViewer.h"
#include "BoardManager.h"

// Welcome to PTT
// Enter your Account to login,  enter Guest to visit, or enter new to register

void LoginViewer::print()
{
	string width = std::to_string(BoardManager::console_width);

	cout << CSI "37;44m";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";

	cout << CSI "2;" << std::to_string(BoardManager::console_width / 2 - 7) << "H";
	cout << "Welcome to PTT";

	BoardManager::Login();
}
