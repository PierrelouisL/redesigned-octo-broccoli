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
option = -Wall
src_dir = src
flags =  -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:.cpp=.o)


.PHONY: all clean

all: $(OBJS) App

clean: 
	rm -rf $(OBJS) App

$(src_dir)/%.o: $(src_dir)/%.cpp 
	$(cc) $(option) -c $< -o $@

App : $(OBJS)
	$(cc) $(option) $(OBJS) -o App $(flags)


