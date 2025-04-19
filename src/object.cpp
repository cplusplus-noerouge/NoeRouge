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
    class GameObject *newObject = new GameObject(nextId++);
    allObjects[newObject->getId()] = newObject; //add <id, object*> to the map
    this->numberOfObjects++;
    return newObject;
}

class GameObject *ObjectHandler::getObject(int id) {
    return this->allObjects[id];
}

/*------------------------------------------------------------------------------------------------------------------
* transferObject() moves an object from this handler to another object handler
* - devon
* param int objId: id of the object being transfered
* param ObjectHandler &newHandler: the handler the object is being transfered to
* return: alters data in this and newHandler
------------------------------------------------------------------------------------------------------------------*/
void ObjectHandler::transferObject(int objId, ObjectHandler &newHandler)
{
    //this assumes the object exists in the current handler, if it doesn't it gives an error when ticking
    newHandler.allObjects[objId] = this->getObject(objId);
    newHandler.numberOfObjects++;

    this->allObjects.erase(objId);
    this->numberOfObjects--;
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

int ObjectHandler::nextId = 1;  //this is shared between all object handlers. starts at 1 bc the player is always 0