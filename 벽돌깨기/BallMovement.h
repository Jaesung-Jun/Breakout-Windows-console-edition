#pragma once
#define FALSE 0
#define TRUE 1
#include <Windows.h>
#include <iostream>
#include "struct.h"
#include "LinearAlgebra.h"

using namespace std;

//reference : https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-resolution

class BallMovement {
public:
	Direction calc_direction(short* target);
};