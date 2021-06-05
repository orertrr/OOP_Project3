#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
using namespace std;
#define ADMINISTRATOR 3
#define MEMBER 2
#define GUEST 1
#define UserFileName "UserDB.txt"


class User
{
private:
	string name, account, passWord;
	int Permission_level;
public:
	User() : name("Guest"), account("Guest"), passWord("Guest"), Permission_level(0) {}
	User(User& ou) : name(ou.name), account(ou.account), passWord(ou.passWord), Permission_level(ou.Permission_level) {}
	User(string UserName, string UserAccount, string UserPassWord, int UserLevel) : name(UserName), account(UserAccount), passWord(UserPassWord), Permission_level(UserLevel) {}
	User& self() { return *this; }
	bool isAdministrator() { return this->Permission_level == ADMINISTRATOR ? true : false; }
	bool isMember() { return this->Permission_level >= MEMBER ? true : false; }
	const string& getName() { return this->name; }
	const string& getAccount() { return this->account; }
	const string& getPassWorrd() { return this->passWord; }
	const int getPermission_level() { return this->Permission_level; }
	void setName(string s) { this->name = s; }
	void setAccount(string s) { this->account = s; }
	void setPassWord(string s) { this->passWord = s; }
	void setPermission_level(int pl) { this->Permission_level = pl; }
};

class Administrator : public User
{
private:
public:
	Administrator() : User("admin", "admin", "admin", ADMINISTRATOR) {}
	Administrator(User& oa) : User(oa) {}
	Administrator(Administrator& oa) : User(oa.self()) {}
	Administrator(string UserName, string UserAccount, string UserPassWord) : User(UserName, UserAccount, UserPassWord, ADMINISTRATOR) {}

};

class Member : public User
{
private:
public:
	Member() : User("member", "member", "member", MEMBER) {}
	Member(User& om) : User(om) {}
	Member(Member& om) : User(om.self()) {}
	Member(string UserName, string UserAccount, string UserPassWord) : User(UserName, UserAccount, UserPassWord, MEMBER) {}

};

class Guest : public User
{
private:
public:
	Guest() : User("member", "member", "member", GUEST) {}
	Guest(Guest& og) : User(og.self()) {}
	Guest(string UserName, string UserAccount, string UserPassWord) : User(UserName, UserAccount, UserPassWord, GUEST) {}

};

class UserManager
{
private:
	string fileName;
	fstream dataFile;
	vector<User*> UserList;
public:
	UserManager();
	~UserManager();
	void Store();
	bool Insert(User&);
	bool Update(User&);
	bool Delete(User&);
	User* Get(string);
	vector<User*> GetAll() { return this->UserList; }
};