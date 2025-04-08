#include "object.h"

// ----- gameObject -----

int gameObject::getId() {
    return this->id;
}

void gameObject::setId(int id) {
    this->id = id;
}

void gameObject::onTick(const std::vector<Rectangle> collidables) {
    printf("I am a generic object, my id is %d, and I have been ticked\n", this->id);
    return;
}

void gameObject::onRender() {
    return;
}

// ----------

// ----- objectHandler -----

class gameObject *objectHandler::createObject() {
    class gameObject *newObject = new gameObject(this->nextId++);
    this->allObjects.push_back(newObject);
    this->numberOfObjects++;
    return newObject;
}

class gameObject *objectHandler::getObject(int id) {
    return this->allObjects[id];
}

void objectHandler::tickAll(const std::vector<Rectangle> collidables) {
    for (int x = 0; x < this->numberOfObjects; x++) {
        this->allObjects[x]->onTick(collidables);
    }
}

void objectHandler::renderAll()
{
    for (int x = 0; x < this->numberOfObjects; x++) 
    {
        this->allObjects[x]->onRender();
    }
}
