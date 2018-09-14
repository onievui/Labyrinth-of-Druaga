#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//敵の魔法の初期化
void InitializeMagics();

//敵の魔法の生成
BOOL CreateMagic(MagicPattern knd, Vector2DF *pos, BOOL isLeft);

//敵の魔法の更新
void UpdateMagics();

//敵の魔法の描画
void DrawMagics();

//敵の魔法の当たり判定の設定
void SetMagicsCollider(BoxCollider collider[]);

//敵の魔法の壁衝突処理
BOOL CollisionMagic(int i);

//敵の魔法の消滅
void DestroyMagic(int i);

//敵の魔法のダメージ量の取得
int GetMagicPower(int i);


