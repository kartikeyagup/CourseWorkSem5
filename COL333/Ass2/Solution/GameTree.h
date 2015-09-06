#include <iostream>
#include "Game.h"

class ChaosNode
{
public:
	ChaosNode();
	Game* getgame(ChaosNode*);
	float getprobabiltiy(ChaosNode*);
	ChanceNode* getparent(ChaosNode*);

private:
	Game* game;
	char color;
	float probability;
	ChanceNode* parent;
	std::vector<OrderNode*> children;
};

class OrderNode
{
public:
	Game* getgame();
	std::vector<ChanceNode*> getchildren(OrderNode*);
	ChaosNode* getparent(OrderNode*);
private:
	Game* game;
	std::vector<ChanceNode*> children;
	ChaosNode* parent;
	float utility;
};

class ChanceNode
{
public:
	Game* getgame();
	std::vector<ChaosNode*> getchildren(ChanceNode*);
	OrderNode* getparent(ChanceNode*);
private:
	Game* game;
	float utility;
	std::vector<ChaosNode*> children;
	OrderNode* parent;
	//int* colorbag;			// contains no. of tiles present of each color
};

std::pair<int,int> getbestmoveChaos(Game*,char);
std::pair<std::pair<int,int>,std::pair<int,int> > getbestmoveOrder(Game*);
