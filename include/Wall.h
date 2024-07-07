#pragma once
#include "StaticObject.h"
#include "GameResources.h"
#include "const.h"


class Wall : public StaticObject {

public:
    Wall                    ();
    ~Wall                   () = default;
    void updateAnimation    (const int& a, const float& b) {};
    
private:

};
