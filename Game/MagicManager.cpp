#pragma once



//ヘッダファイルの読み込み
#include "Magic.h"
#include "Mediator.h"






//プロトタイプ宣言
void DestroyMagic(int i);


//グローバル変数の宣言
Magic g_prototype_magic[MAGIC_PATTERN_NUM];	//敵の魔法のプロトタイプ
Magic g_magic[MAGIC_MAX];					//敵の魔法オブジェクト
int g_active_magic_num;						//使用中の敵の魔法の数


//各敵の魔法の更新処理の関数ポインタ
void(*g_update_magic[MAGIC_PATTERN_NUM])(Magic *magic) = {
	UpdateMagicWhite,
	UpdateMagicGreen
};

//各敵の魔法の描画処理の関数ポインタ
void(*g_draw_magic[MAGIC_PATTERN_NUM])(Magic *magic) = {
	DrawMagicWhite,
	DrawMagicGreen
};

//各敵の魔法の壁衝突処理の関数ポインタ
BOOL(*g_collision_magic[MAGIC_PATTERN_NUM])(Magic *magic) = {
	CollisionMagicWhite,
	CollisionMagicGreen
};

//各敵の魔法の消滅処理の関数ポインタ
void(*g_destroy_magic[MAGIC_PATTERN_NUM])(Magic *magic) = {
	DestroyMagicWhite,
	DestroyMagicGreen
};


//敵の魔法の初期化
void InitializeMagics() {

	//データの初期化
	memset(g_magic, 0, sizeof(g_magic));

	//敵の魔法のプロトタイプの初期化
	InitializePrototypeMagic(g_prototype_magic);

	//カウンタのリセット
	g_active_magic_num = 0;
}


//敵の魔法の生成
BOOL CreateMagic(MagicPattern knd, Vector2DF *pos, BOOL isLeft) {

	//エラーチェック
	if (knd < 0 || knd >= MAGIC_PATTERN_NUM) {
		MessageBox(NULL, "敵の魔法の生成で不正な値が渡されました", "", MB_OK);
		return FALSE;
	}

	//敵の魔法の空きがあるかどうか
	if (g_active_magic_num != MAGIC_MAX) {

		//敵の魔法の初期化
		g_magic[g_active_magic_num] = g_prototype_magic[knd];
		g_magic[g_active_magic_num].pos = *pos;
		//向きで移動方向を変える
		if (isLeft) {
			g_magic[g_active_magic_num].vel.x *= -1;
		}

		//使用中の数を増やす
		g_active_magic_num++;

		return TRUE;
	}

	return FALSE;
	
}

//敵の魔法の更新
void UpdateMagics() {
	int i;
	for (i = 0; i < g_active_magic_num; i++) {
		//更新処理
		g_update_magic[g_magic[i].knd](&g_magic[i]);
		//マップ外判定
		if (OrderIsOutsideMap(&g_magic[i].pos, &g_magic[i].col)) {
			DestroyMagic(i);
		}
	}
}

//敵の魔法の描画
void DrawMagics() {
	int i;
	for (i = 0; i < g_active_magic_num; i++) {
		g_draw_magic[g_magic[i].knd](&g_magic[i]);
	}
}

//敵の魔法の当たり判定の設定
void SetMagicsCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < MAGIC_MAX; i++) {
		collider[i].state = &g_magic[i].state;
		collider[i].pos = &g_magic[i].pos;
		collider[i].col = &g_magic[i].col;
		collider[i].vel = &g_magic[i].vel;
		collider[i].ride = NULL;
		collider[i].collision_state = NULL;
		collider[i].ground_flag = NULL;
	}
}

//敵の魔法の壁衝突処理
BOOL CollisionMagic(int i) {

	//エラーチェック
	if (i < 0 || i >= g_active_magic_num) {
		MessageBox(NULL, "敵の魔法のダメージ処理で不正な値が渡されました", "", MB_OK);
		return FALSE;
	}

	//消えるなら通知する
	if (g_collision_magic[g_magic[i].knd](&g_magic[i])) {
		DestroyMagic(i);
		return TRUE;
	}
	return FALSE;
}

//敵の魔法の消滅
void DestroyMagic(int i) {

	//エラーチェック
	if (i < 0 || i >= g_active_magic_num) {
		MessageBox(NULL, "敵の魔法の消滅で不正な値が渡されました", "", MB_OK);
		return;
	}

	g_destroy_magic[g_magic[i].knd](&g_magic[i]);

	//敵の魔法オブジェクトの配列に隙間ができたかどうか
	if (g_active_magic_num != 1 && i != g_active_magic_num - 1) {
		//空いた場所と最後尾の敵の魔法を入れ替える
		g_magic[i] = g_magic[g_active_magic_num - 1];
		g_magic[g_active_magic_num - 1].state = 0;
	}

	//使用中の数を減らす
	g_active_magic_num--;

}

//敵の魔法のダメージ量の取得
int GetMagicPower(int i) {

	//エラーチェック
	if (i < 0 || i >= g_active_magic_num) {
		MessageBox(NULL, "敵の魔法のダメージ量の取得で不正な値が渡されました", "", MB_OK);
		return 0;
	}

	return g_magic[i].power;
}

