#include "Game.h"

bool CheckPalindrome(char* inp,int st,int en)
{
	// From st to en, both included
	int lim= en;
	for (int i=st;i<=lim; i++)
	{
		if (inp[i]!=inp[en])
		{
			return false;
		}
		en--;
	}
	return true;
}

bool CheckValidPalin(char* inp,int st, int en)
{
	if (CheckPalindrome(inp,st,en))
	{
		for (int i=st; i<=en; i++)
		{
			if (inp[i]=='-')
			{
				return false;
			}
		}
	}
	return true;
}

int ScoreString(char* inp, int st, int en)
{
	if (CheckValidPalin(inp,st,en))
	{
		return(1+en-st); 
	}
	return 0;
}

int GetEntireScore(char* inp, int leng)
{
	int sc=0;
	for (int i=0; i<leng; i++)
	{
		for (int j=i+1; j<leng; j++)
		{
			sc += ScoreString(inp,i,j);
		}
	}	
	return sc;
}

Game::Game()
{
	Dimension=0;
	TypePlayer=0;
	Board = new char*[1];
	Board[0] = new char[1];
	Pscore=0;
}

int Game::CalculateScore()
{
	int sccal=0;
	for (int i=0; i<Dimension; i++)
	{
		sccal += GetEntireScore(Board[i],Dimension);
		char *vert= new char[Dimension];
		for (int j=0; j<Dimension; j++)
		{
			vert[j]=Board[j][i];
		}
		sccal += GetEntireScore(vert,Dimension);
	}
	return sccal;
}

Game::Game(int dim,bool type)
{
	// 0 is order, 1 is chaos
	TypePlayer = type;
	Dimension = dim;
	Pscore=0;
	Board = new char*[Dimension];
	for (int i=0; i<dim;i++)
	{
		Board[i]=new char[Dimension];
		memset(Board[i],'-',Dimension);
	}
}


void Game::ShowPresent()
{
	char endl='\n';
	printf("Playing as: %d, 0 is order 1 is chaos\nDimension: %d,Present Score: %d\n",TypePlayer,Dimension,Pscore);
	for (int i=0; i<Dimension; i++)
	{
		puts(Board[i]);
		putchar(endl);
	}
}


int Game::GetPresentScore()
{
	return Pscore;
}


void Game::Move(int initx,int inity, int finx, int finy)
{
	// (initx)(inity) -> (finx)(finy)
	Board[finx][finy]=Board[initx][inity];
	Board[initx][inity]='-';
	// TODO: Put in Pscore change
}

void Game::AddNew(char nchar,int xpos, int ypos)
{
	Board[xpos][ypos]=nchar;
	// TODO: Put in Pscore change
}

int main(int argc, char const *argv[])
{
	/* code */
	int dim;
	std::cin >> dim;
	bool type;
	std::cin>> type;
	Game g1 = Game(dim,type);
	g1.ShowPresent();
	std::cout << g1.CalculateScore() <<" is calculated\n";
	return 0;
}