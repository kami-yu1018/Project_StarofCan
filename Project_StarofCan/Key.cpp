#include<stdio.h>
#include<windows.h>
#include"Key.h"

int key_count = 0;

//	キー押下状態にTRUEを返す
bool CheckHitKey(int key)
{
	if (GetAsyncKeyState(key)&0x8000)
	{
		return true;
	}
	return false;
}

//	キーを押した瞬間にTRUEを返す
bool PushHitKey(int key)
{
	if (GetAsyncKeyState(key)&0x8000)
	{
		key_count++;
	}

	if (key_count == 1)
	{
		return true;
	}
	else
	{
		key_count = 0;
		return false;
	}
}