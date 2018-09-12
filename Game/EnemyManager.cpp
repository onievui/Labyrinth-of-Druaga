#pragma once



//ヘッダファイルの読み込み
#include "Enemy.h"
#include "Mediator.h"






//プロトタイプ宣言
void DestroyEnemy(int i);


//グローバル変数の宣言
Enemy g_prototype_enemy[ENEMY_PATTERN_NUM];	//敵モンスターのプロトタイプ
Enemy g_enemy[ENEMY_MAX];					//敵モンスターオブジェクト
int g_active_enemy_num;						//使用中の敵モンスターの数


//各敵モンスターの更新処理の関数ポインタ
void(*g_update_enemy[ENEMY_PATTERN_NUM])(Enemy *enemy) = {
	UpdateEnemyDruid,
	UpdateEnemyWizard
};

//各敵モンスターの描画処理の関数ポインタ
void(*g_draw_enemy[ENEMY_PATTERN_NUM])(Enemy *enemy) = {
	DrawEnemyDruid,
	DrawEnemyWizard
};

//各敵モンスターのダメージ処理の関数ポインタ
BOOL(*g_damage_enemy[ENEMY_PATTERN_NUM])(Enemy *enemy, int power) = {
	DamageEnemyDruid,
	DamageEnemyWizard
};

//各敵モンスターの消滅処理の関数ポインタ
void(*g_destroy_enemy[ENEMY_PATTERN_NUM])(Enemy *enemy) = {
	DestroyEnemyDruid,
	DestroyEnemyWizard
};


//敵モンスターの初期化
void InitializeEnemies() {

	//データの初期化
	memset(g_enemy, 0, sizeof(g_enemy));

	//敵モンスターのプロトタイプの初期化
	InitializePrototypeEnemy(g_prototype_enemy);

	//カウンタのリセット
	g_active_enemy_num = 0;
}


//敵モンスターの生成
BOOL CreateEnemies(EnemyList enemy_list[]) {

	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		//使われるかどうか
		if (enemy_list[i].is_use) {
			//エラーチェック
			if (enemy_list[i].knd < 0 || enemy_list[i].knd >= ENEMY_PATTERN_NUM) {
				MessageBox(NULL, "敵モンスターの生成で不正な値が渡されました", "", MB_OK);
				return FALSE;
			}
			//敵モンスターの初期化
			g_enemy[i] = g_prototype_enemy[enemy_list[i].knd];
			g_enemy[i].knd = enemy_list[i].knd;
			g_enemy[i].pos = enemy_list[i].pos;
			//向きで画像が変わる場合
			if (!(g_enemy[i].is_left = enemy_list[i].is_left)) {
				g_enemy[i].sprite_num++;
				//スプライトの再設定
				g_enemy[i].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_enemy[i].sprite_num);
			}
			//使用中の数を増やす
			g_active_enemy_num++;
		}
		//リストの終わりなら処理を抜ける
		else {
			break;
		}
	}

	return TRUE;
}

//敵モンスターの更新
void UpdateEnemies() {
	int i;
	for (i = 0; i < g_active_enemy_num; i++) {
		//更新処理
		g_update_enemy[g_enemy[i].knd](&g_enemy[i]);
		//マップ外判定
		if (OrderIsOutsideMap(&g_enemy[i].pos, &g_enemy[i].col)) {
			DestroyEnemy(i);
		}
	}
}

//敵モンスターの描画
void DrawEnemies() {
	int i;
	for (i = 0; i < g_active_enemy_num; i++) {
		g_draw_enemy[g_enemy[i].knd](&g_enemy[i]);
	}
}

//敵モンスターの当たり判定の設定
void SetEnemiesCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < ENEMY_MAX; i++) {
		collider[i].state = &g_enemy[i].state;
		collider[i].pos = &g_enemy[i].pos;
		collider[i].col = &g_enemy[i].col;
		collider[i].vel = &g_enemy[i].vel;
		collider[i].ride = &g_enemy[i].ride;
		collider[i].collision_state = &g_enemy[i].collision_state;
		collider[i].ground_flag = &g_enemy[i].ground_flag;
	}
}

//敵モンスターのダメージ処理
BOOL DamageEnemy(int i, int power) {

	//エラーチェック
	if (i < 0 || i >= g_active_enemy_num) {
		MessageBox(NULL, "敵モンスターのダメージ処理で不正な値が渡されました", "", MB_OK);
		return FALSE;
	}

	//体力が0なら消滅させる
	if (g_damage_enemy[g_enemy[i].knd](&g_enemy[i], power)) {
		DestroyEnemy(i);
		return TRUE;
	}
	return FALSE;
}

//敵モンスターの消滅
void DestroyEnemy(int i) {

	//エラーチェック
	if (i < 0 || i >= g_active_enemy_num) {
		MessageBox(NULL, "敵モンスターの消滅で不正な値が渡されました", "", MB_OK);
		return;
	}

	g_destroy_enemy[g_enemy[i].knd](&g_enemy[i]);

	//敵モンスターオブジェクトの配列に隙間ができたかどうか
	if (g_active_enemy_num != 1 && i != g_active_enemy_num - 1) {
		//空いた場所と最後尾の敵モンスターを入れ替える
		g_enemy[i] = g_enemy[g_active_enemy_num - 1];
		g_enemy[g_active_enemy_num - 1].state = 0;
	}

	//使用中の数を減らす
	g_active_enemy_num--;

}


