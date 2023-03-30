#include "dossier_test/boids.hpp"
#include <stdlib.h>
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "p6/p6.h"

// Boids::Boids():m_pos(glm::vec2{0.,0.}), m_color(glm::vec3{1.,1.,1.}), m_size(0.2){}

// Boids::Boids(glm::vec2 pos, glm::vec3 color, float size):m_pos(pos), m_color(color), m_size(size){}

Boids::Boids(float aspect_ratio)
    : m_pos(glm::vec2{p6::random::number(-aspect_ratio, aspect_ratio), p6::random::number(-1, 1)}), m_color(glm::vec3{p6::random::number(0, 1), p6::random::number(0, 1), p6::random::number(0, 1)}), m_size(0.02), 
    m_speed(p6::random::number(0., 0.02), p6::random::number(0., 0.02)), m_aspect_ratio(aspect_ratio)
{}

void Boids::drawBoids(p6::Context& ctx, p6::Radius radius) const
{
    ctx.fill = {this->m_color.x, this->m_color.y, this->m_color.z};
    ctx.circle(p6::Center{this->m_pos.x, this->m_pos.y}, p6::Radius(radius));
    ctx.use_stroke = false;
}

void Boids::updateBoids(std::vector<Boids>& boids_tab, float sRadius, float cRadius, float aRadius)
{

    for (auto& elem : boids_tab)
    {
               elem.alignmentBoids(boids_tab, aRadius); 
               elem.separationBoids(boids_tab, sRadius);

        elem.cohesionBoids(boids_tab, cRadius);
        
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

    
}



void Boids::separationBoids(std::vector<Boids>& boids_tab, float sRadius)
{
    
    glm::vec2 new_displacement{0.0f, 0.0f};

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
            count++;
        }
    }

    if (count > 0)
    {
        new_displacement /= count;// pour gérer par rapport à tous les éléments autours


        if (length(new_displacement)>m_max_force){
            new_displacement = glm::normalize(new_displacement)*m_max_force;//normalise pour avoir que la direction
        }

        m_speed = new_displacement;

    }
}

void Boids::cohesionBoids(std::vector<Boids>& boids_tab, float cRadius)
{
    glm::vec2 new_position{0.0f, 0.0f};
    float     cohesion_weight = 0.5f;
    int count = 0;

    for (auto& elem : boids_tab)
    {
        if (&elem == this)
            continue;

        float distance = glm::length(elem.m_pos - this->m_pos);

        if (distance < cRadius)
        {
            new_position += (elem.m_pos -m_pos)* cohesion_weight;
            count++;
        }
    }

    if (count > 0)
    {
        new_position /= count;

        if (length(new_position)>m_max_force){
            new_position = glm::normalize(new_position)*m_max_force;
        }

        m_speed += (new_position)*m_max_force;
    }
}

void Boids::alignmentBoids(std::vector<Boids>& boids_tab, float aRadius)
{
    glm::vec2 new_velocity{0.0f, 0.0f};
    int count = 0;

    for (auto& elem : boids_tab)
     {
       const float distance = glm::length(elem.m_pos - this->m_pos);

        if (distance < aRadius)
        {
            new_velocity += elem.m_speed;
            count++;
        }
    }

    if (count > 0)
    {
        new_velocity /= count;

        if(length(new_velocity)>m_max_force){
            new_velocity = glm::normalize(new_velocity);
            m_speed            = new_velocity * this->m_speed_max;
        }
    }
}
