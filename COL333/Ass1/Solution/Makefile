all: Main.exe

Run: Main.exe
	./Main.exe $(in) $(out)

Main.exe: Main.o TimeTable.o Schedule.o
	g++ -o Main.exe Schedule.o TimeTable.o Main.o

Main.o: Main.cpp
	g++ -c Main.cpp

Schedule.o: Schedule.cpp
	g++ -c Schedule.cpp

TimeTable.o: TimeTable.cpp
	g++ -c TimeTable.cpp

clean:
	rm -rf *.o
	rm -rf *.exe