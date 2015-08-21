#include "Schedule.h"

Schedule::Schedule()
{
	Sp.k=0;
	Sp.t=0;
	Sp.p=0;
	Sp.c=0;
	Sp.d=new double*[1];
	schedule = new int[0];
}

Schedule::Schedule(std::string filename)
{
	vector<string> lines;
    string line;
    ifstream myfile ( filename.c_str () );
    if ( myfile.is_open ( ) )
    {
        while ( getline ( myfile, line ) )
        {
            //cout<<"Line read:"<<line<<endl;
            lines.push_back ( line );
        }
        myfile.close ( );
    }
    else
    {
        cout << "Unable to open input file";
        exit ( 0 );
    }

    if ( 6 > lines.size ( ) )
    {
        cout << "Not enough information given, check format of input file "<<lines.size()<<"\n";
        exit ( 0 );
    }

    processtime = 60*(atof ( lines[0].c_str () ));
    Sp.k = atoi ( lines[1].c_str () );
    Sp.p = atoi ( lines[2].c_str () );
    Sp.t = atoi ( lines[3].c_str () );
    Sp.c = atof ( lines[4].c_str () );

    int n = lines.size ( ) - 5;
    double ** tempDistanceMatrix = new double*[n];
    for ( int i = 0; i < n; ++i )
    {
        tempDistanceMatrix[i] = new double[n];
    }


    for ( int i = 0; i < n; i++ )
    {
        string tempLine = lines[ i + 5 ];
        string elements[n];
        splitString ( tempLine, " ", elements, n );

        for ( int j = 0; j < n; j++ )
        {
            tempDistanceMatrix[i][j] = atof ( elements[j].c_str () );
        }
    }
    Sp.d = tempDistanceMatrix;

    int numberOfPapers = n;
    totalpapers =n ;
    int slots = Sp.k * Sp.t* Sp.p;
    if ( slots != numberOfPapers )
    {
        cout << "More papers than slots available! slots:" << slots << " num papers:" << numberOfPapers << endl;
        exit ( 0 );
    }
    Sp.tp = Sp.t*Sp.p;
    Sp.pk = Sp.p*Sp.k;
    schedule = new int[totalpapers];
    for (int i=0;i<totalpapers;i++)
    {
    	schedule[i]=i+1;
    }
    std::cout << "created schedule\n";
    presentgoodness = GetHappiness(schedule);
}

float Schedule::GetHappiness(int *scheduleinp)
{
	float ans = (Sp.tp*(Sp.k)*(Sp.k-1))/2;
	for (int i=0; i<Sp.tp; i++)
	{
		for (int j=0; j<Sp.k; j++)
		{
			for (int k=j+1; k<Sp.k; k++)
			{
				// std::cout <<"this will come: " << i*Sp.k+j <<"\t" << scheduleinp[i*Sp.k+j] <<" " << scheduleinp[i*Sp.tp+k]<<"\n";
				ans -= Sp.d[scheduleinp[i*Sp.k+j]-1][scheduleinp[i*Sp.k+k]-1];
				// std::cout <<"this wont come: " << j <<" " << k<<"\n";
			}
		}
	}
	// std::cout <<"done first part\n";
	
	float anst=0;
	for (int i=0; i<Sp.t; i++)
	{
		for (int j=0;j<Sp.p;j++)
		{
			for (int k=0;k<Sp.k;k++)
			{
				for (int l=i*Sp.pk+(j+1)*Sp.k;l<(1+i)*Sp.pk;l++)
				{
					anst += Sp.d[scheduleinp[l]-1][scheduleinp[i*Sp.pk + j*Sp.k + k]-1];		
				}
			}
			// for (int k=(1+i)*Sp.k;k<totalpapers;k++)
			// {
			// 	anst += Sp.d[scheduleinp[Sp.k*i+j]-1][scheduleinp[k]-1];
			// }
		}
	}
	anst *= Sp.c;
	return ans+anst;
}

void Schedule::ShowSchedule()
{
	// TODO: Remove the stray vertical line
	for (int i=0; i< Sp.t;i++)
	{
		for (int j=0; j< Sp.p; j++)
		{
			for (int k=0; k<Sp.k; k++)
			{
				std::cout << schedule[i*Sp.pk + j*Sp.k + k] <<" ";
			}
			std::cout <<"| ";
		}
		std::cout <<"\n";
	}
}

void Schedule::NormalDFS()
{
	std::cout <<"starting normal dfs\n";
	time_t time_start,presenttime;
	time (&time_start);
	int *presentbest = new int[totalpapers];
	for (int i=0; i<totalpapers; i++)
	{
		presentbest[i]=schedule[i];
	}
	float presenthp = presentgoodness;
	std::cout <<"made initial copies and all\n";
	while (std::next_permutation(schedule,schedule+totalpapers))
	{
		// std::cout <<"in the while loop\n";
		presentgoodness = GetHappiness(schedule);
		time (&presenttime);
		// std::cout <<"got present time\n";
		// TODO: Change Taking 5 seconds as a wrapper processing time.
		if (difftime(presenttime,time_start) > processtime + 5)
		{
			if (presentgoodness!=presenthp)
			{
				if (presentgoodness<presenthp)
				{
					presentgoodness= presenthp;
					for (int i=0; i<totalpapers; i++)
					{
						schedule[i]=presentbest[i];
					}
				}
			}
			break;
		}
		// std::cout <<"outside if loop of time\n";
		if (presentgoodness>presenthp)
		{
			ShowSchedule();
			std::cout <<"value: " << presentgoodness <<"\n";
			for (int i=0; i<totalpapers; i++)
			{
				presentbest[i]=schedule[i];
			}
			presenthp=presentgoodness;
		}
	}
	std::cout << presentgoodness << " ";
	ShowSchedule();
}

void Schedule::SwapIJ(int i,int j)
{
	if (i/Sp.k != j/Sp.k)
	{
		if (i/Sp.pk == j/ Sp.pk)
		{
			// Same time slot swapping
			double pscore = presentgoodness;
			for (int q=0; q<Sp.k; q++)
			{
				pscore -= (1-Sp.d[schedule[i]-1][schedule[Sp.k*(i/Sp.k) + q]-1]);
				pscore -= (1-Sp.d[schedule[j]-1][schedule[Sp.k*(j/Sp.k) + q]-1]);
				
				pscore -= Sp.c*Sp.d[schedule[i]-1][schedule[Sp.k*(j/Sp.k) +q] -1];
				pscore -= Sp.c*Sp.d[schedule[j]-1][schedule[Sp.k*(i/Sp.k) +q] -1];
			}

			int temp = schedule[i];
			schedule[i] = schedule[j];
			schedule[j]= temp;

			for (int q=0; q<Sp.k;q++)
			{	
				pscore += (1-Sp.d[schedule[i]-1][schedule[Sp.k*(i/Sp.k) + q]-1]);
				pscore += (1-Sp.d[schedule[j]-1][schedule[Sp.k*(j/Sp.k) + q]-1]);
				
				pscore += Sp.c*Sp.d[schedule[i]-1][schedule[Sp.k*(j/Sp.k) +q] -1];
				pscore += Sp.c*Sp.d[schedule[j]-1][schedule[Sp.k*(i/Sp.k) +q] -1];
			}

			// std::cout << pscore<<"\t"<<GetHappiness(schedule)<<"\n";
			if (pscore != GetHappiness(schedule))
			{
				std::cout << "SWAPPING SCORE CALC INCORRECT FOR SAME\t" << GetHappiness(schedule)-pscore <<"\n";
			}

			if (pscore<presentgoodness)
			{
				temp = schedule[i];
				schedule[i] = schedule[j];
				schedule[j] = temp;
			}
			else
			{
				std::cout << presentgoodness << " ";
				ShowSchedule();
				presentgoodness=pscore;
			}

		}
		else
		{
			// Different time slot swapping
			double pscore = presentgoodness;
			int rowi = (i/Sp.pk)*Sp.pk;
			int rowj = (j/Sp.pk)*Sp.pk;
			for (int q=0; q<Sp.pk; q++)
			{
				if (q/Sp.k == (i%Sp.pk)/Sp.k)
				{
					pscore -= (1-Sp.d[schedule[i]-1][schedule[rowi+q]-1]);
				}
				else
				{
					pscore -= Sp.c*Sp.d[schedule[i]-1][schedule[rowi+q]-1];
				}
				if (q/Sp.k == (j%Sp.pk)/Sp.k)
				{
					pscore -= (1-Sp.d[schedule[j]-1][schedule[rowj+q]-1]);
				}
				else
				{
					pscore -= Sp.c*Sp.d[schedule[j]-1][schedule[rowj+q]-1];
				}				
			}
			
			int temp = schedule[i];
			schedule[i] = schedule[j];
			schedule[j] = temp;
			
			temp= rowi;
			rowi = rowj;
			rowj = temp;

			for (int q=0; q<Sp.pk; q++)
			{
				if (q/Sp.k == (i%Sp.pk)/Sp.k)
				{
					pscore += (1-Sp.d[schedule[i]-1][schedule[rowi+q]-1]);
				}
				else
				{
					pscore += Sp.c*Sp.d[schedule[i]-1][schedule[rowi+q]-1];
				}
				if (q/Sp.k == (j%Sp.pk)/Sp.k)
				{
					pscore += (1-Sp.d[schedule[j]-1][schedule[rowj+q]-1]);
				}
				else
				{
					pscore += Sp.c*Sp.d[schedule[j]-1][schedule[rowj+q]-1];
				}				
			}
			// std::cout << pscore<<"\t"<<GetHappiness(schedule)<<"\n";			
			if (pscore != GetHappiness(schedule))
			{
				std::cout << "SWAPPING SCORE CALC INCORRECT FOR SEAPARATE\t" << GetHappiness(schedule)-pscore <<"\n";
			}
			else
			{
				std::cout << "SWAPPING correct from separate\n";
			}

			if (pscore<presentgoodness)
			{
				temp = schedule[i];
				schedule[i] = schedule[j];
				schedule[j] = temp;
			}
			else
			{
				std::cout << presentgoodness << " ";
				ShowSchedule();
				presentgoodness=GetHappiness(schedule);
			}		
		}
	}
}

void Schedule::RandomMovement()
{
	time_t time_start,presenttime;
	time (&time_start);
	int pos1,pos2;
	while (true)
	{
		pos1 = rand() % totalpapers;
		pos2 = rand() % totalpapers;
		SwapIJ(pos1,pos2);
		time (&presenttime);
		if (difftime(presenttime,time_start) > processtime + 5)
		{
			break;
		}
	}
}

int main(int argc, char *argv[])
{
	srand(time(NULL));

	char* fname= argv[1];
	std::cout <<"fname is: "<<fname<<"\n";
	Schedule n1 = Schedule(fname);
	// n1.ShowSchedule();
	// n1.NormalDFS();
	n1.RandomMovement();
	return 0;
}