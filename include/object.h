#pragma once

#include <cstdio>
#include <vector>
#include "raylib.h"


class GameObject {
private:
    int id;

public:

    // gameObject() : id(0) {} // Default constructor <<<<<<< combat-character-copy

    GameObject() {}
    GameObject(int id) {

        this->id = id;
    }
    ~GameObject() {
        // No memory is currently allocated, do nothing
        ;;
    }

    // Getters
    int getId();
    // Setters
    void setId(int id);


    // virtual void onTick(); <<<<<<< combat-character-copy
    virtual void onTick(const std::vector<Rectangle> collidables);
    // TODO 00

    virtual void onRender();
};

class ObjectHandler 
{
private:
   

public:

    int numberOfObjects;
    int nextId;

    // std::vector<class gameObject *> allObjects; <<<<<<< combat-character-copy
    // objectHandler() { <<<<<<< combat-character-copy
    std::vector<class GameObject *> allObjects;

public:
    ObjectHandler() 
    {
        this->numberOfObjects = 0;
        this->nextId = 0;
    }
    ~ObjectHandler() 
    {
        ;;
    }

    void tickAll(const std::vector<Rectangle> collidables);
    void renderAll();
    class GameObject *getObject(int id);
    class GameObject *createObject();
    class Player *createPlayer(Vector2 position, Vector2 size, int speed);
// }; <<<<<<< combat-character-copy
    class Enemy* createEnemy( Vector2 position, Vector2 size, int speed );
};
