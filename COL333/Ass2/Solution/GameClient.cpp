#include "GameClient.h"

std::unordered_map<std::string,float> PalidromeScoreData;

int main(int argc, char const *argv[])
{
	int dim;
	std::cin >> dim;
	std::string role;
	std::cin >>role;

	bool typeg = (role=="CHAOS");

	PopulateTable();

	Game *GameToPlay =new Game(dim,typeg);
	std::cerr<<"Type: "<<typeg<<"\n";
	if (typeg)
	{
		//Playing as Chaos
		char inp;
		std::cin >>inp;
		std::cerr << "Char obtained is: " << inp <<"\n";
		std::pair<int,int> mbest= getbestmoveChaos(GameToPlay,inp);
		std::cerr << "received move from ronak\n";
		GameToPlay->AddNew(inp,mbest.first,mbest.second);
		std::cout << mbest.first <<" "<<mbest.second <<"\n";
		GameToPlay->ShowPresent();
		
		while (true)
		{
			if (GameToPlay->IsCompleted())
			{
				break;
			}

			int InpInitx;
			int InpInity;
			int FinInitx;
			int FinInity;

			std::cin >> InpInitx >> InpInity >> FinInitx >> FinInity;
			GameToPlay->Move(InpInitx,InpInity,FinInitx,FinInity);
			std::cin >> inp;
			mbest = getbestmoveChaos(GameToPlay,inp);
			GameToPlay->AddNew(inp,mbest.first,mbest.second);
			std::cout << mbest.first <<" "<<mbest.second <<"\n";
			GameToPlay->ShowPresent();
		}
	}
	else
	{
		std::cerr<<"In the else case\n";
		//Playing as Order
		return 0;
		while (true)
		{
			GameToPlay->ShowPresent();
			int posx,posy;
			char col;
			std::cin >> posx>>posy>>col;
			GameToPlay->AddNew(col,posx,posy);
			if (GameToPlay->IsCompleted())
			{
				break;
			}
			std::pair<std::pair<int,int>,std::pair<int,int> > mv = getbestmoveOrder(GameToPlay);
			std::cerr << "Received move from ronak\t" << mv.first.first << "\t" <<mv.first.second <<"\t" << mv.second.first <<"\t" << mv.second.second<<"\n";
			GameToPlay->Move(mv.first.first,mv.first.second,mv.second.first,mv.second.second);
			std::cout << mv.first.first << " " <<mv.first.second << " " << mv.second.first << " " << mv.second.second <<"\n";
		}
	}

	// fprintf(stderr,"This is an error print\n");
	// printf("this is a normal print\n");

	// Game x = Game(5,0);
	// GameToPlay.ShowPresent();

	fprintf(stderr,"This is another error print\n");
	// printf("this is another normal print\n");
	return 0;
}