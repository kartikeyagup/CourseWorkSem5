#include <iostream>
#include <vector>
#include "Game.h"

class ChaosNode;
class OrderNode;
class ChanceNode;

extern Game GlobalGame;

class ChaosNode
{
public:
	ChaosNode(char,float,float,float);
	~ChaosNode();
	ChaosNode(char,float,float,ChanceNode*,float);
	float getprobability();
	float getutility();
	float score;
	ChanceNode* getparent();
	std::vector<OrderNode*> getchildren();	//	to complete
	char getcolor();
	void setutility(float);
	bool children_visited;
	float alpha;
	float beta;
	// bool hasinferred;

private:
	char color;
	float probability;
	float utility;
	ChanceNode* parent;
};

class OrderNode
{
public:
	//OrderNode();
	OrderNode(float,ChaosNode*,float,ChaosMove*);
	OrderNode(float,float);
	~OrderNode();
	std::vector<ChanceNode*> getchildren();		// to complete
	ChaosNode* getparent();
	float getutility();
	void setutility(float);
	float score;
	bool children_visited;
	float alpha;
	float beta;
	ChaosMove* move;
	// bool hasinferred;

private:
	ChaosNode* parent;
	float utility;
};

class ChanceNode
{
public:
	ChanceNode(float,OrderNode*,float,OrderMove*);
	~ChanceNode();
	Game* getgame();
	std::vector<ChaosNode*> getchildren();		// to complete
	OrderNode* getparent();
	float getutility();
	float score;
	void setutility(float);
	bool children_visited;	
	float alpha;
	float beta;
	OrderMove* move;
	// bool hasinferred;

private:
	float utility;
	OrderNode* parent;
	//int* colorbag;			// contains no. of tiles present of each color
};

std::pair<int,int> getbestmoveChaos(char);
std::pair<std::pair<int,int>,std::pair<int,int> > getbestmoveOrder();
