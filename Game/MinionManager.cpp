#pragma once



//ヘッダファイルの読み込み
#include "Minion.h"
#include "Mediator.h"




//定数の定義
#define SUMMON_POS_OFFSET_X	(-3)		//モンスターの召喚位置のオフセット



//プロトタイプ宣言
void DestroyMinion(int i);


//グローバル変数の宣言
Minion g_prototype_minion[MINION_PATTERN_NUM];	//召喚モンスターのプロトタイプ
Minion g_minion[MINION_MAX];					//召喚モンスターオブジェクト
int g_active_minion_num;						//使用中の召喚モンスターの数

//各召喚モンスターの更新処理の関数ポインタ
void(*g_update_minion[MINION_PATTERN_NUM])(Minion *minion) = {
	UpdateMinionSlime,
	UpdateMinionGhost
};

//各召喚モンスターの描画処理の関数ポインタ
void(*g_draw_minion[MINION_PATTERN_NUM])(Minion *minion) = {
	DrawMinionSlime,
	DrawMinionGhost
};

//各召喚モンスターのダメージ処理の関数ポインタ
BOOL(*g_damage_minion[MINION_PATTERN_NUM])(Minion *minion, int power) = {
	DamageMinionSlime,
	DamageMinionGhost
};

//各召喚モンスターの消滅処理の関数ポインタ
void(*g_destroy_minion[MINION_PATTERN_NUM])(Minion *minion) = {
	DestroyMinionSlime,
	DestroyMinionGhost
};


//召喚モンスターの初期化
void InitializeMinions() {

	//召喚モンスターオブジェクトの初期化
	memset(g_minion, 0, sizeof(g_minion));

	//召喚モンスターのプロトタイプの初期化
	InitializePrototypeMinion(g_prototype_minion);

	//カウンタのリセット
	g_active_minion_num = 0;
}

//召喚モンスターの生成
int CreateMinion(MinionPattern knd, Vector2DF pl_pos, RectF pl_col, BOOL isLeft) {

	//エラーチェック
	if (knd < 0 || knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "召喚モンスターの生成で不正な値が渡されました", "", MB_OK);
		return FALSE;
	}

	//召喚モンスターの空きがあるかどうか
	if (g_active_minion_num != MINION_MAX) {
		//召喚スペースがあるかどうか
		Vector2DF s_pos = pl_pos;
		Vector2DF s_vel = { 0,0 };
		if (isLeft) {
			s_pos.x += pl_col.left - g_prototype_minion[knd].col.right + SUMMON_POS_OFFSET_X;
		}
		else {
			s_pos.x += pl_col.right - g_prototype_minion[knd].col.left - SUMMON_POS_OFFSET_X;
		}
		if (OrderCollisionObjectMap(&s_pos, &s_vel, &g_prototype_minion[knd].col)) {
			//スペースがないなら失敗
			return FALSE;
		}
		//召喚モンスターの初期化
		g_minion[g_active_minion_num] = g_prototype_minion[knd];
		g_minion[g_active_minion_num].pos = s_pos;
		g_minion[g_active_minion_num].is_left = isLeft;
		if (!isLeft && knd == MINION_GHOST) {
			g_minion[g_active_minion_num].sprite_num++;
		}
		//スプライトの設定
		g_minion[g_active_minion_num].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_minion[g_active_minion_num].sprite_num);

		//使用中の数を増やす
		g_active_minion_num++;

		return g_minion[g_active_minion_num].summon_time;
	}
	
	return FALSE;
}

//召喚モンスターの更新
void UpdateMinions() {
	int i;
	for (i = 0; i < g_active_minion_num; i++) {
		g_update_minion[g_minion[i].knd](&g_minion[i]);
	}
}

//召喚モンスターの描画
void DrawMinions() {
	int i;
	for (i = 0; i < g_active_minion_num; i++) {
		g_draw_minion[g_minion[i].knd](&g_minion[i]);
	}
}

//召喚モンスターの当たり判定の設定
void SetMinionsCollider(BoxCollider collider[]) {
	int i;
	for (i = 0; i < MINION_MAX; i++) {
		collider[i].state = &g_minion[i].state;
		collider[i].pos = &g_minion[i].pos;
		collider[i].vel = &g_minion[i].vel;
		collider[i].col = &g_minion[i].col;
	}
}

//召喚モンスターのダメージ処理
void DamageMinion(int i, int power) {

	//エラーチェック
	if (i < 0 || i >= g_active_minion_num) {
		MessageBox(NULL, "召喚モンスターのダメージ処理で不正な値が渡されました", "", MB_OK);
		return;
	}

	//体力が0なら消滅させる
	if (g_damage_minion[g_minion[i].knd](&g_minion[i], power)) {
		DestroyMinion(i);
	}

}

//召喚モンスターの消滅
void DestroyMinion(int i) {

	//エラーチェック
	if (i < 0 || i >= g_active_minion_num) {
		MessageBox(NULL, "召喚モンスターの消滅で不正な値が渡されました", "", MB_OK);
		return;
	}

	g_destroy_minion[g_minion[i].knd](&g_minion[i]);

	//召喚モンスターオブジェクトの配列に隙間ができたかどうか
	if (g_active_minion_num != 1 && i != g_active_minion_num - 1) {
		//空いた場所と最後尾の召喚モンスターを入れ替える
		g_minion[i] = g_minion[g_active_minion_num - 1];
		g_minion[g_active_minion_num - 1].state = 0;
	}

	//使用中の数を減らす
	g_active_minion_num--;

}


