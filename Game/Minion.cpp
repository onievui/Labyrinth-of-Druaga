#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"
#include <math.h>


//定数の定義
#define GHOST_SPEED		(3)		//ゴーストの移動速度



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
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		12,
		0,
		{ 1,32 }
	};
	proto_minion[MINION_SLIME].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_minion[MINION_SLIME].sprite_num);

	//ゴースト
	proto_minion[MINION_GHOST] =
	{
		MINION_GHOST,
		1,
		1,
		{ 0,0 },
		{ -29,-29,29,25 },
		{ 0,0 },
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		66,
		0,
		{ 3,64 }
	};
	proto_minion[MINION_GHOST].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_minion[MINION_GHOST].sprite_num);
}


//スライムの更新
void UpdateMinionSlime(Minion *minion) {

	//移動量を座標に足す
	AddVector2DF(minion->pos, minion->vel);

	//着地していたなら速度を0にする
	if ((minion->collision_state & ISGROUND) && minion->vel.y > 0) {
		minion->vel.y = 0;
	}
	//上昇していたら地面から離れたとみなす
	else if (minion->vel.y > 0) {
		minion->ground_flag = FALSE;
	}

	//横方向の速度をリセットする
	minion->vel.x = 0;
	
	//マップとの着地判定の適用
	if ((minion->collision_state |= minion->ground_flag*ISGROUND) & ISGROUND) {
		minion->vel.y = 0;
	}
	else {
		//重力を加える
		minion->vel.y += GRAVITY;
	}

	//乗っているオブジェクトの速度を加える
	if (minion->ride) {
		AddVector2DF(minion->vel, *minion->ride);
	}

}

//ゴーストの更新
void UpdateMinionGhost(Minion *minion) {

	//移動量を座標に足す
	AddVector2DF(minion->pos, minion->vel);

	//移動処理
	if (minion->is_left) {
		minion->vel.x = -GHOST_SPEED;
	}
	else {
		minion->vel.x = GHOST_SPEED;
	}

	//マップとの当たり判定
	if (minion->is_left && (minion->collision_state & ISLEFT)) {
		minion->is_left = !minion->is_left;
		minion->sprite_num++;
		minion->graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, minion->sprite_num);
		minion->collision_state -= ISLEFT;
	}
	else if (!minion->is_left && (minion->collision_state & ISRIGHT)) {
		minion->is_left = !minion->is_left;
		minion->sprite_num--;
		minion->graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, minion->sprite_num);
		minion->collision_state -= ISRIGHT;
	}
}

//スライムの描画
void DrawMinionSlime(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
	
}

//ゴーストの描画
void DrawMinionGhost(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
	/*Vector2DF pos = minion->pos;
	SubVector2DF(pos, OrderGetCameraOffset());
	RectF rect = { pos.x + minion->col.left,
	pos.y + minion->col.top,
	pos.x + minion->col.right,
	pos.y + minion->col.bottom };
	DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_RED, 0);*/
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
	OrderAddPlayerSp(minion->s_dat.cost);
}

//ゴーストの消滅
void DestroyMinionGhost(Minion *minion) {
	minion->state = 0;
	OrderAddPlayerSp(minion->s_dat.cost);
}



