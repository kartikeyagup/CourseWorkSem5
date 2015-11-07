#include "GameTree.h"
#include <stack>
#define CHAOS_DEFAULT 10000.0
#define ORDER_DEFAULT -10000.0


ChaosNode::ChaosNode(char c,float p,float u,ChanceNode* par,float sc)
{
	score = sc;
	color = c;
	probability = p;
	utility = u;
	parent = par;
	children_visited = 0;
	alpha = ORDER_DEFAULT;
	beta = CHAOS_DEFAULT;
	//hasinferred = 0;
}

ChaosNode::~ChaosNode()
{
}

ChaosNode::ChaosNode(char c,float p,float u,float sc)
{
	score = sc;
	color = c;
	probability = p;
	utility = u;
	parent = NULL;
	children_visited = 0;
	alpha = ORDER_DEFAULT;
	beta = CHAOS_DEFAULT;
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

bool Chaos_child (OrderNode* i,OrderNode* j) { return (i->score > j->score); }
bool Order_child (ChanceNode* i,ChanceNode* j) { return (i->score < j->score);}

void ChaosNode::getchildren(std::vector<OrderNode*> &child_chaos)
{
	// std::vector<OrderNode*> child_chaos;
	for(int i=0;i<GlobalGame.GetDimension();i++)
	{
		for(int j=0;j<GlobalGame.GetDimension();j++)
		{
			if(GlobalGame.GetValidMoveInsert(this->getcolor(),i,j))
			{
				ChaosMove* cmove = new ChaosMove();
				cmove->posx = i;
				cmove->posy = j;
				cmove->color= this->getcolor();
				float score = GlobalGame.MoveAndUndoChaos(cmove);
				OrderNode* child = new OrderNode(ORDER_DEFAULT,this,score,cmove);
				child_chaos.push_back(child);
				// delete dup_game;
				// delete child;
			}
		}
	}
	std::sort (child_chaos.begin(), child_chaos.end(), Chaos_child);
	// return child_chaos;
}

OrderNode::OrderNode(float u,ChaosNode* par,float sc,ChaosMove* a)
{
	score = sc;
	move = a;
	parent = par;
	utility = u;
	children_visited = 0;
	alpha = ORDER_DEFAULT;
	beta = CHAOS_DEFAULT;
	//hasinferred = 0;
}

OrderNode::OrderNode(float u,float sc)
{
	score = sc;
	move = NULL;
	parent = NULL;
	utility = u;
	children_visited = 0;
	alpha = ORDER_DEFAULT;
	beta = CHAOS_DEFAULT;
	//hasinferred = 0;
}
OrderNode::~OrderNode()
{
	delete move;
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

void OrderNode::getchildren(std::vector<ChanceNode*> &v1)
{
	// std::cerr << "Starting get children of order\n";
	// std::vector<ChanceNode*> v;
	// std::vector<ChanceNode*> v1;
	if(this->getparent()!=NULL)
	{
		GlobalGame.MoveChaos(this->move);
	}
	bool dupdone=false;
	// std::cerr << "Starting get children of order\n";
	// for(int i=0;i<GlobalGame.GetDimension();i++)
	// {
	// 	for(int j=0;j<GlobalGame.GetDimension();j++)
	// 	{
	// 		if (!GlobalGame.GetValidMoveInsert('A',i,j))
	// 		{
	// 			// for (int k=i; k<GlobalGame.GetDimension(); k++)
	// 			// {
	// 			// 	if (GlobalGame.GetValidMoveInsert('A',k,j))
	// 			// 	{
	// 			// 		OrderMove* omove = new OrderMove();
	// 			// 		omove->initx = i;
	// 			// 		omove->inity = j;
	// 			// 		omove->finx = k;
	// 			// 		omove->finy = j;
	// 			// 		float score = GlobalGame.MoveAndUndoOrder(omove);
	// 			// 		if (i==k)
	// 			// 		{
	// 			// 			if (!dupdone)
	// 			// 			{
	// 			// 				dupdone=true;
	// 			// 				ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 			// 				v.push_back(child);
	// 			// 			}
	// 			// 		}
	// 			// 		else
	// 			// 		{
	// 			// 			ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 			// 			v.push_back(child);	
	// 			// 		}	
	// 			// 	}
	// 			// 	else
	// 			// 	{
	// 			// 		break;
	// 			// 	}
	// 			// }
	// 			// for (int k=i-1; k>=0; k--)
	// 			// {
	// 			// 	if (GlobalGame.GetValidMoveInsert('A',k,j))
	// 			// 	{
	// 			// 		OrderMove* omove = new OrderMove();
	// 			// 		omove->initx = i;
	// 			// 		omove->inity = j;
	// 			// 		omove->finx = k;
	// 			// 		omove->finy = j;
	// 			// 		float score = GlobalGame.MoveAndUndoOrder(omove);
	// 			// 		if (i==k)
	// 			// 		{
	// 			// 			if (!dupdone)
	// 			// 			{
	// 			// 				dupdone=true;
	// 			// 				ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 			// 				v.push_back(child);
	// 			// 			}
	// 			// 		}
	// 			// 		else
	// 			// 		{
	// 			// 			ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 			// 			v.push_back(child);	
	// 			// 		}	
	// 			// 	}
	// 			// 	else
	// 			// 	{
	// 			// 		break;
	// 			// 	}
	// 			// }

	// 			for (int k=0; k<GlobalGame.GetDimension(); k++)
	// 			{
	// 				for (int l=0; l<GlobalGame.GetDimension(); l++)
	// 				{
	// 				if(GlobalGame.GetValidMoveShift(i,j,k,l))
	// 				{
	// 					// std::cerr << "Adding ronak " << i <<"\t" << j <<"\t" <<k <<"\t" <<l<<"\n";
	// 					OrderMove* omove = new OrderMove();
	// 					omove->initx = i;
	// 					omove->inity = j;
	// 					omove->finx = k;
	// 					omove->finy = l;
	// 					float score = GlobalGame.MoveAndUndoOrder(omove);
	// 					if ((i==k) && (j==l))
	// 					{
	// 						if (!dupdone)
	// 						{
	// 							dupdone=true;
	// 							ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 							v.push_back(child);
	// 						}
	// 					}
	// 					else
	// 					{
	// 						ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 						v.push_back(child);	
	// 					}
	// 				}}}					
				

	// 			// for (int k=j+1; k<GlobalGame.GetDimension(); k++)
	// 			// {
	// 			// 	if(GlobalGame.GetValidMoveInsert('A',i,k))
	// 			// 	{
	// 			// 		OrderMove* omove = new OrderMove();
	// 			// 		omove->initx = i;
	// 			// 		omove->inity = j;
	// 			// 		omove->finx = i;
	// 			// 		omove->finy = k;
	// 			// 		float score = GlobalGame.MoveAndUndoOrder(omove);
	// 			// 		ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 			// 		v.push_back(child);	
	// 			// 	}
	// 			// 	else
	// 			// 	{
	// 			// 		break;
	// 			// 	}					
	// 			// }
	// 			// for (int k=j-1; k>=0; k--)
	// 			// {
	// 			// 	if(GlobalGame.GetValidMoveInsert('A',i,k))
	// 			// 	{
	// 			// 		OrderMove* omove = new OrderMove();
	// 			// 		omove->initx = i;
	// 			// 		omove->inity = j;
	// 			// 		omove->finx = i;
	// 			// 		omove->finy = k;
	// 			// 		float score = GlobalGame.MoveAndUndoOrder(omove);
	// 			// 		ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 			// 		v.push_back(child);	
	// 			// 	}
	// 			// 	else
	// 			// 	{
	// 			// 		break;
	// 			// 	}					
	// 			// }


	// 			// for(int k=0;k<GlobalGame.GetDimension();k++)
	// 			// {
	// 			// 	// TODO: Replace by separate for order
	// 			// 	for(int l=0;l<GlobalGame.GetDimension();l++)
	// 			// 	{
	// 			// 		if(GlobalGame.GetValidMoveShift(i,j,k,l))
	// 			// 		{
	// 			// 			OrderMove* omove = new OrderMove();
	// 			// 			omove->initx = i;
	// 			// 			omove->inity = j;
	// 			// 			omove->finx = k;
	// 			// 			omove->finy = l;
	// 			// 			float score = GlobalGame.MoveAndUndoOrder(omove);
	// 			// 			if (i==k && j==l)
	// 			// 			{
	// 			// 				if (!dupdone)
	// 			// 				{
	// 			// 					dupdone=true;
	// 			// 					ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 			// 					v.push_back(child);
	// 			// 				}
	// 			// 			}
	// 			// 			else
	// 			// 			{
	// 			// 				ChanceNode* child = new ChanceNode(0,this,score,omove);
	// 			// 				v.push_back(child);	
	// 			// 			}
	// 			// 		}
	// 			// 	}
	// 			// }
	// 		}
	// 	}
	// }
	dupdone=false;
	
	for(int i=0;i<GlobalGame.GetDimension();i++)
	{
		for(int j=0;j<GlobalGame.GetDimension();j++)
		{
			if (!GlobalGame.GetValidMoveInsert('A',i,j))
			{
				if (!dupdone)
				{
					OrderMove* omove = new OrderMove();
					omove->initx = i;
					omove->inity = j;
					omove->finx = i;
					omove->finy = j;
					float score = GlobalGame.MoveAndUndoOrder(omove);
				
					dupdone=true;
					ChanceNode* child = new ChanceNode(0,this,score,omove);
					v1.push_back(child);
				}		
				for (int k=i+1; k<GlobalGame.GetDimension(); k++)
				{
					if (GlobalGame.GetValidMoveInsert('A',k,j))
					{
						// std::cerr << "KG1 " << i <<"\t" << j <<"\t" << k <<"\t" << j <<"\n";
						OrderMove* omove = new OrderMove();
						omove->initx = i;
						omove->inity = j;
						omove->finx = k;
						omove->finy = j;
						float score = GlobalGame.MoveAndUndoOrder(omove);
						ChanceNode* child = new ChanceNode(0,this,score,omove);
						v1.push_back(child);	
					}
					else
					{
						break;
					}
				}
				for (int k=i-1; k>=0; k--)
				{
					if (GlobalGame.GetValidMoveInsert('A',k,j))
					{
						// std::cerr << "KG2 " << i <<"\t" << j <<"\t" << k <<"\t" << j <<"\n";
						OrderMove* omove = new OrderMove();
						omove->initx = i;
						omove->inity = j;
						omove->finx = k;
						omove->finy = j;
						float score = GlobalGame.MoveAndUndoOrder(omove);
						if (i==k)
						{
							if (!dupdone)
							{
								dupdone=true;
								ChanceNode* child = new ChanceNode(0,this,score,omove);
								v1.push_back(child);
							}
						}
						else
						{
							ChanceNode* child = new ChanceNode(0,this,score,omove);
							v1.push_back(child);	
						}	
					}
					else
					{
						break;
					}
				}

				for (int k=j+1; k<GlobalGame.GetDimension(); k++)
				{
					if(GlobalGame.GetValidMoveInsert('A',i,k))
					{
						// std::cerr << "KG3 " << i <<"\t" << j <<"\t" << i <<"\t" << k <<"\n";
						OrderMove* omove = new OrderMove();
						omove->initx = i;
						omove->inity = j;
						omove->finx = i;
						omove->finy = k;
						float score = GlobalGame.MoveAndUndoOrder(omove);
						ChanceNode* child = new ChanceNode(0,this,score,omove);
						v1.push_back(child);	
					}
					else
					{
						break;
					}					
				}
				for (int k=j-1; k>=0; k--)
				{
					if(GlobalGame.GetValidMoveInsert('A',i,k))
					{
						// std::cerr << "KG4 " << i <<"\t" << j <<"\t" << i <<"\t" << k <<"\n";
						OrderMove* omove = new OrderMove();
						omove->initx = i;
						omove->inity = j;
						omove->finx = i;
						omove->finy = k;
						float score = GlobalGame.MoveAndUndoOrder(omove);
						ChanceNode* child = new ChanceNode(0,this,score,omove);
						v1.push_back(child);	
					}
					else
					{
						break;
					}					
				}
			}
		}
	}
	std::sort(v1.begin(),v1.end(),Order_child);
	// return v1;
}

ChanceNode::ChanceNode(float u, OrderNode* par,float sc,OrderMove* a)
{
	score = sc;
	move = a;
	utility = u;
	parent = par;
	children_visited = 0;
	//hasinferred = 0;
	alpha = ORDER_DEFAULT;
	beta = CHAOS_DEFAULT;
}

ChanceNode::~ChanceNode()
{
	delete move;
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

void ChanceNode::getchildren(std::vector<ChaosNode*> &v)
{
	float score = GlobalGame.MoveOrder(this->move);
	for(int i=0;i<GlobalGame.GetDimension();i++)
	{
		if(GlobalGame.GetProbabilities()[i]>0.0001)
		{
			ChaosNode* child = new ChaosNode(i+'A',(GlobalGame.GetProbabilities())[i],CHAOS_DEFAULT,this,score);
			v.push_back(child);
		}
		// delete child;
	}
	// return v;
}

int count_no_chaos_moves = 0;

std::pair<int,int> getbestmoveChaos(char b)
{
	count_no_chaos_moves ++;
	int d=7;
	if (GlobalGame.GetDimension()==6)
	{
		d=6;
		if (count_no_chaos_moves>17)
		{
			d=7;
		}
		if (count_no_chaos_moves>=23)
		{
			d=9;
		}
		d = std::min(d,(GlobalGame.GetDimension() * GlobalGame.GetDimension() - GlobalGame.GetNumCompleted())*2) ;
	}
	else if(GlobalGame.GetDimension()==7)
	{
		// TODO: 6 throughout
		d = std::min(6,(GlobalGame.GetDimension() * GlobalGame.GetDimension() - GlobalGame.GetNumCompleted())*2) ;
	}
	else
	{
		if(count_no_chaos_moves>=13)
		{
			// depth d;
			d = 8;
		}
		d = std::min(d,(GlobalGame.GetDimension()*GlobalGame.GetDimension() - GlobalGame.GetNumCompleted())*2) ;
	}
	std::cerr << "GOING TILL DEPTH " << d<<"\n";	
	//float init_util = 10000.0;
	ChaosNode* node_chaos = new ChaosNode(b,1.0,CHAOS_DEFAULT,0);

	// initial value of the state to be backed up
	float initvalue;
	// if(constantweights == "0")
	// {
		initvalue = GlobalGame.GetPresentScore();
	// }

	std::stack<std::pair<OrderNode*,int> > order_stack;
	std::stack<std::pair<ChaosNode*,int> > chaos_stack;
	std::stack<std::pair<ChanceNode*,int> > chance_stack;
	
	chaos_stack.push(std::make_pair(node_chaos,0));

	float min_utility = 100000.0;			// minimum utility of the chaos node
	OrderNode* c=NULL;
	std::vector<OrderNode*> Level1Order;	// to finally delete level 1 order nodes

	int depth_order;
	int depth_chaos;
	int depth_chance;
	// std::cerr << "Initialised the stacks for depth of "<< d << " \n";
	// std::cerr << "Elements in Order, chaos, chance: "<< order_stack.size() << "\t" << chaos_stack.size() << "\t" << chance_stack.size() <<"\n";
	while(!order_stack.empty() || !chaos_stack.empty() || !chance_stack.empty())
	{
		// break;
		// std::cerr << "Elements in Order, chaos, chance: "<< order_stack.size() << "\t" << chaos_stack.size() << "\t" << chance_stack.size() <<"\n";
		if(order_stack.empty())
		{	
			depth_order = -1;
		}
		else
		{
			depth_order = order_stack.top().second;
			
		}
		if(chaos_stack.empty())
		{
			depth_chaos=-1;
		}
		else
		{
			depth_chaos = chaos_stack.top().second;
		}
		if(chance_stack.empty())
		{
			depth_chance = -1;
		}
		else
		{
			depth_chance = chance_stack.top().second;
		}

		// find which stack has maximum depth
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
			ChaosNode* n_chaos = chaos_stack.top().first;
			// do operation in the chaos stack
			// std::cerr << "in chaos node\n";
			if(depth_chaos == d)
			{
				chaos_stack.pop();
				if(chaos_stack.empty()==true || chaos_stack.top().second != depth_chaos)
				{
					GlobalGame.UndoMoveOrder(n_chaos->getparent()->move);
				}
				n_chaos -> getparent() -> setutility (n_chaos->score * n_chaos->getprobability() + n_chaos->getparent()->getutility());
				delete n_chaos;
			}
			else
			{
				if(chaos_stack.top().first->children_visited == 0)
				{
					if (n_chaos->getparent()!=NULL)
					{
						n_chaos -> alpha = n_chaos -> getparent() -> alpha;
						n_chaos -> beta  = n_chaos -> getparent() -> beta;
					}

					std::vector<OrderNode*> v_children;
					chaos_stack.top().first->getchildren(v_children);
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
					// std::cerr << "Removing node from chaos\n";
					if(n_chaos->getparent()!=NULL)
					{
						if(chaos_stack.empty()==true || chaos_stack.top().second != depth_chaos)
						{
							GlobalGame.UndoMoveOrder(n_chaos->getparent()->move);
						}
						n_chaos -> getparent() -> setutility (n_chaos->getutility() * n_chaos->getprobability() + n_chaos->getparent()->getutility());
					}
					if(depth_chaos!=0)
					{
						delete n_chaos;
					}
				}

			}
		}
		else if(max == depth_chance)
		{
			ChanceNode* n_chance = chance_stack.top().first;				
			if(depth_chance == d)
			{
				chance_stack.pop();

				if(n_chance->getparent()->alpha >= n_chance->getparent()->beta)
				{
					GlobalGame.UndoMoveChaos(n_chance->getparent()->move);
					while(!chance_stack.empty() && chance_stack.top().second==depth_chance)
					{
						ChanceNode* prune = chance_stack.top().first;
						chance_stack.pop();
						delete prune;
					}
					// start pruning
					// remove elements from chance_stack till depth is equal to
				}
				else
				{
					if(chance_stack.empty()==true || chance_stack.top().second !=depth_chance)
					{
						GlobalGame.UndoMoveChaos(n_chance->getparent()->move);
					}

					n_chance->getparent()->alpha = std::max(n_chance->getparent()->alpha,n_chance->score);

					// std::cerr << "Removing node from chance at d\n";
					if(n_chance->score > n_chance->getparent()->getutility())
					{
						n_chance->getparent()->setutility(n_chance->score);

					}
					delete n_chance;
				}
			}
			else
			{
				if(chance_stack.top().first->children_visited ==0)
				{
					n_chance -> alpha = n_chance -> getparent() -> alpha;
					n_chance -> beta  = n_chance -> getparent() -> beta;
					
					std::vector<ChaosNode*> v_children;
					chance_stack.top().first->getchildren(v_children);
					if(v_children.size()>0)
					{
						for(int i=0;i<v_children.size();i++)
						{
							// v_children[i]->getgame()->ShowPresent();
							chaos_stack.push(std::make_pair(v_children[i],depth_chance+1));
						}
						chance_stack.top().first->children_visited = 1;
					}
				}
				else
				{
					ChanceNode* n_chance = chance_stack.top().first;
					chance_stack.pop();

					if(n_chance->getparent()->alpha >= n_chance->getparent()->beta)
					{
						GlobalGame.UndoMoveChaos(n_chance->getparent()->move);
						while(!chance_stack.empty() && chance_stack.top().second == depth_chance)
						{
							ChanceNode* prune = chance_stack.top().first;
							chance_stack.pop();
							delete prune;
						}
						// start pruning
						// remove elements from chance_stack till depth is equal to
					}
					else
					{
						if(chance_stack.empty()==true || chance_stack.top().second !=depth_chance)
						{
							GlobalGame.UndoMoveChaos(n_chance->getparent()->move);
						}
						n_chance->getparent()->alpha = std::max(n_chance->getparent()->alpha,n_chance->getutility());

						// std::cerr << "Removing node from chance at d\n";
						if(n_chance->getutility()>n_chance->getparent()->getutility())
						{
							n_chance->getparent()->setutility(n_chance->getutility());

						}
						delete n_chance;
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

				// std::cerr << "Removing node from order at d\n";
				// if(n_order -> getparent() -> hasinferred == 0)
				// {
				// 	if(n_order->getparent()->getparent()!=NULL)
				// 	{
				// 		n_order -> getparent() -> alpha = n_order -> getparent() -> getparent() -> alpha;
				// 		n_order -> getparent() -> beta = n_order -> getparent() -> getparent() -> beta;
				// 	}
				// 	n_order->getparent()->hasinferred = 1;
				// }

				if(n_order->getparent()->alpha>= n_order->getparent()->beta)
				{
					while(!order_stack.empty() && order_stack.top().second == depth_order)
					{
						OrderNode* prune = order_stack.top().first;
						order_stack.pop();
						delete prune;
					}
					// start pruning
					// remove elements from order stack till depth is depth_order
				}
				else
				{					
					n_order->getparent()->beta = std::min(n_order->getparent()->beta,n_order->score);

					if(n_order->score < n_order->getparent()->getutility())
					{
						n_order->getparent()->setutility(n_order->score);
						if(depth_order == 1)
						{
							c = n_order;
						}
					}
					// std::cerr<<"Deleting order node: "<<depth_order<<"\n";
					if(depth_order==1)
					{
						Level1Order.push_back(n_order);
					}
					else
					{
						delete n_order;
					}
				}
			}
			else
			{
				if( order_stack.top().first->children_visited==0)
				{
					OrderNode* n_order = order_stack.top().first;
					n_order -> alpha = n_order -> getparent() -> alpha;
					n_order -> beta  = n_order -> getparent() -> beta;
					
					std::vector<ChanceNode*> v_children;
					order_stack.top().first->getchildren(v_children);
					if(v_children.size()>1)
					{
						for(int i=0;i<v_children.size();i++)
						{
							chance_stack.push(std::make_pair(v_children[i],depth_order+1));
						}

					}
					order_stack.top().first->children_visited = 1;
				}
				else
				{
					if(order_stack.top().second == 1)
					{
						OrderNode* n_order = order_stack.top().first;
						order_stack.pop();
						
						Level1Order.push_back(n_order);
						// std::cerr << "Removing node from order\n";

						if(n_order->getparent()->alpha>= n_order->getparent()->beta)
						{
							c= n_order;
							while(!order_stack.empty() && order_stack.top().second == depth_order)
							{
								OrderNode* prune = order_stack.top().first;
								order_stack.pop();
								delete prune;
							}
							// start pruning
							// remove elements from order stack till depth is depth_order
						}
						else
						{
							n_order->getparent()->beta = std::min(n_order->getparent()->beta,n_order->getutility());

							if(n_order->getutility()<n_order->getparent()->getutility())
							{
								c = n_order;
								n_order->getparent()->setutility(n_order->getutility());
							}
							// std::cerr<<"Deleting order node: "<<depth_order<<"\n";			
						}	
					}
					else 
					{
						OrderNode* n_order = order_stack.top().first;
						order_stack.pop();
						
						if(n_order->getparent()->alpha>=n_order->getparent()->beta)
						{
							
							while(!order_stack.empty() && order_stack.top().second == depth_order)
							{
								OrderNode* prune = order_stack.top().first;
								order_stack.pop();
								delete prune;
							}
							// start pruning
							// remove elements from order stack till depth is depth_order
						}
						else
						{
							n_order->getparent()->beta = std::min(n_order->getparent()->beta,n_order->getutility());

							if(n_order->getutility()<n_order->getparent()->getutility())
							{
								n_order->getparent()->setutility(n_order->getutility());
							}
							// std::cerr<<"Deleting order node: "<<depth_order<<"\n";
							delete n_order;
						}					

					}
				}
			}
		}
	}


	float finvalue = c->getparent()->getutility();
	std::cerr << "Final value is: " << finvalue <<"\t" << initvalue <<"\n";
	// final backed up value
	if(constantweights == "0")
	{
		if (GlobalGame.GetNumCompleted()<toggleHeuristic)
		{
			// updating the weights for the heuristics
			// std::cerr << "Final value is: " << finvalue <<"\t" << initvalue <<"\n";
			float contr1 = GlobalGame.CalculateScoreH1();
			float contr2 = GlobalGame.CalculateScoreH2();
			std::cerr << contr1 <<"\t" << contr2 <<" are the contrs\n";
			std::cerr << initvalue <<"\t" <<finvalue <<" are the init and final values\n";
			w1_chaos = w1_chaos + learningrate_chaos*(finvalue - initvalue)*(contr1)/(contr1+contr2);
			w2_chaos = w2_chaos + learningrate_chaos*(finvalue - initvalue)*(contr2)/(contr1+contr2);
			float tot = w1_chaos + w2_chaos;
			w1_chaos /= tot;
			w2_chaos /=tot;
			if (w1_chaos<0)
			{
				w1_chaos=0.0;
				w2_chaos=1.0;
			}
			if (w2_chaos<0.0)
			{
				w2_chaos=0.0;
				w1_chaos=1.0;
			}
		}
	}

	std::pair<int,int> ans = std::make_pair(c->move->posx,c->move->posy);

	for(std::vector<OrderNode*>::iterator it = Level1Order.begin();it!=Level1Order.end();++it)
	{
		delete *it;
	}
	// delete node_chaos;
	return ans;
}

int count_no_order_moves=0;
std::pair<std::pair<int,int>,std::pair<int,int> > getbestmoveOrder()
{
	count_no_order_moves++;
	// int d = 7;
	int d=7;
	if (GlobalGame.GetDimension()==6)
	{
		//TODO: Keep depth 5 and 6
		d=5;
		// if (count_no_order_moves>20)
		// {
		// 	d=6;
		// }
		if (count_no_order_moves>20)
		{
			d=7;
		}
		d = std::min(d,(GlobalGame.GetDimension() * GlobalGame.GetDimension() - GlobalGame.GetNumCompleted())*2) ;
	}
	else if(GlobalGame.GetDimension()==7)
	{
		// TODO: Greater than 24 : 6 and Greater than 39: 7
		d=5;
		if (count_no_order_moves>24)
		{
			d=6;
		}
		if (count_no_order_moves>39)
		{
			d=7;
		}
		d = std::min(d,(GlobalGame.GetDimension() * GlobalGame.GetDimension() - GlobalGame.GetNumCompleted())*2) ;	
	}
	else
	{
		d=6;
		if(count_no_order_moves>12)
		{
			d = 7;
		}
		d = std::min(d,(GlobalGame.GetDimension() * GlobalGame.GetDimension() - GlobalGame.GetNumCompleted())*2) ;
	}
	std::cerr << "GOING TILL DEPTH " << d<<"\n";
	float initvalue;
	if(constantweights == "0")
	{
		initvalue = GlobalGame.GetPresentScore();
	}
	
	//int d = 6;  // cut-off depth;

	OrderNode* node_order = new OrderNode(ORDER_DEFAULT,0);
	//ChaosNode* node_chaos = new ChaosNode(a,b,1.0,init_util);
	std::stack<std::pair<OrderNode*,int> > order_stack;
	std::stack<std::pair<ChaosNode*,int> > chaos_stack;
	std::stack<std::pair<ChanceNode*,int> > chance_stack;
	
	// push children of chaos node into the stack
	order_stack.push(std::make_pair(node_order,0));

	float max_utility = ORDER_DEFAULT;			// minimum utility of the chaos node
	ChanceNode* c=NULL;
	std::vector<ChanceNode*> Level1Chance;


	int depth_order;
	int depth_chaos;
	int depth_chance;
	// std::cerr << "Initialised the stacks\n";
	// std::cerr << "Elements in Order, chaos, chance: "<< order_stack.size() << "\t" << chaos_stack.size() << "\t" << chance_stack.size() <<"\n";
	
	while(!order_stack.empty() || !chaos_stack.empty() || !chance_stack.empty())
	{
		if(order_stack.empty())
		{
			depth_order = -1;
		}
		else
		{
			depth_order = order_stack.top().second;	
		}
		
		if(chaos_stack.empty())
		{
			depth_chaos=-1;
		}
		else
		{
			depth_chaos = chaos_stack.top().second;
		}

		if(chance_stack.empty())
		{
			depth_chance = -1;
		}
		else
		{
			depth_chance = chance_stack.top().second;
		}

		// find which stack has maximum depth
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
				if(chaos_stack.empty()==true || chaos_stack.top().second != depth_chaos)
				{
					GlobalGame.UndoMoveOrder(n_chaos->getparent()->move);
				}
				// look at its parent and change the utility accordingly
				n_chaos -> getparent() -> setutility (n_chaos->score * n_chaos->getprobability() + n_chaos->getparent()->getutility());
				delete n_chaos;
			}
			else
			{

				// if the boolean is 0 then do a top and push the children into the order stack
				if(chaos_stack.top().first->children_visited == 0)
				{
					chaos_stack.top().first->alpha = chaos_stack.top().first->getparent()->alpha;
					chaos_stack.top().first->beta = chaos_stack.top().first->getparent()->beta;
					std::vector<OrderNode*> v_children;
					chaos_stack.top().first->getchildren(v_children);
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
					if(n_chaos->getparent()!=NULL)
					{
						if(chaos_stack.empty()==true || chaos_stack.top().second != depth_chaos)
						{
							GlobalGame.UndoMoveOrder(n_chaos->getparent()->move);
						}
						n_chaos -> getparent() -> setutility (n_chaos->getutility() * n_chaos->getprobability() + n_chaos->getparent()->getutility());
					}
					delete n_chaos;
				}

			}
		}
		else if(max == depth_chance)
		{
			if(depth_chance == d)
			{
				ChanceNode* n_chance = chance_stack.top().first;
				chance_stack.pop();
				if(n_chance->getparent()->alpha >= n_chance->getparent()->beta)
				{
					GlobalGame.UndoMoveChaos(n_chance->getparent()->move);
					while(!chance_stack.empty() && chance_stack.top().second == depth_chance)
					{
						ChanceNode* prune = chance_stack.top().first;
						chance_stack.pop();
						delete prune;
					}
				}
				else
				{
					// chance_stack.pop();
					if(chance_stack.empty()==true || chance_stack.top().second !=depth_chance)
					{
						GlobalGame.UndoMoveChaos(n_chance->getparent()->move);
					}
	

					n_chance->getparent()->alpha = std::max(n_chance->score,n_chance->getparent()->alpha);
					if(n_chance->getutility()>n_chance->getparent()->getutility())
					{
						n_chance->getparent()->setutility(n_chance->score);
						if(depth_chance == 1)
						{
							c = n_chance;
						}
					}
					if(depth_chance==1)
					{
						Level1Chance.push_back(n_chance);
					}
					else
					{
						delete n_chance;
					}
				}
				
			}
			else
			{
				if(chance_stack.top().first->children_visited ==0)
				{
					chance_stack.top().first->alpha = chance_stack.top().first->getparent()->alpha;
					chance_stack.top().first->beta = chance_stack.top().first->getparent()->beta;
					std::vector<ChaosNode*> v_children;
					chance_stack.top().first->getchildren(v_children);
					if(v_children.size()>0)
					{
						for(int i=0;i<v_children.size();i++)
						{
							chaos_stack.push(std::make_pair(v_children[i],depth_chance+1));
						}
						chance_stack.top().first->children_visited = 1;	
					}
				}
				else
				{
					ChanceNode* n_chance = chance_stack.top().first;
					// chance_stack.pop();
					if(n_chance->getparent()->alpha >= n_chance->getparent()->beta)
					{
						if (depth_chance!=1)
						{
							GlobalGame.UndoMoveChaos(n_chance->getparent()->move);
						}
						while(!chance_stack.empty() && chance_stack.top().second == depth_chance)
						{
							ChanceNode* prune = chance_stack.top().first;
							chance_stack.pop();
							delete prune;
						}
					}
					else
					{


						n_chance->getparent()->alpha = std::max(n_chance->getutility(),n_chance->getparent()->alpha);
						if(chance_stack.top().second==1)
						{
							// std::cerr << chance_stack.top().first->getutility() <<"\n";
							

							if (chance_stack.top().first->getutility()<=0)
							{
								chance_stack.top().first->setutility(chance_stack.top().first->score);
							}

							if(max_utility<chance_stack.top().first->getutility())
							{
								c = chance_stack.top().first;
								max_utility = chance_stack.top().first->getutility();
							}
							// chance_stack.top().first->getgame()->ShowPresent();

							// if(chance_stack.top().first->getutility()>chance_stack.top().first->getparent()->getutility())
							// {
							// 	c = chance_stack.top().first;
							// 	chance_stack.top().first->getparent()->setutility(chance_stack.top().first->getutility());
							// }
							// if (c==NULL)
							// {
							// 	c = chance_stack.top().first;		
							// }
							chance_stack.pop();
							Level1Chance.push_back(n_chance);
							// std::cerr<<"Pushing into the vector:"<<Level1Chance.size()<<"\n";
							if(n_chance->getutility()>n_chance->getparent()->getutility())
							{
								n_chance->getparent()->setutility(n_chance->getutility());
							}
						}
						else
						{
							ChanceNode* n_chance = chance_stack.top().first;
							chance_stack.pop();
							if(chance_stack.empty()==true || chance_stack.top().second !=depth_chance)
							{
								GlobalGame.UndoMoveChaos(n_chance->getparent()->move);
							}
							if(n_chance->getutility()>n_chance->getparent()->getutility())
							{
								n_chance->getparent()->setutility(n_chance->getutility());
							}
							delete n_chance;						
						}
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
				if(n_order->getparent()->alpha>=n_order->getparent()->beta)
				{
					while(!order_stack.empty() && order_stack.top().second == depth_order)
					{
						OrderNode* prune = order_stack.top().first;
						order_stack.pop();
						delete prune;
					}
				}
				else
				{
					n_order->getparent()->beta = std::min(n_order->getparent()->beta,n_order->score);
					// order_stack.pop();
					if(n_order->getutility()<n_order->getparent()->getutility())
					{
						n_order->getparent()->setutility(n_order->score);
					}
					delete n_order;
				}
			}
			else
			{
				if( order_stack.top().first->children_visited==0)
				{
					if(order_stack.top().first->getparent()!=NULL)
					{
						order_stack.top().first->alpha = order_stack.top().first->getparent()->alpha;
						order_stack.top().first->beta = order_stack.top().first->getparent()->beta;
					}
					std::vector<ChanceNode*> v_children;
					order_stack.top().first->getchildren(v_children);
					if(v_children.size()>1)
					{
						for(int i=0;i<v_children.size();i++)
						{
							chance_stack.push(std::make_pair(v_children[i],depth_order+1));
						}
					}

					order_stack.top().first->children_visited = 1;
				}
				else
				{

					OrderNode* n_order = order_stack.top().first;
					order_stack.pop();
					if(n_order->getparent()!=NULL)
					{

						if(n_order->getparent()->alpha>=n_order->getparent()->beta)
						{
							while(!order_stack.empty() && order_stack.top().second == depth_order)
							{
								OrderNode* prune = order_stack.top().first;
								order_stack.pop();
								delete prune;
							}
						}
						else
						{
							
							n_order->getparent()->beta = std::min(n_order->getparent()->beta,n_order->getutility());
							// order_stack.pop();
							if(n_order->getutility()<n_order->getparent()->getutility())
							{
								n_order->getparent()->setutility(n_order->getutility());
							}
						}
					}

					if(depth_order!=0)
					{
						delete n_order;
					}
				}
			}
		}
	}

	if(constantweights == "0")
	{
		if (GlobalGame.GetNumCompleted()<toggleHeuristic)
		{
			float finvalue = c->getparent()->getutility();
			std::cerr << "Value is changinf from " << initvalue <<"\t" << finvalue <<"\n";
			// updating the weights for the heuristics
			float contr1 = GlobalGame.CalculateScoreH1();
			float contr2 = GlobalGame.CalculateScoreH2();
			std::cerr << contr1 <<"\t" << contr2 <<" are the contrs\n";
			w1_order = w1_order + learningrate_order*(finvalue - initvalue)*contr1/(contr1+contr2);
			w2_order = w2_order + learningrate_order*(finvalue - initvalue)*contr2/(contr1+contr2);
			float tot = w1_order + w2_order;
			w1_order /= tot;
			w2_order /=tot;
			if (w1_order<0)
			{
				w1_order=0;
				w2_order=1;
			}
			if (w2_order<0)
			{
				w2_order=0;
				w1_order=1.0;
			}
		}
	}
	// std::cerr << "done with computations, now taking difference\t" << Level1Chance.size() <<"\t" << max_utility <<"\n" ;
	// a->ShowPresent();
	// c->getgame()->ShowPresent();
	auto ans = std::make_pair(std::make_pair(c->move->initx,c->move->inity),std::make_pair(c->move->finx,c->move->finy));
	// std::cerr << "done with difference now deleting\n";
	for(std::vector<ChanceNode*>::iterator it = Level1Chance.begin();it!= Level1Chance.end();++it)
	{
		delete *it;
	}
	// std::cerr << "done with deleting\n";
	return (ans);
}
