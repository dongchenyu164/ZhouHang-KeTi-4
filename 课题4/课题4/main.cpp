#include "Define.h"



u8 Play[4][4] = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
ValideDirection VD[16] = { SD,ASD,ASD,AS,WSD,WASD,WASD,WAS,WSD,WASD,WASD,WAS,WD,WAD,WAD,WA };
std::queue<Node*> Finding;

bool Diff[4][4];
MovingDirection Dir_Initial[_DISTURB_STEP_];
Node Root;

bool Check(u8 Pos_X, u8 Pos_Y, u8 LimitOfLayer);

int main()
{
	Root.Coast = -1;
	srand(12345);//unsigned(time(0))
	u8 Pos=InitialDir();
	Display();
	Check(Pos%4,Pos/4,20);
	return 0;
}

void Display()
{
	for (u8 i = 0; i < 16; i++)
	{
		std::cout << "\t" << (int)*(Play[0] + i);
		if (i % 4 == 3)
		{
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}
	}
}

MovingDirection GetRandomNum(u8 start=1, u8 range=4)
{
	return (MovingDirection)(rand() % range + start);
}
/// 检查从该位置出发，方向是否正确
/// 是否会出4*4的范围
/// 
bool CheckValideDirection(u8* Pos_X, u8* Pos_Y, MovingDirection Dir, MovingDirection PreDir)
{
	switch (Dir)
	{
	case W:
		if (*Pos_Y - 1 < 0 || PreDir==S)
			return false;
		else
			(*Pos_Y)--;
		break;
	case A:
		if (*Pos_X - 1 < 0 || PreDir == D)
			return false;
		else
			(*Pos_X)--;
		break;
	case S:
		if (*Pos_Y + 1 > 3 || PreDir == W)
			return false;
		else
			(*Pos_Y)++;
		break;
	case D:
		if (*Pos_X + 1 > 3 || PreDir == A)
			return false;
		else
			(*Pos_X)++;
		break;
	default:
		break;
	}
	return true;
}
void MovingByDir(u8* Pos_X, u8* Pos_Y, MovingDirection Dir)
{
		switch (Dir)
		{
		case W:
			Play[*Pos_Y + 1][(*Pos_X)] = Play[*Pos_Y][*Pos_X];
			Play[*Pos_Y][(*Pos_X)] = 16;
			break;	  
		case A:		  
			Play[(*Pos_Y)][*Pos_X + 1] = Play[*Pos_Y][*Pos_X];
			Play[(*Pos_Y)][*Pos_X] = 16;
			break;
		case S:
			Play[*Pos_Y - 1][(*Pos_X)] = Play[*Pos_Y][*Pos_X];
			Play[*Pos_Y][(*Pos_X)] = 16;
			break;	   			
		case D:		   			
			Play[(*Pos_Y)][*Pos_X - 1] = Play[*Pos_Y][*Pos_X];
			Play[(*Pos_Y)][*Pos_X] = 16;
			break;
		default:
			break;
		}
}
u8 _Pos_X = 3, _Pos_Y = 3;
u8 InitialDir()
{
	MovingDirection _PreDir = A;
	for (u8 i = 0; i < _DISTURB_STEP_; i++, _PreDir = Dir_Initial[i - 1])
	{
		do
		{
			Dir_Initial[i] = GetRandomNum();
		} while (!CheckValideDirection(&_Pos_X, &_Pos_Y, Dir_Initial[i], _PreDir));
		MovingByDir(&_Pos_X, &_Pos_Y, Dir_Initial[i]);
		//Display();
		//system("pause");
		//system("cls");
	}
	return _Pos_Y * 4 + _Pos_X;
}
//Pos_X,Pos_Y:空位要移到的位置坐标(因为CheckValideDirection函数已经将原始坐标向相应位置 改变)



/*********************************************************************/

u8 CalCoast()
{
	u8 _Sum = 0, _t = 0;
	for (u8 i = 0; i < 16; i++)
	{
		_t = *(Play[0] + i)-1;
		_Sum += labs(_t / 4 - i / 4) + labs(_t % 4 - i % 4);
	}
	return _Sum;
}
void MovingByDir(u8 Pos_X, u8 Pos_Y, MovingDirection Dir)
{
	switch (Dir)
	{
	case W:
		Play[Pos_Y][(Pos_X)] = Play[Pos_Y - 1][Pos_X];
		Play[Pos_Y - 1][(Pos_X)] = 16;
		break;
	case A:
		Play[(Pos_Y)][Pos_X] = Play[Pos_Y][Pos_X - 1];
		Play[(Pos_Y)][Pos_X - 1] = 16;
		break;
	case S:
		Play[Pos_Y][(Pos_X)] = Play[Pos_Y + 1][Pos_X];
		Play[Pos_Y + 1][(Pos_X)] = 16;
		break;
	case D:
		Play[(Pos_Y)][Pos_X] = Play[Pos_Y][Pos_X + 1];
		Play[(Pos_Y)][Pos_X + 1] = 16;
		break;
	default:
		break;
	}
}
void MovingBySeqDir(u8 Pos_X, u8 Pos_Y,u8 Long, MovingDirection Dir[])
{
	while (Long--)
	{
		switch (Dir[Long])
		{
		case NONE:
			break;
		case W:
			MovingByDir(Pos_X, Pos_Y--, W);
			break;
		case A:
			MovingByDir(Pos_X--, Pos_Y, A);
			break;
		case S:
			MovingByDir(Pos_X, Pos_Y++, S);
			break;
		case D:
			MovingByDir(Pos_X++, Pos_Y, D);
			break;
		default:
			break;
		}
	}
}
void ReverseMovingBySeqDir(u8 Pos_X, u8 Pos_Y, MovingDirection Dir[])
{
	u8 i = 0;
	while (Dir[i] > 0)
	{
		switch (Dir[i++])
		{
		case NONE:
			break;
		case W:
			MovingByDir(Pos_X, Pos_Y++, S);
			break;
		case A:
			MovingByDir(Pos_X++, Pos_Y, D);
			break;
		case S:
			MovingByDir(Pos_X, Pos_Y--, W);
			break;
		case D:
			MovingByDir(Pos_X--, Pos_Y, A);
			break;
		default:
			break;
		}

	}
}
void PushCalDirections(u8 Pos_X, u8 Pos_Y,u8 _Layer, MovingDirection _WhereAreYouFrom,Node* Father)
{
	Node* _NewNode = new Node();

	//MovingDirection _Step[100];
	//Node* _t=Father;
	//u8 i = 0;
	//while (_t->Pre!=nullptr)
	//{
	//	_Step[i] = _t->Move;
	//	_t = _t->Pre;
	//	i++;
	//}
	//while (i)
	//{
	//	MovingByDir(Pos_X, Pos_Y, _Step[--i]);
	//}

	switch (_WhereAreYouFrom)
	{
	case NONE:
		break;
	case W:
		MovingByDir(Pos_X, Pos_Y, _WhereAreYouFrom);
		*_NewNode = Node( Pos_X,Pos_Y - 1, CalCoast(), true, _Layer, _WhereAreYouFrom, Father );
		Finding.push(_NewNode);
		Father->AddToNext(_NewNode);
		MovingByDir(Pos_X, Pos_Y - 1, S);
		break;
	case A:
		MovingByDir(Pos_X, Pos_Y, _WhereAreYouFrom);
		*_NewNode = Node(Pos_X - 1,Pos_Y, CalCoast(), true, _Layer, _WhereAreYouFrom, Father);
		Finding.push(_NewNode);
		Father->AddToNext(_NewNode); 
		MovingByDir(Pos_X - 1, Pos_Y, D);
		break;
	case S:
		MovingByDir(Pos_X, Pos_Y, _WhereAreYouFrom);
		*_NewNode = Node(Pos_X,Pos_Y + 1, CalCoast(), true, _Layer, _WhereAreYouFrom, Father);
		Finding.push(_NewNode);
		Father->AddToNext(_NewNode);
		MovingByDir(Pos_X, Pos_Y + 1, W);
		break;
	case D:
		MovingByDir(Pos_X, Pos_Y, _WhereAreYouFrom);
		*_NewNode = Node(Pos_X + 1,Pos_Y, CalCoast(), true, _Layer, _WhereAreYouFrom, Father);
		Finding.push(_NewNode);
		Father->AddToNext(_NewNode);
		MovingByDir(Pos_X + 1, Pos_Y, A);
		break;
	default:
		break;
	}
	//Display();
	//system("pause");
	//system("cls");
}
bool Check(u8 Pos_X, u8 Pos_Y,u8 LimitOfLayer)
{
	MovingDirection _WhereAreYouFrom = NONE;
	u8 _Layer = 1,_X=Pos_X,_Y=Pos_Y;
	Node* _NodeCur=&Root;
	while (1)
	{
		MovingDirection _Step[100];
		Node* _t = _NodeCur;
		u8 i = 0;
		while (_t->Pre != nullptr)
		{
			_Step[i] = _t->Move;
			_t = _t->Pre;
			i++;
		}
		//Display();
		//system("cls");

		MovingBySeqDir(Pos_X, Pos_Y,i,_Step);

		//Display();
		//system("cls");
		//Finding.push({ _X,_Y, CalCoast(), true, _Layer, W, &_NodeCur, NULL });
		//Finding.push({ _X,_Y, CalCoast(), true, _Layer, A, &_NodeCur, NULL });
		//Finding.push({ _X,_Y, CalCoast(), true, _Layer, S, &_NodeCur, NULL });
		//Finding.push({ _X,_Y, CalCoast(), true, _Layer, D, &_NodeCur, NULL });
		//将添加至队列

		switch (VD[_Y * 4 + _X])
		{
		case SD:
			switch (_WhereAreYouFrom)
			{
			case NONE:
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			case W:
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case A:
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			default:
				break;
			}
			break;
		case AS:
			switch (_WhereAreYouFrom)
			{
			case NONE:
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			case W:
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				break;
			case D:
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			default:
				break;
			}
			break;
		case WD:
			switch (_WhereAreYouFrom)
			{
			case NONE:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case A:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				break;
			case S:
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			default:
				break;
			}
			break;
		case WA:
			switch (_WhereAreYouFrom)
			{
			case NONE:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				break;
			case S:
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				break;
			case D:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				break;
			default:
				break;
			}
			break;
		case ASD:
			switch (_WhereAreYouFrom)
			{
			case NONE:
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case W:
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case A:
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			case D:
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			default:
				break;
			}
			break;
		case WSD:
			switch (_WhereAreYouFrom)
			{
			case NONE:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case W:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case A:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			case S:
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			default:
				break;
			}
			break;
		case WAS:
			switch (_WhereAreYouFrom)
			{
			case NONE:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			case W:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				break;
			case S:
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			case D:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			default:
				break;
			}
			break;
		case WAD:
			switch (_WhereAreYouFrom)
			{
			case NONE:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case A:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				break;
			case S:
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case D:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			default:
				break;
			}
			break;
		case WASD:
			switch (_WhereAreYouFrom)
			{
			case NONE:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case W:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case A:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				break;
			case S:
				PushCalDirections(_X, _Y, _Layer, A, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			case D:
				PushCalDirections(_X, _Y, _Layer, W, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, S, _NodeCur);
				PushCalDirections(_X, _Y, _Layer, D, _NodeCur);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		/*while (_Step[i] > 0)
		{
			switch (_Step[i++])
			{
			case NONE:
				break;
			case W:
				MovingByDir(_X, _Y, S);
				break;
			case A:
				MovingByDir(_X, _Y, D);
				break;
			case S:
				MovingByDir(_X, _Y, W);
				break;
			case D:
				MovingByDir(_X, _Y, A);
				break;
			default:
				break;
			}
			
		}
		*/
		ReverseMovingBySeqDir(_X, _Y, _Step);

		if (_NodeCur->Coast == 0)
			break;
		_NodeCur = (Finding.front());
		Finding.pop();
		_Layer = _NodeCur->Layer + 1;
		_X = _NodeCur->X, _Y = _NodeCur->Y;
		_WhereAreYouFrom = _NodeCur->Move;

	}
	
	return true;
}
