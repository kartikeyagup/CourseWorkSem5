#include "PalindromePopulation.h"



std::vector<std::string> join(std::string a)
{
	std::string c = a;
	std::vector<std::string> ret;

	ret.push_back(c.append("-"));
	c=a;
	for(int i=65;i<GlobalGameDim + 65;i++)
	{
		std::string b;
		b = (char)i;
		ret.push_back(c.append(b));
		c = a;
	}
	return ret;
}

void makeallstrings(std::queue<std::string> init)
{
	// init.pop();
	// final.push_back(a);
	while(!init.empty())
	{
		std::string a = init.front();
		init.pop();
		std::vector<std::string> newvector;
		if(a.length()<GlobalGameDim)
		{
			newvector = join(a);
		}
		for(int i=0;i<newvector.size();i++)
		{
			init.push(newvector[i]);
		}
		if(a.length()==GlobalGameDim)
		{
			// std::cerr<<a<<"\n";
			AllStrings.push_back(a);
		}
	}
}


bool CheckPalind(std::string inp,int st,int en)
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
	// std::cerr << "Returning true for palindrome for " << inp.substr(st,1+lim-st) <<"\n";
	return true;
}

bool CheckValidPalind(std::string inp,int st, int en)
{
	if (CheckPalind(inp,st,en))
	{
		for (int i=st; i<=en; i++)
		{
			if (inp[i]=='-')
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

int PalindScore(std::string inp, int st, int en)
{
	if (CheckValidPalind(inp,st,en))
	{
		return(1+en-st); 
	}
	return 0;
}

int GetEntireScoreSt(std::string inp, int leng)
{
	int sc=0;
	for (int i=0; i<leng; i++)
	{
		for (int j=i+1; j<leng; j++)
		{
			// std::cerr << inp <<"\t" << i << "\t" << j <<"\t" << PalindScore(inp,i,j) <<"\n";
			sc += PalindScore(inp,i,j);
		}
	}	
	return sc;
}

template <typename T>
std::vector<T> operator+(const std::vector<T> &A, const std::vector<T> &B)
{
    std::vector<T> AB;
    AB.reserve( A.size() + B.size() );                // preallocate memory
    AB.insert( AB.end(), A.begin(), A.end() );        // add A;
    AB.insert( AB.end(), B.begin(), B.end() );        // add B;
    return AB;
}

std::vector<std::string> GetFilledIn(std::string s)
{
	for (int i=0; i<s.size(); i++)
	{
		if (s[i]=='-')
		{
			std::vector<std::string> ans;
			for (int j=0; j<GlobalGameDim ; j++)
			{
				std::string TempStr = s.c_str();
				TempStr[i] = 'A'+j;
				ans = ans+ GetFilledIn(TempStr);
			}
			return ans;
		}
	}
	return std::vector<std::string> (1,s);
}

std::vector<std::string> GetFillinOne(std::string s)
{
	for (int i=0; i<s.size() ; i++)
	{
		if (s[i]=='-')
		{
			std::vector<std::string> ans;
			for (int j=0; j<GlobalGameDim; j++)
			{
				std::string TempStr = s.c_str();
				TempStr[i] = 'A'+j;
				ans.push_back(TempStr);
			}
			return ans;
		}
	}	
	return std::vector<std::string> {s};
}

std::vector<std::string> GetFilledIn2(std::string s,char c)
{
	for (int i=0; i<s.size(); i++)
	{
		if (s[i]=='-')
		{
			std::string A = s.c_str();
			A[i]=c;
			return GetFilledIn(A);
		}
	}
	return std::vector<std::string> (1,s);
}


float GiveExpect(std::string s)
{
	std::vector<std::string> allpos = GetFilledIn(s);
	float tot=0.0;
	for (int i=0; i< allpos.size(); i++)
	{
		if (allpos[i]=="AAAAA" ||allpos[i]=="AAAAAA" ||allpos[i]=="AAAAAAA" ||
			allpos[i]=="BBBBB" ||allpos[i]=="BBBBBB" ||allpos[i]=="BBBBBBB" ||
			allpos[i]=="CCCCC" ||allpos[i]=="CCCCCC" ||allpos[i]=="CCCCCCC" ||
			allpos[i]=="DDDDD" ||allpos[i]=="DDDDDD" ||allpos[i]=="DDDDDDD" ||
			allpos[i]=="EEEEE" ||allpos[i]=="EEEEEE" ||allpos[i]=="EEEEEEE" ||
			allpos[i]=="FFFFFF" ||allpos[i]=="FFFFFFF" ||
			allpos[i]=="GGGGGGG" )
		{
			tot += GetEntireScoreSt(allpos[i],GlobalGameDim);
		}
		else
		{
			tot += pow(GetEntireScoreSt(allpos[i],GlobalGameDim),2);	
		}
	}
	tot /= allpos.size();
	return tot;
}

float GiveExpect1(std::string s)
{
	std::vector<std::string> allpos = GetFilledIn(s);
	float tot=0.0;
	for (int i=0; i< allpos.size(); i++)
	{
			tot += GetEntireScoreSt(allpos[i],GlobalGameDim);	
	}
	tot /= allpos.size();
	return tot;
}



float GiveExpect2(std::string s, char c)
{
	std::string x = s.c_str();
	for (int i=0; i<GlobalGameDim; i++)
	{
		if (s[i]=='-')
		{
			x[i]=c;
			return PalidromeScoreData[x];
		}
	}
	return PalidromeScoreData[x];
}

float GiveExpectChaos(std::string s,bool typeinp)
{
	std::vector<std::string> allpos = GetFilledIn(s);
	float tot=0.0;
	for (int i=0; i< allpos.size(); i++)
	{
		if (allpos[i]=="AAAAA" ||allpos[i]=="AAAAAA" ||allpos[i]=="AAAAAAA" ||
			allpos[i]=="BBBBB" ||allpos[i]=="BBBBBB" ||allpos[i]=="BBBBBBB" ||
			allpos[i]=="CCCCC" ||allpos[i]=="CCCCCC" ||allpos[i]=="CCCCCCC" ||
			allpos[i]=="DDDDD" ||allpos[i]=="DDDDDD" ||allpos[i]=="DDDDDDD" ||
			allpos[i]=="EEEEE" ||allpos[i]=="EEEEEE" ||allpos[i]=="EEEEEEE" ||
			allpos[i]=="FFFFFF" ||allpos[i]=="FFFFFFF" ||
			allpos[i]=="GGGGGGG" )
		{
			tot += GetEntireScoreSt(allpos[i],GlobalGameDim);
		}
		else
		{
			tot += pow(GetEntireScoreSt(allpos[i],GlobalGameDim),2);	
		}
	}
	tot /= allpos.size();
	return tot;
}

void Initialise(bool typeinp)
{
	std::queue<std::string> init;
	init.push("");
	makeallstrings(init);
	std::cerr << "Got all strings from ronak\t" << AllStrings.size() <<"\n";
	// if (GlobalGameDim<7)
	// {
		for (int i=0; i< AllStrings.size(); i++)
		{
			// NormalPalindromeScores.push_back(GiveExpect1(AllStrings[i]));
			PopulateTable1(AllStrings[i]);
		}
		// for (int i=0; i<AllStrings.size(); i++)
		// {
		// 	if (abs(PalidromeScoreData[AllStrings[i]] - NormalPalindromeScores[i]) > 0.01 )
		// 		std::cerr << "MISMATCH AT " << AllStrings[i] << "\t" << PalidromeScoreData[AllStrings[i]] <<"\t" << NormalPalindromeScores[i] <<"\n";
		// }
	// }
	// std::cerr << "Obtained normal palindrome scores\n";
	// if (GlobalGameDim==5)
	// {
	// 	PopulateTable1("-----");
	// }
	// else if (GlobalGameDim==6)
	// {
	// 	PopulateTable1("------");
	// }
	// else
	// 	PopulateTable1("-------");
	std::cerr << "Done with normal expectations\t" << AllStrings.size() <<"\t" << PalidromeScoreData.size() <<"\n";
	PopulateTable(typeinp);
	std::cerr << "Done with other tables\n";
}

float PopulateTable1(std::string b)
{
	if (PalidromeScoreData.find(b)==PalidromeScoreData.end())
	{
		std::vector<std::string> children = GetFillinOne(b);
		float temp=0;
		if (children.size()==1)
		{
			PalidromeScoreData[b] = GetEntireScoreSt(b,GlobalGameDim);
		}
		else
		{
			for (int i=0; i<children.size(); i++)
			{
				temp += PopulateTable1(children[i]);
			}
			temp /= children.size();
			PalidromeScoreData[b]=temp;
		}	
		// std::cerr << b << "\t"<< PalidromeScoreData[b]<<"\n";	
		return PalidromeScoreData[b];
	}
	else
	{
		return PalidromeScoreData[b];
	}
}


void PopulateTable(bool x)
{
	if (false)
	{

		for (int i=0; i<AllStrings.size(); i++)
		{
			PalidromeScoreData[AllStrings[i]]=NormalPalindromeScores[i];
		}
	}
	else
	{
		// for (int i=0; i<AllStrings.size(); i++)
		// {
		// 	PalidromeScoreData[AllStrings[i]]=NormalPalindromeScores[i];
		// }
	
		for (int i=0; i<AllStrings.size(); i++)
		{
			for (int j=0; j<GlobalGameDim; j++)
			{
				AllPalindromesData[j][AllStrings[i]] = GiveExpect2(AllStrings[i],'A'+j); 
			}
		}
	}
}	