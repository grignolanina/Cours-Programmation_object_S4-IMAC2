#pragma once

#include "glm/fwd.hpp"
#include "p6/p6.h"

class Boid{
	private:
	glm::vec2 m_pos;
	glm::vec3 m_color;
	float m_size;
	glm::vec2 m_speed;
	float m_aspect_ratio;
	

	public :
	/// \brief default constructor
	// Boid();

	/// \brief constructor random
	/// \param aspect_ratio window ratio
	explicit Boid(float aspect_ratio);

	/// \brief destructor
	// ~Boid();


	//constructeur classique et fonction libre qui met random
	//add par defaut
	//destructeur

	/// \brief draw boid in p6 window
	/// \param ctx the p6 context of creation
	void drawBoid(p6::Context& ctx) const;

	/// \brief update behavior and position of all boids in the tab
	/// \param boidsTab tab of boids
	/// \param sRadius radius of separation
	/// \param cRadius radius of cohesion
	/// \param aRadius radius of alignement
	void updateBoid(std::vector<Boid>& boidsTab, float sRadius, float cRadius, float aRadius);

	/// \brief verify if the boids stay in the windows
	void stayInWindows();

	/// \brief update behavior and position of all boids in the tab
	/// \param boidsTab tab of boids
	/// \param sRadius radius of separation
	void separationBoids(std::vector<Boid>& boidsTab, float sRadius);

	/// \brief update behavior and position of all boids in the tab
	/// \param boidsTab tab of boids
	/// \param cRadius radius of cohesion
	void cohesionBoids(std::vector<Boid>& boidsTab, float cRadius);

	/// \brief update behavior and position of all boids in the tab
	/// \param boidsTab tab of boids
	/// \param aRadius radius of alignement
	void alignmentBoids(std::vector<Boid>& boidsTab, float aRadius);

};

