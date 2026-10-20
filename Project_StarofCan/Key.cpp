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
    static bool previousKey[256] = {};

    //  現在のキー状態
    bool current = CheckHitKey(key);

    //  前回は話していた今回押された場合のみ true
    bool pushed = current && !previousKey[key];

    //  今回の状態を保存
    previousKey[key] = current;

    return pushed;
}