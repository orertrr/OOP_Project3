#include "SelectBoardViewer.h"
#include "BoardManager.h"

void SelectBoardViewer::move_up()
{
	if (index - 1 < 0) return;

	cout << CSI "1A";
	index--;
}

void SelectBoardViewer::move_down()
{
	if (index + 1 >= count) return;

	cout << CSI "1B";
	index++;
}

void SelectBoardViewer::enter()
{
	BoardManager::Forward(new BoardViewer(boards[index]));
}

SelectBoardViewer::SelectBoardViewer(int Typeid)
{
	index = 0; count = 0;

	BoardController controller;
	auto table = controller.GetAll();

	for (auto element : table)
	{
		if (element->getTypeID() == Typeid)
			boards.push_back(element);
	}
}

void SelectBoardViewer::print()
{
	string width = std::to_string(BoardManager::console_width);
	string title = "Select Board";

	cout << CSI "?12h";

	cout << CSI "37;44m";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";
	cout << CSI "2;" << std::to_string(BoardManager::console_width / 2 - title.length() / 2) << "H";
	cout << title;

	cout << CSI "5;0H";
	cout << CSI "30;48;2;224;224;224m";
	cout << CSI << width << "@\n";
	cout << CSI "5;0H";
	printf("%6s %s\n", "ID", "BoardName");
	cout << CSI "0m";

	index = 0; count = boards.size();
	cout << CSI "6;0H";

	for (auto& element : boards)
	{
		printf("%6d %s\n", element->getBoardID(), element->getBoardName().c_str());
	}
	cout << CSI "6;0H";
}

void SelectBoardViewer::receive(int key)
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
	else if (key == 75)
		BoardManager::Back();
}
