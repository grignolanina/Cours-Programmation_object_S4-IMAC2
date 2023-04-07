#include "obstacle.hpp"
#include <stdlib.h>
#include "boids/obstacle.hpp"
#include "glm/fwd.hpp"
#include "p6/p6.h"


Obstacle::Obstacle():
m_pos(glm::vec2(0., 0.)),
m_color(glm::vec3(1., 1., 1.)),
m_size(0.02),
m_speed(0.02)
{
}

Obstacle::Obstacle(glm::vec2 pos, glm::vec3 color, float size, glm::vec2 speed):
m_pos(pos),
m_color(color),
m_size(size),
{
}


Obstacle::Obstacle(float aspectRatio)
    : 
    m_pos(glm::vec2{p6::random::number(-aspectRatio, aspectRatio), p6::random::number(-1, 1)}), 
    m_color(glm::vec3{p6::random::number(0, 1), p6::random::number(0, 1), p6::random::number(0, 1)}), 
    // m_color(glm::vec3{0., 0., 1.}), 
    m_size(0.02), 
    m_speed(p6::random::number(0., 0.02), p6::random::number(0., 0.02))
{
}