#ifndef PIXELARRAY_H
#define PIXELARRAY_H

#include <SFML/Graphics.hpp>

/**
 * @brief An array of pixels that can be drawn to a target
 */
class PixelArray
{
public:

    /**
     * @brief Create a new array of pixels
     *
     * @param width Width in pixels of the array
     * @param height Height in pixels of the array
     */
    PixelArray(int width, int height);

    /**
     * @brief Delete the array of pixels
     */
    ~PixelArray();

    /**
     * @brief Place a rect into the pixel array
     *
     * @param x Position of the rect
     * @param y Position of the rect
     * @param width Size of the rect's height
     * @param height Size of the rect's width
     * @param color Color of the rect
     */
    void setRect(int x, int y, int width, int height, const sf::Color& color);

    /**
     * @brief Place a single pixel into the pixel array
     *
     * @param x Position of the pixel
     * @param y Position of the pixel
     * @param color Color of the pixel
     */
    void setPixel(int x, int y, const sf::Color &color);

    /**
     * @brief Update the texture and draw the sprite
     *
     * @param target Window to draw the pixel array
     */
    void draw(sf::RenderTarget &target);

private:

    int            m_height;    // Height in pixels of the array
    int            m_width;     // Width of pixels of the array
    unsigned char *m_pixels;    // Pointer to the pixel array
    sf::Texture    m_texture;   // Texture for the pixel array
    sf::Sprite     m_sprite;    // Sprite for the texture

};


#endif //PIXELARRAY_H
