CXX = g++
CXXFLAGS = -std=c++11 -Wall

all: program1 program2

program1: FirstProgram/app/First_Program.cpp FirstProgram/lib/Client.cpp FirstProgram/lib/FirstProgram.cpp utility/Utils.cpp
	$(CXX) $(CXXFLAGS) -o program1 $^

program2: SecondProgram/app/Second_Program.cpp SecondProgram/lib/SecondProgram.cpp utility/Utils.cpp SecondProgram/lib/Server.cpp
	$(CXX) $(CXXFLAGS) -o program2 $^

.PHONY: clean

clean:
	rm -f program1 program2
