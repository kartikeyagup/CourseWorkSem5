#ifndef GAMETREE_H
#define GAMETREE_H

#include <iostream>
#include <vector>
#include "Game.h"
#include <string>

class ChaosNode;
class OrderNode;
class ChanceNode;

extern Game GlobalGame;
extern float w1_chaos,w2_chaos,w1_order,w2_order;
extern float learningrate_chaos,learningrate_order;
extern float f1_chaos,f2_chaos,f1_order,f2_order;
extern std::string constantweights;			// denotes whether the player is playing with static weights or variable weights;

class ChaosNode
{
public:
	ChaosNode(char,float,float,float);
	~ChaosNode();
	float getprobability();
	float getutility();
	float score;
	void getchildren(std::vector<OrderNode*> &);	//	to complete
	char getcolor();
	void setutility(float);
	bool children_visited;
	float alpha;
	float beta;
	// bool hasinferred;

private:
	char color;
	float probability;
	float utility;			// gives the backed up value
};

class OrderNode
{
public:
	//OrderNode();
	OrderNode(float,float,ChaosMove*);
	OrderNode(float,float);
	~OrderNode();
	void getchildren(std::vector<ChanceNode*> &);		// to complete
	float getutility();
	void setutility(float);
	float score;
	bool children_visited;
	float alpha;
	float beta;
	ChaosMove* move;
	// bool hasinferred;

private:
	float utility;
};

class ChanceNode
{
public:
	ChanceNode(float,float,OrderMove*);
	~ChanceNode();
	Game* getgame();
	void getchildren(std::vector<ChaosNode*> &);		// to complete
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
	//int* colorbag;			// contains no. of tiles present of each color
};

std::pair<int,int> getbestmoveChaos(char);
std::pair<std::pair<int,int>,std::pair<int,int> > getbestmoveOrder();

#endif