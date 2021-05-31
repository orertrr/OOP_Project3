#pragma once

#include <fstream>
#include "User.h"

using std::fstream;
using std::string;

enum CommentType
{
	Push, Pull, None
};

class Comment
{
private:
	int CommentID;
	User* PostID;
	User* UserID;
	string Content;
	CommentType Type;
	string Delete;
};