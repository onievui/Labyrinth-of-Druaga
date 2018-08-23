//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Treasure.cpp
//!
//! @brief  お宝オブジェクトの処理
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"


//グローバル変数の宣言
Treasure g_treasure;


//お宝の初期化
void InitializeTreasure() {
	g_treasure.state = 1;
	g_treasure.pos = Vector2DF{ (float)FIELD_CENTER_X,(float)FIELD_HEIGHT - 100 };
	g_treasure.col = RectF{ -32,-13,20,24 };
	g_treasure.vel = Vector2DF{ 0,0 };
	g_treasure.graph = Graph{ g_sprite[SPR_OBJECT_TREASURE],1.0,0.0 };
	
}

//お宝の更新
void UpdateTreasure() {

	//重力を加える
	g_treasure.vel.y += GRAVITY;

	//マップとの当たり判定
	OrderCollisionObjectMap(&g_treasure.pos, &g_treasure.vel, &g_treasure.col);

	//移動量を座標に足す
	AddVector2DF(g_treasure.pos, g_treasure.vel);
}

//お宝の描画
void DrawTreasure() {
	if (g_treasure.state) {
		DrawGraphicToMap(g_treasure.pos, &g_treasure.graph);
	}
}

//お宝の座標を設定する
void SetTreasurePos(Vector2DF pos) {
	g_treasure.pos = pos;
}

//お宝の当たり判定を設定する
void SetTreasureCollider(BoxCollider *collider) {
	collider->state = &g_treasure.state;
	collider->pos = &g_treasure.pos;
	collider->vel = &g_treasure.vel;
	collider->col = &g_treasure.col;
}

//お宝がプレイヤーと衝突したときの処理
void CollisionTreasure() {
	g_treasure.state = 0;
}