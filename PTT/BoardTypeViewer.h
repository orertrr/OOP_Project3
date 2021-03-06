#pragma once

#include "Viewer.h"
#include "Board.h"
#include "SelectBoardViewer.h"

class BoardTypeViewer : public Viewer
{
private:
	int index;
	int count;

	void move_up();
	void move_down();
	void enter();

	vector<int> typesid;

public:
	void print();
	void receive(int key);
};