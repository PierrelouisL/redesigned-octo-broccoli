#include <SFML/Graphics.hpp>
#include <math.h>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

    ParticleSystem(unsigned int count) :
    m_particles(count),
    m_vertices(sf::Points, count),
    m_lifetime(sf::seconds(3)),
    m_emitter(0.f, 0.f)
    {
    }

    void setEmitter(sf::Vector2f position)
    {
        m_emitter = position;
    }

    void update(sf::Time elapsed)
    {
        for (std::size_t i = 0; i < m_particles.size(); ++i)
        {
            // on met à jour la durée de vie de la particule
            Particle& p = m_particles[i];
            p.lifetime -= elapsed;

            // si la particule est arrivée en fin de vie, on la réinitialise
            if (p.lifetime <= sf::Time::Zero)
                resetParticle(i);

            // on met à jour la position du vertex correspondant
            m_vertices[i].position += p.velocity * elapsed.asSeconds();

            // on met à jour l'alpha (transparence) de la particule en fonction de sa durée de vie
            float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
            m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255);
        }
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // on applique la transformation
        states.transform *= getTransform();

        // nos particules n'utilisent pas de texture
        states.texture = NULL;

        // on dessine enfin le vertex array
        target.draw(m_vertices, states);
    }

private:

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time lifetime;
    };

    void resetParticle(std::size_t index)
    {
        // on donne une vitesse et une durée de vie aléatoires à la particule
        float angle = (std::rand() % 360) * 3.14f / 180.f;
        float speed = (std::rand() % 50) + 50.f;
        m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
        m_particles[index].lifetime = sf::milliseconds((std::rand() % 2000) + 1000);

        // on remet à zéro la position du vertex correspondant à la particule
        m_vertices[index].position = m_emitter;
    }

    std::vector<Particle> m_particles;
    sf::VertexArray m_vertices;
    sf::Time m_lifetime;
    sf::Vector2f m_emitter;
};

int main()
{
    // on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(512, 256), "Particles");

    // on crée un système de 1000 particules
    ParticleSystem particles(100000);

    // on crée un chrono pour mesurer le temps écoulé
    sf::Clock clock;

    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        // on gère les évènements
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // on fait en sorte que l'émetteur des particules suive la souris
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        // on met à jour le système de particules
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        // on le dessine
        window.clear();
        window.draw(particles);
        window.display();
    }

    return 0;
}