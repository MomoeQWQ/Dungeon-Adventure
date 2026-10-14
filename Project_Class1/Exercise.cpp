#include <iostream>
#include "GamesEngineeringBase.h" //include the GamesEngineeringBase header


int main() {

    // Create a canvas window with dimensions 1024x768 and title “Tiles"
    GamesEngineeringBase::Window canvas;
    canvas.create(1024, 768, "Tiles");
    bool running = true; // Variable to control the main loop's running state.

    while (running)
    {
        // Check for input (key presses or window events)
        if (canvas.keyPressed(VK_ESCAPE)) break;

        // Clear the window for the next frame rendering
        canvas.clear();
        // Update game logic
        // Clear the entire canvas with a blue background (RGB: 0, 0, 255)
        for (unsigned int i = 0; i < (canvas.getWidth() * canvas.getHeight()); i++)
        {
            canvas.draw(i, 0, 0, 255); // Drawing the blue background pixel by pixel.
        }
        // Draw()-->Draw a white line at center        
        for (int i = 0; i < 768; i++)
        {
            canvas.draw(512, i, 255, 255, 255);
        }

        // Display the frame on the screen. This must be called once the frame is finished in order to display the frame.
        canvas.present();
    }
    return 0;
}