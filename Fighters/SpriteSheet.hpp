#ifndef SFML_SPRITESHEET_HPP
#define SFML_SPRITESHEET_HPP

#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <SFML/Graphics/Texture.hpp>

class SpriteSheet
{
public:
    SpriteSheet();
    bool loadFromFile(const std::string& filename);
    sf::Texture& getTexture(const std::string& texturename);
    std::string getFilename();
    std::string getTextureFilename();
private:
    std::string m_filename;
    std::string m_textureFilename;
    std::map<std::string, sf::Texture> m_sheet;
    void trim(std::string& str);
};

#endif // SFML_SPRITESHEET_HPP
