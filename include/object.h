#pragma once

#include <cstdio>
#include <vector>
#include <map>
#include "raylib.h"
#include "objectHandler.h"

class ObjectHandler;

class GameObject {
	private:
	int id;


protected:
    ObjectHandler* handler;

public:
    

    GameObject( );
    GameObject( ObjectHandler* handler );
    GameObject( int id );
    ~GameObject() {
        // No memory is currently allocated, do nothing
        ;;
    }

    // Getters
    int getId();
    ObjectHandler* getHandler( );
    // Setters
    void setId(int id);
    void setHandler( ObjectHandler* handler );


	virtual void onTick( const std::vector<Rectangle> collidables );
	// TODO 00

	virtual void onRender( );
};