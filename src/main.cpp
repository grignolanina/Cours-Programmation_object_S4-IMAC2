#include <stdlib.h>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "dossier_test/test.hpp"
#include "dossier_test/boids.hpp"

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "Projet-Programmation_objet_IMAC2"}};
    // p6::Angle rotation = 0.011_turn;
    ctx.maximize_window();

    // Declare your infinite update loop. == fonction de base
    // ctx.update = [&]() {
    //     ctx.background(p6::NamedColor::Blue);
    //     ctx.circle(
    //         p6::Center{ctx.mouse()},
    //         p6::Radius{0.2f}
    //     );
    // };
    //base_function(ctx);


    /***********TP1***********/
    //couleurs changees
    // circle_erase(ctx);

    //changement de param
    // circle_different_param(ctx);  

    //square
    //test_square(ctx, rotation);

    //line
    // test_line(ctx);

    //react mouse pressed
    // read_moussed_pressed(ctx);
    // draw_rectangle(ctx);


    // test_square_move(ctx);
    glm::vec2 P = glm::vec2{0., 0.};

    ctx.update = [&](){
        ctx.background(p6::NamedColor::Red);

      

        // Boids b = Boids(P, 0.3);
        draw_boids(ctx, P, 0.3);
        P+=0.01;

        
        
    };


    

    


    

    // Should be done last. It starts the infinite loop.
    ctx.start();
}

TEST_CASE("Addition is commutative")
{
    CHECK(1 + 2 == 2 + 1);
    CHECK(4 + 7 == 7 + 4);
}