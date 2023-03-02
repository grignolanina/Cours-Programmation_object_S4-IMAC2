#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boids{
	private:
	glm::vec2 m_pos;
	float m_size;


	public :
	Boids(glm::vec2 pos, float size);

	

};

void draw_boids(p6::Context& ctx, glm::vec2 pos, float size);