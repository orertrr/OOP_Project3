#pragma once

#include "Viewer.h"
#include "BoardTypeViewer.h"

class HomeViewer : public Viewer
{
private:
	int selection_index;
	int selection_count;
	bool enable_state[4];

	void move_up();
	void move_down();
	void enter();

public:
	void print();
	void receive(int key);
};