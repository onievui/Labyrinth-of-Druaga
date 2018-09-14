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

//プレイヤー関係の情報の描画
void DrawPlayerUI();

//プレイヤーの座標を取得する
Vector2DF GetPlayerPos();

//プレイヤーの座標を設定する
void SetPlayerPos(Vector2DF pos);

//プレイヤーの召喚可能モンスターを設定する
void SetPlayerSummonable(BOOL summonable[]);

//プレイヤーのSPを設定する
void SetPlayerSp(int sp);

//プレイヤーの当たり判定を設定する
void SetPlayerCollider(BoxCollider *collider);

//プレイヤーのSPを回復する
void AddPlayerSp(int plus);

//プレイヤーがお宝を取得したときの処理
void PlayerGetTreasure();

//プレイヤーがダメージ判定と衝突したときの処理
void CollisionPlayer();


