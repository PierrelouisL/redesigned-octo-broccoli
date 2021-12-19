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
src_combat_dir = src_combat
flags =  -lsfml-graphics -lsfml-window -lsfml-system

SRC = $(wildcard src/*.cpp)
OBJS = $(SRC:.cpp=.o)

SRC_COMBAT = $(wildcard src_combat/*.cpp)
OBJS_COMBAT = $(SRC_COMBAT:.cpp=.o)

.PHONY: all clean

all: $(OBJS) App Combat

clean: 
	rm -rf $(OBJS) $(OBJS_COMBAT) App Combat

$(src_dir)/%.o: $(src_dir)/%.cpp 
	$(cc) $(option) -c $< -o $@

App : $(OBJS)
	$(cc) $(option) $(OBJS) -o App $(flags)


$(src_combat_dir)/%.o: $(src_combat_dir)/%.cpp 
	$(cc) $(option) -c $< -o $@

Combat : $(OBJS_COMBAT)
	$(cc) $(option) $(OBJS_COMBAT) -o Combat $(flags)
