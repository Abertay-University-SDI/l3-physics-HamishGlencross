#include "Sheep.h"
#include <iostream>

Sheep::Sheep()
{
	// initialise animations
	for (int i = 0; i < 4; i++)
		m_walkDown.addFrame({ { 64 * i, 0 }, { 64, 64 } });
	m_walkDown.setLooping(true);
	m_walkDown.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUp.addFrame({ { (64 * (i + 4)), 0 }, { 64, 64 } });
	m_walkUp.setLooping(true);
	m_walkUp.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkUpRight.addFrame({ { 64 * i, 64 }, { 64, 64 } });
	m_walkUpRight.setLooping(true);
	m_walkUpRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkRight.addFrame({ { (64 * (i + 4)), 64 }, { 64, 64 } });
	m_walkRight.setLooping(true);
	m_walkRight.setFrameSpeed(0.25f);

	for (int i = 0; i < 4; i++)
		m_walkDownRight.addFrame({ { 64 * i, 128 }, { 64, 64 } });
	m_walkDownRight.setLooping(true);
	m_walkDownRight.setFrameSpeed(0.25f);

	// the next 4 animations go clockwise from Up through Right to Down.

	m_currentAnimation = &m_walkDown;
	setTextureRect(m_currentAnimation->getCurrentFrame());
}

Sheep::~Sheep()
{
}

void Sheep::handleInput(float dt)
{
	sf::Vector2f inputDir = { 0, 0 };

	if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
	{
		inputDir.x = -1;
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
	{
		inputDir.x = 1;
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
	{
		inputDir.y = -1;
	}
	if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
	{
		inputDir.y = 1;
	}

	if (inputDir.lengthSquared() > 0)
	{
		inputDir = inputDir.normalized();
	}

	m_acceleration = inputDir * ACCELERATION;
	std::cout << inputDir.x << " : " << inputDir.y << std::endl;
}


void Sheep::update(float dt)
{
	checkWallAndBounce();
	
	m_velocity += m_acceleration * dt;
	m_velocity *= DRAG_FACTOR;

	//std::cout << m_velocity.x << std::endl;
	move(m_velocity);
}

void Sheep::setWorldSize(sf::Vector2f worldSize)
{
	m_worldSize = worldSize;
}

void Sheep::checkWallAndBounce()
{
	/*if (getPosition().x < 0 && m_velocity.x < 0)
	{
		m_velocity.x *= -COEFF_OF_RESTITUTION;
		std::cout << "Outside left" << std::endl;
	}
	if (getPosition().x > m_worldSize.x && m_velocity.x > 0)
	{
		m_velocity.x *= -COEFF_OF_RESTITUTION;
		std::cout << "Outside right" << std::endl;
	}
	if (getPosition().y < 0 && m_velocity.y < 0)
	{
		m_velocity.y *= -COEFF_OF_RESTITUTION;
		std::cout << "Outside top" << std::endl;
	}
	if (getPosition().y > m_worldSize.y && m_velocity.y > 0)
	{
		m_velocity.y *= -COEFF_OF_RESTITUTION;
		std::cout << "Outside bottom" << std::endl;
	}*/

	if (
		getPosition().x < 0 && m_velocity.x < 0 ||
		getPosition().x > m_worldSize.x && m_velocity.x > 0 ||
		getPosition().y < 0 && m_velocity.y < 0 ||
		getPosition().y > m_worldSize.y && m_velocity.y > 0
		)
	{
		m_velocity *= -COEFF_OF_RESTITUTION;
	}
}