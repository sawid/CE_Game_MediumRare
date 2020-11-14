#pragma once
#include "SFML/Graphics.hpp"

class Collider
{
public:
	Collider(sf::RectangleShape& body);
	~Collider();

	void Move(float dx, float dy) { body.move(dx, dy); }

	bool CheckCollision(Collider& other, float push, float type, float* buttonStatus,float buttonID,int* objectStatus, int* score, float* nextObjectRequest, int* availbleStatus, int* cooldownCounter);
	sf::Vector2f GetPosition() { return body.getPosition(); }
	sf::Vector2f GetHalfSize() { return body.getSize() / 2.0f; }
private:
	sf::RectangleShape& body;

};

