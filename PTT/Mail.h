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
	string FromAccount, ToAccount, Title, content;
public:
	Mail() : MailID(-1), FromAccount(""), ToAccount(""), Title(""), content("") {}
	Mail(Mail& om) : MailID(om.MailID), FromAccount(om.FromAccount), ToAccount(om.ToAccount), Title(om.Title), content(om.content) {}
	Mail(string fa, string ta, string title, string cont) : FromAccount(fa), ToAccount(ta), Title(title), content(cont) {}
	Mail(int mid, string fa, string ta, string title, string cont) : MailID(mid), FromAccount(fa), ToAccount(ta), Title(title), content(cont) {}
	int getMailID() { return this->MailID; }
	string getFromAccount() { return this->FromAccount; }
	string getToAccount() { return this->ToAccount; }
	string getTitle() { return this->Title; }
	string getContent() { return this->content; }
	void setMailID(int nmid) { this->MailID = nmid; }
	void setFromAccount(string nfa) { this->FromAccount = nfa; }
	void setToAccount(string nta) { this->ToAccount = nta; }
	void setTitle(string nfa) { this->Title = nfa; }
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