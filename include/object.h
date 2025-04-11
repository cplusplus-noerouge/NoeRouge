#pragma once
#include <cstdio>
#include <vector>
#include "raylib.h"


class gameObject {
private:
    int id;

public:
    gameObject() : id(0) {} // Default constructor
    gameObject(int id) {
        this->id = id;
    }
    ~gameObject() {
        // No memory is currently allocated, do nothing
        ;;
    }

    // Getters
    int getId();
    // Setters
    void setId(int id);

    virtual void onTick();
    virtual void onRender();
};

class objectHandler {
private:
   

public:

    int numberOfObjects;
    int nextId;
    std::vector<class gameObject *> allObjects;
    objectHandler() {
        this->numberOfObjects = 0;
        this->nextId = 0;
    }
    ~objectHandler() {
        ;;
    }

    void tickAll();
    void renderAll();
    class gameObject *getObject(int id);
    class gameObject *createObject();
    class player *createPlayer(Vector2 position, Vector2 size, int speed);
};
