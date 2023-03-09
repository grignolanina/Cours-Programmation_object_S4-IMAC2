#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boids{
	private:
	glm::vec2 m_pos;
	glm::vec3 m_color;
	float m_size;
	p6::Angle m_dir;
	glm::vec2 m_speed;  //creer une classe deplacement ? pour donner le meme déplacement à des groupes de boids
	float m_aspect_ratio; // pour recup la taille de la fenetre


	public :
	// Boids();
	// Boids(glm::vec2 pos, glm::vec3 color, float size);
	explicit Boids(float aspect_ratio);

	// Boids(Boids& b); //par copie


	void drawBoids(p6::Context& ctx) const;

	void updateBoids();

	// void separationBoids(std::vector<Boids> boids);

};

