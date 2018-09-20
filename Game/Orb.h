#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//オーブの初期化
void InitializeOrbs();

//オーブの生成
BOOL CreateOrb(Vector2DF *pos, int sp);

//オーブの更新
void UpdateOrbs();

//オーブの描画
void DrawOrbs();

//オーブの当たり判定の設定
void SetOrbsCollider(BoxCollider collider[]);

//オーブの消滅処理
void DestroyOrb(int i);




