#include "GameTree.h"


ChaosNode::ChaosNode(Game* g,char c,float u,ChanceNode* par)
{
	game = g;
	color = c;
	utility = u;
	parent = par;
}

ChaosNode::ChaosNode(Game* g,char c,float u)
{
	game = g;
	color = c;
	utility = u;
	parent = NULL;
}

Game* ChaosNode::getgame(ChaosNode* a)
{
	return a->game;
}

float ChaosNode::getprobabilty(ChaosNode* a)
{
	return a->probabiltiy;
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


