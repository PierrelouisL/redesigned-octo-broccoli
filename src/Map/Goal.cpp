#include "Goal.h"

void TileGoal::display_goal(sf::RenderWindow &window, sf::Vector2f center){
	sf::Text objectif;

	TileWindow object;
	int level[] = { 0 };

	//Objectif tree
	object.load("images/Decors/arbre_hud.png", level, 1, 1);
	object.setPosition(center + sf::Vector2f(6*64, -6*64));
	
	objectif.setFont(_NiceFont);
	objectif.setOutlineThickness(2.5);
	objectif.setCharacterSize(45);
	objectif.setFillColor(sf::Color(0, 200, 100, 255));
	objectif.setPosition(center + sf::Vector2f(7*64, -6*64));
	objectif.setString(std::to_string(_nTree) + " / 31");
	
	window.draw(object);
	window.draw(objectif);

	// Objective camera
	object.load("images/Decors/camera_hud.png", level, 1, 1);
	object.setPosition(center + sf::Vector2f(6*64, -5*64));
	
	objectif.setFont(_NiceFont);
	objectif.setOutlineThickness(2.5);
	objectif.setCharacterSize(45);
	objectif.setFillColor(sf::Color(0, 200, 100, 255));
	objectif.setPosition(center + sf::Vector2f(7*64, -5*64));
	objectif.setString(std::to_string(_goalCamera) + " / 1");

	window.draw(object);
	window.draw(objectif);

	// Objectif Trump
	if(_goalTree){
		object.load("images/Decors/Trump_hud.png", level, 1, 1);
		object.setPosition(center + sf::Vector2f(4*64, -4*64));
		
		objectif.setFont(_NiceFont);
		objectif.setOutlineThickness(2.5);
		objectif.setCharacterSize(45);
		objectif.setFillColor(sf::Color(0, 200, 100, 255));
		objectif.setPosition(center + sf::Vector2f(5*64, -4*64));
		objectif.setString("Found him !");

		window.draw(object);
		window.draw(objectif);
	}
}