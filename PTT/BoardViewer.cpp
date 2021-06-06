#include "BoardViewer.h"
#include "BoardManager.h"

void BoardViewer::move_up()
{
	if (index - 1 < 0) return;

	cout << CSI "1A";
	index--;
}

void BoardViewer::move_down()
{
	if (index + 1 >= count) return;

	cout << CSI "1B";
	index++;
}

void BoardViewer::enter()
{
	BoardManager::Forward(new PostViewer(posts[index]));
}

BoardViewer::BoardViewer(Board* board)
{
	title = board->getBoardName();
	index = 0; count = 0;
	posts.clear();

	for (auto element : BoardManager::posts)
	{
		if (element->getBoardID() == board->getBoardID())
			posts.push_back(element);
	}
}

void BoardViewer::print()
{
	string width = std::to_string(BoardManager::console_width);

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
	printf("%6s %s\n", "ID", "Title");
	cout << CSI "0m";

	index = 0; count = posts.size();
	cout << CSI "6;0H";

	for (auto& element : posts)
	{
		printf("%6d %s\n", element->getPostID(), element->getTitle().c_str());
	}
	cout << CSI "6;0H";
}

void BoardViewer::receive(int key)
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
