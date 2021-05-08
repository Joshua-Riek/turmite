#include <SFML/Graphics.hpp>
#include <thread>
#include <random>
#include <iostream>
#include "PixelArray.h"
#include "World.h"
#include "Turmite.h"
#include "CmdParser.h"

void updateThread(Turmite *turmite, bool wrap, float delay);
bool quit = false;

int main(int argc, const char *argv[])
{
    int scale = 8;
    int offset = 0;
    int width = 1024;
    int height = 1024;
    float delay = 0.006f;
    bool help = false;
    bool wrap = false;
    std::string rule;
    std::string color;

    // Add arguments to the parser
    CmdParser parser(argc, argv);
    parser.addArgument({"-h", "--help"}, &help, "Display help information", false);
    parser.addArgument({"-w", "--wrap"}, &wrap, "Wrap turmite around window edges", false);
    parser.addArgument({"-r", "--rule"}, &rule, "Specify the turn rule", false, "<rule>");
    parser.addArgument({"-d", "--delay"}, &delay, "Seconds between turmite steps", false, "<delay>");
    parser.addArgument({"-c", "--color"}, &color, "Primary color of the turmite", false, "<color>");
    parser.addArgument({"-s", "--scale"}, &scale, "Size of each cell", false, "<scale>");
    parser.addArgument({"-o", "--offset"}, &offset, "Spacing between cells", false, "<offset>");
    parser.addArgument({"-x", "--width"}, &width, "Window width in pixels", false, "<width>");
    parser.addArgument({"-y", "--height"}, &height, "Window height in pixels", false, "<height>");

    // Parse through the arguments
    try {
        parser.parse();
    } catch (std::runtime_error const &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    // Display help information
    if (help) {
        parser.help();
        return 1;
    }

    // Initialize random seed
    std::mt19937 seed(time(nullptr));

    // Set a random rule if one is not given
    if (rule.empty())
    {
        // Set a range for random number distribution
        std::uniform_int_distribution<> range(0, 44);

        // Set the rule to one of the examples
        rule = turmiteExampleRules[range(seed)];
    }

    // Set a random color if one is not given
    if (color.empty())
    {
        // Set a range for random number distribution
        std::uniform_int_distribution<> range(0, 5);

        // Random default colors
        std::string colors[] = {"white", "green", "blue", "yellow", "magenta", "cyan"};

        // Set the color to one of the defaults
        color = colors[range(seed)];
    }

    // Make sure the color is valid
    sf::Color sfColor;
    if (color == "black")
        sfColor = sf::Color::Black;
    else if (color == "white")
        sfColor = sf::Color::White;
    else if (color == "red")
        sfColor = sf::Color::Red;
    else if (color == "green")
        sfColor = sf::Color::Green;
    else if (color == "blue")
        sfColor = sf::Color::Blue;
    else if (color == "yellow")
        sfColor = sf::Color::Yellow;
    else if (color == "magenta")
        sfColor = sf::Color::Magenta;
    else if (color == "cyan")
        sfColor = sf::Color::Cyan;
    else
        throw std::runtime_error("error: invalid color: " + color);

    // Create the window
    sf::RenderWindow window(sf::VideoMode(width, height), "Turmites");

    // Create the world of cells
    World world(width, height, scale, offset, sfColor);

    // Create a single turmite
    Turmite turmite(&world, rule, world.getRows() / 2, world.getColumns() / 2, 0);

    // Spawn the thread to update cells each tick
    std::thread thread(&updateThread, &turmite, wrap, delay);

    // Set the framerate limit
    window.setFramerateLimit(60);

    // Run while the window is open
    while (window.isOpen())
    {
        sf::Event event{};

        // while there are pending events
        while (window.pollEvent(event))
        {
            // Close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Draw the world to the screen
        world.draw(window);

        // End the current frame
        window.display();
    }

    // Set the quit flag
    quit = true;

    // End the thread
    thread.join();
}

// Loop to update the cells on a separate thread
void updateThread(Turmite *turmite, bool wrap, float delay)
{
    sf::Time lastTime;
    sf::Clock dt;

    // Im not sure how safe this is, but it works for now
    while (!quit)
    {
        // Get the current elapsed time
        sf::Time now = dt.getElapsedTime();

        // Check to see if its been once second since the last cell update
        if (now.asSeconds() - lastTime.asSeconds() >= delay)
        {
            // Let the turmite step, unless it dies and the wrap flag is set
            wrap ? turmite->step() : turmite->isAlive() ? turmite->step() : void();

            // Set the last time to now
            lastTime = now;
        }
    }
}
