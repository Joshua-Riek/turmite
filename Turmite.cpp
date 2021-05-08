#include "Turmite.h"

// Turmite example rules by EdPegJr
const std::string turmiteExampleRules[45] = {
        "{{{1, 2, 0}, {0, 8, 0}}}",  // 1: Langton's ant
        "{{{1, 2, 0}, {0, 1, 0}}}",  // 2: binary counter
        "{{{0, 8, 1}, {1, 2, 1}}, {{1, 1, 0}, {1, 1, 1}}}", // 3: (filled triangle)
        "{{{0, 1, 1}, {0, 8, 1}}, {{1, 2, 0}, {0, 1, 1}}}", // 4: spiral in a box
        "{{{0, 2, 1}, {0, 8, 0}}, {{1, 8, 1}, {0, 2, 0}}}", // 5: stripe-filled spiral
        "{{{0, 2, 1}, {0, 8, 0}}, {{1, 8, 1}, {1, 1, 0}}}", // 6: stepped pyramid
        "{{{0, 2, 1}, {0, 1, 1}}, {{1, 2, 1}, {1, 8, 0}}}", // 7: contoured island
        "{{{0, 2, 1}, {0, 2, 1}}, {{1, 1, 0}, {0, 2, 1}}}", // 8: woven placemat
        "{{{0, 2, 1}, {1, 2, 1}}, {{1, 8, 1}, {1, 8, 0}}}", // 9: snowflake-ish
        "{{{1, 8, 0}, {0, 1, 1}}, {{0, 8, 0}, {0, 8, 1}}}", // 10: slow city builder
        "{{{1, 8, 0}, {1, 2, 1}}, {{0, 2, 0}, {0, 8, 1}}}", // 11: framed computer art
        "{{{1, 8, 0}, {1, 2, 1}}, {{0, 2, 1}, {1, 8, 0}}}", // 12: balloon bursting (makes a spreading highway)
        "{{{1, 8, 1}, {0, 8, 0}}, {{1, 1, 0}, {0, 1, 0}}}", // 13: makes a horizontal highway
        "{{{1, 8, 1}, {0, 8, 0}}, {{1, 2, 1}, {1, 2, 0}}}", // 14: makes a 45 degree highway
        "{{{1, 8, 1}, {0, 8, 1}}, {{1, 2, 1}, {0, 8, 0}}}", // 15: makes a 45 degree highway
        "{{{1, 8, 1}, {0, 1, 0}}, {{1, 1, 0}, {1, 2, 0}}}", // 16: spiral in a filled box
        "{{{1, 8, 1}, {0, 2, 0}}, {{0, 8, 0}, {0, 8, 0}}}", // 17: glaciers
        "{{{1, 8, 1}, {1, 8, 1}}, {{1, 2, 1}, {0, 1, 0}}}", // 18: golden rectangle!
        "{{{1, 8, 1}, {1, 2, 0}}, {{0, 8, 0}, {0, 8, 0}}}", // 19: fizzy spill
        "{{{1, 8, 1}, {1, 2, 1}}, {{1, 1, 0}, {0, 1, 1}}}", // 20: nested cabinets
        "{{{1, 1, 1}, {0, 8, 1}}, {{1, 2, 0}, {1, 1, 1}}}", // 21: (cross)
        "{{{1, 1, 1}, {0, 1, 0}}, {{0, 2, 0}, {1, 8, 0}}}", // 22: saw-tipped growth
        "{{{1, 1, 1}, {0, 1, 1}}, {{1, 2, 1}, {0, 1, 0}}}", // 23: curves in blocks growth
        "{{{1, 1, 1}, {0, 2, 0}}, {{0, 8, 0}, {0, 8, 0}}}", // 24: textured growth
        "{{{1, 1, 1}, {0, 2, 1}}, {{1, 8, 0}, {1, 2, 0}}}", // 25: (diamond growth)
        "{{{1, 1, 1}, {1, 8, 0}}, {{1, 2, 1}, {0, 1, 0}}}", // 26: coiled rope
        "{{{1, 2, 0}, {0, 8, 1}}, {{1, 8, 0}, {0, 1, 1}}}", // 27: (growth)
        "{{{1, 2, 0}, {0, 8, 1}}, {{1, 8, 0}, {0, 2, 1}}}", // 28: (square spiral)
        "{{{1, 2, 0}, {1, 2, 1}}, {{0, 1, 0}, {0, 1, 1}}}", // 29: loopy growth with holes
        "{{{1, 2, 1}, {0, 8, 1}}, {{1, 1, 0}, {0, 1, 0}}}", // 30: Lanton's Ant drawn with squares
        "{{{1, 2, 1}, {0, 2, 0}}, {{0, 8, 1}, {1, 8, 0}}}", // 31: growth with curves and blocks
        "{{{1, 2, 1}, {0, 2, 0}}, {{0, 1, 0}, {1, 2, 1}}}", // 32: distracted spiral builder
        "{{{1, 2, 1}, {0, 2, 1}}, {{1, 1, 0}, {1, 1, 1}}}", // 33: cauliflower stalk (45 deg highway)
        "{{{1, 2, 1}, {1, 8, 1}}, {{1, 2, 1}, {0, 2, 0}}}", // 34: worm trails (eventually turns cyclic!)
        "{{{1, 2, 1}, {1, 1, 0}}, {{1, 1, 0}, {0, 1, 1}}}", // 35: eventually makes a two-way highway!
        "{{{1, 2, 1}, {1, 2, 0}}, {{0, 1, 0}, {0, 1, 0}}}", // 36: almost symmetric mould bloom
        "{{{1, 2, 1}, {1, 2, 0}}, {{0, 2, 0}, {1, 1, 1}}}", // 37: makes a 1 in 2 gradient highway
        "{{{1, 2, 1}, {1, 2, 1}}, {{1, 8, 1}, {0, 2, 0}}}", // 38: immediately makes a 1 in 3 highway
        "{{{0, 2, 1}, {1, 2, 1}}, {{0, 8, 2}, {0, 8, 0}}, {{1, 2, 2}, {1, 8, 0}}}", // 39: squares and diagonals growth
        "{{{1, 8, 1}, {0, 1, 0}}, {{0, 2, 2}, {1, 8, 0}}, {{1, 2, 1}, {1, 1, 0}}}", // 40: streak at approx. an 8.1 in 1 gradient
        "{{{1, 8, 1}, {0, 1, 2}}, {{0, 2, 2}, {1, 1, 1}}, {{1, 2, 1}, {1, 1, 0}}}", // 41: streak at approx. a 1.14 in 1 gradient
        "{{{1, 8, 1}, {1, 8, 1}}, {{1, 1, 0}, {0, 1, 2}}, {{0, 8, 1}, {1, 1, 1}}}", // 42: maze-like growth
        "{{{1, 8, 2}, {0, 2, 0}}, {{1, 8, 0}, {0, 2, 0}}, {{0, 8, 0}, {0, 8, 1}}}", // 43: growth by cornices
        "{{{1, 2, 0}, {0, 2, 2}}, {{0, 8, 0}, {0, 2, 0}}, {{0, 1, 1}, {1, 8, 0}}}", // 44: makes a 1 in 7 highway
        "{{{1, 2, 1}, {0, 8, 0}}, {{1, 2, 2}, {0, 1, 0}}, {{1, 8, 0}, {0, 8, 0}}}", // 45: makes a 4 in 1 highway
};

// Constructor
Turmite::Turmite(World *world, const std::string& rule, int x, int y, int direction)
{
    // Get ptr to the world and set the initial position of the turmite
    m_world = world, m_posX = x, m_posY = y, m_lastX = x, m_lastY = y, m_currentDirection = direction;

    // Initialize some default values
    m_currentState = 0, m_generationCount = 0, m_isAlive = true;

    // Turmite formatted rule
    std::string turmiteRule = rule;

    // Translate from ant to implicit
    if (rule.find_first_of("RLBF") != std::string::npos)
    {
        turmiteRule = "{";

        // Iterate through the ant formatted rule and convert into the turmite format
        for (int i = 0; i < rule.length(); i++)
        {
            // The new color to write
            turmiteRule += "{{" + std::to_string(i == rule.length() - 1 ? 0: i + 1) + ", ";

            // The new movement
            int c = toupper(rule[i]);
            turmiteRule += std::to_string(c == 'R' ? 2 : c == 'L' ? 8 : c == 'B' ? 4 : c == 'F' ? 1 : 0) + ", ";

            // New state to adopt
            turmiteRule += "0}}, ";
        }
        // Return the string with the last two chars snipped off and a closing bracket
        turmiteRule = turmiteRule.substr(0, turmiteRule.length() - 2) + "}";
    }
    // Translate from turmite to implicit
    std::string implicitRule;
    int commas = 0, braces = 0;

    // Count commas and open braces, then strip unnecessary characters
    for (auto c : turmiteRule)
    {
        // Keep track of all commas and open braces
        c == ',' ? commas++ : braces = c == '{' || c == '[' ? braces + 1 : braces;

        // Strip all characters that are not needed and convert into an implicit rule
        if (c != ',' && c != '{' && c != '}' && c != ' ' && c != '[' && c != ']')
            implicitRule.push_back(c);
    }
    // Keep track of the unique colors and states
    m_numberOfStates = braces - 1 - (commas + 1) / 3;
    m_numberOfColors = (commas + 1) / 3 / m_numberOfStates;

    // Allocate space for the translation table
    m_transitionTable = new unsigned char**[m_numberOfStates];
    for (int i = 0, index = 0; i < m_numberOfStates; i++)
    {
        // Allocate more space for the translation stable
        m_transitionTable[i] = new unsigned char*[m_numberOfColors];
        for (int j = 0; j < m_numberOfColors; j++)
        {
            // Set and allocate the triplet values in the transition table
            m_transitionTable[i][j] = new unsigned char[3];
            for (int k = 0; k < 3; k++)
                m_transitionTable[i][j][k] = atoi(implicitRule.substr(index++, 1).c_str());
        }
    }
}

// Destructor
Turmite::~Turmite()
{
    // Delete the space allocated for the 3d array
    for (int i = 0; i < m_numberOfStates; i++)
    {
        for (int j = 0; j < m_numberOfColors; j++)
            delete[] m_transitionTable[i][j];
        delete[] m_transitionTable[i];
    }
    delete[] m_transitionTable;
}

// Preform one iteration for the turmite
void Turmite::step()
{
    // Keep track of the number of generations
    m_generationCount++;

    // Preform the transition rule
    transitionFunction();

    // Set the current head of the turmite
    head();

    // Move and update the turmite
    move();
}

// Simply set the head of the turmite
void Turmite::head()
{
    // Tell the world that the last cell is no longer the head of the turmite
    m_world->setHead(m_lastX, m_lastY, false);

    // Tell the world that this cell is the current head of the turmite
    m_world->setHead(m_posX, m_posY, true);

    // Keep track of the last position of the turmite
    m_lastX = m_posX, m_lastY = m_posY;
}

// Update the turmite position based on it's direction
void Turmite::move()
{
    const int movements[4][2] = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    // Set the current location to the next cell
    m_posX += movements[m_currentDirection][0];
    m_posY += movements[m_currentDirection][1] ;

    // If leaving the map, adjust the position
    if (m_posX < 0 || m_posY < 0 || m_posX >= m_world->getRows() || m_posY >= m_world->getColumns())
    {
        // Wrap the current position around the screen
        m_posX = (m_posX + m_world->getRows()) % m_world->getRows();
        m_posY = (m_posY + m_world->getColumns()) % m_world->getColumns();

        // Keep track of the wrapped state
        m_isAlive = false;
    }
}

// Preform actions specified by the transition table
void Turmite::transitionFunction()
{
    int currentColor = m_world->getIndex(m_posX, m_posY);

    // A: The new color of the cell
    m_world->setIndex(m_posX, m_posY, m_transitionTable[m_currentState][currentColor][0]);

    // B: The direction for the turmite to turn
    switch (m_transitionTable[m_currentState][currentColor][1])
    {
        // Continue on forward
        case 1:
            m_currentDirection = (m_currentDirection + 0) % 4;
            break;

        // Turn to the right 90 degrees
        case 2:
            m_currentDirection = (m_currentDirection + 1) % 4;
            break;

        // Turn 180 degrees around
        case 4:
            m_currentDirection = (m_currentDirection + 2) % 4;
            break;

        // Turn to the left 90 degrees
        case 8:
            m_currentDirection = (m_currentDirection + 3) % 4;
            break;
    }
    // C: The new internal state of the turmite
    m_currentState = m_transitionTable[m_currentState][currentColor][2];
}

// Get the total number of generations the turmite has been alive
int Turmite::getGenerationCount() const
{
    return m_generationCount;
}

// Check to see if the turmite is starting to wrap around the screen
bool Turmite::isAlive() const
{
    return m_isAlive;
}
