#include "dossier_test/boids.hpp"
// #include <corecrt_math.h>
#include <stdlib.h>
// #include <vcruntime.h>
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "p6/p6.h"

// Boids::Boids():m_pos(glm::vec2{0.,0.}), m_color(glm::vec3{1.,1.,1.}), m_size(0.2){}

// Boids::Boids(glm::vec2 pos, glm::vec3 color, float size):m_pos(pos), m_color(color), m_size(size){}

Boids::Boids(float aspect_ratio)
    : m_pos(glm::vec2{p6::random::number(-aspect_ratio, aspect_ratio), p6::random::number(-1, 1)}), m_color(glm::vec3{p6::random::number(0, 1), p6::random::number(0, 1), p6::random::number(0, 1)}), m_size(0.05), 
    // m_dir(glm::vec2(p6::random::number(-aspect_ratio, aspect_ratio), p6::random::number(-aspect_ratio, aspect_ratio))), 
    m_speed(p6::random::number(0., 0.02), p6::random::number(0., 0.02)), m_aspect_ratio(aspect_ratio)
{}

// Boids::Boids(Boids& b):m_pos(b.m_pos), m_color(b.m_color), m_size(b.m_size){}

void Boids::drawBoids(p6::Context& ctx, p6::Radius radius) const
{
    ctx.fill = {this->m_color.x, this->m_color.y, this->m_color.z};
    ctx.square(p6::Center{this->m_pos.x, this->m_pos.y}, p6::Radius(radius));
    ctx.use_stroke = false;
}

void Boids::updateBoids(std::vector<Boids>& boids_tab, float sRadius, float cRadius, float aRadius)
{
    //glm::vec2 displacement = p6::rotated_by(m_dir, m_speed);
    //m_pos += displacement;
    for (auto& elem : boids_tab)
    {
        elem.alignmentBoids(boids_tab, aRadius);
        elem.cohesionBoids(boids_tab, cRadius);
        elem.separationBoids(boids_tab, sRadius);
    }
    m_pos += m_speed;
    if(m_pos.x < -m_aspect_ratio+m_size){
        m_speed.x += 0.05;
    }
    if(m_pos.x >m_aspect_ratio-m_size){
        m_speed.x -= 0.05;
    }
    if(m_pos.y < -1+m_size){
        m_speed.y += 0.05;
    }
    if(m_pos.y > 1-m_size){
        m_speed.y -=0.05;
    }
    // if (abs(m_pos.x) >= m_aspect_ratio)
    // {
    //     // glm::normalize(m_speed)
    //     m_speed = -m_speed;
    //     // m_pos.x *= -1;
    // }
    // if (abs(m_pos.y) >= 1)
    // {
    //     // m_pos.y *= -1;
    //     m_speed = -m_speed;

    // }

    
}

// bool Boids::inWindows(){
//     if(abs(this->m_pos.x) > m_aspect_ratio){
//         return false;
//     } 
//     if(abs(this->m_pos.y) >=1) {
//         return false;
//     } 

// }

// //pour éviter les collisions
// void Boids::separationBoids(std::vector<Boids>& boids_tab){
// 	float perceptionRadius = 0.1;
// 	glm::vec2 newPos = glm::vec2();
// 	int count =0;

// 	for(auto& elem : boids_tab){
// 		float distance = sqrt((this->m_pos.x-elem.m_pos.x)*(this->m_pos.x-elem.m_pos.x)+(this->m_pos.y-elem.m_pos.y)*(this->m_pos.y-elem.m_pos.y));
// 		//elem pas ok
// 		if(&elem != this && distance < perceptionRadius){
// 			glm::vec2 difference = this->m_pos - elem.m_pos;
// 			difference = difference/((distance/perceptionRadius)*(distance/perceptionRadius));
// 			newPos = difference;
// 			count++;
// 		}

// 	}
// 	if(count > 0){
// 		this->m_pos += newPos;
// 		this->m_dir += 0.1_turn; //voir comment mieux faire varier cet angle
// 	}
// }

void Boids::separationBoids(std::vector<Boids>& boids_tab, float sRadius)
{
    // float perceptionRadius = 0.19f;
    glm::vec2 new_displacement{0.0f, 0.0f};
    //float     separation_weight = 1.f;
    // glm::vec2 new_speed(0.0f, 0.0f);
    int count = 0;

    for (auto& elem : boids_tab)
    {
        if (&elem == this)
            continue;

        float distance = glm::length(elem.m_pos - this->m_pos);

        if (distance < sRadius)
        {
            glm::vec2 difference = glm::normalize(this->m_pos-elem.m_pos);
            difference /= distance;
            new_displacement += difference;
            
            // new_speed += elem.m_speed;
            count++;
        }
    }

    if (count > 0)
    {
        new_displacement /= count;                           // pour gérer par rapport à tous les éléments autours
        //new_displacement = glm::normalize(new_displacement); // normalize pour avoir que la direction
        // new_speed /= count;

        if (length(new_displacement)>m_max_force){
            new_displacement = glm::normalize(new_displacement)*m_max_force;
        }

        m_speed = new_displacement;

        // m_speed = new_speed;
    }
}

void Boids::cohesionBoids(std::vector<Boids>& boids_tab, float cRadius)
{
    // float perceptionRadius = 0.4f;
    glm::vec2 new_displacement{0.0f, 0.0f};
    float     cohesion_weight = 0.5f;

    // float separation_weigth = 1.0f;
    int count = 0;

    for (auto& elem : boids_tab)
    {
        if (&elem == this)
            continue;

        float distance = glm::length(elem.m_pos - this->m_pos);

        if (distance < cRadius)
        {
            new_displacement += elem.m_pos * cohesion_weight;
            count++;
        }
    }

    if (count > 0)
    {
        new_displacement /= count;
        //new_displacement = new_displacement - this->m_pos;
        // new_displacement = glm::normalize(new_displacement);
        //m_speed =new_displacement * this->m_speed_max;

        if (length(new_displacement)>m_max_force){
            new_displacement = glm::normalize(new_displacement)*m_max_force;
        }

        //m_speed = new_displacement;
        m_speed = (new_displacement-m_pos)*m_max_force;
    }
}

void Boids::alignmentBoids(std::vector<Boids>& boids_tab, float aRadius)
{
    // float perceptionRadius = 0.2f;
    glm::vec2 new_displacement{0.0f, 0.0f};
    int       count = 0;

    for (auto& elem : boids_tab)
    {
        if (&elem == this)
            continue;

        float distance = glm::length(elem.m_pos - this->m_pos);

        if (distance < aRadius)
        {
            new_displacement += elem.m_speed;
            count++;
        }
    }

    if (count > 0)
    {
        new_displacement /= count;
        new_displacement = glm::normalize(new_displacement);
        m_speed            = new_displacement * this->m_speed_max;
    }
}
