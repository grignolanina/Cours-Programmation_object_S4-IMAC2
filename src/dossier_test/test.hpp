#pragma once

#include "p6/p6.h"


void base_function(p6::Context& ctx);
void circle_erase(p6::Context& ctx);
void circle_different_param(p6::Context& ctx);
void test_square(p6::Context& ctx, p6::Angle rotation);
void test_line(p6::Context& ctx);
void read_moussed_pressed(p6::Context& ctx);
void test_square_move(p6::Context& ctx);
void moving_rectangle(p6::Context& ctx,  glm::vec2 origin, float deplace_x, float deplace_y);
