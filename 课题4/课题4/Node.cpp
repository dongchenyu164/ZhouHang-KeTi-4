#include "Define.h"
#include "Node.h"

Node::~Node()
{
}

Node::Node(u8 _X=0,
	u8 _Y=0,
	u8 _Coast = 0,
	bool _IsOpen = 0,
	unsigned int _Layer = 0,
	MovingDirection _Move = NONE,
	Node* _Pre = nullptr)
{
	this->X=_X;
	this->Y=_Y;
	this->Coast = _Coast;
	this->IsOpen = _IsOpen;
	this->Layer = _Layer;
	this->Move = _Move;
	this->Pre = _Pre;
	this->NumOfNext = 0;
	this->Next[0] = NULL;
	this->Next[1] = NULL;
	this->Next[2] = NULL;
	this->Next[3] = NULL;
}
Node::Node()
{
	this->X = 0;
	this->Y = 0;
	this->Coast = 0;
	this->IsOpen = true;
	this->Layer = 0;
	this->Move = NONE;
	this->Pre = NULL;
	this->NumOfNext = 0;
	this->Next[0] = NULL;
	this->Next[1] = NULL;
	this->Next[2] = NULL;
	this->Next[3] = NULL;
}

bool Node::operator<(const Node& R)
{
	if (Layer == R.Layer)
		return Coast > R.Coast;
	else
		return Layer > R.Layer;
}

bool operator<(const Node& L, const Node& R)
{
	//if (L->Layer == R->Layer)
	//	return L->Coast > R->Coast;
	//else
	//	return L->Layer > R->Layer;
	if (L.Layer == R.Layer)
		return L.Coast > R.Coast;
	else
		return L.Layer > R.Layer;
}

void Node::AddToNext(Node* _Node)
{
	if (NumOfNext < 4 && NumOfNext >= 0)
	{
		this->Next[NumOfNext] = _Node;
		NumOfNext++;
	}
}