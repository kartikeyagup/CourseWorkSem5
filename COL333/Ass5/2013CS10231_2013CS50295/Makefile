all: a.out

copy: a.out
	cp a.out ../entropy/client/a.out

resetweights:
	cp ChaosWeights.txt ../entropy/clientRon/ChaosWeights.txt
	cp OrderWeights.txt ../entropy/clientRon/OrderWeights.txt

copyall: a.out
	cp a.out ../entropy/clientKG/a.out
	cp a.out ../entropy/clientRon/a.out

debug: Game.cpp GameClient.cpp GameTree.cpp PalindromePopulation.cpp
	g++ -o debug -g Game.cpp PalindromePopulation.cpp GameTree.cpp GameClient.cpp -std=gnu++11 -O3


a.out: Game.o GameClient.o GameTree.o PalindromePopulation.o
	g++ -o a.out Game.o GameClient.o GameTree.o PalindromePopulation.o -std=gnu++11 -O3

Game.o: Game.cpp
	g++ -c Game.cpp -std=gnu++11 -O3

GameClient.o: GameClient.cpp
	g++ -c GameClient.cpp -std=gnu++11 -O3

GameTree.o: GameTree.cpp
	g++ -c GameTree.cpp -std=gnu++11 -O3

PalindromePopulation.o: PalindromePopulation.cpp
	g++ -c PalindromePopulation.cpp -std=gnu++11 -O3

clean:
	rm -rf a.out *.o debug
