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
	// float ans = (Sp.tp*(Sp.k)*(Sp.k-1))/2;
	double ans=0;
	for (int i=0; i<Sp.tp; i++)
	{
		for (int j=0; j<Sp.k; j++)
		{
			for (int k=j+1; k<Sp.k; k++)
			{
				// std::cout <<"this will come: " << i*Sp.k+j <<"\t" << scheduleinp[i*Sp.k+j] <<" " << scheduleinp[i*Sp.tp+k]<<"\n";
				ans += (1-Sp.d[scheduleinp[i*Sp.k+j]-1][scheduleinp[i*Sp.k+k]-1]);
				// std::cout <<"this wont come: " << j <<" " << k<<"\n";
			}
		}
	}
	// std::cout <<"done first part\n";
	
	double anst=0;
	for (int i=0; i<Sp.t; i++)
	{
		// for (int j=0;j<Sp.p;j++)
		// {
		// 	for (int k=0;k<Sp.k;k++)
		// 	{
		// 		for (int l=i*Sp.pk+(j+1)*Sp.k;l<(1+i)*Sp.pk;l++)
		// 		{
		// 			anst += Sp.d[scheduleinp[l]-1][scheduleinp[i*Sp.pk + j*Sp.k + k]-1];
		// 		}
		// 	}
		// 	// for (int k=(1+i)*Sp.k;k<totalpapers;k++)
		// 	// {
		// 	// 	anst += Sp.d[scheduleinp[Sp.k*i+j]-1][scheduleinp[k]-1];
		// 	// }
		// }

		for (int j=0; j<Sp.pk; j++)
		{
			for (int k=(Sp.k)*(1+j/Sp.p);k<Sp.pk; k++)
			{
				anst += Sp.d[scheduleinp[i*Sp.pk+j]-1][scheduleinp[i*Sp.pk+k]-1];
			}
		}		
	}
	anst *= Sp.c;
	return ans+anst;
}


float Schedule::GetHappiness2(int *scheduleinp)
{
	// float ans = (Sp.tp*(Sp.k)*(Sp.k-1))/2;
	double ans=0;
	for (int i=0; i<Sp.tp; i++)
	{
		for (int j=0; j<Sp.k; j++)
		{
			for (int k=j+1; k<Sp.k; k++)
			{
				// std::cout <<"this will come: " << i*Sp.k+j <<"\t" << scheduleinp[i*Sp.k+j] <<" " << scheduleinp[i*Sp.tp+k]<<"\n";
				ans += (1-Sp.d[scheduleinp[i*Sp.k+j]-1][scheduleinp[i*Sp.k+k]-1]);
				// std::cout <<"this wont come: " << j <<" " << k<<"\n";
			}
		}
	}
	// std::cout <<"done first part\n";
	
	double anst=0;
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
}

double Schedule::SwapIJ(int i,int j)
{
	if (i/Sp.k != j/Sp.k)
	{
		if (i/Sp.pk == j/ Sp.pk)
		{
			// Same time slot swapping
			double pscore = presentgoodness;
			for (int q=0; q<Sp.k; q++)
			{
				pscore += (Sp.d[schedule[i]-1][schedule[Sp.k*(i/Sp.k) + q]-1]);
				pscore += (Sp.d[schedule[j]-1][schedule[Sp.k*(j/Sp.k) + q]-1]);
				
				pscore -= Sp.c*Sp.d[schedule[i]-1][schedule[Sp.k*(j/Sp.k) +q] -1];
				pscore -= Sp.c*Sp.d[schedule[j]-1][schedule[Sp.k*(i/Sp.k) +q] -1];
			}

			int temp = schedule[i];
			schedule[i] = schedule[j];
			schedule[j]= temp;

			for (int q=0; q<Sp.k;q++)
			{	
				pscore -= (Sp.d[schedule[i]-1][schedule[Sp.k*(i/Sp.k) + q]-1]);
				pscore -= (Sp.d[schedule[j]-1][schedule[Sp.k*(j/Sp.k) + q]-1]);
				
				pscore += Sp.c*Sp.d[schedule[i]-1][schedule[Sp.k*(j/Sp.k) +q] -1];
				pscore += Sp.c*Sp.d[schedule[j]-1][schedule[Sp.k*(i/Sp.k) +q] -1];
			}

			// std::cout << pscore<<"\t"<<GetHappiness(schedule)<<"\n";
			// if (pscore != GetHappiness(schedule))
			// {
			// 	std::cout << "SWAPPING SCORE CALC INCORRECT FOR SAME\t" << GetHappiness(schedule)<<"\t"<<GetHappiness2(schedule) <<"\n";
			// }

			// if (pscore<presentgoodness)
			// {
				temp = schedule[i];
				schedule[i] = schedule[j];
				schedule[j] = temp;
				return pscore;
			// }
			// else
			// {
			// 	std::cout << presentgoodness << " ";
			// 	ShowSchedule();
			// 	presentgoodness=pscore;
			// }

		}
		else
		{
			double pscore = presentgoodness;
			for (int q=0; q<Sp.pk; q++)
			{
				if (q/Sp.k == (i%Sp.pk)/Sp.k)
				{
					pscore += (Sp.d[schedule[i]-1][schedule[Sp.pk*(i/Sp.pk) + q]-1]);
				}
				else
				{
					pscore -= Sp.c*Sp.d[schedule[i]-1][schedule[Sp.pk*(i/Sp.pk) +q]-1];
				}

				if (q/Sp.k == (j%Sp.pk)/Sp.k)
				{
					pscore += (Sp.d[schedule[j]-1][schedule[Sp.pk*(j/Sp.pk) + q]-1]);
				}
				else
				{
					pscore -= Sp.c*Sp.d[schedule[j]-1][schedule[Sp.pk*(j/Sp.pk) +q]-1];
				}
			}

			int t1 = schedule[i];
			schedule[i] = schedule[j];
			schedule[j] = t1;

			for (int q=0; q<Sp.pk ; q++)
			{
				if (q/Sp.k == (i%Sp.pk)/Sp.k)
				{
					pscore -= (Sp.d[schedule[i]-1][schedule[Sp.pk*(i/Sp.pk) + q]-1]);
				}
				else
				{
					pscore += Sp.c*Sp.d[schedule[i]-1][schedule[Sp.pk*(i/Sp.pk) +q]-1];
				}

				if (q/Sp.k == (j%Sp.pk)/Sp.k)
				{
					pscore -= (Sp.d[schedule[j]-1][schedule[Sp.pk*(j/Sp.pk) + q]-1]);
				}
				else
				{
					pscore += Sp.c*Sp.d[schedule[j]-1][schedule[Sp.pk*(j/Sp.pk) +q]-1];
				}	
			}

			// if (pscore != GetHappiness(schedule))
			// {
			// 	std::cout <<" NOT MATCHING " << pscore << "\t" << GetHappiness(schedule) <<"\n"; 
			// }
			// // Different time slot swapping
			// double pscore = presentgoodness;
			// int rowi = (i/Sp.pk)*Sp.pk;
			// int rowj = (j/Sp.pk)*Sp.pk;
			// for (int q=0; q<Sp.pk; q++)
			// {
			// 	if (q/Sp.k == (i%Sp.pk)/Sp.k)
			// 	{
			// 		pscore -= (1-Sp.d[schedule[i]-1][schedule[rowi+q]-1]);
			// 	}
			// 	else
			// 	{
			// 		pscore -= Sp.c*Sp.d[schedule[i]-1][schedule[rowi+q]-1];
			// 	}

			// 	if (q/Sp.k == (j%Sp.pk)/Sp.k)
			// 	{
			// 		pscore -= (1-Sp.d[schedule[j]-1][schedule[rowj+q]-1]);
			// 	}
			// 	else
			// 	{
			// 		pscore -= Sp.c*Sp.d[schedule[j]-1][schedule[rowj+q]-1];
			// 	}				
			// }
			
			// int temp = schedule[i];
			// schedule[i] = schedule[j];
			// schedule[j] = temp;
			
			// temp= rowi;
			// rowi = rowj;
			// rowj = temp;

			// for (int q=0; q<Sp.pk; q++)
			// {
			// 	if (q/Sp.k == (i%Sp.pk)/Sp.k)
			// 	{
			// 		pscore += (1-Sp.d[schedule[i]-1][schedule[rowi+q]-1]);
			// 	}
			// 	else
			// 	{
			// 		pscore += Sp.c*Sp.d[schedule[i]-1][schedule[rowi+q]-1];
			// 	}

			// 	if (q/Sp.k == (j%Sp.pk)/Sp.k)
			// 	{
			// 		pscore += (1-Sp.d[schedule[j]-1][schedule[rowj+q]-1]);
			// 	}
			// 	else
			// 	{
			// 		pscore += Sp.c*Sp.d[schedule[j]-1][schedule[rowj+q]-1];
			// 	}				
			// }
			// // std::cout << pscore<<"\t"<<GetHappiness(schedule)<<"\n";			
			// if (pscore != GetHappiness(schedule))
			// {
				// std::cout << "SWAPPING SCORE CALC \t" << GetHappiness(schedule)<<"\t" << pscore <<"\n";
			// }
			// else
			// {
			// 	std::cout << "SWAPPING correct from separate\n";
			// }

			// if (pscore<presentgoodness)
			// {
				int temp = schedule[i];
				schedule[i] = schedule[j];
				schedule[j] = temp;
				return pscore;
			// }
			// else
			// {
			// 	std::cout << presentgoodness << " ";
			// 	ShowSchedule();
			// 	presentgoodness=GetHappiness(schedule);
			// }		
		}
	}
}

void Schedule::RandomMovement()
{
	std::cout << "Starting random movements\n";
	time_t time_start,presenttime;
	time (&time_start);
	int pos1,pos2;
	double res;
	std::cout <<"starting happiness value: " << presentgoodness<<"\n";
	while (true)
	{
		pos1 = rand() % totalpapers;
		pos2 = rand() % totalpapers;
		res=SwapIJ(pos1,pos2);
		if (res>presentgoodness)
		{
			int temp= schedule[pos1];
			schedule[pos1]=schedule[pos2];
			schedule[pos2]=temp;
			presentgoodness=res;
			// std::cout << "Happiness increased to: " << presentgoodness<<"\n";
		}
		time (&presenttime);
		if (difftime(presenttime,time_start) > processtime + 5)
		{
			break;
		}
	}
}

void Schedule::LocalSearch()
{
	time_t time_start,presenttime;
	time (&time_start);
	// int pos1,pos2;
	double resbestsofar,tempres;
	int bestpos1,bestpos2,tempst;
	while (true)
	{
		bestpos1=0;
		bestpos2=0;
		resbestsofar=presentgoodness;
		for (int pos1=0; pos1<totalpapers;pos1++)
		{
			for (int pos2=pos1+1;pos2<totalpapers; pos2++)
			{
				tempres = SwapIJ(pos1,pos2);
				if (tempres>resbestsofar)
				{
					resbestsofar=tempres;
					bestpos1=pos1;
					bestpos2=pos2;
				}
			}
		}
		tempst= schedule[bestpos1];
		schedule[bestpos1]=schedule[bestpos2];
		schedule[bestpos2]=tempst;
		if (resbestsofar>presentgoodness)
		{
			std::cout << "Improved to: " << resbestsofar <<"\n";
		}
		presentgoodness=resbestsofar;
		time (&presenttime);
		if (difftime(presenttime,time_start) > processtime + 5)
		{
			break;
		}	
	}
}

void Schedule::ShowScore()
{
	std::cout << "Final happiness: " << presentgoodness <<"\n";
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
	// n1.LocalSearch();
	n1.ShowScore();
	n1.ShowSchedule();
	return 0;
}