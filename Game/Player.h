//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Player.h
//!
//! @brief  プレイヤーオブジェクトのヘッダファイル
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//プレイヤーの初期化
void InitializePlayer();

//プレイヤーの更新
void UpdatePlayer();

//プレイヤーの描画
void DrawPlayer();

//SPと召喚可能なモンスターのリストの描画
void DrawPlayerUI();

//プレイヤーの座標を取得する
Vector2DF GetPlayerPos();

//プレイヤーの座標を設定する
void SetPlayerPos(Vector2DF pos);

//プレイヤーの召喚可能モンスターを設定する
void SetPlayerSummonable(BOOL summonable[]);

//プレイヤーの地面判定を設定する
void SetPlayerIsGround(BOOL isGround);

//プレイヤーの当たり判定を設定する
void SetPlayerCollider(BoxCollider *collider);

//プレイヤーがお宝を取得したときの処理
void PlayerGetTreasure();

//プレイヤーが敵と衝突したときの処理
//void CollisionPlayer();


