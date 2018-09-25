#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//定数の定義
#define ORB_GET_ANIMATE_SPEED		(5)		//オーブ取得エフェクトのアニメーション間隔



//エフェクトのプロトタイプの初期化
void InitializePrototypeEffect(Effect proto_effect[]) {

	//オーブ取得エフェクトのプロトタイプ
	proto_effect[EFFECT_GET_ORB] =
	{
		EFFECT_GET_ORB,
		1,
		0,
		{ 0,0 },
		{ -20,-20,20,20 },
		{ 0,0 },
		0,
		{ g_sprite[SPR_STD_EFFECT1],0.6f,0.0 },
		0,
	};
	proto_effect[EFFECT_GET_ORB].graph.sprite.rect = GetSpriteRect(SPR_STD_EFFECT1, proto_effect[EFFECT_GET_ORB].sprite_num);

	
}


//オーブ取得エフェクトの更新
BOOL UpdateEffectGetOrb(Effect *effect) {


	//アニメーションを行う
	if (effect->count%ORB_GET_ANIMATE_SPEED == ORB_GET_ANIMATE_SPEED - 1) {
		effect->sprite_num++;
		//スプライトの変更
		if (effect->sprite_num < 3) {
			effect->graph.sprite.rect = GetSpriteRect(SPR_STD_EFFECT1, effect->sprite_num);
		}
		//エフェクトの消滅
		else {
			return FALSE;
		}
	}


	effect->count++;

	return TRUE;
}

//オーブ取得エフェクトの描画
void DrawEffectGetOrb(Effect *effect) {

	//徐々に透明にする
	float t = effect->count*1.0f / (ORB_GET_ANIMATE_SPEED * 3);
	t = t*t*t;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * (1-t)));
	DrawGraphicToMap(effect->pos, &effect->graph);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//オーブ取得エフェクトの消滅
void DestroyEffectGetOrb(Effect *effect) {
	effect->state = 0;
}

