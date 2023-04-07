#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

class Obstacle{
	private : 
	glm::vec2 m_pos;
	glm::vec2 m_color;
	float m_size;

	public:
	Obstacle();
	Obstacle(glm::vec2 pos, glm::vec3 color, float size);
	explicit Obstacle(float aspecRatio);
}