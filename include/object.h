#pragma once
#include <cstdio>
#include <vector>
#include "raylib.h"


class GameObject {
private:
    int id;

public:
// <<<<<<< combat-character-copy
//     gameObject() : id(0) {} // Default constructor
//     gameObject(int id) {
// =======
    GameObject() {}
    GameObject(int id) {
// >>>>>>> main-copy
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

// <<<<<<< combat-character-copy
//     virtual void onTick();
// =======
    virtual void onTick(const std::vector<Rectangle> collidables);
    // TODO 00
// >>>>>>> main-copy
    virtual void onRender();
};

class ObjectHandler 
{
private:
   

public:

    int numberOfObjects;
    int nextId;
// <<<<<<< combat-character-copy
//     std::vector<class gameObject *> allObjects;
//     objectHandler() {
// =======
    std::vector<class GameObject *> allObjects;

// public:
    ObjectHandler() 
    {
// >>>>>>> main-copy
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
    class player *createPlayer(Vector2 position, Vector2 size, int speed);
// <<<<<<< combat-character-copy
// };
// =======
    class Enemy* createEnemy( Vector2 position, Vector2 size, int speed );
};
// >>>>>>> main-copy
