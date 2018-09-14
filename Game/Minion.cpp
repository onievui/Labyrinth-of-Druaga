#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"
#include "Fire.h"


//定数の定義
#define GHOST_SPEED		(3)		//ゴーストの移動速度



//召喚モンスターのプロトタイプの初期化
void InitializePrototypeMinion(Minion proto_minion[], SummonData s_data[]) {

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
		0
	};
	s_data[MINION_SLIME] =
	{
		1,
		32,
		{1,0},
		FALSE
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
		0
	};
	s_data[MINION_GHOST] =
	{
		3,
		64,
		{ 1,0 },
		1
	};
	proto_minion[MINION_GHOST].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_minion[MINION_GHOST].sprite_num);

	//クオックス
	proto_minion[MINION_QUOX] =
	{
		MINION_QUOX,
		1,
		5,
		{ 0,0 },
		{ -31,-26,31,32 },//{ -25,-15,25,32 },
		{ 0,0 },
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_DRAGON],1.0,0.0 },
		5,
		0,
	};
	s_data[MINION_QUOX] =
	{
		5,
		64,
		{ 1,0 },
		3
	};
	proto_minion[MINION_QUOX].graph.sprite.rect = GetSpriteRect(SPR_STD_DRAGON, proto_minion[MINION_QUOX].sprite_num);
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
	if (minion->ground_flag) {
		//着地している判定にする
		minion->collision_state |= ISGROUND;
		//速度を0にする
		minion->vel.y = 0;
	}
	else {
		//着地していない判定に戻す
		minion->collision_state &= ~ISGROUND;
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

//クオックスの更新
void UpdateMinionQuox(Minion *minion) {



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

	//60フレーム経過したら130フレーム1回炎を吐く
	if (minion->anime_count % 130 == 60) {
		//炎を生成する
		CreateFire(minion);
		//炎を吐き出している画像に変更する
		minion->sprite_num = 26 + !minion->is_left;
		minion->graph.sprite.rect = GetSpriteRect(SPR_STD_DRAGON, minion->sprite_num);
	}


	//マップとの着地判定の適用
	if (minion->ground_flag) {
		//着地している判定にする
		minion->collision_state |= ISGROUND;
		//速度を0にする
		minion->vel.y = 0;
	}
	else {
		//着地していない判定に戻す
		minion->collision_state &= ~ISGROUND;
		//重力を加える
		minion->vel.y += GRAVITY;
	}

	//乗っているオブジェクトの速度を加える
	if (minion->ride) {
		AddVector2DF(minion->vel, *minion->ride);
	}

	minion->anime_count++;

}

//スライムの描画
void DrawMinionSlime(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
	
}

//ゴーストの描画
void DrawMinionGhost(Minion *minion) {
	DrawGraphicToMap(minion->pos, &minion->graph);
}

//クオックスの描画
void DrawMinionQuox(Minion *minion) {
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

//クオックスのダメージ処理
BOOL DamageMinionQuox(Minion *minion, int power) {
	minion->hp -= power;
	//体力が0なら通知する
	if (minion->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//スライムの消滅
void DestroyMinionSlime(Minion *minion, SummonData *s_dat) {
	minion->state = 0;
	OrderAddPlayerSp(s_dat->cost);
}

//ゴーストの消滅
void DestroyMinionGhost(Minion *minion, SummonData *s_dat) {
	minion->state = 0;
	OrderAddPlayerSp(s_dat->cost);
}

//クオックスの消滅
void DestroyMinionQuox(Minion *minion, SummonData *s_dat) {
	minion->state = 0;
	OrderAddPlayerSp(s_dat->cost);
	//子オブジェクトの炎を消す
	DestroyFire(minion);
}



