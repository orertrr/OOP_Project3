#pragma once

#include "Viewer.h"
#include "Board.h"
#include "Post.h"

class BoardViewer : public Viewer
{
private:
	int index;
	int count;
	string title;

	void move_up();
	void move_down();
	void enter();

	vector<Post*> posts;

public:
	BoardViewer(Board* board);

	void print();
	void receive(int key);
};