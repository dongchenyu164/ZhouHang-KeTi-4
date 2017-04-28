#include "Define.h"
#include "Node.h"

Node::~Node()
{
}

Node::Node(u8 _X=0,
	u8 _Y=0,
	u8 _Coast = 0,
	bool _IsOpen = 0,
	u8 _Layer = 0,
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
	Self = this;
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
}

bool Node::operator<(const Node& R)
{
	//return Coast < R.Coast;
	if (Layer == R.Layer)
		return Coast > R.Coast;
	else
		return Layer > R.Layer;
}

bool operator<(const Node& L, const Node& R)
{
	//return L.Coast < R.Coast;
	if (L.Layer == R.Layer)
		return L.Coast > R.Coast;
	else
		return L.Layer > R.Layer;
}

void Node::AddToNext(Node* _Node)
{
	if (NumOfNext < 4 && NumOfNext >= 0)
	{
		//this->Next[NumOfNext] = _Node;
		NumOfNext++;
	}
}