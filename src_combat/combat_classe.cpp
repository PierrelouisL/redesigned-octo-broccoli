#include "combat.h"

classetest::classetest(){
    atq[0] = "Soulevage en regle";
    atq[1] = "Pleure";
    atq[2] = "HOW DARE YOU";
    atq[3] = "Fuir";

    PV = 200;
    PV_base = PV;

    dmg_atq[0] = 50;
    dmg_atq[1] = 2;
    dmg_atq[2] = 100;
    dmg_atq[3] = -1;

    atq_desc[0] = sf::String("Le souleve avec une puissance phénomenale de 50PV");
    atq_desc[1] = sf::String("0"); // Deuxième ligne atq0
    atq_desc[2] = sf::String("Vous pleurez comme une victime ce qui fait perdre 2 PV a"); // <<<---- TAILLE MAX 
    atq_desc[3] = sf::String("l'adversaire par compassion..."); // Deuxième ligne atq1
    atq_desc[4] = sf::String("HOW DAARE YOU?!");
    atq_desc[5] = sf::String("2"); // Deuxième ligne atq2
    atq_desc[6] = sf::String("Vous fuiez comme un lâche");
    atq_desc[7] = sf::String("3"); // Deuxième ligne atq3
}

sf::String classetest::get_atq(int nb){
    return atq[nb];
}

sf::String classetest::get_Desc_Atq(int nb){
    return atq_desc[nb];
}

int classetest::get_dmg_atq(int nb){
    return dmg_atq[nb];
}

int classetest::get_PV(){
    return PV;
}

int classetest::get_pourcent_PV(){
    return 100-(int)(((float)(PV_base-PV)/(float)PV_base)*100);
}

void classetest::subit_atq(int dmg){
    PV -= dmg;
}

sf::String classetest::phrase_fin(int issue_du_match){
    if(issue_du_match == VICTOIRE)
        return "A mort la planete!";
    else   
        return "D'accord je vais faire attention avec la planete.";
}

void classetest::aff_fin(sf::RenderWindow* window, int issue_du_match){
    static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
    sf::Font NiceFont;
    NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");
    sf::Text Msg_Fin;
    Msg_Fin.setPosition(sf::Vector2f(20.f, 510.f));
    Msg_Fin.setFont(NiceFont);
    Msg_Fin.setString(phrase_fin(issue_du_match));
    Msg_Fin.setCharacterSize(40);
    Msg_Fin.setFillColor(sf::Color(R, G, B, A));
    window->draw(Msg_Fin);
}

void classetest::aff_message(sf::RenderWindow* win, int nb_atq){
    static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
    sf::Font NiceFont;
    NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");
    sf::Text Msg_Atq[2];
    Msg_Atq[0].setPosition(sf::Vector2f(20.f, 510.f));
    Msg_Atq[0].setFont(NiceFont);
    Msg_Atq[0].setString(this->get_Desc_Atq(2*(nb_atq)));
    Msg_Atq[0].setCharacterSize(40);
    Msg_Atq[0].setFillColor(sf::Color(R, G, B, A));
    Msg_Atq[1].setPosition(sf::Vector2f(20.f, 550.f));
    Msg_Atq[1].setFont(NiceFont);
    Msg_Atq[1].setString(this->get_Desc_Atq(2*(nb_atq)+1));
    Msg_Atq[1].setCharacterSize(40);
    Msg_Atq[1].setFillColor(sf::Color(R, G, B, A));
    win->draw(Msg_Atq[0]);
    win->draw(Msg_Atq[1]);
}