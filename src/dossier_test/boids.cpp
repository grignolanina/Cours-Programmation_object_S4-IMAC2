#include "dossier_test/boids.hpp"
#include <stdlib.h>
#include "p6/p6.h"


Boids::Boids(glm::vec2 pos, float size):m_pos(pos), m_size(size){}

void draw_boids(p6::Context& ctx, glm::vec2 pos, float size){
	ctx.fill = {1., 1., 1.};
	ctx.square(p6::Center{pos.x, pos.y}, p6::Radius(size));
}