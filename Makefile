#-------------------------------------------------------------------------------
#
# @File:         Makefile
#
# @Description:  Makefile 
#
# @By: Thanh-Liem TA & Pierre-Louis Lagunegrand
#
#-------------------------------------------------------------------------------

cc = g++
option = -Wall -g -std=c++11
src_dir = src
flags =  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:.cpp=.o)

.PHONY: all clean

all: $(OBJS) Map

$(src_dir)/%.o: $(src_dir)/%.cpp 
	$(cc) $(option) -c $< -o $@

Map : $(OBJS)
	$(cc) $(option) $(OBJS) -o Broccoli $(flags)

clean: 
	rm -rf $(OBJS) Broccoli