TARGET = hr_system

CXX = g++

CXXFLAGS = -Wall -Wextra -std=c++11 -g

SRCS = \
  main/src/main.cpp \
  main/src/model/Candidate.cpp \
  main/src/menu/Menu.cpp \
  libs/util/src/StringUtils.cpp \
  libs/util/src/FileManager.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
