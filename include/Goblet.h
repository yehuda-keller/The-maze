#pragma once
#include "StaticObject.h"
#include "GameResources.h"
#include "const.h"
#include "Animation.h"


class Goblet : public StaticObject {

public:
    Goblet                      ();
    ~Goblet                     () = default;
    void updateAnimation(const int& a, const float& b);


private:
    //------------------protected members-----------------------

    Animation       m_gobletAnimation = Animation(GameResources::getGameResources().getObjectTexture(GOBLET),
                    sf::Vector2u(8, 1), 0.25);

};
