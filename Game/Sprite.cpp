//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sprite.cpp
//!
//! @brief  スプライトデータの処理
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダファイルの読み込み
#include "Load.h"
#include "Sprite.h"

//スプライトデータ
Sprite g_sprite[SPR_ALL_NUM];

//スプライトデータの初期化
void InitializeSprite() {
	int i;
	g_sprite[SPR_LOGO1]        = Sprite{ g_texture[GRP_LOGO1],       RECT{ 0,  0, 256, 256 } };
	g_sprite[SPR_LOGO2]        = Sprite{ g_texture[GRP_LOGO2],       RECT{ 0,  0, 640, 480 } };
	g_sprite[SPR_TITLE]        = Sprite{ g_texture[GRP_TITLE],       RECT{ 0,  0, 800, 600 } };
	g_sprite[SPR_BG]           = Sprite{ g_texture[GRP_BG],          RECT{ 0,  0, 800, 600 } };
	g_sprite[SPR_STD_GIL]      = Sprite{ g_texture[GRP_GIL],         RECT{ 8,  8,  64,  64 } };
	g_sprite[SPR_STD_SWORD]    = Sprite{ g_texture[GRP_SWORD],       RECT{ 8,  8,  96,  96 } };
	g_sprite[SPR_DELETE_ICON]  = Sprite{ g_texture[GRP_DELETE_ICON], RECT{ 0,  0,  64,  64 } };
	g_sprite[SPR_STD_MONSTER]  = Sprite{ g_texture[GRP_MONSTER],     RECT{ 8,  8,  64,  64 } };
	g_sprite[SPR_STD_DRAGON]   = Sprite{ g_texture[GRP_DRAGON],      RECT{ 8,  8,  96,  64 } };
	g_sprite[SPR_STD_FIRE]     = Sprite{ g_texture[GRP_FIRE],        RECT{ 8,  8, 256,  64 } };
	g_sprite[SPR_STD_MAGIC]    = Sprite{ g_texture[GRP_MAGIC],       RECT{ 8,  8,  64,  64 } };
	for (i = 0; i < 11; i++) {
		g_sprite[SPR_MAPCHIP1_1 + i] = Sprite{ g_texture[GRP_MAPCHIP1],  RECT{ 4 + i*(64 + 4),  4,  64,  64 } };
	}
	g_sprite[SPR_OBJECT_TREASURE] = Sprite{ g_texture[GRP_OBJECT_OTHER], RECT{ 8 + 2*(64 + 8),  8,  64,  64 } };
	g_sprite[SPR_STD_EFFECT1]     = Sprite{ g_texture[GRP_EFFECT1],      RECT{ 8,  8,  64,  64 } };
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
	//剣スプライト
	case SPR_STD_SWORD:
		rect = RECT{ 8 + (num % 8)*(96 + 8),8 + (num / 8)*(96 + 8),96,96 };
		break;
	//モンスタースプライト
	case SPR_STD_MONSTER:
		rect = RECT{ 8 + (num % 12)*(64 + 8),8 + (num / 12)*(64 + 8),64,64 };
		break;
	//ドラゴンスプライト
	case SPR_STD_DRAGON:
		rect = RECT{ 8 + (num % 12)*(96 + 8),8 + (num / 12)*(64 + 8),96,64 };
		break;
	//ドラゴンの炎スプライト
	case SPR_STD_FIRE:
		rect = RECT{ 8, 8 + num*(64 + 8),256,64 };
		break;
	//モンスターの魔法スプライト
	case SPR_STD_MAGIC:
		rect = RECT{ 8 + (num % 4)*(64 + 8),8 + (num / 4)*(64 + 8),64,64 };
		break;
	//エフェクト1スプライト
	case SPR_STD_EFFECT1:
		rect = RECT{ 8 + (num % 4)*(64 + 8),8 + (num / 4)*(64 + 8),64,64 };
		break;
	default:
		MessageBox(NULL, "スプライトの切り出し位置の取得で不正な値が渡されました", "", MB_OK);
		break;
	}

	return rect;
}

