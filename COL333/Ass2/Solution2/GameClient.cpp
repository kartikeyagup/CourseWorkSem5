#include "GameClient.h"

std::unordered_map<std::string,float> PalidromeScoreData;
Game GlobalGame;
char* vert;

int main(int argc, char const *argv[])
{
	int dim;
	std::cin >> dim;
	std::string role;
	std::cin >>role;

	bool typeg = (role=="CHAOS");

	PopulateTable(typeg);

	Game *GlobalGame1 =new Game(dim,typeg);
	GlobalGame= *GlobalGame1;

	std::cerr<<"Type: "<<typeg<<"\n";
	if (typeg)
	{
		//Playing as Chaos
		char inp;
		std::cin >>inp;
		std::cerr << "Char obtained is: " << inp <<"\n";
		GlobalGame.ShowPresent();
		std::pair<int,int> mbest= getbestmoveChaos(inp);
		std::cerr << "received move from ronak\n";
		GlobalGame.AddNew(inp,mbest.first,mbest.second);
		std::cout << mbest.first <<" "<<mbest.second <<"\n";
		GlobalGame.ShowPresent();
		
		while (true)
		{
			if (GlobalGame.IsCompleted())
			{
				break;
			}

			int InpInitx;
			int InpInity;
			int FinInitx;
			int FinInity;

			std::cin >> InpInitx >> InpInity >> FinInitx >> FinInity;
			GlobalGame.Move(InpInitx,InpInity,FinInitx,FinInity);
			std::cerr << "Doing order move\n";
			GlobalGame.ShowPresent();
			std::cerr << "Now starting chaos move\n";	
			std::cin >> inp;
			mbest = getbestmoveChaos(inp);
			std::cerr << "Obtained move from ronak\n";
			GlobalGame.ShowPresent();
			GlobalGame.AddNew(inp,mbest.first,mbest.second);
			std::cout << mbest.first <<" "<<mbest.second <<"\n";
			GlobalGame.ShowPresent();
		}
	}
	else
	{
		std::cerr<<"In the else case\n";
		//Playing as Order
		// return 0;
		while (true)
		{
			GlobalGame.ShowPresent();
			int posx,posy;
			char col;
			std::cin >> posx>>posy>>col;
			GlobalGame.AddNew(col,posx,posy);
			if (GlobalGame.IsCompleted())
			{
				break;
			}
			GlobalGame.ShowPresent();
			std::pair<std::pair<int,int>,std::pair<int,int> > mv = getbestmoveOrder();
			std::cerr << "Received move from ronak\t" << mv.first.first << "\t" <<mv.first.second <<"\t" << mv.second.first <<"\t" << mv.second.second<<"\n";
			GlobalGame.Move(mv.first.first,mv.first.second,mv.second.first,mv.second.second);
			std::cout << mv.first.first << " " <<mv.first.second << " " << mv.second.first << " " << mv.second.second <<"\n";
		}
	}

	// fprintf(stderr,"This is an error print\n");
	// printf("this is a normal print\n");

	// Game x = Game(5,0);
	// GlobalGame.ShowPresent();

	fprintf(stderr,"This is another error print\n");
	// printf("this is another normal print\n");
	return 0;
}