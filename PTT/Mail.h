#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
using namespace std;
#define MAILFileName "MailDB.txt"
#define MAILPREFIX "mail"

class Mail
{
private:
	int MailID;
	string FromAccount, ToAccount, content;
public:
	Mail() : MailID(-1), FromAccount(""), ToAccount(""), content("") {}
	Mail(Mail& om) : MailID(om.MailID), FromAccount(om.FromAccount), ToAccount(om.ToAccount), content(om.content) {}
	Mail(int mid, string fa, string ta, string cont) : MailID(mid), FromAccount(fa), ToAccount(ta), content(cont) {}
	int getMailID() { return this->MailID; }
	string getFromAccount() { return this->FromAccount; }
	string getToAccount() { return this->ToAccount; }
	string getContent() { return this->content; }
	void setMailID(int nmid) { this->MailID = nmid; }
	void setFromAccount(string nfa) { this->FromAccount = nfa; }
	void setToAccount(string nta) { this->ToAccount = nta; }
	void setContent(string ncon) { this->content = ncon; }
};

class MailController
{
private:
	string fileName;
	fstream dataFile, mailFile;
	vector<Mail*> MailList;
public:
	MailController();
	~MailController();
	void Store();
	bool Insert(Mail&);
	bool Update(Mail&);
	bool Delete(Mail&);
	Mail* Get(int);
	vector<Mail*> GetAll() { return this->MailList; };
};