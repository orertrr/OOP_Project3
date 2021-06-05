#pragma once

#include <iostream>
#include <Windows.h>
#include "Viewer.h"

using std::cin;
using std::cout;

class LoginViewer : public Viewer
{
public:
	void print();
	void receive(char key) {};
};