#include <include/raylib-cpp.hpp> // Cpp headers that include class functionality

#include "settings.hpp" // My global variables
#include "entities/entities.hpp" // Entities include header

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    raylib::Window window(settings::screenSize.x, settings::screenSize.y, settings::title);

    window.SetState(FLAG_VSYNC_HINT); // Use V-Sync to autodetect and run at monitor refresh rate

    Player player{ { 1, 2 }, { 25, 15 }, BLUE }; // Initialise a player
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!window.ShouldClose()) {   // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------
        player.move();
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            window.ClearBackground(settings::backgroundColour);
            player.drawOutline(3);
        }
        EndDrawing();   
        //----------------------------------------------------------------------------------
    }
    
    return 0;
}
