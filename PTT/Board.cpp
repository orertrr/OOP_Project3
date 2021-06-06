#include"Board.h"

BoardController::BoardController() : fileName(BOARDFileName)
{
	dataFile.open(fileName, fstream::in);
	int BoardIDTemp, TypeIDTemp;
	string BoardNameTemp;
	if (dataFile.is_open())
	{
		while (dataFile >> BoardIDTemp >> TypeIDTemp)
		{
			getline(dataFile, BoardNameTemp);
			getline(dataFile, BoardNameTemp);
			BoardList.push_back(new Board(BoardIDTemp, TypeIDTemp, BoardNameTemp));
		}
		dataFile.close();
	}
}
BoardController::~BoardController()
{
	this->Store();
	/*for (auto& i : BoardList)
	{
		delete i;
	}*/
}
void BoardController::Store()
{
	dataFile.open(fileName, fstream::out | fstream::trunc);
	if (dataFile.is_open())
	{
		for (auto& i : this->BoardList)
		{
			dataFile << i->getBoardID() << '\n' << i->getTypeID() << '\n' << i->getBoardName() << '\n';
		}
		dataFile.close();
	}
}
bool BoardController::Insert(Board& nb)
{
	for (auto& i : BoardList)
	{
		if (i->getBoardID() == nb.getBoardID())
		{
			return false;
		}
	}
	this->BoardList.push_back(new Board(nb));
	return true;
}
bool BoardController::Update(Board& ob)
{
	for (auto& i : BoardList)
	{
		if (i->getBoardID() == ob.getBoardID())
		{
			i->setTypeID(ob.getTypeID());
			i->setBoardName(ob.getBoardName());
			return true;
		}
	}
	return false;
}
bool BoardController::Delete(Board& db)
{
	for (auto& i : BoardList)
	{
		if (i->getBoardID() == db.getBoardID())
		{
			delete i;
			this->BoardList.erase(BoardList.begin() + (&i - &BoardList[0]));
			return true;
		}
	}
	return false;
}
Board* BoardController::Get(int bid)
{
	for (auto& i : BoardList)
	{
		if (i->getBoardID() == bid)
		{
			return i;
		}
	}
	return nullptr;
}

BoardTypeController::BoardTypeController() : fileName(BOARDTYPEFileName)
{
	dataFile.open(fileName, fstream::in);
	int TypeIDTemp;
	string NameTemp;
	if (dataFile.is_open())
	{
		while (dataFile >> TypeIDTemp)
		{
			getline(dataFile, NameTemp);
			getline(dataFile, NameTemp);
			BoardTypeList.push_back(new BoardType(TypeIDTemp, NameTemp));
		}
		dataFile.close();
	}
}

BoardTypeController::~BoardTypeController()
{
	this->Store();
	/*for (auto& i : BoardTypeList)
	{
		delete i;
	}*/
}
void BoardTypeController::Store()
{
	dataFile.open(fileName, fstream::out | fstream::trunc);
	if (dataFile.is_open())
	{
		for (auto& i : this->BoardTypeList)
		{
			dataFile << i->getTypeID() << '\n' << i->getName() << '\n';
		}
		dataFile.close();
	}
}
bool BoardTypeController::Insert(BoardType& nbt)
{
	for (auto& i : BoardTypeList)
	{
		if (i->getTypeID() == nbt.getTypeID())
		{
			return false;
		}
	}
	this->BoardTypeList.push_back(new BoardType(nbt));
	return true;
}
bool BoardTypeController::Update(BoardType& obt)
{
	for (auto& i : BoardTypeList)
	{
		if (i->getTypeID() == obt.getTypeID())
		{
			i->setName(obt.getName());
			return true;
		}
	}
	return false;
}
bool BoardTypeController::Delete(BoardType& dbt)
{
	for (auto& i : BoardTypeList)
	{
		if (i->getTypeID() == dbt.getTypeID())
		{
			delete i;
			this->BoardTypeList.erase(BoardTypeList.begin() + (&i - &BoardTypeList[0]));
			return true;
		}
	}
	return false;
}
BoardType* BoardTypeController::Get(int tid)
{
	for (auto& i : BoardTypeList)
	{
		if (i->getTypeID() == tid)
		{
			return i;
		}
	}
	return nullptr;
}
