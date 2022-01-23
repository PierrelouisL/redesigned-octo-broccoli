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
src_Map_dir = src/Map
flags =  -lsfml-graphics -lsfml-window -lsfml-system -pthread

SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:.cpp=.o)

SRC_COMBAT = $(wildcard src_combat/*.cpp)
OBJS_COMBAT = $(SRC_COMBAT:.cpp=.o)
	
SRC_MAP = $(wildcard src/Map/*.cpp)
OBJS_MAP = $(SRC_MAP:.cpp=.o)


.PHONY: all clean

all: $(OBJS) App Combat Map


$(src_dir)/%.o: $(src_dir)/%.cpp 
	$(cc) $(option) -c $< -o $@

App : $(OBJS)
	$(cc) $(option) $(OBJS) -o App $(flags)

$(src_combat_dir)/%.o: $(src_combat_dir)/%.cpp 
	$(cc) $(option) -c $< -o $@

Combat : $(OBJS_COMBAT)
	$(cc) $(option) $(OBJS_COMBAT) -o Combat $(flags)

$(src_Map_dir)/%.o: $(src_Map_dir)/%.cpp 
	$(cc) $(option) -c $< -o $@

Map : $(OBJS_MAP)
	$(cc) $(option) $(OBJS_MAP) -o Map $(flags)

clean: 
	rm -rf $(OBJS) $(OBJS_MAP) App Combat Map