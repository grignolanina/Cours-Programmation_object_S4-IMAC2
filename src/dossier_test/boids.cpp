#include "dossier_test/boids.hpp"
#include <corecrt_math.h>
#include <stdlib.h>
#include <vcruntime.h>
#include "glm/fwd.hpp"
#include "p6/p6.h"


// Boids::Boids():m_pos(glm::vec2{0.,0.}), m_color(glm::vec3{1.,1.,1.}), m_size(0.2){}

// Boids::Boids(glm::vec2 pos, glm::vec3 color, float size):m_pos(pos), m_color(color), m_size(size){}

Boids::Boids(float aspect_ratio): 
	m_pos(glm::vec2{p6::random::number(-aspect_ratio,aspect_ratio), p6::random::number(-1,1)}),
	m_color(glm::vec3{p6::random::number(0,1),p6::random::number(0,1),p6::random::number(0,1)}),
	m_size(0.05),
	m_dir(glm::vec2(p6::random::number(-aspect_ratio,aspect_ratio), p6::random::number(-aspect_ratio,aspect_ratio))),
	m_speed(p6::random::number(0., 0.02), p6::random::number(0., 0.02)),
	m_aspect_ratio(aspect_ratio)
{}


// Boids::Boids(Boids& b):m_pos(b.m_pos), m_color(b.m_color), m_size(b.m_size){}



void Boids::drawBoids(p6::Context& ctx) const{
	ctx.fill = {this->m_color.x, this->m_color.y, this->m_color.z};
	ctx.square(p6::Center{this->m_pos.x, this->m_pos.y}, p6::Radius(this->m_size));
	ctx.use_stroke = false;
}

void Boids::updateBoids(){
	glm::vec2 displacement = p6::rotated_by(m_dir, m_speed);
	m_pos += displacement;
	if(abs(m_pos.x)>m_aspect_ratio){
		m_pos.x *= -1;
	}
	if(abs(m_pos.y)>m_aspect_ratio){
		m_pos.y *= -1;
	}
}

// void Boids::separationBoids(std::vector<Boids> boids){
// 	float perceptionRadius = 0.05;
// 	glm::vec2 direction = glm::vec2();
// 	int count ;
// 	for(auto& elem : boids){
// 		float distance = sqrt((this->m_pos.x-elem.m_pos.x)*(this->m_pos.x-elem.m_pos.x)+(this->m_pos.y-elem.m_pos.y)*(this->m_pos.y-elem.m_pos.y));
// 		//elem pas ok
// 		// if(elem != this && distance < perceptionRadius){
// 		// 	float difference = 
// 		// }

// 	}

// }