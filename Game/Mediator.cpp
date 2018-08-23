#pragma once




//ヘッダファイルの読み込み
#include "Mediator.h"
#include "Map.h"
#include "Player.h"
#include "MinionManager.h"
#include "Treasure.h"
#include "Collision.h"



//グローバル変数の宣言
static StageId g_select_stage;	//選択中のステージ
static int g_clear_time;		//ステージクリアまでの時間




//グローバル変数の初期化
void InitializeMediator() {
	g_select_stage = (StageId)-1;
	g_clear_time = -1;
}

//選択中のステージの設定
void SetSelectStage(StageId stageId) {
	g_select_stage = stageId;
}

//選択中のステージの取得
StageId GetSelectStage() {
	return g_select_stage;
}

//プレイ画面のクリア時間の設定
void SetClearTime(int time) {
	g_clear_time = time;
}

//プレイ画面のクリア時間の取得
int GetClearTime() {
	return g_clear_time;
}

//プレイヤーの座標を取得する依頼
Vector2DF OrderGetPlayerPos() {
	return GetPlayerPos();
}

//プレイヤーの座標を設定する依頼
void OrderSetPlayerPos(Vector2DF pos) {
	SetPlayerPos(pos);
}

//プレイヤーの地面判定を設定する依頼
void OrderSetPlayerIsGround(BOOL isGround) {
	SetPlayerIsGround(isGround);
}

//プレイヤーの召喚可能モンスターを設定する依頼
void OrderSetPlayerSummonable(BOOL summonable[]) {
	SetPlayerSummonable(summonable);
}

//プレイヤーの当たり判定を設定する依頼
void OrderSetPlayerCollider(BoxCollider *collider) {
	SetPlayerCollider(collider);
}

//プレイヤーがお宝を取得したときの処理依頼
void OrderPlayerGetTreasure() {
	PlayerGetTreasure();
}

//召喚モンスターの生成依頼
int OrderCreateMinion(MinionPattern knd, Vector2DF pos, RectF pl_col, BOOL isLeft) {
	return CreateMinion(knd, pos, pl_col, isLeft);
}

//召喚モンスターの当たり判定の設定依頼
void OrderSetMinionsCollider(BoxCollider collider[]) {
	SetMinionsCollider(collider);
}

//お宝の座標を設定する
void OrderSetTreasurePos(Vector2DF pos) {
	SetTreasurePos(pos);
}

//お宝の当たり判定を設定する
void OrderSetTreasureCollider(BoxCollider *collider) {
	SetTreasureCollider(collider);
}

//お宝がプレイヤーと衝突したときの処理依頼
void OrderCollisionTreasure() {
	CollisionTreasure();
}

//マップを取得する依頼
MapData OrderGetMap() {
	return GetMap();
}

//指定した座標が通過不可マスかどうかの依頼
BOOL OrderIsMapPosWall(float x, float y) {
	return IsMapPosWall(x, y);
}

//オブジェクトとマップの当たり判定依頼
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col) {
	return CollisionObjectMap(pos, vel, col);
}

//カメラのオフセットを取得する依頼
Vector2DF OrderGetCameraOffset() {
	return GetCameraOffset();
}


