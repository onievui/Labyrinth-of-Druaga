#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//エフェクトのプロトタイプの初期化
void InitializePrototypeEffect(Effect proto_effect[]) {

	//
	proto_effect[EFFECT_GET_ORB] =
	{
		EFFECT_GET_ORB,
		1,
		0,
		{ 0,0 },
		{ 0,0 },
		0,
		{ g_sprite[SPR_STD_EFFECT1],1.0,0.0 },
		0,
	};
	proto_effect[EFFECT_GET_ORB].graph.sprite.rect = GetSpriteRect(SPR_STD_EFFECT1, proto_effect[EFFECT_GET_ORB].sprite_num);

	
}


//オーブ取得エフェクトの更新
void UpdateEffectGetOrb(Effect *effect) {

	//移動量を座標に足す
	AddVector2DF(effect->pos, effect->vel);

	effect->state++;
}

//オーブ取得エフェクトの描画
void DrawEffectGetOrb(Effect *effect) {
	DrawGraphicToMap(effect->pos, &effect->graph);
}



