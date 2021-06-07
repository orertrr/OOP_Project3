#pragma once

#include "Viewer.h"
#include "Mail.h"

class MailViewer : public Viewer
{
	friend class BoardManager;

private:
	int pull;
	int push;

	Mail* mail;

public:
	MailViewer(Mail* mail);

	void print();
	void receive(int key);
};