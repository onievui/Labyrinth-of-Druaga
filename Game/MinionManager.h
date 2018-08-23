#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//召喚モンスターの初期化
void InitializeMinions();

//召喚モンスターの生成
int CreateMinion(MinionPattern knd, Vector2DF pos, RectF pl_col, BOOL isLeft);

//召喚モンスターの更新
void UpdateMinions();

//召喚モンスターの描画
void DrawMinions();

//召喚モンスターの当たり判定の設定
void SetMinionsCollider(BoxCollider collider[]);

//召喚モンスターのダメージ処理
void DamageMinion(int i, int power);

//召喚モンスターの消滅
void DestroyMinion(int i);








