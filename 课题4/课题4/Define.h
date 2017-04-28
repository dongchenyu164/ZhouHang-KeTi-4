#pragma once
#define _WORLDSIZE_Y_ 4
#define _WORLDSIZE_X_ 4
#define _DISTURB_STEP_ 14

#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <queue> 
#include <math.h>

typedef unsigned char u8;

enum ValideDirection
{
	SD = 1, AS = 2, WD = 3, WA = 4, ASD = 5, WSD = 6, WAS = 7, WAD = 8, WASD = 9
};
enum MovingDirection
{
	STOP = -1, NONE = 0, W, A, S, D
};

u8 InitialDir();
void Display();

extern MovingDirection Step[1000];
extern u8 Play[4][4];
extern bool Diff[4][4];
extern MovingDirection Dir_Initial[_DISTURB_STEP_];
extern ValideDirection VD[16];