#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
using namespace std;
#define COMMENTFileName "CommentDB.txt"
#define COMMENTPREFIX "comment"


class Comment
{
private:
	int CommentID, PostID, Kind;
	string content, Delete, UserAccount;
	bool beDelete;
public:
	Comment() : CommentID(-1), PostID(-1), Kind(0), UserAccount(""), content(""), Delete(""), beDelete(false) {}
	Comment(Comment& oc) : CommentID(-1), PostID(-1), Kind(0), UserAccount(""), content(""), Delete(""), beDelete(false) {}
	Comment(string cont, string ua, int pid, int ckind) : CommentID(-1), PostID(pid), Kind(ckind), UserAccount(ua), content(cont), Delete(""), beDelete(false) {}
	Comment(string cont, string ua, string dmsg, int pid, int cid, int ckind, bool bd) : CommentID(cid), PostID(pid), Kind(ckind), UserAccount(ua), content(cont), Delete(dmsg), beDelete(bd) {}
	int getCommentID() { return this->CommentID; }
	int getPostID() { return this->PostID; }
	int getKind() { return this->Kind; }
	string getContent() { return this->content; }
	string getDelete() { return this->Delete; }
	string getUserAccount() { return this->UserAccount; }
	bool getBeDelete() { return this->beDelete; }
	void setCommentID(int cid) { this->CommentID = cid; }
	void setPostID(int pid) { this->PostID = pid; }
	void setKind(int kamo) { this->Kind = kamo; }
	void setContent(string cont) { this->content = cont; }
	void setDelete(string delmsg) { this->Delete = delmsg; }
	void setUserAccount(string ua) { this->UserAccount = ua; }
	void setBeDelete(bool bd) { this->beDelete = bd; }
};

class CommentController
{
private:
	string fileName;
	fstream dataFile, commentFile;
	vector<Comment*> CommentList;
public:
	CommentController();
	~CommentController();
	void Store();
	bool Insert(Comment&);
	bool Update(Comment&);
	bool Delete(Comment&);
	Comment* Get(int);
	vector<Comment*> GetAll() { return this->CommentList; }
};