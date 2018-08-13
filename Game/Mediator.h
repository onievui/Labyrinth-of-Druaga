#pragma once




//ヘッダファイルの読み込み
#include "GameObjectStruct.h"




//グローバル変数の初期化
void InitializeMediator();

//選択中のステージの設定
void SetSelectStage(StageId stageId);

//選択中のステージの取得
StageId GetSelectStage();

//プレイヤーの座標を取得する依頼
Vector2DF OrderGetPlayerPos();

//プレイヤーの座標を設定する依頼
void OrderSetPlayerPos(Vector2DF pos);

//プレイヤーの当たり判定を設定する依頼
void OrderSetPlayerCollider(BoxCollider *collider);

//マップを取得する依頼
MapAll OrderGetMap();

//指定した座標が通過不可マスかどうかの依頼
BOOL OrderIsMapPosWall(float x, float y);

//オブジェクトとマップの当たり判定依頼
int OrderCollisionObjectMap(Vector2DF *pos, Vector2DF *vel, RectF *col);

//カメラのオフセットを取得する依頼
Vector2DF OrderGetCameraOffset();

