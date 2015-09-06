#include <iostream>
#include "Game.h"

class ChaosNode;
class OrderNode;
class ChanceNode;

class ChaosNode
{
public:
	ChaosNode(Game*,char,float);
	ChaosNode(Game*,char,float,ChanceNode*);
	Game* getgame(ChaosNode*);
	float getprobabiltiy(ChaosNode*);
	ChanceNode* getparent(ChaosNode*);
	std::vector<OrderNode*> getchildren(ChaosNode*);	//	to complete

private:
	Game* game;
	char color;
	float probability;
	ChanceNode* parent;
};

class OrderNode
{
public:
	//OrderNode();
	OrderNode(Game*,float,ChaosNode*);
	Game* getgame(OrderNode*);
	std::vector<ChanceNode*> getchildren(OrderNode*);		// to complete
	ChaosNode* getparent(OrderNode*);
private:
	Game* game;
	ChaosNode* parent;
	float utility;
};

class ChanceNode
{
public:
	ChanceNode();
	ChanceNode(Game*,float);
	Game* getgame();
	std::vector<ChaosNode*> getchildren(ChanceNode*);		// to complete
	OrderNode* getparent(ChanceNode*);	
private:
	Game* game;
	float utility;
	OrderNode* parent;
	//int* colorbag;			// contains no. of tiles present of each color
};

std::pair<int,int> getbestmoveChaos(Game*,char);
std::pair<std::pair<int,int>,std::pair<int,int> > getbestmoveOrder(Game*);
