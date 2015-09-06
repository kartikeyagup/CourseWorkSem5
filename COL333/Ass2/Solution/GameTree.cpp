#include "GameTree.h"


ChaosNode::ChaosNode(Game* g,char c,float p,ChanceNode* par)
{
	game = g;
	color = c;
	probability = p;
	parent = par;
}

ChaosNode::ChaosNode(Game* g,char c,float p)
{
	game = g;
	color = c;
	probability = p;
	parent = NULL;
}

Game* ChaosNode::getgame(ChaosNode* a)
{
	return a->game;
}

float ChaosNode::getprobability(ChaosNode* a)
{
	return a->probability;
}

ChanceNode* ChaosNode::getparent(ChaosNode* a)
{
	return a->parent;
}


OrderNode::OrderNode(Game* g,float u,ChaosNode* par)
{
	game = g;
	parent = par;
	utility = u;
}


Game* OrderNode::getgame(OrderNode* a)
{
	return a->game;
}

ChaosNode* OrderNode::getparent(OrderNode* a)
{
	return a->parent;
}

ChanceNode::ChanceNode(Game* g, float u, OrderNode* par)
{
	game = g;
	utility = u;
	parent = par;
}

Game* ChanceNode::getgame(ChanceNode* a)
{
	return a->game;
}

OrderNode* ChanceNode::getparent(ChanceNode* a)
{
	return a->parent;
}

