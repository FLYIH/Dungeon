# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -g -Wall

# Source files
SRCS = main.cpp Dungeon.cpp Room.cpp Object.cpp Poison.cpp GameCharacter.cpp Item.cpp Skill.cpp Monster.cpp NPC.cpp Player.cpp 


# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = dungeon

# Build rule
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

# Rule to compile .cpp files into .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(EXEC)
