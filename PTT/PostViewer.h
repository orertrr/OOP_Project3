#pragma once

#include "Viewer.h"
#include "Comment.h"
#include "Post.h"
#include "User.h"

class PostViewer : public Viewer
{
	friend class BoardManager;

private:
	int pull;
	int push;
	vector<Comment*> comments;
	vector<User*> comment_users;
	Post* p;
	User* u;

public:
	PostViewer(Post* post);

	void print();
	void receive(int key);
};