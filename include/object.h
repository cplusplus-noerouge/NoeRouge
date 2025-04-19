#pragma once

#include <cstdio>
#include <vector>
#include <map>
#include "raylib.h"


class GameObject {
private:
    int id;

public:

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

    virtual void onTick(const std::vector<Rectangle> collidables);
    // TODO 00

    virtual void onRender();
};

class ObjectHandler 
{
private:
   

public:

    int numberOfObjects;
    static int nextId; //this is shared between all object handlers (each floor has one)

    std::map<int, GameObject* > allObjects;

public:
    ObjectHandler() 
    {
        this->numberOfObjects = 0;
    }
    ~ObjectHandler() 
    {
        ;;
    }

    void tickAll(const std::vector<Rectangle> collidables);
    void renderAll();
    void transferObject(int objId, ObjectHandler& newHandler);
    class GameObject *getObject(int id);
    class GameObject *createObject();
    class Player *createPlayer(Vector2 position, Vector2 size, int speed);
    class Enemy* createEnemy( Vector2 position, Vector2 size, int speed );
};