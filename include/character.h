/*----------------------------------------------------------------------------------------------------------------------------------------
* noeRouge
* Character class
* Ben A, Kaleb, Reese, Ethan
* The Character class is a parent class for any player or enemy character that is rendered on screen and moves.
----------------------------------------------------------------------------------------------------------------------------------------*/

#pragma once
#include "object.h"
#include "raylib.h"

class Character : public GameObject
{
	private:

	Vector2 size;                        //Character's rectangle size

	protected:

	Vector2 position;                    //Character's map position
	Vector2 direction;                   //Character's direction
	Vector2 velocity;                    //Character's velocity
	Vector2 target;                      //Position of target.

	public:

	int speed;                                                                            //Speed of the character in pixels per second.

	//Character( int _id, Vector2 _position, Vector2 _size, Vector2 target, int _speed );   //Parameterized Class constructor, including target.
	Character( int _id, Vector2 _position, Vector2 _size, int _speed );                   //Parameterized Class constructor.
	Character( int _id );                                                                 //Class constructor based on object ID. 

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

	void moveToTarget( Vector2 target, float distanceMaintained, std::vector<Rectangle> colliders );  //
	Ray relationToTarget( );                                                                          //
	bool updateLOS( const std::vector<Rectangle> colliders );                                         //
	float getTargetDistance( );                                                                       //Calculates the distance between the character and a target.

	~Character( )                                                                                     //Destructor
	{

	}
};