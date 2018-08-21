#pragma once




//ヘッダファイルの読み込み
#include "GameObjectStruct.h"




//グローバル変数の初期化
void InitializeMediator();

//選択中のステージの設定
void SetSelectStage(StageId stageId);

//選択中のステージの取得
StageId GetSelectStage();

//プレイ画面のクリア時間の記憶
void SetClearTime(int time);

//プレイ画面のクリア時間の取得
int GetClearTime();

//プレイヤーの座標を取得する依頼
Vector2DF OrderGetPlayerPos();

//プレイヤーの座標を設定する依頼
void OrderSetPlayerPos(Vector2DF pos);

//プレイヤーの地面判定を設定する依頼
void OrderSetPlayerIsGround(BOOL isGround);

//プレイヤーの当たり判定を設定する依頼
void OrderSetPlayerCollider(BoxCollider *collider);

//プレイヤーがお宝を取得したときの処理依頼
void OrderPlayerGetTreasure();

//召喚モンスターの生成依頼
int OrderCreateMinion(MinionPattern knd, Vector2DF pos, BOOL isLeft);

//お宝の座標を設定する
void OrderSetTreasurePos(Vector2DF pos);

//お宝の当たり判定を設定する
void OrderSetTreasureCollider(BoxCollider *collider);

//お宝がプレイヤーと衝突したときの処理依頼
void OrderCollisionTreasure();

//マップを取得する依頼
MapData OrderGetMap();

//指定した座標が通過不可マスかどうかの依頼
BOOL OrderIsMapPosWall(float x, float y);

//オブジェクトとマップの当たり判定依頼
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);

//カメラのオフセットを取得する依頼
Vector2DF OrderGetCameraOffset();

