#include "PixelArray.h"

// Constructor
PixelArray::PixelArray(int width, int height)
{
    // Width and height of the pixel array
    m_width = width, m_height = height;

    // Allocate space for the required pixel array
    m_pixels = new unsigned char[m_width * m_height * 4];

    // Create a new texture for the pixel array
    m_texture.create(m_width, m_height);

    // Set the texture as a sprite, so the image can be drawn
    m_sprite.setTexture(m_texture);

    // Iterate over the entire pixel array, setting colors to black
    for (int i = 0; i < m_width * m_height * 4; i += 4)
    {
        m_pixels[i + 0] = 0;
        m_pixels[i + 1] = 0;
        m_pixels[i + 2] = 0;
        m_pixels[i + 3] = 255;
    }
}

// Destructor
PixelArray::~PixelArray()
{
    // Delete the pixel array
    delete[] m_pixels;
}

// Draw a rectangle into the array
void PixelArray::setRect(int x, int y, int width, int height, const sf::Color& color)
{
    // Iterate over the pixels to draw a pixel of a defined size
    for (int i = x; i < x + width; i++)
        for (int j = y; j < y + height; j++)
            setPixel(i, j, color);
}

// Draw a pixel into the array
void PixelArray::setPixel(int x, int y, const sf::Color& color)
{
    // Position of the actual pixel
    int pixel = (m_width * 4 * y) + x * 4;

    // Set the RGBA values for the pixel
    m_pixels[pixel + 0] = color.r;
    m_pixels[pixel + 1] = color.g;
    m_pixels[pixel + 2] = color.b;
    m_pixels[pixel + 3] = color.a;
}

// Update pixel array texture and draw the sprite
void PixelArray::draw(sf::RenderTarget& target)
{
    m_texture.update(m_pixels);
    target.draw(m_sprite);
}
