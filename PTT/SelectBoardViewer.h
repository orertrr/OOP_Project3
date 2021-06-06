#pragma once

#include "Viewer.h"
#include "Board.h"
#include "BoardViewer.h"

class SelectBoardViewer : public Viewer
{
private:
	int index;
	int count;

	void move_up();
	void move_down();
	void enter();

	vector<Board*> boards;

public:
	SelectBoardViewer(int Typeid);

	void print();
	void receive(int key);
};