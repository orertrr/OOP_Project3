#include"Mail.h"


MailController::MailController() : fileName(MAILFileName)
{
	dataFile.open(fileName, fstream::in);
	int MailIDTemp;
	string FATemp, TATemp, ContentTemp, ContentTT;

	if (dataFile.is_open())
	{
		while (dataFile >> fileName)
		{
			mailFile.open(fileName, fstream::in);
			if (mailFile.is_open())
			{
				mailFile >> MailIDTemp >> FATemp >> TATemp;
				getline(mailFile, ContentTemp);//¥h±¼\n
				ContentTemp = "";
				while (getline(mailFile, ContentTT, '\n'))
				{
					ContentTemp += ContentTT;
				}
				mailFile.close();
				MailList.push_back(new Mail(MailIDTemp, FATemp, TATemp, ContentTemp));
			}
		}
		dataFile.close();
	}
}
MailController::~MailController()
{
	this->Store();
	/*for (auto& i : MailList)
	{
		delete i;
	}*/
}
void MailController::Store()
{
	fileName = MAILFileName;
	dataFile.open(fileName, fstream::out | fstream::trunc);
	if (dataFile.is_open())
	{
		for (auto& i : this->MailList)
		{
			fileName = MAILPREFIX + to_string(i->getMailID()) + ".txt";
			mailFile.open(fileName, fstream::out | fstream::trunc);
			if (mailFile.is_open())
			{
				mailFile << i->getMailID() << '\n' << i->getFromAccount() << '\n' << i->getToAccount() << '\n' << i->getContent();
				mailFile.close();

				dataFile << fileName << '\n';
			}
		}
		dataFile.close();
	}
}
bool MailController::Insert(Mail& nm)
{
	if (MailList.size() > 0)
		nm.setMailID(MailList.back()->getMailID() + 1);
	else
		nm.setMailID(1);
	MailList.push_back(new Mail(nm));
	return true;
}
bool MailController::Update(Mail& om)
{
	for (auto& i : MailList)
	{
		if (i->getMailID() == om.getMailID())
		{
			i->setFromAccount(om.getFromAccount());
			i->setToAccount(om.getToAccount());
			i->setContent(om.getContent());
			return true;
		}
	}
	return false;
}
bool MailController::Delete(Mail& dm)
{
	for (auto& i : MailList)
	{
		if (i->getMailID() == dm.getMailID())
		{
			fileName = MAILPREFIX + to_string(i->getMailID()) + ".txt";

			remove(fileName.c_str());
			delete i;
			this->MailList.erase(MailList.begin() + (&i - &MailList[0]));
			return true;
		}
	}
	return false;
}
Mail* MailController::Get(int mid)
{
	for (auto& i : MailList)
	{
		if (i->getMailID() == mid)
		{
			return i;
		}
	}
	return nullptr;
}