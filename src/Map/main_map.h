#pragma once

#include <stdlib.h>
#include <SFML/Audio.hpp>
#include "Window.h"
#include "Character.h"
#include "CharacterMario.h"
#include "Map.h"
#include "Element.h"
#include "bot.h"


extern int obstacle_ville1[61][60];

typedef enum Gamemode{ normal, mario, fight } Gamemode;