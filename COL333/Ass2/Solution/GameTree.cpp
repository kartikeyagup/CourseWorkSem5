#include "GameTree.h"
#include <stack>


ChaosNode::ChaosNode(Game* g,char c,float p,float u,ChanceNode* par)
{
	game = g;
	color = c;
	probability = p;
	utility = u;
	parent = par;
	children_visited = 0;
}

ChaosNode::~ChaosNode()
{
	delete game;
	delete parent;
}

ChaosNode::ChaosNode(Game* g,char c,float p,float u)
{
	game = g;
	color = c;
	probability = p;
	utility = u;
	parent = NULL;
	children_visited = 0;
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

float ChaosNode::getutility()
{
	return utility;
}

void ChaosNode::setutility(float a)
{
	utility = a;
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
	children_visited = 0;
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

float OrderNode::getutility()
{
	return utility;
}

void OrderNode::setutility(float a)
{
	utility = a;
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
	children_visited = 0;
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

float ChanceNode::getutility()
{
	return utility;
}

void ChanceNode::setutility(float a)
{
	utility = a;
}

std::vector<ChaosNode*> ChanceNode::getchildren()
{
	std::vector<ChaosNode*> v;
	for(int i=0;i<this->getgame()->GetDimension();i++)
	{
		ChaosNode* child = new ChaosNode(this->getgame(),i+'A',(this->getgame()->GetProbabilities())[i],this->getgame()->GetPresentScore(),this);
		v.push_back(child);
		delete child;
	}
	return v;
}

std::pair<int,int> getbestmoveChaos(Game* a,char b)
{

	// depth d;
	int d = 5;
	ChaosNode* node_chaos = new ChaosNode(a,b,a->GetProbabilities()[b-'A'],0);
	std::stack<std::pair<OrderNode*,int> > order_stack;
	std::stack<std::pair<ChaosNode*,int> > chaos_stack;
	std::stack<std::pair<ChanceNode*,int> > chance_stack;
	
	// push children of chaos node into the stack
	std::vector<OrderNode*> v = node_chaos->getchildren();
	chaos_stack.push(std::make_pair(node_chaos,0));
	for(int i=0;i<v.size();i++)
	{
		order_stack.push(std::make_pair(v[i],1));		
	}

	// make boolean of chaos node to be true
	node_chaos->children_visited = 1;

	// push children of the first order node into the stack chance

	std::vector<ChanceNode*> a_v = v[0]->getchildren();
	for(int i=0;i<a_v.size();i++)
	{
		chance_stack.push(std::make_pair(a_v[i],2));

	}

	// make boolean of node v[0] to be true
	v[0]->children_visited = 0;



	while(!order_stack.empty() || !chaos_stack.empty() || !chance_stack.empty())
	{
		int depth_chaos = chaos_stack.top().second;
		int depth_order = order_stack.top().second;
		int depth_chance = chance_stack.top().second;

		int max = depth_chaos;
		if(depth_order>max)
		{
			max = depth_order;
		}
		if(depth_chance>max)
		{
			max = depth_chance;
		}
		if(max == depth_chaos)
		{
			// do operation in the chaos stack
			if(depth_chaos == d)
			{
				// then pop from the chaos stack
				ChaosNode* n_chaos = chaos_stack.top().first;
				chaos_stack.pop();
				// look at its parent and change the utility accordingly
				n_chaos -> getparent() -> setutility (n_chaos->getutility() * n_chaos->getprobability() + n_chaos->getparent()->getutility());
			}
			else
			{

				// if the boolean is 0 then do a top and push the children into the order stack
				if(chaos_stack.top().first->children_visited == 0)
				{
					std::vector<OrderNode*> v_children = chaos_stack.top().first->getchildren();
					for(int i=0;i<v_children.size();i++)
					{
						order_stack.push(std::make_pair(v_children[i],depth_chaos+1));
					}
					// make boolean of chaos_stack.top as 1
					chaos_stack.top().first->children_visited =1;
				}
				else
				{
					ChaosNode* n_chaos = chaos_stack.top().first;
					chaos_stack.pop();
					n_chaos -> getparent() -> setutility (n_chaos->getutility() * n_chaos->getprobability() + n_chaos->getparent()->getutility());
				}

			}
		}
		else if(max == depth_chance)
		{
			if(depth_chance == d)
			{
				ChanceNode* n_chance = chance_stack.top().first;
				chance_stack.pop();
				if(n_chance->getutility()>n_chance->getparent()->getutility())
				{
					n_chance->getparent()->setutility(n_chance->getutility());
				}
			}
			else
			{
				if(chance_stack.top().first->children_visited ==0)
				{
					std::vector<ChaosNode*> v_children = chance_stack.top().first->getchildren();
					for(int i=0;i<v_children.size();i++)
					{
						chaos_stack.push(std::make_pair(v_children[i],depth_chance+1));
					}
					chance_stack.top().first->children_visited = 1;
				}
				else
				{
					ChanceNode* n_chance = chance_stack.top().first;
					chance_stack.pop();
					if(n_chance->getutility()>n_chance->getparent()->getutility())
					{
						n_chance->getparent()->setutility(n_chance->getutility());
					}
				}
			}
		}
		else
		{
			if(depth_order == d)
			{
				OrderNode* n_order = order_stack.top().first;
				order_stack.pop();
				if(n_order->getutility()<n_order->getparent()->getutility())
				{
					n_order->getparent()->setutility(n_order->getutility());
				}
			}
			else
			{
				if( order_stack.top().first->children_visited==0)
				{
					std::vector<ChanceNode*> v_children = order_stack.top().first->getchildren();
					for(int i=0;i<v_children.size();i++)
					{
						chance_stack.push(std::make_pair(v_children[i],depth_order+1));
					}
					order_stack.top().first->children_visited = 1;
				}
				else
				{
					OrderNode* n_order = order_stack.top().first;
					order_stack.pop();
					if(n_order->getutility()<n_order->getparent()->getutility())
					{
						n_order->getparent()->setutility(n_order->getutility());
					}
				}
			}
		}
	}

}