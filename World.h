#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "PixelArray.h"

/**
 * @brief World
 */
class World
{
public:

    /**
     * @brief Create a cellular world
     *
     * @param width Width in pixels of grid
     * @param height Height in pixels of the grid
     * @param scale Size of each cell in the grid
     * @param offset Space between each cell
     */
    World(int width, int height, int scale, int offset, sf::Color color);

    /**
     * @brief Delete the array of cells
     */
    ~World();

    /**
     * @brief Get the color index of a cell
     *
     * @param y Position of the cell
     * @param x Position of the cell
     * @return Indexed color
     */
    int getIndex(int x, int y);

    /**
     * @brief Set the color index of a cell
     *
     * @param x Position of the cell
     * @param y Position of the cell
     * @param index Indexed color
     */
    void setIndex(int x, int y, int index);

    /**
     * @brief Set the head state of a cell
     *
     * @param x Position of the cell
     * @param y Position of the cell
     * @param flag Head of turmite
     */
    void setHead(int x, int y, bool flag);

    /**
     * @brief Get the color of a cell
     *
     * @param y Position of the cell
     * @param x Position of the cell
     * @return Color
     */
    sf::Color getColor(int x, int y);

    /**
     * @brief Get the of rows in the array
     *
     * @return Rows
     */
    int getRows() const;

    /**
     * @brief Get the columns in the array
     *
     * @return Columns
     */
    int getColumns() const;

    /**
     * @brief Draw all cell's to the screen
     *
     * @param target Window to draw the cells
     */
    void draw(sf::RenderTarget& target);

private:

    struct Cell
    {
        int index;
        bool head;
    };

    int          m_rows;           // Rows of cells
    int          m_scale;          // Size of each cell
    int          m_offset;         // Space between cells
    int          m_columns;        // Columns of cells
    int          m_colorTableSize; // Size of the color table
    Cell       **m_cellArray;      // An array of cells
    PixelArray   m_pixelArray;     // An array of singular pixels
    sf::Color    m_color;          // Cell color
    sf::Color   *m_colorTable;     // Table holding all cell colors

};


#endif //WORLD_H
