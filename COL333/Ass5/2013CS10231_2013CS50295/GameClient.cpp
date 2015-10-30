#include "GameClient.h"

std::unordered_map<std::string,float> PalidromeScoreData;
std::unordered_map<std::string,float>* AllPalindromesData;
Game GlobalGame;
char* vert;
std::vector<std::string> AllStrings;
std::vector<float> NormalPalindromeScores;
int GlobalGameDim;

float w1_chaos,w2_chaos,w1_order,w2_order;
float learningrate_chaos,learningrate_order;
float f1_chaos,f2_chaos,f1_order,f2_order;
std::string constantweights;			// denotes whether the player is playing with static weights or variable weights;




int main(int argc, char const *argv[])
{
	int dim;
	std::cin >> dim;
	std::string role;
	std::cin >>role;

	bool typeg = (role=="CHAOS");
	
	GlobalGameDim = dim;
	AllPalindromesData= new std::unordered_map<std::string,float>[dim];
	std::cerr << "Starting preprocessing\n";
	Initialise(typeg);
	std::cerr << "Done with all preprocessing\n";
	// PopulateTable(typeg);
	// PopulateAllTables(typeg);
	// std::cerr << PalidromeScoreData["AC---"]<<"\n";
	// std::cerr << AllPalindromesData[0]["-C---"] <<"\n";
	// return 0;
	Game *GlobalGame1 =new Game(dim,typeg);
	GlobalGame= *GlobalGame1;
	double t_chaos;
	double t_order;
	double t_chaostime = 0.0;
	double t_ordertime = 0.0;
	double dim_timeout ;

	learningrate_order = 1.0;
	learningrate_chaos = 1.0;
	if(GlobalGame.GetDimension()==5)
	{
		dim_timeout = 56.66;
	}
	else if(GlobalGame.GetDimension() == 6)
	{
		dim_timeout = 116.66;
	}
	else if(GlobalGame.GetDimension() == 7)
	{
		dim_timeout = 176.66;
	}
	bool timed_out = 0;
	std::cerr<<"Type: "<<typeg<<"\n";
	constantweights = argv[1];
	if (typeg)
	{
		//Playing as Chaos
		std::ifstream fil;
		fil.open("ChaosWeights.txt");
		if(fil.is_open())
		{
			float a,b;
			while(fil >> a >> b)
			{
				w1_chaos = a;
				w2_chaos = b;
			}
			fil.close();
		}


		char inp;
		timed_out = 0;
		
		std::cin >>inp;

		t_chaos = clock()/double(CLOCKS_PER_SEC);

		std::cerr << "Char obtained is: " << inp <<"\n";
		// GlobalGame.ShowPresent();
		std::pair<int,int> mbest(1,1);
		// std::pair<int,int> mbest= getbestmoveChaos(inp);
		// std::cerr << "received move from ronak\n";

		GlobalGame.AddNew(inp,mbest.first,mbest.second);
		std::cout << mbest.first <<" "<<mbest.second <<"\n";
		t_chaos = clock()/double(CLOCKS_PER_SEC) - t_chaos;
		t_chaostime += t_chaos;
		// GlobalGame.ShowPresent();
		
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
			t_chaos = clock()/double(CLOCKS_PER_SEC);
			GlobalGame.Move(InpInitx,InpInity,FinInitx,FinInity);
			// std::cerr << "Doing order move\n";
			// GlobalGame.ShowPresent();
			// std::cerr << "Now starting chaos move\n";	
			std::cin >> inp;
			if(t_chaostime<dim_timeout)
			{
				mbest = getbestmoveChaos(inp);
				// std::cerr << "Obtained move from ronak\n";
				// GlobalGame.ShowPresent();
				GlobalGame.AddNew(inp,mbest.first,mbest.second);
				std::cout << mbest.first <<" "<<mbest.second <<"\n";
				t_chaos = clock()/double(CLOCKS_PER_SEC) - t_chaos;
				//std::cerr<<"Printing Clock  "<<t_chaos<<"\n";
				t_chaostime += t_chaos;
				GlobalGame.ShowPresent();
				// std::cerr<<"Printing time: "<<t_chaostime<<"\n";
			}
			else
			{
				// std::cerr<<"**********************************************Timed out chaos\n";
				mbest = GlobalGame.GetRandomMoveChaos();
				GlobalGame.AddNew(inp,mbest.first,mbest.second);
				std::cout << mbest.first <<" "<<mbest.second <<"\n";
			}
		}
	}
	else
	{
		// std::cerr<<"In the else case\n";
		//Playing as Order
		// return 0;
		std::ifstream fil;
		fil.open("OrderWeights.txt");
		if(fil.is_open())
		{
			float a,b;
			while(fil >> a >> b)
			{
				w1_order = a;
				w2_order = b;
			}
			fil.close();
		}

		std::pair<std::pair<int,int>,std::pair<int,int> > mv;
		timed_out = 0;
		while (true)
		{
			// GlobalGame.ShowPresent();
			int posx,posy;
			char col;
			std::cin >> posx>>posy>>col;
			t_order = clock()/double(CLOCKS_PER_SEC);
			GlobalGame.AddNew(col,posx,posy);
			if (GlobalGame.IsCompleted())
			{
				break;
			}
			GlobalGame.ShowPresent();
			if(t_ordertime<dim_timeout)
			{
				mv = getbestmoveOrder();
				// std::cerr << "Received move from ronak\t" << mv.first.first << "\t" <<mv.first.second <<"\t" << mv.second.first <<"\t" << mv.second.second<<"\n";
				GlobalGame.ShowPresent();
				GlobalGame.Move(mv.first.first,mv.first.second,mv.second.first,mv.second.second);
				std::cout << mv.first.first << " " <<mv.first.second << " " << mv.second.first << " " << mv.second.second <<"\n";
				t_order = clock()/double(CLOCKS_PER_SEC) - t_order;
				t_ordertime += t_order;
				// std::cerr<<"Printing time spent: "<< t_ordertime <<"\n";
			}
			else
			{
				// std::cerr<<"**********************************8Timed out\n";
				mv = GlobalGame.GetRandomMoveOrder();
				GlobalGame.Move(mv.first.first,mv.first.second,mv.second.first,mv.second.second);
				std::cout << mv.first.first << " " <<mv.first.second << " " << mv.second.first << " " << mv.second.second <<"\n";
			}
		}
	}


	std::ofstream fil;
	fil.open("ChaosWeights.txt");

	fil<<std::to_string(w1_chaos);
	fil<<" ";
	fil<<std::to_string(w2_chaos);

	fil.close();


	fil.open("OrderWeights.txt");

	fil<<std::to_string(w1_order);
	fil<<" ";
	fil<<std::to_string(w2_order);

	fil.close();



	// fprintf(stderr,"This is an error print\n");
	// printf("this is a normal print\n");

	// Game x = Game(5,0);
	// GlobalGame.ShowPresent();

	// fprintf(stderr,"This is another error print\n");
	// printf("this is another normal print\n");
	return 0;
}