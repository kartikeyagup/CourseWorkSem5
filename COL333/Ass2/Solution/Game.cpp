#include "Game.h"

// TODO: Check the palindrome from a pivot point. 
// Will make the complexity order n^2 instead of present n^3
// No need for this, use a hastable. 8)

char* Game::GetColumn(int col)
{
	char* ans= new char[Dimension];
	for (int i=0; i<Dimension; i++)
	{
		ans[i]=Board[i][col];
	}
	return ans;
}

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

int GetEntireScore2(char* inp)
{
	// std::string temp(inp);
	std::string temp;
	temp.assign(inp,5);
	// std::cerr << temp << " was scored to: " << PalidromeScoreData[inp]
	return PalidromeScoreData[temp];
}

Game::Game()
{
	Dimension=0;
	TypePlayer=0;
	Board = new char*[1];
	Board[0] = new char[1];
	Pscore=0;
	ColCompleted = new int[1];
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
	ColCompleted = new int[Dimension];
	for (int i=0; i<Dimension; i++)
	{
		ColCompleted[i]=0;
	}
}

Game::Game(int dim,bool ty,char** board,float score,int numcomp,int* coloursfilled)
{
	Dimension=dim;
	TypePlayer = ty;
	NumCompleted=numcomp;
	Pscore=score;
	Board = board;
	ColCompleted = coloursfilled;
}

Game::~Game()
{
	for (int i=0; i<Dimension; i++)
	{
		delete Board[i];
	}
	delete Board;
	delete ColCompleted;
}

int Game::GetDimension()
{
	return Dimension;	
}

bool Game::GetType()
{
	return TypePlayer;
}

char** Game::GetBoard()
{
	return Board;
}

int Game::GetNumCompleted()
{
	return NumCompleted;
}

int Game::CalculateScore()
{
	int sccal=0;
	for (int i=0; i<Dimension; i++)
	{
		// sccal += GetEntireScore(Board[i],Dimension);
		sccal += GetEntireScore2(Board[i]);
		char *vert= new char[Dimension];
		for (int j=0; j<Dimension; j++)
		{
			vert[j]=Board[j][i];
		}
		// sccal += GetEntireScore(BoardT[i],Dimension);
		sccal += GetEntireScore2(vert);
	}
	return sccal;
}


void Game::ShowPresent()
{
	char endl='\n';
	fprintf(stderr,"Playing as: %d, 0 is order 1 is chaos\nDimension: %d,Present Score: %f\n",TypePlayer,Dimension,Pscore);
	for (int i=0; i<Dimension; i++)
	{
		// fputs(stderr,Board[i]);
		// fprintf(stderr,Board[i]);
		std::cerr << Board[i] <<"\n";
		// fprintf(stderr,"\n");
		// fputchar(stderr,endl);
	}
	fprintf(stderr,"Present colour counts: ");
	for (int i=0; i<Dimension; i++)
	{
		std::cerr << ColCompleted[i] <<" ";
	}
	std::cerr <<"\n";
}

float Game::GetPresentScore()
{
	return Pscore;
}

void Game::Move(int initx,int inity, int finx, int finy)
{
	// (initx)(inity) -> (finx)(finy)
	// std::cerr << "previous score move " << Pscore << "\t";
	Pscore = GetNewScoreMove(initx,inity,finx,finy);
	// std::cerr << "final score move" << Pscore << "\n";

	if (initx!=finx || inity!=finy)
	{
		Board[finx][finy]=Board[initx][inity];
		Board[initx][inity]='-';
	}
}

void Game::AddNew(char nchar,int xpos, int ypos)
{
	// std::cerr << "previous score move" << Pscore << "\t";
	Pscore = GetNewScoreInsert(nchar,xpos,ypos);
	// std::cerr << "final score move" << Pscore << "\n";
	Board[xpos][ypos]=nchar;
	NumCompleted +=1;
	ColCompleted[nchar-'A']+=1;
}

float Game::GetNewScoreInsert(char nchar,int xpos,int ypos)
{
	// Give the new score on inserting nchar at xpos,ypos but not making any change in the memory
	// int scorepresentrowcol = GetEntireScore(Board[xpos],Dimension) + GetEntireScore(BoardT[ypos],Dimension);
	int scorepresentrowcol = GetEntireScore2(Board[xpos]) + GetEntireScore2(GetColumn(ypos));
	Board[xpos][ypos]=nchar;
	// int newscorepresentrowcol = GetEntireScore(Board[xpos],Dimension) + GetEntireScore(BoardT[ypos],Dimension);
	int newscorepresentrowcol = GetEntireScore2(Board[xpos]) + GetEntireScore2(GetColumn(ypos));
	Board[xpos][ypos]='-';
	// std::cerr << "row col "<<scorepresentrowcol << "\t" << newscorepresentrowcol <<"\n";
	return Pscore + newscorepresentrowcol - scorepresentrowcol;
}

bool Game::IsCompleted()
{
	return (NumCompleted==(Dimension*Dimension));
}

float Game::GetNewScoreMove(int prevx,int prevy,int newx,int newy)
{
	// Give the new score on moving the tile from (prevxy,prevy) to (newx,newy) without making change in memory
	float ans=0;
	if (newx==prevx)
	{
		//Same row motion
		if (newy==prevy)
		{
			ans=0;
		}
		else 
		{
			// int scorecons = GetEntireScore(Board[prevx],Dimension) + GetEntireScore(BoardT[prevy],Dimension)+GetEntireScore(BoardT[newy],Dimension);
			int scorecons = GetEntireScore2(Board[prevx]) + GetEntireScore2(GetColumn(prevy))+GetEntireScore2(GetColumn(newy));
			Board[newx][newy]=Board[prevx][prevy];
			Board[prevx][prevy]='-';
			// int scoreconschange = GetEntireScore(Board[prevx],Dimension) + GetEntireScore(BoardT[prevy],Dimension)+GetEntireScore(BoardT[newy],Dimension);
			int scoreconschange = GetEntireScore2(Board[prevx]) + GetEntireScore2(GetColumn(prevy))+GetEntireScore2(GetColumn(newy));
			Board[prevx][prevy]=Board[newx][newy];
			Board[newx][newy]='-';
			ans = scoreconschange - scorecons;
		}
	}
	else
	{
		// Same column Motion
		// int scorecons = GetEntireScore(Board[prevx],Dimension) + GetEntireScore(Board[newx],Dimension)+GetEntireScore(BoardT[newy],Dimension);
		int scorecons = GetEntireScore2(Board[prevx]) + GetEntireScore2(Board[newx])+GetEntireScore2(GetColumn(newy));
		Board[newx][newy]=Board[prevx][prevy];
		Board[prevx][prevy]='-';
		// int scoreconschange = GetEntireScore(Board[prevx],Dimension) + GetEntireScore(Board[newx],Dimension)+GetEntireScore(BoardT[newy],Dimension);
		int scoreconschange = GetEntireScore2(Board[prevx]) + GetEntireScore2(Board[newx])+GetEntireScore2(GetColumn(newy));
		Board[prevx][prevy]=Board[newx][newy];
		Board[newx][newy]='-';
		ans = scoreconschange - scorecons;	
	}
	// std::cerr << "ans is" << Pscore << " " << ans<<"\n";
	return Pscore+ans;
}

bool Game::GetValidMoveInsert(char newc,int posx,int posy)
{
	return (Board[posx][posy]=='-');
}

bool Game::GetValidMoveShift(int prevx,int prevy,int newx,int newy)
{
	if (Board[prevx][prevy]=='-')
		return false;
	if (prevx==newx)
	{
		if (newy>prevy)
		{
			for(int i=prevy+1; i<=newy; i++)
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
			for (int i=prevy-1 ; i>=newy; i--)
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
			for (int i=prevx+1;i<=newx; i++)
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
			for(int i=prevx-1; i>=newx; i--)
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

int* Game::GetColCompleted()
{
	return ColCompleted;
}

float* Game::GetProbabilities()
{
	float *ans = new float[Dimension];
	for (int i=0; i<Dimension; i++)
	{
		ans[i]=((Dimension-ColCompleted[i])*1.0)/(Dimension*Dimension - NumCompleted);
	}
	return ans;
}

Game* GetDuplicate(Game* inp)
{
	int dim= inp->GetDimension();
	bool t = inp->GetType();
	char** board = inp->GetBoard();
	float pscore = inp->GetPresentScore();
	int numcompleted= inp->GetNumCompleted();
	int* colcomp = inp->GetColCompleted();

	char **newb = new char*[dim];
	int *newcolcomp = new int[dim];
	for (int i=0; i<dim; i++)
	{
		newb[i]=new char[dim];
	}
	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			newb[i][j]=board[i][j];
		}
		newcolcomp[i]=colcomp[i];
	}
	Game* newgame = new Game(dim,t,newb,pscore,numcompleted,newcolcomp);
	return newgame;
}

std::pair<int,int> GetDifferenceInsert(Game* previous,Game* present)
{
	char** boardprev= previous->GetBoard();
	char** boardnew= present->GetBoard();
	int dim = previous->GetDimension();
	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			if (boardnew[i][j]!=boardprev[i][j])
			{
				return std::pair<int,int> (i,j);
			}
		}
	}
	std::cerr<<"Some error has happened. Check the boards given\n";
}

std::pair<std::pair<int,int>,std::pair<int,int> > GetDifferenceMove(Game* previous, Game* present)
{
	char **boardprev= previous->GetBoard();
	char **boardnew = present->GetBoard();
	// previous->ShowPresent();
	// present->ShowPresent();
	int dim= previous->GetDimension();
	int prevx=-1,prevy=-1,newx=-1,newy=-1;
	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
		{
			if (boardnew[i][j]!=boardprev[i][j])
			{
				if (boardprev[i][j]=='-')
				{
					newx = i;
					newy = j;
				}
				else
				{
					prevx = i;
					prevy = j;
				}
			}
		}
	}
	if (prevx==-1 || newx==-1)
	{
		for (int i=0; i<dim; i++)
		{
			for (int j=0; j<dim; j++)
			{
				if (boardprev[i][j]!='-')
				{
					prevx=i;
					newx=i;
					prevy=j;
					newy=j;
				}
			}
		}
	}
	// std::cerr << prevx <<"\t" << prevy <<"\t" <<newx <<"\t" << newy <<"\n";
	std::pair<int,int> st1, end1;
	st1 = std::pair<int,int> (prevx,prevy);
	end1 = std::pair<int,int> (newx,newy);
	return std::pair<std::pair<int,int>,std::pair<int,int> > (st1,end1);
}

// int main(int argc, char const *argv[])
// {
// 	/* code */
// 	int dim;
// 	std::cin >> dim;
// 	bool type;
// 	std::cin>> type;
// 	Game g1 = Game(dim,type);
// 	g1.ShowPresent();
// 	std::cout << g1.CalculateScore() <<" is calculated\n";
// 	return 0;
// }