#pragma once

class Viewer
{
public:
	virtual void print() = 0;
	virtual void receive(char key) = 0;
};