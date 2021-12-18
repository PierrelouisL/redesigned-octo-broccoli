#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

/*
 *  Nous aurons une map de 944 pixels de large contre 576 pixels de hauteur en 16x16, nous affichons
 *  en 64x64(tile map déjà faite comme ça). Donc cela nous fait 59 blocs de large et 36 blocks de hauteur.
 *  Il y a donc une map de 59*64=3776 pixels de large et 36*64=2304 pixels de hauteur. Tous ces pixels ne seront 
 *  cependant pas affichés car la fenetre n'affichera que 3 immeubles de large et 1 immeuble + une route de hauteur.
 *  Cela fait donc une fenêtre de 3*6*64=1152 pixels de large et (7+4)*64=704 pixels de hauteur.
 *  Chaque case de 64*64 correspond à une classe définie: Immeuble, Route, voiture, Décor...
 *  Un immeuble n'est pas un décor (comme la route par exemple) car on peut interagir avec lui, pour entrer chez les boss.
 *  Nous aurons un vecteur géant 2D qui nous servira de map, permettant de situer n'importe quel élément et accéder directement
 *  aux fonctions de sa classe, l'affichage sera géré par les classes (constructeurs), collisions de même. 
 *  Pour cela nous aurons une classe mère, la classe Map qui servira de mère pour toutes les autres classes et ainsi créer un
 *  vecteur de la classe "Map". 
 *             
 */



class TileMap : public sf::Drawable, public sf::Transformable, public sf::Clock
{
public:

    bool load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height)
    {
        // on charge la texture du tileset
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // on redimensionne le tableau de vertex pour qu'il puisse contenir tout le niveau
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(width * height * 4);

        // on remplit le tableau de vertex, avec un quad par tuile
        // Width et Height -> largeur et hauteur de l'image finale!
        for (unsigned int i = 0; i < width; ++i)
            for (unsigned int j = 0; j < height; ++j)
            {
                // on récupère le numéro de tuile courant
                int tileNumber = tiles[i + j * width];

                // on en déduit sa position dans la texture du tileset
                int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
                int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

                // on récupère un pointeur vers le quad à définir dans le tableau de vertex
                sf::Vertex* quad = &m_vertices[(i + j * width) * 4];

                // on définit ses quatre coins
                quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                // on définit ses quatre coordonnées de texture
                quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
                quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
                quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
                quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
            }

        return true;
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();

        // on applique la texture du tileset
        states.texture = &m_tileset;

        // et on dessine enfin le tableau de vertex
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};

std::vector<std::vector<TileMap>> MainVect;

int main()
{
    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(1152, 704), "EcoBehave");

    // on définit le niveau à l'aide de numéro de tuiles
    const int level[]=
    {
        0, 1, 2, 3, 4, 5, 25, 26, 27, 28, 29, 30,
        50, 51, 52, 53, 54, 55, 75, 76, 77, 78, 79,
        80, 100, 101, 102, 103, 104, 105, 125, 126, 127,
        128, 129, 130, 150, 151, 152, 153, 154, 155 
    };

    // on crée la tilemap avec le niveau précédemment défini
    TileMap map;
    sf::View view = window.getDefaultView();
    window.setView(view);
    if (!map.load("images/tileset_nouv64.png", sf::Vector2u(64, 64), level, 6, 7))
        return -1;


    // Flags for key pressed
    bool upFlag    = false;
    bool downFlag  = false;
    bool leftFlag  = false;
    bool rightFlag = false;

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape){
                window.close();
            }
            
            // Si on appuit sur une touche
            if (event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                    case sf::Keyboard::Up :     upFlag=true; break;
                    case sf::Keyboard::Down:    downFlag=true; break;
                    case sf::Keyboard::Left:    leftFlag=true; break;
                    case sf::Keyboard::Right:   rightFlag=true; break;
                    default : break;
                }
            }

            // Si on relache la touche
            if (event.type == sf::Event::KeyReleased){
                switch (event.key.code){
                // Process the up, down, left and right keys
                case sf::Keyboard::Up :     upFlag=false; break;
                case sf::Keyboard::Down:    downFlag=false; break;
                case sf::Keyboard::Left:    leftFlag=false; break;
                case sf::Keyboard::Right:   rightFlag=false; break;
                default : break;
                }
            }
            
        }

        if(leftFlag){  // left key is pressed: move our character
            view.move(0.5f, 0.f);
        }
        if(rightFlag){  // right key is pressed: move our character
            view.move(-0.5f, 0.f);
        }
        if(upFlag){     // up key is pressed: move our character
            view.move(0.f, 0.5f);
        }
        if(downFlag){   // down key is pressed: move our character
            view.move(0.f, -0.5f);              
        }

        window.setView(view);

        // on dessine le niveau
        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}
