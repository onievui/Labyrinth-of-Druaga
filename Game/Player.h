//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  プレイヤーオブジェクトのヘッダファイル
//!
//! @date   2018/08/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダーファイルの読み込み
#include "Vector2DF.h"
//#include "Collision.h"



//プレイヤーの初期化
void InitializePlayer();

//プレイヤーの更新
void UpdatePlayer();

//プレイヤーの描画
void DrawPlayer();

//プレイヤーの座標を取得する
Vector2DF GetPlayerPos();


//プレイヤーの当たり判定を設定する
//void SetPlayerCollider(CircleCollider *collider);

//プレイヤーが敵と衝突したときの処理
//void CollisionPlayer();


