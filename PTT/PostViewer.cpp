#include "PostViewer.h"
#include "BoardManager.h"

PostViewer::PostViewer(Post* post)
{
	u = UserController().Get(post->getUserAccount());

	p = post;

	for (auto element : BoardManager::comments)
	{
		push = 0;
		pull = 0;

		if (element->getPostID() == post->getPostID())
		{
			comments.push_back(element);
			if (element->getKind() == 1)
				push++;
			else if (element->getKind() == -1)
				pull++;
		}
	}
}

void PostViewer::print()
{
	string width = std::to_string(BoardManager::console_width);
	cout << CSI "?12h";

	cout << CSI "37;44m";
	cout << CSI << width << "@\n";
	cout << CSI << width << "@\n";

	cout << CSI "0;0H";
	cout << "Title: " + p->getTitle() << '\n';
	cout << "Author: " + u->getName() << '\n';

	cout << CSI "0m" << CSI "4;0H";
	cout << p->getContent();

	cout << "\n\n";
	cout << "Comments:\n";

	int index = 0;
	for (auto element : comments)
	{
		if (element->getKind() == 1)
		{
			printf(CSI "32m");
			printf("Push ");
		}
		else if (element->getKind() == 0)
			printf("---> ");
		else
		{
			printf(CSI "31m");
			printf("Pull ");
		}
		printf(CSI "0m");

		printf("%-15s: ", comment_users[index]->getName());
		printf("%s", element->getContent());
	}
}

void PostViewer::receive(int key)
{
	if (key == 3)
		BoardManager::Create_comment(this);

	if (key != 224) return;

	key = _getch();
	if (key == 75)
		BoardManager::Back();
}
