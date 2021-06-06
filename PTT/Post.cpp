#include"Post.h"

PostController::PostController() : fileName(PostListFileName)
{
	dataFile.open(fileName, fstream::in);
	int postIDTemp, boardIDTemp;
	string userAccountTemp, titleTemp, contentTemp, contentTT;

	if (dataFile.is_open())
	{
		while (dataFile >> fileName)
		{
			postFile.open(fileName, fstream::in);
			if (postFile.is_open())
			{
				postFile >> postIDTemp >> boardIDTemp >> userAccountTemp;
				getline(postFile, titleTemp);//去掉\n
				getline(postFile, titleTemp);
				contentTemp = "";
				while (getline(postFile, contentTT, '\n'))
				{
					contentTemp += contentTT;
				}
				postFile.close();
				PostList.push_back(new Post(postIDTemp, boardIDTemp, userAccountTemp, titleTemp, contentTemp));
			}
		}
		dataFile.close();
	}
}
PostController::~PostController()
{
	this->Store();
	/*for (auto& i : PostList)
	{
		delete i;
	}*/
}
void PostController::Store()
{
	fileName = PostListFileName;
	dataFile.open(fileName, fstream::out | fstream::trunc);
	if (dataFile.is_open())
	{
		for (auto& i : this->PostList)
		{
			fileName = "Posts\\" POSTPREFIX + to_string(i->getPostID()) + ".txt";
			postFile.open(fileName, fstream::out | fstream::trunc);
			if (postFile.is_open())
			{
				postFile << i->getPostID() << '\n' << i->getBoardID() << '\n' << i->getUserAccount() << '\n' << i->getTitle() << '\n' << i->getContent();
				postFile.close();

				dataFile << fileName << '\n';
			}
		}
		dataFile.close();
	}
}
bool PostController::Insert(Post& np)
{
	if (PostList.size() > 0)
		np.setPostID(PostList.back()->getPostID() + 1);
	else
		np.setPostID(1);
	PostList.push_back(new Post(np));
	return true;
}
bool PostController::Update(Post& op)
{
	for (auto& i : PostList)
	{
		if (i->getPostID() == op.getPostID())
		{
			i->setBoardID(op.getBoardID());
			i->setUserAccount(op.getUserAccount());
			i->setTitle(op.getTitle());
			i->setContent(op.getContent());
			return true;
		}
	}
	return false;
}
bool PostController::Delete(Post& op)
{
	for (auto& i : PostList)
	{
		if (i->getPostID() == op.getPostID())
		{
			fileName = POSTPREFIX + to_string(i->getPostID()) + ".txt";

			remove(fileName.c_str());
			delete i;
			this->PostList.erase(PostList.begin() + (&i - &PostList[0]));
			return true;
		}
	}
	return false;
}
Post* PostController::Get(int pid)
{
	for (auto& i : PostList)
	{
		if (i->getPostID() == pid)
		{
			return i;
		}
	}
	return nullptr;
}