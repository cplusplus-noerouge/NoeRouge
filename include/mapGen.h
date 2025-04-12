#pragma once

#include <raylib.h>
#include <iostream>
#include <vector>
#include <list>

using namespace std;

constexpr int WIDTH = 70;               //width/columns/maximum x of each floor in tiles
constexpr int HEIGHT = 30;              //height/rows/maximum y of each floor in tiles
constexpr int MINSIZE = 10;             //minimum for each partition/BSP leaf's width and height

constexpr int TILE_SIZE = 8;            //tile size in pixels, the width and height of every tile.

constexpr char WALL = '#';              //char to represent walls
constexpr char FLOOR = '.';             //char to represent floors
constexpr char DEBUGPARTITION = '*';    //a wall that is within a partition aka an ok place for rooms to spawn
constexpr char PLAYER_SPAWN = 'p';      //The spot which designates where the player will spawn

//BSP STUFF START=============================================================================================================================
// Class representing a node in the BSP tree
class BspNode {
public:
    int x, y, width, height;         // Position and size of the node
    BspNode* left;                   // Pointer to the left child node
    BspNode* right;                  // Pointer to the right child node

    BspNode(int x, int y, int width, int height) :
        x(x), y(y), width(width), height(height), left(nullptr), right(nullptr)
    {
    }

    // Function to split the node into two child nodes
    bool split();

    //added this method -devon
    list<BspNode*> getAllLeafNodes();
};
//BSP STUFF END=============================================================================================================================

//renamed this and removed const params -devon
BspNode* generateBspTree();

// Function to print the dungeon split scheme
void printPartitions(BspNode* node, vector<vector<char>>& map); //renamed this -devon

//replace this with the std function im just lazy
int randRange(int minVal, int maxVal);

void makeRectRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

void makeFullRectRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

void makeCircleRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

void makeBlobRoom(BspNode& p, char(&map)[WIDTH][HEIGHT]);

//this is prob temporary
void makeRoomOfShape(char shape, BspNode& p, char(&map)[WIDTH][HEIGHT]);

class Floor {
public:
        //TODO make this private with accessor or something like that
    char data[WIDTH][HEIGHT];//TODO make this private with accessor or something like that
        //additional member variables are probably data structures for items and enemies

    Floor(char roomShape);

        //will eventually return a list of colliders near a position, right now just returns all colliders.
    std::vector<Rectangle> getNearCollidables();
};