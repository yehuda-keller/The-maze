#include "CollisionHandling.h"

#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "Wall.h"
#include "Player.h"
#include "Goblet.h"
#include "Door.h"
#include "Enemy.h"
#include "EmptyTile.h"

namespace // anonymous namespace — the standard way to make function "static"
{

// primary collision-processing functions

// ----------------- player -----------------
    // player with wall
    void playerWall(GameObject& p,GameObject& w)
    {
        Player& player = dynamic_cast<Player&>(p);
        Wall& wall = dynamic_cast<Wall&>(w);
        player.moveStepBack();
    }
    // player with goblet
    void playerGoblet(GameObject& p, GameObject& g)
    {
        Player& player = dynamic_cast<Player&>(p);
        Goblet& goblet = dynamic_cast<Goblet&>(g);
        player.incGoblet();
        goblet.setExposed();
        GameResources::getGameResources().playSound(GobletEffect);

    }
    // player with door
    void playerDoor(GameObject& p, GameObject& d)
    {
        Player& player = dynamic_cast<Player&>(p);
        Door& door = dynamic_cast<Door&>(d);
        if (player.getMountGoblet() < AMOUNT_OF_GOBLETS) {
            player.moveStepBack();
        }
        else
            player.setEnterDoor(true);
        

    }
    // player with enemy
    void playerEnemy(GameObject& p, GameObject& e)
    {
        Player& player = dynamic_cast<Player&>(p);
        Enemy& enemy = dynamic_cast<Enemy&>(e);
        player.moveStepBack();
        player.setPlayerDeath();
        GameResources::getGameResources().playSound(DeathPlayerSound);

    }
    // player with enpty tile
    void playerEmpty(GameObject& p, GameObject& e)
    {
        Player& player = dynamic_cast<Player&>(p);
        EmptyTile& empty = dynamic_cast<EmptyTile&>(e);
    }
    // ----------------- Enemy -----------------
    //enemy wall
    void enemyWall(GameObject& e, GameObject& w)
    {
        Enemy& enemy = dynamic_cast<Enemy&>(e);
        Wall& wall = dynamic_cast<Wall&>(w);
        enemy.moveStepBack();
        enemy.setDirection();
       
    }
    //enem door
    void enemyDoor(GameObject& e, GameObject& d)
    {
        Enemy& enemy = dynamic_cast<Enemy&>(e);
        Door& door = dynamic_cast<Door&>(d);
        enemy.moveStepBack();
        enemy.setDirection();

    }
    //enem door
    void enemyGoblet(GameObject& e, GameObject& g)
    {
        Enemy& enemy = dynamic_cast<Enemy&>(e);
        Goblet& goblet = dynamic_cast<Goblet&>(g);
        enemy.moveStepBack();
        enemy.setDirection();
        

    }
    // ememy with enpty tile
    void enemyEmpty(GameObject& p, GameObject& e)
    {
        Enemy& enemy = dynamic_cast<Enemy&>(p);
        EmptyTile& empty = dynamic_cast<EmptyTile&>(e);
    }
    // ememy with player
    void enemyPlayer(GameObject& p, GameObject& e)
    {
        Enemy& enemy = dynamic_cast<Enemy&>(p);
        Player& player = dynamic_cast<Player&>(e);
        enemy.moveStepBack();
    }

    using HitFunctionPtr = std::function<void(GameObject&, GameObject&)>;
    
    using Key = std::pair<std::type_index, std::type_index>;
    
    using HitMap = std::map<Key, HitFunctionPtr>;


    //--------------initializeCollisionMap-----------
    HitMap initializeCollisionMap()
    {
        HitMap phm;

        //----------------- player collision ------------------------
        phm[Key(typeid(Player), typeid(Wall))] = &playerWall;
        phm[Key(typeid(Player), typeid(Goblet))] = &playerGoblet;
        phm[Key(typeid(Player), typeid(Door))] = &playerDoor;
        phm[Key(typeid(Player), typeid(Enemy))] = &playerEnemy;
        phm[Key(typeid(Player), typeid(EmptyTile))] = &playerEmpty;
        phm[Key(typeid(Enemy), typeid(Wall))] = &enemyWall;
        phm[Key(typeid(Enemy), typeid(Door))] = &enemyDoor;
        phm[Key(typeid(Enemy), typeid(Goblet))] = &enemyGoblet;
        phm[Key(typeid(Enemy), typeid(Player))] = &enemyPlayer;
        phm[Key(typeid(Enemy), typeid(EmptyTile))] = &enemyEmpty;

        return phm;
    }

    //-------------lookup----------------
    HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
    {
        static HitMap collisionMap = initializeCollisionMap();
        auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
        if (mapEntry == collisionMap.end())
        {
            return nullptr;
        } 
        return mapEntry->second;
    }

} // end namespace

//------------processCollision------------
void processCollision(GameObject& object1, GameObject& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}
