#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "MagicManager.h"
#include "Sound.h"


//定数の定義



//敵モンスターのプロトタイプの初期化
void InitializePrototypeEnemy(Enemy proto_enemy[]) {

	//ドルイド
	proto_enemy[ENEMY_DRUID] =
	{
		ENEMY_DRUID,
		1,
		0,
		1,
		{ 0,0 },
		{ -18,-30,18,30 },
		{ 0,0 },
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		46,
		0
	};
	proto_enemy[ENEMY_DRUID].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_enemy[ENEMY_DRUID].sprite_num);

	//ウィザード
	proto_enemy[ENEMY_WIZARD] =
	{
		ENEMY_WIZARD,
		1,
		0,
		1,
		{ 0,0 },
		{ -18,-30,18,30 },
		{ 0,0 },
		NULL,
		TRUE,
		0,
		FALSE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		50,
		0
	};
	proto_enemy[ENEMY_WIZARD].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, proto_enemy[ENEMY_WIZARD].sprite_num);
	
}


//ドルイドの更新
void UpdateEnemyDruid(Enemy *enemy) {



	//移動量を座標に足す
	AddVector2DF(enemy->pos, enemy->vel);

	//着地していたなら速度を0にする
	if ((enemy->collision_state & ISGROUND) && enemy->vel.y > 0) {
		enemy->vel.y = 0;
	}
	//上昇していたら地面から離れたとみなす
	else if (enemy->vel.y > 0) {
		enemy->ground_flag = FALSE;
	}

	//横方向の速度をリセットする
	enemy->vel.x = 0;

	//60フレームに1回白魔法を撃ち出す
	if (enemy->count % 60 == 59) {
		CreateMagic(MAGIC_WHITE, &enemy->pos, enemy->is_left);
	}

	//マップとの着地判定の適用
	if (enemy->ground_flag) {
		//着地している判定にする
		enemy->collision_state |= ISGROUND;
		//速度を0にする
		enemy->vel.y = 0;
	}
	else {
		//着地していない判定に戻す
		enemy->collision_state &= ~ISGROUND;
		//重力を加える
		enemy->vel.y += GRAVITY;
	}

	//乗っているオブジェクトの速度を加える
	if (enemy->ride) {
		AddVector2DF(enemy->vel, *enemy->ride);
	}


	enemy->count++;

}

//ウィザードの更新
void UpdateEnemyWizard(Enemy *enemy) {



	//移動量を座標に足す
	AddVector2DF(enemy->pos, enemy->vel);

	//着地していたなら速度を0にする
	if ((enemy->collision_state & ISGROUND) && enemy->vel.y > 0) {
		enemy->vel.y = 0;
	}
	//上昇していたら地面から離れたとみなす
	else if (enemy->vel.y > 0) {
		enemy->ground_flag = FALSE;
	}

	//横方向の速度をリセットする
	enemy->vel.x = 0;

	//60フレームに1回緑魔法を撃ち出す
	if (enemy->count % 60 == 59) {
		CreateMagic(MAGIC_GREEN, &enemy->pos, enemy->is_left);
	}

	//マップとの着地判定の適用
	if (enemy->ground_flag) {
		//着地している判定にする
		enemy->collision_state |= ISGROUND;
		//速度を0にする
		enemy->vel.y = 0;
	}
	else {
		//着地していない判定に戻す
		enemy->collision_state &= ~ISGROUND;
		//重力を加える
		enemy->vel.y += GRAVITY;
	}

	//乗っているオブジェクトの速度を加える
	if (enemy->ride) {
		AddVector2DF(enemy->vel, *enemy->ride);
	}


	enemy->count++;

}

//ドルイドの描画
void DrawEnemyDruid(Enemy *enemy) {
	DrawGraphicToMap(enemy->pos, &enemy->graph);
	/*Vector2DF pos = enemy->pos;
	SubVector2DF(pos, OrderGetCameraOffset());
	RectF rect = { pos.x + enemy->col.left,
	pos.y + enemy->col.top,
	pos.x + enemy->col.right,
	pos.y + enemy->col.bottom };
	DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_BLUE, 0);*/
}

//ウィザードの描画
void DrawEnemyWizard(Enemy *enemy) {
	DrawGraphicToMap(enemy->pos, &enemy->graph);
}

//ドルイドのダメージ処理
BOOL DamageEnemyDruid(Enemy *enemy, int power) {
	enemy->hp -= power;
	//体力が0なら通知する
	if (enemy->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//ウィザードのダメージ処理
BOOL DamageEnemyWizard(Enemy *enemy, int power) {
	enemy->hp -= power;
	//体力が0なら通知する
	if (enemy->hp <= 0) {
		return TRUE;
	}
	return FALSE;
}

//ドルイドの消滅
void DestroyEnemyDruid(Enemy *enemy) {
	enemy->state = 0;
	SetSE(SE_ENEMY_STRIKE);
}

//ウィザードの消滅
void DestroyEnemyWizard(Enemy *enemy) {
	enemy->state = 0;
	SetSE(SE_ENEMY_STRIKE);
}




