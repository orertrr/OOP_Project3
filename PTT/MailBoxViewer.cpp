#include "MailBoxViewer.h"
#include "BoardManager.h"

void MailBoxViewer::move_up()
{
	if (index - 1 < 0) return;

	cout << CSI "1A";
	index--;
}

void MailBoxViewer::move_down()
{
	if (index + 1 >= count) return;

	cout << CSI "1B";
	index++;
}

void MailBoxViewer::enter()
{
	if (!mails.empty())
		BoardManager::Forward(new MailViewer(mails[index]));
}

MailBoxViewer::MailBoxViewer()
{
	index = 0; count = 0;

	for (auto element : BoardManager::mails)
	{
		if (element->getToAccount() == BoardManager::current_User->getAccount() || element->getFromAccount() == BoardManager::current_User->getAccount())
		{
			mails.push_back(element);
		}
	}
}

void MailBoxViewer::print()
{
	string width = std::to_string(BoardManager::console_width);
	string title = BoardManager::current_User->getName() + "'s Mails";

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
	printf("%4s %10s %10s %s\n", "ID", "Form", "To", "Title");
	cout << CSI "0m";

	index = 0; count = mails.size();
	cout << CSI "6;0H";

	for (auto& element : mails)
	{
		printf("%4d %10s %10s %s\n", element->getMailID(), element->getFromAccount().c_str(), element->getToAccount().c_str(), element->getTitle().c_str());
	}
	cout << CSI "6;0H";
}

void MailBoxViewer::receive(int key)
{
	// 224 extended value code
	// 72 Key_Up
	// 75 Key_Left
	// 77 Key_Right
	// 80 Key_Down

	if (key == 3)
		BoardManager::Create_mail();

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