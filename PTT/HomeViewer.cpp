#include "HomeViewer.h"
#include "BoardManager.h"

// View Board
// Mail
// Admin Page
// Logout

void HomeViewer::move_up()
{
	do
	{
		if (selection_index - 1 < 0) return;

		cout << CSI "1A";
		selection_index--;
	} while (!enable_state[selection_index]);
}

void HomeViewer::move_down()
{
	do
	{
		if (selection_index + 1 >= selection_count) return;

		cout << CSI "1B";
		selection_index++;
	} while (!enable_state[selection_index]);
}

void HomeViewer::enter()
{
	if (selection_index == 0)
		BoardManager::Forward(new BoardTypeViewer());
	else if (selection_index == 3)
		BoardManager::Logout();
}

void HomeViewer::print()
{
	selection_count = 4; selection_index = 0;

	string width = std::to_string(BoardManager::console_width);
	string title = "Welcome " + BoardManager::current_User->getName();

	cout << CSI "?12h";

	cout << CSI "37;44m";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";
	cout << CSI "2;" << std::to_string(BoardManager::console_width / 2 - title.length() / 2) << "H";
	cout << title;

	cout << CSI "0m";

	cout << CSI "5;" << std::to_string(BoardManager::console_width / 2 - 5) << "H";
	cout << "View Board\n";
	enable_state[0] = true;

	cout << CSI "6;" << std::to_string(BoardManager::console_width / 2 - 5) << "H";
	cout << "View Mail\n";
	enable_state[1] = true;

	cout << CSI "7;" << std::to_string(BoardManager::console_width / 2 - 5) << "H";
	cout << "Admin Page\n";
	enable_state[2] = true;

	cout << CSI "8;" << std::to_string(BoardManager::console_width / 2 - 5) << "H";
	cout << "Logout\n";
	enable_state[3] = true;

	cout << CSI "5;" << std::to_string(BoardManager::console_width / 2 - 6) << "H";
}

void HomeViewer::receive(int key)
{
	// 224 extended value code
	// 72 Key_Up
	// 75 Key_Left
	// 77 Key_Right
	// 80 Key_Down

	if (key == 13)
		enter();

	if (key != 224) return;

	key = _getch();
	if (key == 72)
		move_up();
	else if (key == 80)
		move_down();
	else if (key == 77)
		enter();
}
