#include "CACEnemy.h"

CACEnemy::CACEnemy() {
	shape = new sf::RectangleShape();
	shape->setFillColor(sf::Color::Red);

	((sf::RectangleShape*)shape)->setSize({5,5});
}