#pragma once
#include "StaticObject.h"
#include "GameResources.h"
#include "Animation.h"


class Door : public StaticObject {

public:
    Door                    ();
    ~Door                   () = default;
    void updateAnimation(const int& a, const float& b);
    

private:
    Animation m_doorAnimation = Animation(GameResources::getGameResources().getObjectTexture(DOOR)
        , sf::Vector2u(5, 1), 0.25);

};
