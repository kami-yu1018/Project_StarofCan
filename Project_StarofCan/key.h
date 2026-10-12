#pragma once

///	ここにキー入力設定用関数を定義
extern int key_count;

bool CheckHitKey(int key);	//	キー押下状態の処理
bool PushHitKey(int key);	//	キーを押した瞬間の処理
