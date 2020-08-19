CXX = g++
CXXFLAGS = -std=c++11 -pedantic

treasure-quest.exe : main.o menu.o Board.o Space.o Player.o
	$(CXX) $(CXXFLAGS) -o treasure-quest.exe main.o menu.o Board.o Space.o Player.o

clean :
	rm *.o treasure-quest.exe