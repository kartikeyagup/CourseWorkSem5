#include "GameClient.h"

int main(int argc, char const *argv[])
{
	int dim;
	std::cin >> dim;
	std::string role;
	std::cin >>role;

	bool typeg = (role=="CHAOS");

	Game GameToPlay = Game(dim,typeg);

	// fprintf(stderr,"This is an error print\n");
	// printf("this is a normal print\n");

	// Game x = Game(5,0);
	GameToPlay.ShowPresent();


	fprintf(stderr,"This is another error print\n");
	// printf("this is another normal print\n");
	return 0;
}