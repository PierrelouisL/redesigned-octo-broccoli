#include "../headers/menu.h"
#include "math.h"

menu::menu() : rotation(0), rotation2(0){
    TextFont.loadFromFile("images/webpixel bitmap_medium.otf");
    SelFont.loadFromFile("images/webpixel bitmap_medium-italic.otf");
    // Background management
    Background = new sf::Texture;
    //Background->loadFromFile(""); BG IM
    Background_sprite = new sf::Sprite;
    Background_sprite->setTexture(*Background);

    // Logo management - octo broccoli
    Brocco_T = new sf::Texture;
    Brocco_T->loadFromFile("images/broccoli.png");
    for(int i = 0; i < 8; ++i){
        Brocco_S.push_back(new sf::Sprite);
        Brocco_S[i]->setTexture(*Brocco_T); 
    }

    rotate_circle(rotation);
    selected = intro;
    Sel_arrow_T = new sf::Texture;
    Sel_arrow_T->loadFromFile("images/fleche2.png"); 
    Sel_arrow_S = new sf::Sprite;
    Sel_arrow_S->setTexture(*Sel_arrow_T);

    for(int i = 0; i< 3; ++i){
        Menu_options.push_back(new sf::Text);
        Menu_options[i]->setFont(SelFont);
        Menu_options[i]->setCharacterSize(40);
    }
    Menu_options[0]->setString(sf::String(L"Instructions"));
    Menu_options[0]->setPosition(sf::Vector2f(800, 500));
    Menu_options[1]->setString(sf::String(L"Lancer partie"));
    Menu_options[1]->setPosition(sf::Vector2f(800, 550));
    Menu_options[2]->setString(sf::String(L"Crédits"));
    Menu_options[2]->setPosition(sf::Vector2f(800, 600));

    for(int i = 0; i< 8; ++i){
        Menu_text.push_back(new sf::Text);
        Menu_text[i]->setFont(TextFont);
        Menu_text[i]->setCharacterSize(25);
    }
    Menu_text[0]->setPosition(sf::Vector2f(30, 450));
    Menu_text[1]->setPosition(sf::Vector2f(30, 480));
    Menu_text[2]->setPosition(sf::Vector2f(30, 510));
    Menu_text[3]->setPosition(sf::Vector2f(30, 540));
    Menu_text[4]->setPosition(sf::Vector2f(30, 570));
    Menu_text[5]->setPosition(sf::Vector2f(30, 600));
    Menu_text[6]->setPosition(sf::Vector2f(30, 630));
    Menu_text[7]->setPosition(sf::Vector2f(30, 660));
    update_displayed_text();
    
}

void menu::update_displayed_text(){
    switch (selected)
    {
    case intro:
        Menu_text[0]->setString(sf::String(L"Bonjour et bienvenue sur redesigned-octo-broccoli!"));
        Menu_text[1]->setString(sf::String(L"Le but du jeu est de sauver la planete, vous incarnez"));
        Menu_text[2]->setString(sf::String(L"la jeune militante Greta Thunberg. "));
        Menu_text[3]->setString(sf::String(L"A vous de sauver la planete contre les pollueurs, "));
        Menu_text[4]->setString(sf::String(L"n'hésitez pas à planter des arbres dans les emplacements"));
        Menu_text[5]->setString(sf::String(L"avec de la terre pour regénérer votre vie entre les combats."));
        Menu_text[6]->setString(sf::String(L"La touche d'action (planter arbre, parler devant la camera"));
        Menu_text[7]->setString(sf::String(L"ou encore entrer dans la Trump Tower) est la touche Espace."));
        break;
    case play:  
        // No text bcs we launch game
        break;
    case credits:
        Menu_text[0]->setString(sf::String(L"Jeu créé par Thanh-Liem TA et Pierre-Louis "));
        Menu_text[1]->setString(sf::String(L"Lagunegrand, graphiques en jeu entièrement fait à la main"));
        Menu_text[2]->setString(sf::String(L"principalement par Thanh-Liem."));
        Menu_text[3]->setString(sf::String(L" "));
        Menu_text[4]->setString(sf::String(L" "));
        Menu_text[5]->setString(sf::String(L" "));
        Menu_text[6]->setString(sf::String(L" "));
        Menu_text[7]->setString(sf::String(L"(font) Webpixel bitmap by Manuel Viergutz"));
        break;
    }
}

void menu::rotate_circle(float theta){
    
    float x0 = 570, y0 = 200, r = 200;
    Brocco_S[0]->setPosition(sf::Vector2f(x0+r*cos(theta*PI/180), y0+r*sin(theta*PI/180)));
    Brocco_S[0]->setRotation(rotation2);
    Brocco_S[1]->setPosition(sf::Vector2f(x0+r*cos((theta+45)*PI/180), y0+r*sin((theta+45)*PI/180)));
    Brocco_S[1]->setRotation(rotation2);
    Brocco_S[2]->setPosition(sf::Vector2f(x0+r*cos((theta+90)*PI/180), y0+r*sin((theta+90)*PI/180)));
    Brocco_S[2]->setRotation(rotation2);
    Brocco_S[3]->setPosition(sf::Vector2f(x0+r*cos((theta+135)*PI/180), y0+r*sin((theta+135)*PI/180)));
    Brocco_S[3]->setRotation(rotation2);
    Brocco_S[4]->setPosition(sf::Vector2f(x0+r*cos((theta+180)*PI/180), y0+r*sin((theta+180)*PI/180)));
    Brocco_S[4]->setRotation(rotation2);
    Brocco_S[5]->setPosition(sf::Vector2f(x0+r*cos((theta+225)*PI/180), y0+r*sin((theta+225)*PI/180)));
    Brocco_S[5]->setRotation(rotation2);
    Brocco_S[6]->setPosition(sf::Vector2f(x0+r*cos((theta+270)*PI/180), y0+r*sin((theta+270)*PI/180)));
    Brocco_S[6]->setRotation(rotation2);
    Brocco_S[7]->setPosition(sf::Vector2f(x0+r*cos((theta+315)*PI/180), y0+r*sin((theta+315)*PI/180)));
    Brocco_S[7]->setRotation(rotation2);
    
}


void menu::Display(sf::RenderWindow &window){
    window.setActive(true);
	window.clear();
	window.setView(window.getDefaultView());

    sf::Text t_redesigned(sf::String(L"redesigned"),TextFont, 70);
    t_redesigned.setPosition(470.f, 148.f);
    sf::Text t_octo(sf::String(L"octo"),TextFont, 70);
    t_octo.setPosition(540.f, 205.f);
    sf::Text t_broccoli(sf::String(L"broccoli"),TextFont, 70);
    t_broccoli.setPosition(500.f, 260.f);

    sf::Event event;
    while(window.isOpen()){
        if(g_mode == menu_){
            
            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                    std::cout << "Tchao bye!"<< std::endl;
                    window.close();
                    quit = true;
                }
                // Si on relache la touche
                if (event.type == sf::Event::KeyReleased){
                    switch (event.key.code){
                        // Process the up and down keys
                        case sf::Keyboard::Up :     _upFlag    	= true; break;
                        case sf::Keyboard::Down:    _downFlag  	= true; break;
                        case sf::Keyboard::Return:  _returnFlag = true; break;
                        default : break;
                    }
                }
            }
            if(_upFlag){
                if(selected == play){
                    selected = intro;
                }else if(selected == credits){
                    selected = play;
                }
            }else if(_downFlag){
                if(selected == intro){
                     selected = play;
                }else if(selected == play){
                    selected = credits;
                }
            }else if(_returnFlag){
                if(selected == play){
                    return;
                }
                update_displayed_text();
                _returnFlag = false;
            }
            update_arrow();
            if(rotation < 180){
                rotation += 0.5;
            }else{
                rotation = 0;
            }
            
            //rotation2 += 2;
            rotate_circle(rotation);
            window.clear();
            window.draw(*Sel_arrow_S);
            for(int i = 0; i< 8; ++i){
                window.draw(*Brocco_S[i]);
            }
            for(int i = 0; i < 8; ++i){
                window.draw(*Menu_text[i]);
            }
            for(int i=0; i< 3; ++i){
                window.draw(*Menu_options[i]);
            }
            window.draw(t_redesigned);
            window.draw(t_octo);
            window.draw(t_broccoli);

            window.display();
            _upFlag = false;
            _downFlag = false;
        }
    }
}

void menu::update_arrow(){
    switch(selected){
        case intro:
            Sel_arrow_S->setPosition(sf::Vector2f(1000, 515));
            break;
        case play:
            Sel_arrow_S->setPosition(sf::Vector2f(1000, 565));
            break;
        case credits:
            Sel_arrow_S->setPosition(sf::Vector2f(1000, 615));
            break;
    }
}

menu::~menu()
{
    delete Background;
    delete Background_sprite;
    delete Sel_arrow_S;
    delete Sel_arrow_T;
    delete Brocco_T;
    for(auto& broco : Brocco_S){
        delete broco;
    }
    for(auto& options : Menu_options){
        delete options;
    }
    for(auto& text : Menu_text){
        delete text;
    }
}
