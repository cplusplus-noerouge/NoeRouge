#include <cstdio>
#include "raylib.h"

#include "object.h"
#include "character.h"

class player : public Character 
{

private:
    ;;

public:
    player(int id): Character(id) { }
    player(int id, Vector2 _position, Vector2 _size, int _speed) : Character(id, _position, _size, _speed) { }
    
    void onRender() override;

    void updateDirection() override;
};
