// exdll.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include "Maze.h"
#include <stdio.h>


#define EXPORT extern "C" __declspec(dllexport)

//  This componet uses operations, provided by container in this structure,
//  to get data from container
IMAZE *pIMaze; 

     
/*---------------------------------------------------------------------------*/
/*                                  Init()                                   */
/*---------------------------------------------------------------------------*/

//  convey primary operations in container to component, so that component
//  can get some data from container. data flow from container to component
EXPORT bool Init(IMAZE *Imaze)
{
	pIMaze = Imaze;			//  interface initialization
	return true;
}


/*---------------------------------------------------------------------------*/
/*                            GetNextDirection()                             */
/*---------------------------------------------------------------------------*/


struct postRecord {
	//  The jump direction from previous position to this position 
	Direction comeDirct;

	/*  false means cooresponding direction is Wall, or had been tried.
	 *  true means corresponding direction has not been tried.
	 */
	bool leftValid;
	bool rightValid;
	bool upValid;
	bool downValid;

	//  for linking to a stack 
	struct postRecord* nStep;
};

//  stack header, is also used as stack top.
struct postRecord* stack;

//  used as global, because it store data that maybe used the next time invoking
//  getNextDirection
Direction gloComeDirct;
bool newNode;

// current stack footprint
bool map[10][10];

/*----- Stack operations -----------------------------------------------------*/

void push(struct postRecord* node)
{

	node->nStep = stack;
	stack = node;
}

void pop()
{
	if(NULL == stack )
	{
		//  TODO: throw exception
		return;
	}
	postRecord* tmp = stack;
	stack = stack->nStep;
	free(tmp);
}

bool empty(struct postRecord* stackHeader)
{
	return (stackHeader == NULL);
}

/*----- miscellies -----------------------------------------------------------*/

//  Get adverse direction of specified direction.
Direction getAdverDirct(Direction direct)
{
	switch (direct) 
	{
	case Left:
		return Right;
		break;
	case Right:
		return Left;
		break;
	case Up:
		return Down;
		break;
	case Down:
		return Up;
		break;
	}
}

//  Is specified direction is position visiting in stack?
bool isDirectionVisiting(Direction dirc)
{
	Position cur = pIMaze->GetCurrentPosition();
	switch (dirc)
	{
		case Left:
			--cur.X;
			break;
		case Right:
			++cur.X;
			break;
		case Up:
			--cur.Y;
			break;
		case Down:
			++cur.Y;
			break;
	}
	return map[cur.X][cur.Y];
}

//  Set values for current position according to current info.
void inspectAround( postRecord* node )
{
	//  detect Left
	if (pIMaze->GetPositionInfo(Left) == Wall )
	{
		node->leftValid = false;
	}
	else if( isDirectionVisiting(Left) )
	{
		node->leftValid = false;
	}
	else
	{
		node->leftValid = true;
	}

	//  detect right
	if (pIMaze->GetPositionInfo(Right) == Wall )
	{
		node->rightValid = false;
	}
	else if( isDirectionVisiting(Right) )
	{
		node->rightValid = false;
	}
	else
	{
		node->rightValid = true;
	}

	//  detect up
	if (pIMaze->GetPositionInfo(Up) == Wall )
	{
		node->upValid = false;
	}
	else if( isDirectionVisiting(Up) )
	{
		node->upValid = false;
	}
	else
	{
		node->upValid = true;
	}

	//  detect down
	if (pIMaze->GetPositionInfo(Down) == Wall )
	{
		node->downValid = false;
	}
	else if( isDirectionVisiting(Down) )
	{
		node->downValid = false;
	}
	else
	{
		node->downValid = true;
	}
}

//  Taging invalid direction of certain position.
void tagInvalid( postRecord* rcd, Direction dirc)
{
	switch(dirc)
	{
		case Left:
			rcd->leftValid = false;
			break;
		case Right:
			rcd->rightValid = false;
			break;
		case Up:
			rcd->upValid = false;
			break;
		case Down:
			rcd->downValid = false;
			break;
	}
}

// Create a frame of stack unit, and initialize it with current position infos.
postRecord* createNode()
{
	//  allocate memory
	postRecord* pRcd = (postRecord*)malloc( sizeof(postRecord) );
	//  inspect 4 direction, if wall of visiting, taging invalid
	inspectAround(pRcd);
	
	//  make the coming direction invalid
	pRcd->comeDirct = gloComeDirct;
	Direction adverse = getAdverDirct( pRcd->comeDirct );
	tagInvalid( pRcd, adverse);

	pRcd->nStep = NULL;
	return pRcd;
}


//  Update stack condition to current reality.
void refreshStatus()
{
	//  if the jump from previous position to current position is forward(not 
	//  withdrawing), create newNode for current position in stack.
	if(newNode)
	{
		Position cur = pIMaze->GetCurrentPosition();
		map[cur.X][cur.Y] = true;
		postRecord* tmp = createNode();
		// adjust stack
		push(tmp);
	}
	//  if previous jump is withdrawing, pop stack and taging invalid path
	else if(!newNode)
	{
		// adjust stack
		Direction tmp = stack->comeDirct;
		pop();
		// modify top record, taging that it is invalid path
		tagInvalid( stack, tmp );
	}
}

//  Return how many directions are untried.
int avaDirctAmt(postRecord* node, Direction* dirc)
{
	int ret = 0;
	*dirc = Left;
	if(node->rightValid == true)
	{
		++ret;
		*dirc = Right;
	}
	if(node->leftValid == true)
	{
		++ret;
		*dirc = Left;
	}
	
	if(node->downValid == true)
	{
		++ret;
		*dirc = Down;
	}
	if(node->upValid == true)
	{
		++ret;
		*dirc = Up;
	}

	return ret;
}

//  If the dirction of current position is untried.
bool isValid(postRecord* rcd, Direction dirc)
{
	switch(dirc)
	{
	case Left:
		return rcd->leftValid;
	case Right:
		return rcd->rightValid;
	case Up:
		return rcd->upValid;
	case Down:
		return rcd->downValid;
	}
}

/*-----GetNextDirection------------------------------------------------------*/

//  Provide direction guidance for container
EXPORT Direction GetNextDirection()
{
	Position cur = pIMaze->GetCurrentPosition();
	Position ext = pIMaze->GetExitPosition();
	Position etr = pIMaze->GetEntracePosition();
	Direction tmp;

	//  If current Position is EntracePosition, initialize variables
	if( cur.X == etr.X && cur.Y == etr.Y )
	{
		stack = NULL;
		newNode = true;
		gloComeDirct = Left;
		for(int i=0;i<=9;++i)
		{
			for(int j=0;j<=9;++j)
			{
				map[i][j] = false;
			}
		}
	}

	//  Update stack status to be identical to current condition
	refreshStatus();

	// If can approach ExitPosition in X axis coordinate 
	if( cur.X > ext.X)
	{
		if( isValid(stack, Left) )
		{
			newNode = true;
			gloComeDirct = Left;
			return Left;
		}
	}
	else if( cur.X < ext.X)
	{
		if( isValid(stack, Right) )
		{
			newNode = true;
			gloComeDirct = Right;
			return Right;
		}
	}


	// If can approach ExitPosition in Y axis coordinate 
	if( cur.Y > ext.Y)
	{
		if( isValid(stack, Up) )
		{
			newNode = true;
			gloComeDirct = Up;
			return Up;
		}
	}
	else if( cur.Y < ext.Y)
	{
		if( isValid(stack, Down) )
		{
			newNode = true;
			gloComeDirct = Down;
			return Down;
		}
	}

	//  Cannot approach Destination directly, and 2 directions remained available
	if(avaDirctAmt(stack, &tmp) ==2)
	{
		newNode = true;

		if(isValid(stack, stack->comeDirct))
		{
			gloComeDirct = stack->comeDirct;
			return stack->comeDirct;
		}
		// TODO:here can be optimized,
		// statistic history directions.
		else
		{
			gloComeDirct = tmp;
			return tmp;
		}
	}

	//  Cannot approach destination directly, and 1 direction remained
	else if(avaDirctAmt(stack, &tmp) == 1)
	{
		if( isValid(stack, tmp) )
		{
			newNode = true;
			gloComeDirct = tmp;
			return tmp;
		}
	}

	//  Dead path
	//  (avaDirctAmt(&curRecord, &tmp) == 0)
	//  Should pop stack and jump to the adverse direction
	else 
	{
		newNode = false;
		map[cur.X][cur.Y] = false;
		return getAdverDirct( stack->comeDirct );
	}



}

/*
EXPORT Direction GetNextDirection()
{
	Direction d = (Direction)(rand() % 4);	// 上下左右随即取一个方向
	while(pIMaze->GetPositionInfo(d) == Wall)
	{
		d = (Direction)(rand() % 4);		//  取下一个方向
	}
	return d;
}
*/

/*---------------------------------------------------------------------------*/
/*                                    Show()                                 */
/*---------------------------------------------------------------------------*/
EXPORT void Show(HDC hdc)					//  显示探险家的图案
{
	HBRUSH yBrush = NULL;
	HPEN hPen = NULL;
	RECT rect;
	
	yBrush = CreateSolidBrush(RGB(255, 255, 0));		// 创建黄色画刷
	hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));		// 创建红色画笔

	SelectObject(hdc, yBrush);
	SelectObject(hdc, hPen);

	rect.left = 0;
	rect.top = 0;
	rect.right = rect.left + 49;
	rect.bottom = rect.top + 49;

	Ellipse(hdc, 0, 0, 49, 49);			// 画大圆圈
	Ellipse(hdc, 10, 10, 39, 39);		// 画小圆圈

	DeleteObject(yBrush);
	DeleteObject(hPen);
}

/*---------------------------------------------------------------------------*/
/*                                  MISC()                                   */
/*---------------------------------------------------------------------------*/
EXPORT void OnSuccess()
{
}
EXPORT void OnError()
{
}
EXPORT void Destroy()
{
}
