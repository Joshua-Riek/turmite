#include "World.h"

// Constructor
World::World(int width, int height, int scale, int offset, sf::Color color) : m_pixelArray(width, height)
{
    // Columns and rows of the grid
    m_columns = height / scale, m_rows = width / scale;

    // Space between tiles, size of each tile, and tile color
    m_offset = offset, m_scale = scale, m_color = color, m_colorTableSize = 1;

    // Allocate space for the color table
    m_colorTable = new sf::Color[m_colorTableSize + 1];

    // Allocate space for the required cell array rows
    m_cellArray = new Cell*[m_rows];

    // Allocate space for the required cell array columns
    for (int i = 0; i < m_rows; i++)
        m_cellArray[i] = new Cell[m_columns];

    // Populate the 2d cell array with default values
    for (int i = 0; i < m_rows; i++)
        for (int j = 0; j < m_columns; j++)
            m_cellArray[i][j] = {.index = 0, .head = false};

    // Populate the table with colors
    for (int i = 0; i < m_colorTableSize + 1; i++)
        m_colorTable[i] = sf::Color(
                m_color.r ? (255 / m_colorTableSize) * i : m_color.r,
                m_color.g ? (255 / m_colorTableSize) * i : m_color.g,
                m_color.b ? (255 / m_colorTableSize) * i : m_color.b);
}

// Destructor
World::~World()
{
    // Delete the space allocated for each cell
    for (int i = 0; i < m_rows; i++)
        delete[] m_cellArray[i];

    // Delete the cell array
    delete[] m_cellArray;

    // Delete the color table
    delete[] m_colorTable;
}

// Get the color of a cell
int World::getIndex(int x, int y)
{
    return m_cellArray[x][y].index;
}

// Set the color of a cell
void World::setIndex(int x, int y, int index)
{
    m_cellArray[x][y].index = index;

    // Check for the greater number of colors
    if (index > m_colorTableSize)
    {
        // Delete the color table
        delete[] m_colorTable;

        // Keep track of the size of the color table
        m_colorTableSize = index;

        // Reallocate the color table to the adjusted size
        m_colorTable = new sf::Color[m_colorTableSize + 1];

        // Populate the table with colors
        for (int i = 0; i < m_colorTableSize + 1; i++)
            m_colorTable[i] = sf::Color(
                    m_color.r ? (255 / m_colorTableSize) * i : m_color.r,
                    m_color.g ? (255 / m_colorTableSize) * i : m_color.g,
                    m_color.b ? (255 / m_colorTableSize) * i : m_color.b);
    }
}

// Set the head of a cell
void World::setHead(int x, int y, bool flag)
{
    m_cellArray[x][y].head = flag;
}

// Get the color of the cell
sf::Color World::getColor(int x, int y)
{
    return m_colorTable[m_cellArray[x][y].index];
}

// Get the rows in the array
int World::getRows() const
{
    return m_rows;
}

// Get the columns in the array
int World::getColumns() const
{
    return m_columns;
}

// Draw all cell's to the screen
void World::draw(sf::RenderTarget &target)
{
    // Go over each cell and draw it to the screen
    for (int x = 0; x < m_rows; x++)
        for (int y = 0; y < m_columns; y++)
            m_pixelArray.setRect(
                    x * m_scale + m_offset, y * m_scale + m_offset,
                    m_scale - m_offset, m_scale - m_offset,
                    m_cellArray[x][y].head ? sf::Color::Red : getColor(x, y));

    // Draw the array of pixels onto the screen
    m_pixelArray.draw(target);
}
