//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Treasure.h
//!
//! @brief  お宝オブジェクトのヘッダファイル
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//お宝の初期化
void InitializeTreasure();

//お宝の更新
void UpdateTreasure();

//お宝の描画
void DrawTreasure();

//お宝の座標を設定する
void SetTreasurePos(Vector2DF pos);

//お宝の当たり判定を設定する
void SetTreasureCollider(BoxCollider *collider);

//お宝がプレイヤーと衝突したときの処理
void CollisionTreasure();
