#pragma once



//ヘッダファイルの読み込み
#include "Minion.h"
#include "Mediator.h"






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
		int mx, my;
		s_pos.x += isLeft ? pl_col.left : pl_col.right;
		OrderGetMapPosWithPos(s_pos, &mx, &my);
		mx += isLeft ? -1 : 1;
		s_pos = OrderGetPosWithMapPos(mx, my);
		if (OrderIsWallWithPos(s_pos.x, s_pos.y)) {
			//スペースがないなら失敗
			return FALSE;
		}
		
		//召喚モンスターの初期化
		g_minion[g_active_minion_num] = g_prototype_minion[knd];
		g_minion[g_active_minion_num].pos = s_pos;
		g_minion[g_active_minion_num].is_left = isLeft;
		//向きで画像が変わる場合
		if (!isLeft && knd == MINION_GHOST) {
			g_minion[g_active_minion_num].sprite_num++;
			//スプライトの再設定
			g_minion[g_active_minion_num].graph.sprite.rect = GetSpriteRect(SPR_STD_MONSTER, g_minion[g_active_minion_num].sprite_num);
		}
		

		//使用中の数を増やす
		g_active_minion_num++;

		return g_prototype_minion[knd].s_dat.time;
	}
	
	return FALSE;
}

//召喚モンスターを消す
void DeleteMinion(Vector2DF *pl_pos, RectF *pl_col, BOOL isLeft) {

	//消す範囲の作成
	Vector2DF pos = *pl_pos;
	RectF col = { -32,-32,32,32 };
	pos.x += isLeft ? pl_col->left - 32: pl_col->right + 32;

	//敵との当たり判定
	OrderCollisionObjectMinions(&pos, &col);

}

//召喚コストの取得
int GetSummonCost(MinionPattern knd) {

	//エラーチェック
	if (knd < 0 || knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "召喚モンスターのコスト取得で不正な値が渡されました", "", MB_OK);
		return FALSE;
	}

	return g_prototype_minion[knd].s_dat.cost;
}

//召喚モンスターの画像取得
Sprite GetMinionSprite(MinionPattern knd) {

	//エラーチェック
	if (knd < 0 || knd >= MINION_PATTERN_NUM) {
		MessageBox(NULL, "召喚モンスターの画像取得で不正な値が渡されました", "", MB_OK);
		return g_sprite[SPR_STD_MONSTER];
	}

	return g_prototype_minion[knd].graph.sprite;
}

//召喚モンスターの更新
void UpdateMinions() {
	int i;
	for (i = 0; i < g_active_minion_num; i++) {
		//更新処理
		g_update_minion[g_minion[i].knd](&g_minion[i]);
		//マップ外判定
		if (OrderIsOutsideMap(&g_minion[i].pos, &g_minion[i].col)) {
			DestroyMinion(i);
		}
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
		collider[i].col = &g_minion[i].col;
		collider[i].vel = &g_minion[i].vel;
		collider[i].ride = &g_minion[i].ride;
		collider[i].is_ground = &g_minion[i].is_ground;
		collider[i].ground_flag = &g_minion[i].ground_flag;
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


