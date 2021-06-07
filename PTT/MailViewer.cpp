#include "MailViewer.h"
#include "BoardManager.h"

MailViewer::MailViewer(Mail* _mail)
{
	mail = _mail;
}

void MailViewer::print()
{
	string width = std::to_string(BoardManager::console_width);
	cout << CSI "?12h";

	cout << CSI "37;44m";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";

	cout << CSI "0;0H";
	cout << "Title: " + mail->getTitle() << '\n';
	cout << "From: " + mail->getFromAccount() << '\n';
	cout << "To: " + mail->getToAccount() << '\n';

	cout << CSI "0m" << CSI "5;0H";
	cout << mail->getContent();
}

void MailViewer::receive(int key)
{
	if (key != 224) return;

	key = _getch();

	if (key == 75)
		BoardManager::Back();
}
