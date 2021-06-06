#include"Comment.h"


CommentController::CommentController()
{
	dataFile.open(fileName, fstream::in);
	int CIDTemp, PIDTemp, KindTemp;
	string UATemp, DMSGTemp, contentTemp, contentTT;
	bool BDTemp;

	if (dataFile.is_open())
	{
		while (dataFile >> fileName)
		{
			commentFile.open(fileName, fstream::in);
			if (commentFile.is_open())
			{
				commentFile >> CIDTemp >> PIDTemp >> KindTemp >> BDTemp >> UATemp;
				getline(commentFile, DMSGTemp);//¥h±¼\n
				getline(commentFile, DMSGTemp);
				contentTemp = "";
				while (getline(commentFile, contentTT, '\n'))
				{
					contentTemp += contentTT;
				}
				commentFile.close();
				CommentList.push_back(new Comment(contentTemp, UATemp, DMSGTemp, PIDTemp, CIDTemp, KindTemp, BDTemp));
			}
		}
		dataFile.close();
	}
}
CommentController::~CommentController()
{
	this->Store();
	/*for (auto& i : CommentList)
	{
		delete i;
	}*/
}
void CommentController::Store()
{
	fileName = COMMENTFileName;
	dataFile.open(fileName, fstream::out | fstream::trunc);
	if (dataFile.is_open())
	{
		for (auto& i : this->CommentList)
		{
			fileName = COMMENTPREFIX + to_string(i->getCommentID()) + ".txt";
			commentFile.open(fileName, fstream::out | fstream::trunc);
			if (commentFile.is_open())
			{
				commentFile << i->getCommentID() << '\n' << i->getPostID() << '\n' << i->getKind() << '\n' << i->getBeDelete() << '\n' << i->getUserAccount() << '\n' << i->getDelete() << '\n' << i->getContent();
				commentFile.close();

				dataFile << fileName << '\n';
			}
		}
		dataFile.close();
	}
}
bool CommentController::Insert(Comment& nc)
{
	nc.setCommentID(CommentList.back()->getCommentID() + 1);
	CommentList.push_back(new Comment(nc));
	return true;
}
bool CommentController::Update(Comment& oc)
{
	for (auto& i : CommentList)
	{
		if (i->getCommentID() == oc.getCommentID())
		{
			i->setBeDelete(oc.getBeDelete());
			i->setCommentID(oc.getCommentID());
			i->setContent(oc.getContent());
			i->setDelete(oc.getDelete());
			i->setKind(oc.getKind());
			i->setPostID(oc.getPostID());
			i->setUserAccount(oc.getUserAccount());
			return true;
		}
	}
	return false;
}
bool CommentController::Delete(Comment& oc)
{
	for (auto& i : CommentList)
	{
		if (i->getCommentID() == oc.getCommentID())
		{
			fileName = COMMENTPREFIX + to_string(i->getCommentID()) + ".txt";

			remove(fileName.c_str());
			delete i;
			this->CommentList.erase(CommentList.begin() + (&i - &CommentList[0]));
			return true;
		}
	}
	return false;
}
Comment* CommentController::Get(int cid)
{
	for (auto& i : CommentList)
	{
		if (i->getCommentID() == cid)
		{
			return i;
		}
	}
	return nullptr;
}