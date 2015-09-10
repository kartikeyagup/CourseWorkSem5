#include <iostream>
#include <vector>
#include "Game.h"

class ChaosNode;
class OrderNode;
class ChanceNode;

class ChaosNode
{
public:
	ChaosNode(Game*,char,float,float);
	~ChaosNode();
	ChaosNode(Game*,char,float,float,ChanceNode*);
	Game* getgame();
	float getprobability();
	float getutility();
	ChanceNode* getparent();
	std::vector<OrderNode*> getchildren();	//	to complete
	char getcolor();
	void setutility(float);
	bool children_visited;
	float alpha;
	float beta;
	// bool hasinferred;

private:
	Game* game;
	char color;
	float probability;
	float utility;
	ChanceNode* parent;
};

class OrderNode
{
public:
	//OrderNode();
	OrderNode(Game*,float,ChaosNode*);
	OrderNode(Game*,float);
	~OrderNode();
	Game* getgame();
	std::vector<ChanceNode*> getchildren();		// to complete
	ChaosNode* getparent();
	float getutility();
	void setutility(float);
	bool children_visited;
	float alpha;
	float beta;
	// bool hasinferred;

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
	float getutility();
	void setutility(float);
	bool children_visited;	
	float alpha;
	float beta;
	// bool hasinferred;
	
private:
	Game* game;
	float utility;
	OrderNode* parent;
	//int* colorbag;			// contains no. of tiles present of each color
};

std::pair<int,int> getbestmoveChaos(Game*,char);
std::pair<std::pair<int,int>,std::pair<int,int> > getbestmoveOrder(Game*);
