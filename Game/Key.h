//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Key.h
//!
//! @brief  キー入力関連のヘッダファイル
//!
//! @date   2018/08/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once


// 関数の宣言 ==============================================================


//キーボードのすべてのキーの押下状態、入力フレーム数を取得する
//この関数を毎フレーム呼び出さないと下の関数を使えません
int GetHitKeyStateAll_2(void);

//特定のキーの入力状態を返す
int CheckStateKey(unsigned char Handle);

//特定のキーを押していない状態から押したかどうかを返す
int CheckHitKeyDown(unsigned char Handle);

//特定のキーを押した状態から離したかどうかを返す
int CheckHitKeyUp(unsigned char Handle);

//２つの特定のキーの後から押されているほうを判別する
// return longer 0:どちらも押されていない 1:第１引数 2:第２引数
int CheckStateKeyLater(unsigned char Handle1, unsigned char Handle2);

//４つの特定のキーの後から押されているほうを判別する
// return longer 0:いずれも押されていない 1 : 第１引数 2 : 第２引数 3 : 第３引数 4 : 第４引数
int CheckStateKeyLater4(unsigned char Handle1, unsigned char Handle2, unsigned char Handle3, unsigned char Handle4);