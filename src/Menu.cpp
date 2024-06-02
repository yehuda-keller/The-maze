#include "Menu.h"
#include "GameResources.h"
#include <SFML/audio.hpp>


//------------------------constractor--------------------
Menu::Menu()
{
    m_button.resize(NUMBER_OF_MENU_BUTTONS);


    m_soundStatus.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::MUSIC_ON));
    m_soundStatus.setScale(0.55, 0.55);
    m_soundStatus.setPosition(sf::Vector2f(1300, 700));

    for (int i = 0, y = BUTTON_Y_LOCITION; i < NUMBER_OF_MENU_BUTTONS; i++, y += MIDDLE_BUTTON_Y) {
        m_button[i].setTexture(&GameResources::getGameResources().getButton(Button(i)));
        m_button[i].setSize({ MENU_BUTTON_SIZE });
        m_button[i].setPosition(65.f, float(y + BUTTON_Y * i));
        m_button[i].setOutlineColor(sf::Color::Black);
        m_button[i].setOutlineThickness(6);
    }

    m_button[Back].setPosition(10,690);

    
}
//-------------------------distractor------------------------
Menu::~Menu()
{
}

//--------------------------runMunu---------------------------
void Menu::runMenu(sf::RenderWindow& window)
{

    bool MenuMode = true;

    GameResources::getGameResources().PlayMusic(MenuMusic);

    while (window.isOpen() && MenuMode)
    {
        drawMenu(window);

        if (auto event = sf::Event{}; window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                exit(EXIT_SUCCESS);
                break;
            case sf::Event::MouseMoved:
                handleMouseMove(window);
                break;
            case sf::Event::MouseButtonReleased:
            {
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                    handleClick(MenuMode, window);
           
                break;

            }
            }
        }
    }


}
//-----------------------------drawMenu------------------------
void Menu::drawMenu(sf::RenderWindow& window)
{
    window.clear();
    auto sprite = sf::Sprite(GameResources::getGameResources().getBackground(Background::MenuBackground));
    window.draw(sprite);

    for (int i = 0; i < NUMBER_OF_MENU_BUTTONS-1; i++)
        window.draw(m_button[i]);

    
    window.draw(m_soundStatus);


    window.display();
}

//------------------------handleMouseMove---------------------
void Menu::handleMouseMove(const sf::RenderWindow& window) {

    for (int i = 0; i < NUMBER_OF_MENU_BUTTONS-1; i++) {

        if (m_button[i].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            m_button[i].setOutlineColor(sf::Color::White);
        }
        else
            m_button[i].setOutlineColor(sf::Color::Black);
    }
}

//----------------------------handleMenuClick----------------------
void Menu::handleClick(bool& MenuMode, sf::RenderWindow& window) {

    // run game
    if (m_button[0].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        GameResources::getGameResources().playSound(ButtonClick);
        MenuMode = false;
        
    }
    //help 
    else if (m_button[1].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        GameResources::getGameResources().playSound(ButtonClick);
        helpButton(window);
    }
    //exit game
    else if (m_button[2].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        GameResources::getGameResources().playSound(ButtonClick);
        exit(EXIT_SUCCESS);
    }
    //music status
    else if (m_soundStatus.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {

        if (!m_soundStat)
        {
            m_soundStatus.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::MUSIC_ON));
            m_soundStat = true;
            GameResources::getGameResources().setMute(false);
        }
        else
        {
            m_soundStatus.setTexture(GameResources::getGameResources().getObjectTexture(ObjectType::MUSIC_OFF));
            m_soundStat = false;
            GameResources::getGameResources().setMute(true);
        }
    }
       
}

//-----------------------------helpButton-------------------
void Menu::helpButton(sf::RenderWindow& window) {

    //help loop
    while (window.isOpen())
    {
        drawHelpButton(window);

        if (auto event = sf::Event{}; window.waitEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                exit(EXIT_SUCCESS);
                break;
            case sf::Event::MouseMoved:

                if (m_button[Back].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
                    m_button[Back].setOutlineColor(sf::Color::White);
                else
                    m_button[Back].setOutlineColor(sf::Color::Transparent);
                break;

            case sf::Event::MouseButtonReleased:

                if (event.mouseButton.button == sf::Mouse::Button::Left &&
                    m_button[Back].getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    GameResources::getGameResources().playSound(ButtonClick);
                    return;
                }
                break;
            }
        }
    }
}
//-------------------------drawHelp-----------------------
void Menu::drawHelpButton(sf::RenderWindow& window) {

    window.clear();
    auto sprite = sf::Sprite(GameResources::getGameResources().getBackground(Background::HelpBackground));
    window.draw(sprite);
    window.draw(m_button[Back]);
    window.display();
}