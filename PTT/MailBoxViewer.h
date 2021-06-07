#pragma once

#include "Mail.h"
#include "Viewer.h"
#include "MailViewer.h"

class MailBoxViewer : public Viewer
{
private:
	int index;
	int count;
	vector<Mail*> mails;

	void move_up();
	void move_down();
	void enter();

public:
	MailBoxViewer();

	void print();
	void receive(int key);
};