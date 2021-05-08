#ifndef TURMITE_H
#define TURMITE_H

#include <SFML/Graphics.hpp>
#include "PixelArray.h"
#include "World.h"

/**
 * @brief Turmite example rules by EdPegJr
 *
 * source: http://demonstrations.wolfram.com/Turmites/
 * Translated into his later notation: 1=noturn, 2=right, 4=u-turn, 8=left
 * (old notation was: 0=noturn,1=right,-1=left)
 * all these are 2-color patterns)
 */
extern const std::string turmiteExampleRules[45];

/**
 * @brief Turmite
 */
class Turmite
{
public:

    /**
     * @brief Create a turmite
     *
     * To create a turmite, a rule must be made and specified by a curly-bracketed
     * table  of N-State rows by N-color columns, consisting of triples
     * {A, B, C} where A is the new color to write [0,1,2,...,(m_numberOfColors-1)],
     * B is the direction(s) for the turmite to turn 1=forward, 2=right, 4=u-turn,
     * 8=left), and C is the new state to adopt.
     *
     * @param world Pointer to the where the turmite is displayed
     * @param rule Rule that the turmite follows
     * @param x Position of the turmite
     * @param y Position of the turmite
     * @param direction Initial facing direction (0=up, 1=right, 2=down, 3=left)
     */
    Turmite(World *world, const std::string& rule, int x, int y, int direction = 0);

    /**
     * @brief Delete the transition table from memory
     */
    ~Turmite();

    /**
     * @brief Preform one iteration for the turmite
     */
    void step();

    /**
     * @brief Get the total number of generations that the turmite has been alive
     *
     * @return Total generation count
     */
    int getGenerationCount() const;

    /**
     * @brief Check to see if the turmite has wrapped around the edge of the screen
     *
     * @return Wrapped state
     */
    bool isAlive() const;

private:

    /**
     * @brief Update the turmite position based on it's current direction
     */
    void move();

    /**
     * @brief Tell the world where the head of the turmite is
     */
    void head();

    /**
     * @brief Preform actions specified by the transition table
     */
    void transitionFunction();

    int              m_lastX;            // Last x position
    int              m_lastY;            // Last y position
    int              m_posX;             // Current x position
    int              m_posY;             // Current y position
    int              m_generationCount;  // Total number of iterations
    int              m_numberOfColors;   // Total number of colors
    int              m_numberOfStates;   // Total number of states
    int              m_currentState;     // Current internal state
    bool             m_isAlive;          // Is the turmite alive or dead
    unsigned int     m_currentDirection; // Current facing position
    unsigned char ***m_transitionTable;  // Actions to be taken are specified here
    World           *m_world;            // Pointer to the where the turmite is displayed

};


#endif //TURMITE_H
