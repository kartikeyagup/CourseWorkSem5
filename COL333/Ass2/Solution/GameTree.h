#include <iostream>
#include <vector>
#include "Game.h"

class ChaosNode;
class OrderNode;
class ChanceNode;

class ChaosNode
{
public:
	ChaosNode(Game*,char,float);
	~ChaosNode();
	ChaosNode(Game*,char,float,ChanceNode*);
	Game* getgame();
	float getprobability();
	ChanceNode* getparent();
	std::vector<OrderNode*> getchildren();	//	to complete
	char getcolor();

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
	~OrderNode();
	Game* getgame();
	std::vector<ChanceNode*> getchildren();		// to complete
	ChaosNode* getparent();
private:
	Game* game;
	ChaosNode* parent;
	float utility;
};

class ChanceNode
{
public:
	ChanceNode(Game*,float,OrderNode*);
	~ChanceNode();
	Game* getgame();
	std::vector<ChaosNode*> getchildren();		// to complete
	OrderNode* getparent();	
private:
	Game* game;
	float utility;
	OrderNode* parent;
	//int* colorbag;			// contains no. of tiles present of each color
};

std::pair<int,int> getbestmoveChaos(Game*,char);
std::pair<std::pair<int,int>,std::pair<int,int> > getbestmoveOrder(Game*);
