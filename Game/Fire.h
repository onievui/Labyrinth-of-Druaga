#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"




//ドラゴンの炎の初期化
void InitializeFire();

//ドラゴンの炎の生成
BOOL CreateFire(Minion *parent);

//ドラゴンの炎の更新
void UpdateFire();

//ドラゴンの炎の描画
void DrawFire();

//ドラゴンの炎の当たり判定の設定
void SetFireCollider(BoxCollider collider[]);

//ドラゴンの炎の親オブジェクトへのポインタの変更
void ChangeFireParentPt(Minion *pre_parent, Minion *new_parent);

//ドラゴンの炎の親が消えたことの通知
void DestroyFire(Minion *parent);

