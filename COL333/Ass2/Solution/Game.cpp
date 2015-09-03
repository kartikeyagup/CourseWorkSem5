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

int Game::GetNewScoreInsert(char nchar,int xpos,int ypos)
{
	// Give the new score on inserting nchar at xpos,ypos but not making any change in the memory
	return Pscore;
}

int Game::GetNewScoreMove(int prex,int prevy,int newx,int newy)
{
	// Give the new score on moving the tile from (prevxy,prevy) to (newx,newy) without making change in memory
	return Pscore;
}

bool Game::GetValidMoveInsert(char newc,int posx,int posy)
{
	return (Board[posx][posy]!='-');
}

bool Game::GetValidMoveShift(int prevx,int prevy,int newx,int newy)
{
	if (prevx==newx)
	{
		if (newy>prevy)
		{
			for(int i=prevy+1; i<newy; i++)
			{
				if (Board[prevx][i]!='-')
				{
					return false;
				}
			}
			return true;
		}
		else if (prevy>newy)
		{
			for (int i=newy +1; i<prevy; i++)
			{
				if (Board[prevx][i]!='-')
				{
					return false;
				}
			}
			return true;
		}
		// Moving to same point
		return true;
	}
	else if (prevy==newy)
	{
		if (newx>prevx)
		{
			for (int i=prevx+1;i<newx; i++)
			{
				if (Board[i][prevy]!='-')
				{
					return false;
				}
			}
			return true;
		}
		else if(prevx>newx)
		{
			for(int i=newx+1; i<prevx; i++)
			{
				if (Board[i][newy]!='-')
				{
					return false;
				}
			}
			return true;
		}
		// Moving to same point
		return true;
	}
	return false;
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