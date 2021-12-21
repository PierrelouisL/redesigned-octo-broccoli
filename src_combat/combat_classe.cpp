#include "combat.h"

classetest::classetest(){
    atq[0] = "Soulevage en regle";
    atq[1] = "Pleure";
    atq[2] = "HOW DARE YOU";
    atq[3] = "Fuir";

    PV = 200;

    dmg_atq[0] = 50;
    dmg_atq[1] = 2;
    dmg_atq[2] = 100;
    dmg_atq[3] = -1;

    atq_desc[0] = "Le souleve avec une puissance phenomenale de 50PV";
    atq_desc[1] = "Vous pleurez comme une victime ce qui fait perdre 2 PV a l'adversaire par compassion";
    atq_desc[2] = "HOW DAARE YOU?!";
    atq_desc[3] = "Vous fuiez comme un lâche";
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

void classetest::subit_atq(int dmg){
    PV -= dmg;
}

sf::String classetest::phrase_fin(int issue_du_match){
    if(issue_du_match == VICTOIRE)
        return "A mort la planete!";
    else   
        return "D'accord je vais faire attention avec la planete.";
}
