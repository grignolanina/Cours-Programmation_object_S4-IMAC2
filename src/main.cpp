#include <stdlib.h>
#include "glm/fwd.hpp"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "dossier_test/test.hpp"
#include "dossier_test/boids.hpp"
#include <vector>

// constexpr int FLOAT_MIN = 0;
// constexpr int FLOAT_MAX = 1;


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


    std::vector<Boids> boids_tab;
    for(int i = 0; i<20; i++){
        Boids T(ctx.aspect_ratio());
        boids_tab.push_back(T);
    }



    ctx.update = [&](){
        ctx.background(p6::NamedColor::White);

        for(int i = 0; i<20; i++){
            boids_tab[i].drawBoids(ctx);
            boids_tab[i].updateBoids();
        }
        
    };


    

    


    

    // Should be done last. It starts the infinite loop.
    ctx.start();
}

TEST_CASE("Addition is commutative")
{
    CHECK(1 + 2 == 2 + 1);
    CHECK(4 + 7 == 7 + 4);
}