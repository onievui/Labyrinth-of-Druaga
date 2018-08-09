//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sprite.cpp
//!
//! @brief  スプライトデータの処理
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダーファイルの読み込み
#include "Sprite.h"

//スプライトデータ
Sprite g_sprite[SPR_ALL_NUM];

//スプライトデータの初期化
void InitializeSprite() {
	int i;
	g_sprite[SPR_LOGO1]        = Sprite{ g_texture[GRP_LOGO1],     RECT{ 0,  0, 256, 256 } };
	g_sprite[SPR_LOGO2]        = Sprite{ g_texture[GRP_LOGO2],     RECT{ 0,  0, 640, 480 } };
	g_sprite[SPR_TITLE]        = Sprite{ g_texture[GRP_TITLE],     RECT{ 0,  0, 160,  56 } };
	g_sprite[SPR_STD_GIL]      = Sprite{ g_texture[GRP_GIL],       RECT{ 8,  8,  64,  64 } };
	for (i = 0; i < 11; i++) {
		g_sprite[SPR_MAPCHIP1_1 + i] = Sprite{ g_texture[GRP_MAPCHIP1],  RECT{ 4 + i*(64 + 4),  4,  64,  64 } };
	}
}

//スプライト切り出し位置の取得
RECT GetSpriteRect(const SPR_ID sprId, const int num) {

	RECT rect = { 0,0,0,0 };

	//スプライトの種類で分岐
	switch (sprId) {

	//プレイヤースプライト
	case SPR_STD_GIL:
		rect = RECT{ 8 + num*(64 + 8),8,64,64 };
		break;
	default:
		MessageBox(NULL, "スプライトの切り出し位置の取得で不正な値が渡されました", "", MB_OK);
		break;
	}

	return rect;
}