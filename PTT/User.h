#pragma once

#include <fstream>
#include <vector>
#include "Post.h"

using std::string;
using std::vector;

class User
{
private:
	int UserID;
	string Account;
	string Passowrd;
	vector<Post*> Posts;

public:
	
};