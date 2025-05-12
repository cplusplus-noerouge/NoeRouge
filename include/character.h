/*---------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Character class (inherits from GameObject class)
* Ben A, Kaleb, Reese, Ethan
* The Character class is a parent class for any player or enemy character that is rendered on screen and moves.
----------------------------------------------------------------------------------------------------------------------------------------*/

#include "object.h"
#include "objectHandler.h"
#include "raylib.h"

#pragma once
class Objecthandler;

class Character : public GameObject
{
	private:

	Vector2 _size;                       //Character's rectangle size
	
	protected:

	Vector2 _position;                   //Character's map position
	Vector2 direction;                   //Character's direction
	Vector2 velocity;                    //Character's velocity
	Vector2 _target;                     //Position of target.

	public:

	int _speed;                                                                           //Speed of the character in pixels per second.
	bool isDead = false;                                                                  //True if the Character is dead, false if not.
  
	Character( int id, Vector2 position, Vector2 target);                                 //Parameterized Class constructor, including target.
	Character( int id, Vector2 position);                                                 //Parameterized Class constructor.
	Character( int _id = -1 );                                                            //Class constructor based on object ID. 

	void onTick( const std::vector<Rectangle> collidables ) override;                     //Updates the state of the character during a single frame.
	void onRender( ) override;                                                            //Renders the character on screen.

	virtual void updateDirection( );                                                      //Sets the movement direction of the character based on control input.
	void updateDirection( Vector2 target );                                               //Sets the movement direction of the character based on a target position.

	Rectangle bounds( );

	bool collidingLeft( Rectangle other );                                                //Checks for collisions to the left.
	bool collidingRight( Rectangle other );                                               //Checks for collisions to the right.
	bool collidingTop( Rectangle other );                                                 //Checks for collisions to the top.
	bool collidingBottom( Rectangle other );                                              //Checks for collisions to the bottom.
	void updateCollisions( const std::vector<Rectangle> colliders );                      //Detects and resolves collisions between the character and a list of colliders.

	Vector2 getPosition( );                                                               //Getter for the character's position.
	void setPosition( Vector2 newPos );                                                   //Setter for the character's position.

	void moveToTarget( Vector2 _target, float distanceMaintained, std::vector<Rectangle> colliders );  //Moves character to the target's position but maintain a set distance.
	Ray relationToTarget( Vector2 _target );                                              //Calculates the line of sight from the character's position to the target.
	bool updateLOS( const std::vector<Rectangle> colliders, Vector2 _target );            //Updates relation to target and creates line of sight by checking for collisions.
	float getTargetDistance( );                                                           //Calculates the distance between the character and a target.

	~Character( )                                                                         //Destructor
	{

	}
};