#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class classetest{
public:
    classetest();
    std::string get_atq(int nb);

private:
    sf::String atq[4];
};

classetest::classetest(){
    atq[0] = "Bonjour1";
    atq[1] = "Bonjour2";
    atq[2] = "Bonjour3";
    atq[3] = "Fuir";
}

std::string classetest::get_atq(int nb){
    return atq[nb];
}