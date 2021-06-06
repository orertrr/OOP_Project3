#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
using namespace std;
#define PostListFileName "PostDB.txt"
#define POSTPREFIX "post"

class Post
{
private:
	int postID, boardID;
	string userAccount, title, content;
public:
	Post() : postID(-1), boardID(-1), userAccount(""), title(""), content("") {}
	Post(Post& op) : postID(op.getPostID()), boardID(op.getBoardID()), userAccount(op.getUserAccount()), title(op.getTitle()), content(op.getContent()) {}
	Post(int bid, string ua, string tit, string cont) : postID(-1), boardID(bid), userAccount(ua), title(tit), content(cont) {}
	Post(int pid, int bid, string ua, string tit, string cont) : postID(pid), boardID(bid), userAccount(ua), title(tit), content(cont) {}
	int getPostID() { return this->postID; }
	int getBoardID() { return this->boardID; }
	string getUserAccount() { return this->userAccount; }
	string getTitle() { return this->title; }
	string getContent() { return this->content; }
	void setPostID(int npid) { this->postID = npid; }
	void setBoardID(int nbid) { this->boardID = nbid; }
	void setUserAccount(string nua) { this->userAccount = nua; }
	void setTitle(string nt) { this->title = nt; }
	void setContent(string ncon) { this->content = ncon; }
};

class PostController
{
private:
	string fileName;
	fstream dataFile, postFile;
	vector<Post*> PostList;
public:
	PostController();
	~PostController();
	void Store();
	bool Insert(Post&);
	bool Update(Post&);
	bool Delete(Post&);
	Post* Get(int);
	vector<Post*> GetAll() { return this->PostList; }
};