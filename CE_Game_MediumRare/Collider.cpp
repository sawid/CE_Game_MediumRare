#include "Collider.h"
#include <iostream>

Collider::Collider(sf::RectangleShape& body) :
	body(body)
{
}

Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider& other, float push, float type, float* buttonStatus,float buttonID,int* objectStatus,int* score,float* nextObjectRequest,int* availbleStatus,int* cooldownCounter)
{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	int *status = 0;

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);
		if (intersectX > intersectY)
		{
			if (type == 1.0f)
			{
				if (*availbleStatus == 1)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && buttonID == *nextObjectRequest)
					{
						std::cout << "ButtonStatus " << *buttonStatus << std::endl;
						if (buttonID == 0 || buttonID == 6)
						{
							*buttonStatus += 1.0f;
						}
						else if (*cooldownCounter == 0)
						{
							*buttonStatus += 1.0f;
							*cooldownCounter = 1;
						}
						else if (*cooldownCounter == 2)
						{
							*cooldownCounter = 3;
						}
						
						std::cout << "Cooldown Counter " << *cooldownCounter << std::endl;

					}
				}
				
			}
			if (type == 2.0f)
			{
				*score -= 100;
				*objectStatus = 0;
			}
			if (deltaX > 0.0f)
			{
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);
			}
			else
			{
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
			}
		}
		else
		{
			if (type == 1.0f)
			{
				if (*availbleStatus == 1)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && buttonID == *nextObjectRequest)
					{
						std::cout << "ButtonStatus " << *buttonStatus << std::endl;
						if (buttonID == 0 || buttonID == 6)
						{
							*buttonStatus += 1.0f;
						}
						else if (*cooldownCounter == 0)
						{
							*buttonStatus += 1.0f;
							*cooldownCounter = 1;
						}
						else if (*cooldownCounter == 2)
						{
							*cooldownCounter = 3;
						}


						std::cout << "Cooldown Counter " << *cooldownCounter << std::endl;

					}
				}
			}
			if (type == 2.0f)
			{
				*score -= 100;
				*objectStatus = 0;
			}
			if (deltaY > 0.0f)
			{
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f, -intersectY * push);
			}
			else
			{
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
			}
		}

		return true;
	}
	
	return false;
}
