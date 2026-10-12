#include<stdio.h>
#include<windows.h>
#include"Key.h"

//	キー押下状態にTRUEを返す
bool CheckHitKey(int key)
{
	if (GetAsyncKeyState(key))
	{
		return true;
	}
	return false;
}

//	キーを押した瞬間にTRUEを返す
bool PushHitKey(int key)
{
	if (GetAsyncKeyState(key))
	{
		count++;
	}

	if (count == 1)
	{
		return true;
	}
	else
	{
		count = 0;
		return false;
	}
}