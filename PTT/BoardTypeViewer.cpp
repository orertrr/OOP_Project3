#include "BoardTypeViewer.h"
#include "BoardManager.h"

void BoardTypeViewer::move_up()
{
	if (index - 1 < 0)
		return;
	
	index--;
	cout << CSI "1A";
}

void BoardTypeViewer::move_down()
{
	if (index + 1 >= count)
		return;

	index++;
	cout << CSI "1B";
}

void BoardTypeViewer::enter()
{
	BoardManager::Forward(new SelectBoardViewer(typesid[index]));
}

void BoardTypeViewer::print()
{
	index = 0; count = 0;

	string width = std::to_string(BoardManager::console_width);
	string title = "Board Type";

	cout << CSI "?12h";

	cout << CSI "37;44m";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";
	cout << CSI "2;" << std::to_string(BoardManager::console_width / 2 - title.length() / 2) << "H";
	cout << title;

	cout << CSI "5;0H" << CSI "30;47m" << CSI << width << "@" << CSI "5;0H";
	printf("%6s %s\n", "ID", "TypeName");
	cout << CSI "0m";

	typesid.clear();
	BoardTypeController controller;
	for (auto element : controller.GetAll())
	{
		printf("%6d %s\n", element->getTypeID(), element->getName().c_str());
		typesid.push_back(element->getTypeID());
		count++;
	}
	cout << CSI "6;0H";
}

void BoardTypeViewer::receive(int key)
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
