#pragma once
#include "Entity.h"
class Player :
    public Entity
{

private:
    //Variables


    //Intializer functions
    void initVariables();
    void initComponents();

public:
    Player(float x, float y, Texture& texture_sheet);
    virtual ~Player();

    //Functions
    void updateAttack(const float& dt);
    void updateAnimation(const float& dt);
    virtual void update(const float& dt);

};

