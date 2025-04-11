#include "object.h"

// ----- GameObject -----

int GameObject::getId() {
    return this->id;
}

void GameObject::setId(int id) {
    this->id = id;
}

void GameObject::onTick(const std::vector<Rectangle> collidables) {
    printf("I am a generic object, my id is %d, and I have been ticked\n", this->id);
    return;
}

void GameObject::onRender() {
    return;
}

// ----------

// ----- ObjectHandler -----

class GameObject *ObjectHandler::createObject() {
    class GameObject *newObject = new GameObject(this->nextId++);
    this->allObjects.push_back(newObject);
    this->numberOfObjects++;
    return newObject;
}

class GameObject *ObjectHandler::getObject(int id) {
    return this->allObjects[id];
}

void ObjectHandler::tickAll(const std::vector<Rectangle> collidables) {
    for (int x = 0; x < this->numberOfObjects; x++) {
        this->allObjects[x]->onTick(collidables);
    }
}

void ObjectHandler::renderAll()
{
    for (int x = 0; x < this->numberOfObjects; x++) 
    {
        this->allObjects[x]->onRender();
    }
}
