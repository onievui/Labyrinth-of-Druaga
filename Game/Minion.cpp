#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"
#include <math.h>





//召喚モンスターのプロトタイプの初期化
void InitializePrototypeMinion(Minion proto_minion[]) {

	//スライム
	proto_minion[MINION_SLIME] =
	{
		MINION_SLIME,
		1,
		1,
		{ 0,0 },
		{ -21,-12,21,12 },
		{ 0,0 },
		TRUE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		12,
		0,
		32
	};

	//ゴースト
	proto_minion[MINION_GHOST] =
	{
		MINION_GHOST,
		1,
		1,
		{ 0,0 },
		{ -32,-32,32,32 },
		{ 0,0 },
		TRUE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		66,
		0,
		64
	};
}


//スライムの更新
void UpdateMinionSlime(Minion *minion) {

	//移動量を座標に足す
	AddVector2DF(minion->pos, minion->vel);

	//重力を加える
	minion->vel.y += GRAVITY;

	//マップとの当たり判定
	OrderCollisionObjectMap(&minion->pos, &minion->vel, &minion->col);
	
}

//ゴーストの更新
void UpdateMinionGhost(Minion *minion) {

	//移動量を座標に足す
	AddVector2DF(minion->pos, minion->vel);

	//マップとの当たり判定
	OrderCollisionObjectMap(&minion->pos, &minion->vel, &minion->col);
}

//スライムの描画
void DrawMinionSlime(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
	/*Vector2DF pos = minion->pos;
	SubVector2DF(pos, OrderGetCameraOffset());
	RectF rect = { pos.x + minion->col.left,
	pos.y + minion->col.top,
	pos.x + minion->col.right,
	pos.y + minion->col.bottom };
	DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_RED, 0);*/
}

//ゴーストの描画
void DrawMinionGhost(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
}

//スライムのダメージ処理
BOOL DamageMinionSlime(Minion *minion, int power) {
	minion->hp -= power;
	//体力が0なら通知する
	if (minion->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//ゴーストのダメージ処理
BOOL DamageMinionGhost(Minion *minion, int power) {
	minion->hp -= power;
	//体力が0なら通知する
	if (minion->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//スライムの消滅
void DestroyMinionSlime(Minion *minion) {
	minion->state = 0;
}

//ゴーストの消滅
void DestroyMinionGhost(Minion *minion) {
	minion->state = 0;
}



