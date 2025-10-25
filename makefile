CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++14
LDFLAGS = 

# исходные файлы
SRCS := $(wildcard src/*.cpp) $(wildcard src/figures/*.cpp) $(wildcard src/array/*.cpp)
OBJS := $(SRCS:.cpp=.o)

TARGET = main

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@


	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)

build: $(TARGET)
