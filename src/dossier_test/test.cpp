#include "dossier_test/test.hpp"
#include <stdlib.h>
#include "p6/p6.h"


void base_function(p6::Context& ctx)
{
    ctx.update = [&]() {
        ctx.background(p6::NamedColor::Blue);
        ctx.circle(
            p6::Center{ctx.mouse()},
            p6::Radius{0.2f}
        );
    };
}

void circle_erase(p6::Context& ctx)
{
    ctx.update = [&]() {
        // Clear the background with a fading effect
        ctx.use_stroke = false;
        ctx.fill       = {0.2f, 0.1f, 0.3f, 0.1f};
        ctx.rectangle(p6::FullScreen{});
        // Draw something
        ctx.fill = {1.f, 0.7f, 0.2f};
        ctx.circle(p6::Center{ctx.mouse()}, p6::Radius{0.3f});
    };
}

void circle_different_param(p6::Context& ctx)
{
    ctx.fill   = {1, 1, 1}; // White
    ctx.stroke = {0, 0, 0}; // Black
    //=> ces couleurs sont appliques sur tout le reste des elem
    ctx.stroke_weight = 0.1f;
    ctx.background({0, 1, 1}); // Cyan

    ctx.use_fill   = true;
    ctx.use_stroke = true;
    ctx.circle(p6::Center{-0.5f, 0.5f}, p6::Radius{0.5f});
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.circle(p6::Center{0.5f, 0.5f}, p6::Radius{0.5f});
    ctx.use_fill   = true;
    ctx.use_stroke = true;
    ctx.circle(p6::Center{-0.5f, -0.5f}, p6::Radius{0.5f});
}

void first_rectangle(p6::Context& ctx)
{
    ctx.fill   = {1, 1, 1}; // White
    ctx.stroke = {0, 0, 0}; // Black
    //=> ces couleurs sont appliques sur tout le reste des elem
    ctx.stroke_weight = 0.1f;
    ctx.background({0, 1, 1}); // Cyan

    ctx.use_fill   = true;
    ctx.use_stroke = true;
    ctx.circle(p6::Center{-0.5f, 0.5f}, p6::Radius{0.5f});
    ctx.use_fill   = false;
    ctx.use_stroke = true;
    ctx.circle(p6::Center{0.5f, 0.5f}, p6::Radius{0.5f});
    ctx.use_fill   = true;
    ctx.use_stroke = true;
    ctx.circle(p6::Center{-0.5f, -0.5f}, p6::Radius{0.5f});
}

void test_square(p6::Context& ctx, p6::Angle rotation)
{
    ctx.update = [&]() {
        ctx.background({0.4f, 0.6f, 0.1f});
        ctx.stroke = {1, 1, 1, 1};
        // ctx.use_stroke = false; //pour annuler les contours
        ctx.square(p6::Center{0.f, 0.f}, p6::Radius{0.3f}, p6::Rotation{rotation});
    };
}

void test_line(p6::Context& ctx)
{
    ctx.update = [&]() {
        ctx.background({});
        ctx.stroke        = p6::Color{0.7f, 0.1f, 0.1f};
        ctx.stroke_weight = 0.1f;
        ctx.line(glm::vec2{0.f}, ctx.mouse());
    };
}

void read_moussed_pressed(p6::Context& ctx)
{
    ctx.mouse_pressed = [&](p6::MouseButton button) {
        if (button.button == p6::Button::Right)
        {
            ctx.background(p6::Color(0.5f, 0.2f, 0.1f));
        }
        else if (button.button == p6::Button::Left)
        {
            ctx.background(p6::Color{0.1f, 0.9f, 0.1f});
        }
        else
        {
            ctx.background(p6::Color{0.f, 0.f, 0.f});
        }
    };
}



// void moving_rectangle(p6::Context& ctx,  glm::vec2 origin){
// 	ctx.stroke = {1, 1, 1, 1};
// 	ctx.square(p6::Center{origin}, p6::Radius{0.6f});
// 	ctx.
// }

// void test_square_move(p6::Context& ctx)
// {
//     ctx.push_transform(); // Push 1
//     ctx.translate({0.5f, 0.f});
//     ctx.push_transform(); // Push 2
//     ctx.rotate(0.1_turn);
//     ctx.pop_transform(); // Goes back to the Push 2, i.e. undoes the `rotate()`
//     ctx.pop_transform();
// }