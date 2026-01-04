CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude

SRC = \
src/main.cpp \
src/allocator/allocator.cpp \
src/buddy/buddy_allocator.cpp \
src/stats/statistics.cpp \
src/cache/cache.cpp \
src/cache/multilevel_cache.cpp \


OBJ = $(SRC:.cpp=.o)

TARGET = memsim

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)

