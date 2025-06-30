CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g
RM = rm -f
PATH_SEPARATOR = /
TARGET = hr_system
TARGET_EXT = $(TARGET)

ifeq ($(OS),Windows_NT)
  RM = del /q
  PATH_SEPARATOR = \\
  TARGET_EXT = $(if $(findstring .exe,$(TARGET)), $(TARGET), $(TARGET).exe)
endif

SRCS = \
  main$(PATH_SEPARATOR)src$(PATH_SEPARATOR)main.cpp \
  main$(PATH_SEPARATOR)src$(PATH_SEPARATOR)model$(PATH_SEPARATOR)Candidate.cpp \
  main$(PATH_SEPARATOR)src$(PATH_SEPARATOR)menu$(PATH_SEPARATOR)Menu.cpp \
  libs$(PATH_SEPARATOR)util$(PATH_SEPARATOR)src$(PATH_SEPARATOR)StringUtils.cpp \
  libs$(PATH_SEPARATOR)util$(PATH_SEPARATOR)src$(PATH_SEPARATOR)FileManager.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET_EXT)

$(TARGET_EXT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(TARGET_EXT)

.PHONY: all clean
