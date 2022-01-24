#include "../headers/fighter.h"



/**
 * @brief perso = 0 for player, 1 for bot, 2 for Donald Trump
 * 
 * @param perso 
 */
fighter::fighter(int perso){
    switch(perso){
        case 0:
            atk_name[0] = L"How dare you?!";
            atk_name[1] = L"Cop 22";
            atk_name[2] = L"Manifestation";
            atk_name[3] = L"Loi n°2021-1104";

            HP = 200;
            HP_base = HP;

            atk_dmg[0] = 100;
            atk_dmg[1] = 50;
            atk_dmg[2] = 10;
            atk_dmg[3] = 30;

            atk_desc[0] = sf::String(L"How DARE you?!");
            atk_desc[1] = sf::String(L"Vous infligez 100 points de dégats."); // Deuxième ligne atq0
            atk_desc[2] = sf::String(L"Vous faites appel à la COP 22 ce qui fonctionne"); // <<<---- TAILLE MAX 
            atk_desc[3] = sf::String(L"plutôt bien, le pollueur perd 50 points de vie."); // Deuxième ligne atq1
            atk_desc[4] = sf::String(L"Vous manifestez ce qui n'a que peu d'effet, le pollueur");
            atk_desc[5] = sf::String(L"perd 10 points de vie."); // Deuxième ligne atq2
            atk_desc[6] = sf::String(L"Vous invoquez la loi du 22 aout 2021 pour lutter contre");
            atk_desc[7] = sf::String(L"le réchauffement climatique, l'ennemi perd 30 PV."); // Deuxième ligne atq3

            alive = true;
            break;
        case 1:
            atk_name[0] = "Cigarette";
            atk_name[1] = "4x4";
            atk_name[2] = "Coupe";
            atk_name[3] = "CIMENTAGE";

            HP = 200;
            HP_base = HP;

            atk_dmg[0] = 10;
            atk_dmg[1] = 30;
            atk_dmg[2] = 50;
            atk_dmg[3] = 70;

            atk_desc[0] = sf::String(L"Le pollueur jette une cigarette par terre et s'en allume une autre,");
            atk_desc[1] = sf::String(L"vous perdez 10 points de vie."); // Deuxième ligne atq0
            atk_desc[2] = sf::String(L"Le pollueur fonce à toute allure sur l'herbe fraiche avec son "); // <<<---- TAILLE MAX 
            atk_desc[3] = sf::String(L"gros 4x4, ce qui vous fait perdre 30 points de vie."); // Deuxième ligne atq1
            atk_desc[4] = sf::String(L"Attaque coupe! (coupe un arbre dans le coin), ce qui vous fait ");
            atk_desc[5] = sf::String(L"perdre 50 points de vie"); // Deuxième ligne atq2
            atk_desc[6] = sf::String(L"Le pollueur vous CIMENTE LA FACE!");
            atk_desc[7] = sf::String(L"Vous perdez 70 points de vie"); // Deuxième ligne atq3

            alive = true;
            break;

        case 2:
            atk_name[0] = "NOTHING";
            atk_name[1] = "FAKE NEWS";
            atk_name[2] = "TWEET";
            atk_name[3] = "MONEY";

            HP = 400;
            HP_base = HP;

            atk_dmg[0] = 100;
            atk_dmg[1] = 30;
            atk_dmg[2] = -20;
            atk_dmg[3] = 100;

            atk_desc[0] = sf::String(L"Trump ne fait rien... l'environnement en souffre, vous perdez");
            atk_desc[1] = sf::String(L"100 points de vie"); // Deuxième ligne atq0
            atk_desc[2] = sf::String(L"'FAKE NEWS'  Trump crie au mensonge, une centaine d'ahuris le"); // <<<---- TAILLE MAX 
            atk_desc[3] = sf::String(L"croit, vous perdez 30 points de vie"); // Deuxième ligne atq1
            atk_desc[4] = sf::String(L"Trump tweete...");
            atk_desc[5] = sf::String(L"Vous gagnez 20 points de vie"); // Deuxième ligne atq2
            atk_desc[6] = sf::String(L"Trump soudoie d'autres membres du gouvernement, ce qui vous fait");
            atk_desc[7] = sf::String(L"perdre 100 points de vie."); // Deuxième ligne atq3

            alive = true;
            break;
    }
}

fighter::fighter(TileCharacter& character): fighter(){
    this->setOrigin(character.getOrigin());
    this->setPosition(character.getPosition());
    this->setScale(character.getScale());
    this->setRotation(character.getRotation());

    alive = true;
}

sf::String fighter::get_atk(int nb){
    return atk_name[nb];
}

sf::String fighter::get_Desc_Atq(int nb){
    return atk_desc[nb];
}

int fighter::get_dmg_atq(int nb){
    return this->atk_dmg[nb];
}

int fighter::get_PV(){
    return HP;
}

int fighter::get_pourcent_PV(){
    return 100-(int)(((float)(HP_base-HP)/(float)HP_base)*100);
}

void fighter::subit_atq(int dmg){
    HP -= dmg;
}

sf::String fighter::phrase_fin(int issue_du_match){
    if(issue_du_match == VICTOIRE)
        return "A mort la planete!";
    else   
        return L"D'accord je vais faire attention à la planete.";
}

void fighter::aff_fin(sf::RenderWindow* window, int issue_du_match){
    static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
    sf::Font NiceFont;
    NiceFont.loadFromFile("images/webpixel bitmap_medium.otf");
    sf::Text Msg_Fin;
    Msg_Fin.setPosition(sf::Vector2f(20.f, 510.f));
    Msg_Fin.setFont(NiceFont);
    Msg_Fin.setString(phrase_fin(issue_du_match));
    Msg_Fin.setCharacterSize(40);
    Msg_Fin.setFillColor(sf::Color(R, G, B, A));
    window->draw(Msg_Fin);
}

void fighter::aff_message(sf::RenderWindow* win, int nb_atq){
    static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
    sf::Font NiceFont;
    NiceFont.loadFromFile("images/webpixel bitmap_medium.otf");
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
