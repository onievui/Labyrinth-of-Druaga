#pragma once




//ヘッダファイルの読み込み
#include "Mediator.h"
#include "Map.h"
#include "Player.h"
#include "Collision.h"



//グローバル変数の宣言
static StageId g_select_stage;	//選択中のステージ




//グローバル変数の初期化
void InitializeMediator() {
	g_select_stage = (StageId)-1;
	
}

//選択中のステージの設定
void SetSelectStage(StageId stageId) {
	g_select_stage = stageId;
}

//選択中のステージの取得
StageId GetSelectStage() {
	return g_select_stage;
}

//プレイヤーの座標を取得する依頼
Vector2DF OrderGetPlayerPos() {
	return GetPlayerPos();
}

//プレイヤーの座標を設定する依頼
void OrderSetPlayerPos(Vector2DF pos) {
	SetPlayerPos(pos);
}

//プレイヤーの当たり判定を設定する依頼
void OrderSetPlayerCollider(BoxCollider *collider) {
	SetPlayerCollider(collider);
}

//マップを取得する依頼
MapAll OrderGetMap() {
	return GetMap();
}

//指定した座標が通過不可マスかどうかの依頼
BOOL OrderIsMapPosWall(float x, float y) {
	return IsMapPosWall(x, y);
}

//オブジェクトとマップの当たり判定依頼
BOOL OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col) {
	return CollisionObjectMap(pos, vel, col);
}

