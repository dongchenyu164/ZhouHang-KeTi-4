#pragma once
#include "Define.h"

typedef unsigned char u8;

enum MovingDirection;

class Node
{
public:
	u8 Coast;
	bool IsOpen;
	u8 Layer;
	MovingDirection Move;
	u8 X;
	u8 Y;

	Node* Pre;
	Node* Self;
	//Node* Next[4];
private:
	u8 NumOfNext;

public:
	Node(u8 X,
		u8 Y,
		u8 _Coast,
		bool _IsOpen,
		u8 _Layer,
		MovingDirection _Move,
		Node* _Pre);
	bool operator<(const Node& R);
	friend bool operator<(const Node& L, const Node& R);
	//bool operator>(const Node& R);
	//friend bool operator>(const Node& L, const Node& R);
	Node();
	~Node();
	void AddToNext(Node* _Node);
};

