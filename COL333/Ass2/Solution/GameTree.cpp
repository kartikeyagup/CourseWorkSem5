#include "GameTree.h"


ChaosNode::ChaosNode(Game* g,char c,float p,ChanceNode* par)
{
	game = g;
	color = c;
	probability = p;
	parent = par;
}

ChaosNode::~ChaosNode()
{
	delete game;
	delete parent;
}

ChaosNode::ChaosNode(Game* g,char c,float p)
{
	game = g;
	color = c;
	probability = p;
	parent = NULL;
}

Game* ChaosNode::getgame()
{
	return game;
}

float ChaosNode::getprobability()
{
	return probability;
}

char ChaosNode::getcolor()
{
	return color;
}

ChanceNode* ChaosNode::getparent()
{
	return parent;
}

std::vector<OrderNode*> ChaosNode::getchildren()
{
	std::vector<OrderNode*> child_chaos;
	for(int i=0;i<this->getgame()->GetDimension();i++)
	{
		for(int j=0;j<this->getgame()->GetDimension();j++)
		{
			if(this->getgame()->GetValidMoveInsert(getcolor(),i,j))
			{
				Game* dup_game = GetDuplicate(this->getgame());
				dup_game->AddNew(this->getcolor(),i,j);
				int score = this->getgame()->GetNewScoreInsert(this->getcolor(),i,j);
				OrderNode* child = new OrderNode(dup_game,score,this);
				child_chaos.push_back(child);
				delete dup_game;
				delete child;
			}
		}
	}
	return child_chaos;
}

OrderNode::OrderNode(Game* g,float u,ChaosNode* par)
{
	game = g;
	parent = par;
	utility = u;
}

OrderNode::~OrderNode()
{
	delete game;
	delete parent;
}

Game* OrderNode::getgame()
{
	return game;
}

ChaosNode* OrderNode::getparent()
{
	return parent;
}

std::vector<ChanceNode*> OrderNode::getchildren()
{
	std::vector<ChanceNode*> v;
	for(int i=0;i<this->getgame()->GetDimension();i++)
	{
		for(int j=0;j<this->getgame()->GetDimension();j++)
		{
			for(int k=0;k<this->getgame()->GetDimension();k++)
			{
				for(int l=0;l<this->getgame()->GetDimension();l++)
				{
					if(i!=k || j!=l)
					{
						if(this->getgame()->GetValidMoveShift(i,j,k,l))
						{
							Game* dup_game = GetDuplicate(this->getgame());
							dup_game->Move(i,j,k,l);
							int score = this->getgame()->GetNewScoreMove(i,j,k,l);
							ChanceNode* child = new ChanceNode(dup_game,score,this);
							v.push_back(child);
							delete dup_game;
							delete child;
						}
					}
				}
			}
		}
	}
	return v;
}

ChanceNode::ChanceNode(Game* g, float u, OrderNode* par)
{
	game = g;
	utility = u;
	parent = par;
}

ChanceNode::~ChanceNode()
{
	delete game;
	delete parent;
}

Game* ChanceNode::getgame()
{
	return game;
}

OrderNode* ChanceNode::getparent()
{
	return parent;
}

std::vector<ChaosNode*> ChanceNode::getchildren()
{
	std::vector<ChaosNode*> v;
	for(int i=0;i<this->getgame()->GetDimension();i++)
	{
		ChaosNode* child = new ChaosNode(this->getgame(),i+'A',(this->getgame()->GetProbabilities())[i],this);
		v.push_back(child);
		delete child;
	}
	return v;
}

