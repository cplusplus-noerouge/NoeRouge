/* noeRouge - characters.h
*  Worked on by: Ben A, Kaleb, Reese, Ethan */

#pragma once				//only include this .h once

#include "object.h"			//The .h for the super class for all game objects
#include "objecthandler.h"  //Class that manages and keeps track of all GameObjects
#include "raylib.h"			//Library with animation, rendering, interactive, and sound tools

class Objecthandler;

/*-------------------------------------------------------------------------------------------------
*  The Character class is a parent class for any player or enemy character that is rendered on 
*  screen and moves.
*  
*  Character class (inherits from GameObject class)
*------------------------------------------------------------------------------------------------*/
class Character : public GameObject
{
	private:

	Vector2 _size;      //Character's rectangle size

	protected:

	Vector2 _position;	//Character's map position
	Vector2 direction;  //Character's direction
	Vector2 velocity;   //Character's velocity
	Vector2 _target;    //Position of target.

	public:

	int _speed;             //Speed of the character in pixels per second.
	bool isDead = false;	//True if the Character is dead, false if not.
	
		//Parameterized Class constructor, including target.
	Character( int id, Vector2 position, Vector2 target);  

		//Parameterized Class constructor.
	Character( int id, Vector2 position);    

		//Class constructor based on object ID. 
	Character( int _id = -1 );                                                  

		//Updates the state of the character during a single frame.
	void onTick( const std::vector<Rectangle> collidables ) override; 

		//Renders the character on screen.
	void onRender( ) override;                                              

		//Sets the movement direction of the character based on control input.
	virtual void updateDirection( );                                            

		//Sets the movement direction of the character based on a target position.
	void updateDirection( Vector2 target );    

		// Creates a Rectangle representing the character's current position and size.
	Rectangle bounds( );

		//Checks for collisions to the left.
	bool collidingLeft( Rectangle other );                                     

		//Checks for collisions to the right.
	bool collidingRight( Rectangle other );                                    

		//Checks for collisions to the top.
	bool collidingTop( Rectangle other );                                      

		//Checks for collisions to the bottom.
	bool collidingBottom( Rectangle other );                                   

		//Detects and resolves collisions between the character and a list of colliders.
	void updateCollisions( const std::vector<Rectangle> colliders );            

		//Getter for the character's position.
	Vector2 getPosition( );  

		//Setter for the character's position.
	void setPosition( Vector2 newPos );                                         

		//Moves character to the target's position but maintain a set distance.
	void moveToTarget( Vector2 _target, float distanceMaintained, std::vector<Rectangle> colliders );  

		//Calculates the line of sight from the character's position to the target.
	Ray relationToTarget( Vector2 _target );        

		//Updates relation to target and creates line of sight by checking for collisions.
	bool updateLOS( const std::vector<Rectangle> colliders, Vector2 _target );	

		//Calculates the distance between the character and a target.
	float getTargetDistance( );                                                 


		//Destructor
	~Character( )                                                               
	{

	}
};

/*  Changes made during commenting by Evan:
*
*	-Added inline comments to #includes
* 
*	-General formating
*/