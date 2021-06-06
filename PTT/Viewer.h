#pragma once

class Viewer
{
public:
	~Viewer();

	virtual void print() = 0;
	virtual void receive(int key) = 0;
};