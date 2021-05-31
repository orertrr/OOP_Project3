#pragma once

#include <fstream>
#include "User.h"

using std::string;
using std::fstream;

class Mail
{
private:
	int MailID;
	User* FromID;
	User* ToID;
	string Content;
};