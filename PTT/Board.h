#pragma once

#include <fstream>
#include <vector>
#include "Post.h"
#include "BoardType.h"

using std::fstream;
using std::string;
using std::vector;

class Board
{
private:
	int BoardID;
	string BoardName;
	vector<Post*> Posts;
	BoardType* Type;
};