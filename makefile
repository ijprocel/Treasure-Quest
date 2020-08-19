CXX = g++
CXXFLAGS = -std=c++11 -pedantic

final : main.o menu.o Board.o Space.o Player.o
	$(CXX) $(CXXFLAGS) -o final main.o menu.o Board.o Space.o Player.o

clean :
	rm *.o final