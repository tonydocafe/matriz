
EXEC = programa_matriz


CXX = g++
CXXFLAGS = -std=c++17 -Wall

SRCS = main.cpp Matriz.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(EXEC)


$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(EXEC)

