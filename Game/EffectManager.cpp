#pragma once



//ヘッダファイルの読み込み
#include "Effect.h"
#include "Mediator.h"
#include "Sound.h"



//定数の定義
#define EFFECT_MAX		(30)	//エフェクトの最大出現数


//プロトタイプ宣言
void DestroyEffect(int i);



//グローバル変数の宣言
Effect g_prototype_effect[EFFECT_PATTERN_NUM];	//エフェクトのプロトタイプ
Effect g_effect[EFFECT_MAX];					//エフェクトオブジェクト
int g_active_effect_num;						//使用中のエフェクトの数



//各エフェクトの更新処理の関数ポインタ
BOOL(*g_update_effect[EFFECT_PATTERN_NUM])(Effect *effect) = {
	UpdateEffectGetOrb
};

//各エフェクトの描画処理の関数ポインタ
void(*g_draw_effect[EFFECT_PATTERN_NUM])(Effect *effect) = {
	DrawEffectGetOrb
};

//各エフェクトの消滅処理の関数ポインタ
void(*g_destroy_effect[EFFECT_PATTERN_NUM])(Effect *effect) = {
	DestroyEffectGetOrb
};


//エフェクトの初期化
void InitializeEffects() {

	//データの初期化
	memset(g_effect, 0, sizeof(g_effect));

	//エフェクトのプロトタイプの初期化
	InitializePrototypeEffect(g_prototype_effect);

	//カウンタのリセット
	g_active_effect_num = 0;
}

//エフェクトの生成
BOOL CreateEffect(EffectPattern knd, Vector2DF *pos, BOOL isLeft) {

	//エラーチェック
	if (knd < 0 || knd >= EFFECT_PATTERN_NUM) {
		MessageBox(NULL, "エフェクトの生成で不正な値が渡されました", "", MB_OK);
		return FALSE;
	}

	//向きは現在未使用
	isLeft = 0;

	//エフェクトの空きがあるかどうか
	if (g_active_effect_num != EFFECT_MAX) {

		//エフェクトの初期化
		g_effect[g_active_effect_num] = g_prototype_effect[knd];
		g_effect[g_active_effect_num].pos = *pos;
		
		//使用中の数を増やす
		g_active_effect_num++;

		return TRUE;
	}

	return FALSE;

}

//エフェクトの更新
void UpdateEffects() {
	int i;
	for (i = 0; i < g_active_effect_num; i++) {
		//更新処理
		if (!g_update_effect[g_effect[i].knd](&g_effect[i])) {
			//消滅の通知が来たら消滅させる
			DestroyEffect(i);
		}
		//マップ外判定
		else if (OrderIsOutsideMap(&g_effect[i].pos, &g_effect[i].col)) {
			DestroyEffect(i);
		}
	}
}

//エフェクトの描画
void DrawEffects() {
	int i;
	for (i = 0; i < g_active_effect_num; i++) {
		g_draw_effect[g_effect[i].knd](&g_effect[i]);
	}
}

//エフェクトの消滅
void DestroyEffect(int i) {

	//エラーチェック
	if (i < 0 || i >= g_active_effect_num) {
		MessageBox(NULL, "エフェクトの消滅で不正な値が渡されました", "", MB_OK);
		return;
	}

	g_destroy_effect[g_effect[i].knd](&g_effect[i]);

	//エフェクトオブジェクトの配列に隙間ができたかどうか
	if (g_active_effect_num != 1 && i != g_active_effect_num - 1) {
		//空いた場所と最後尾のエフェクトを入れ替える
		g_effect[i] = g_effect[g_active_effect_num - 1];
		g_effect[g_active_effect_num - 1].state = 0;
	}

	//使用中の数を減らす
	g_active_effect_num--;

}
