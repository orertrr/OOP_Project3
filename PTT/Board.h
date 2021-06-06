#pragma once
#include<vector>
#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
using namespace std;
#define BOARDFileName "BoardDB.txt"
#define BOARDTYPEFileName "BoardTypeDB.txt"


class Board
{
private:
	int BoardID, TypeID;
	string BoardName;
public:
	Board() : BoardID(-1), TypeID(-1), BoardName("") {}
	Board(Board& ob) : BoardID(ob.BoardID), TypeID(ob.TypeID), BoardName(ob.BoardName) {}
	Board(int bid, int tid, string bn) : BoardID(bid), TypeID(tid), BoardName(bn) {}
	int getBoardID() { return this->BoardID; }
	int getTypeID() { return this->TypeID; }
	string getBoardName() { return this->BoardName; }
	Board& self() { return *this; }
	void setBoardID(int nbid) { this->BoardID = nbid; }
	void setTypeID(int ntid) { this->TypeID = ntid; }
	void setBoardName(string nbn) { this->BoardName = nbn; }
};

class BoardController
{
private:
	string fileName;
	fstream dataFile;
	vector<Board*> BoardList;
public:
	BoardController();
	~BoardController();
	void Store();
	bool Insert(Board&);
	bool Update(Board&);
	bool Delete(Board&);
	Board* Get(int);
	vector<Board*> GetAll() { return this->BoardList; }
};

class BoardType
{
private:
	int TypeID;
	string Name;
public:
	BoardType() : TypeID(-1), Name("") {}
	BoardType(BoardType& obt) : TypeID(obt.TypeID), Name(obt.Name) {}
	BoardType(int tid, string n) : TypeID(tid), Name(n) {}
	int getTypeID() { return this->TypeID; }
	string getName() { return this->Name; }
	void setTypeID(int ntid) { this->TypeID = ntid; }
	void setName(string nn) { this->Name = nn; }
};

class BoardTypeController
{
private:
	string fileName;
	fstream dataFile;
	vector<BoardType*> BoardTypeList;
public:
	BoardTypeController();
	~BoardTypeController();
	void Store();
	bool Insert(BoardType&);
	bool Update(BoardType&);
	bool Delete(BoardType&);
	BoardType* Get(int);
	vector<BoardType*> GetAll() { return this->BoardTypeList; }
};