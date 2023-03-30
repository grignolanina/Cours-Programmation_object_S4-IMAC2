#include <stdlib.h>
#include "glm/fwd.hpp"
#include "imgui.h"
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include "dossier_test/test.hpp"
#include "dossier_test/boids.hpp"
#include <vector>


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
    ctx.maximize_window();


    std::vector<Boids> boids_tab;
    for(int i = 0; i<50; i++){
        Boids T(ctx.aspect_ratio());
        boids_tab.push_back(T);
    }

    float radius = 0.02;
    float sRadius = 0.05;
    float cRadius = 0.2;
    float aRadius = 0.1;
    int nb_boids = 20;


    ctx.update = [&](){
        ctx.background(p6::NamedColor::Black);

        ImGui::Begin("Params");
        ImGui::SliderInt("Nb boids",&nb_boids, 0, 50, "%.3f", 0 );
        ImGui::SliderFloat("Size", &radius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Separation", &sRadius, 0.f, 0.1f, "%.3f", 0); 
        ImGui::SliderFloat("Cohesion", &cRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::SliderFloat("Alignement", &aRadius, 0.f, 0.5f, "%.3f", 0); 
        ImGui::End();


        for(int i = 0; i<nb_boids; i++){
            boids_tab[i].drawBoids(ctx, radius);
            boids_tab[i].updateBoids(boids_tab, sRadius, cRadius, aRadius);
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