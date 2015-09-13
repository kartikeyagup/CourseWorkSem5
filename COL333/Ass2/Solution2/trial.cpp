#include <iostream>
#include <time.h>

int main()
{
	clock_t t;
	t = clock();
	float tim = (float)t/CLOCKS_PER_SEC;
	std::cout<<tim<<"\n";
	return 0;
}