#include"User.h"

UserManager::UserManager() : fileName(UserFileName)
{
	dataFile.open(fileName, fstream::in);
	string Nametemp, AccountTemp, PassWordTemp;
	int levelTemp;
	User* Utemp;
	if (dataFile.is_open())
	{
		while (dataFile >> levelTemp)
		{
			dataFile >> Nametemp >> AccountTemp >> PassWordTemp;
			switch (levelTemp)
			{
			case MEMBER:
				Utemp = new Member(Nametemp, AccountTemp, PassWordTemp);
				UserList.push_back(Utemp);
				break;
			case ADMINISTRATOR:
				Utemp = new Administrator(Nametemp, AccountTemp, PassWordTemp);
				UserList.push_back(Utemp);
				break;
			default:
				break;
			}
		}
		dataFile.close();
	}
}
UserManager::~UserManager()
{
	this->Store();
	for (auto& i : UserList)
	{
		delete i;
	}
}
void UserManager::Store()
{
	dataFile.open(fileName, fstream::out | fstream::trunc);
	if (dataFile.is_open())
	{
		for (auto& i : this->UserList)
		{
			dataFile << i->getPermission_level() << '\n' << i->getName() << '\n' << i->getAccount() << '\n' << i->getPassWorrd() << '\n';
		}
		dataFile.close();
	}
}
bool UserManager::Insert(User& au)
{
	User* Utemp;
	for (auto& i : UserList)
	{
		if (i->getAccount() == au.getAccount())
			return false;
	}
	switch (au.getPermission_level())
	{
	case MEMBER:
		Utemp = new Member(au);
		break;
	case ADMINISTRATOR:
		Utemp = new Administrator(au);
		break;
	default:
		break;
	}
	this->UserList.push_back(Utemp);
	return true;
}
bool UserManager::Update(User& ou)
{
	for (auto& i : UserList)
	{
		if (ou.getAccount() == i->getAccount())
		{
			delete i;
			this->UserList.erase(UserList.begin() + (&i - &UserList[0]));
			switch (ou.getPermission_level())
			{
			case MEMBER:
				UserList.push_back(new Member(ou));
				break;
			case ADMINISTRATOR:
				UserList.push_back(new Administrator(ou));
				break;
			default:
				break;
			}
			return true;
		}
	}
	return false;
}
bool UserManager::Delete(User& du)
{
	for (auto& i : UserList)
	{
		if (du.getAccount() == i->getAccount())
		{
			delete i;
			this->UserList.erase(UserList.begin() + (&i - &UserList[0]));
			return true;
		}
	}
	return false;
}
User* UserManager::Get(string UserAccount)
{
	for (auto& i : UserList)
	{
		if (UserAccount == i->getAccount())
		{
			return i;
		}
	}
	return nullptr;
}


/*
class UserManager
{
	private:
	string fileName;
	vector<User*> UserList;
};
*/