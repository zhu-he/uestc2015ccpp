#include "SpriteSheet.hpp"

std::string SpriteSheet::m_filename;
std::string SpriteSheet::m_textureFilename;
std::map<std::string, sf::Texture> SpriteSheet::m_sheet;

bool SpriteSheet::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    std::string path = filename.substr(0, filename.find_last_of('/') + 1);
    std::string line;
    m_textureFilename.clear();
    if (!file.is_open())
    {
        return false;
    }
    std::map<std::string, sf::Texture>::iterator it = m_sheet.end();
    int x = 0;
    int y = 0;
    int origX = 0;
    int origY = 0;
    sf::Image image;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }
        int pos = line.find(':');
        if (pos == -1)
        {
            if (m_textureFilename.empty())
            {
                m_textureFilename = path + line;
                image.loadFromFile(m_textureFilename);
            }
            else
            {
                if (it != m_sheet.end())
                {
                    it->second.loadFromImage(image, sf::IntRect(x, y, origX, origY));
                    x = 0;
                    y = 0;
                    origX = 0;
                    origY = 0;
                    it = m_sheet.end();
                }
                it = m_sheet.insert(make_pair(line, sf::Texture())).first;
            }
        }
        else
        {
            std::string name = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            trim(name);
            trim(value);
            if (name == "xy")
            {
                std::stringstream ss(value);
                char comma;
                ss >> x >> comma >> y;
            }
            else if (name == "orig")
            {
                std::stringstream ss(value);
                char comma;
                ss >> origX >> comma >> origY;
            }
        }
    }
    if (it != m_sheet.end())
    {
        it->second.loadFromImage(image, sf::IntRect(x, y, origX, origY));
    }
    file.close();
    m_filename = filename;
    return true;
}

sf::Texture& SpriteSheet::getTexture(const std::string& texturename)
{
    return m_sheet[texturename];
}

void SpriteSheet::trim(std::string& str)
{
    if (!str.empty())
    {
        str.erase(0, str.find_first_not_of(" "));
        str.erase(str.find_last_not_of(" ") + 1);
    }
}

std::string SpriteSheet::getFilename()
{
    return m_filename;
}

std::string SpriteSheet::getTextureFilename()
{
    return m_textureFilename;
}
