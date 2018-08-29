//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sprite.h
//!
//! @brief  スプライトデータのヘッダファイル
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//スプライトのID
//スプライト数が多く同時に複数使用しない場合は基準スプライトを使い、動的に切り出し位置を取得する
enum SPR_ID {
	SPR_LOGO1,				//ロゴスプライト1
	SPR_LOGO2,				//ロゴスプライト2
	SPR_TITLE,				//タイトルスプライト
	SPR_BG,					//背景スプライト
	SPR_STAGESELECT_BG,		//ステージセレクト背景スプライト
	SPR_STAGESELECT_ICON,	//ステージセレクトアイコンスプライト
	SPR_STD_GIL,			//プレイヤー基準スプライト
	SPR_STD_SWORD,			//剣基準スプライト
	SPR_STD_MONSTER,		//モンスター基準スプライト
	SPR_MAPCHIP1_1,			//マップチップ1スプライト1
	SPR_MAPCHIP1_2,			//マップチップ1スプライト2
	SPR_MAPCHIP1_3,			//マップチップ1スプライト3
	SPR_MAPCHIP1_4,			//マップチップ1スプライト4
	SPR_MAPCHIP1_5,			//マップチップ1スプライト5
	SPR_MAPCHIP1_6,			//マップチップ1スプライト6
	SPR_MAPCHIP1_7,			//マップチップ1スプライト7
	SPR_MAPCHIP1_8,			//マップチップ1スプライト8
	SPR_MAPCHIP1_9,			//マップチップ1スプライト9
	SPR_MAPCHIP1_10,		//マップチップ1スプライト10
	SPR_MAPCHIP1_11,		//マップチップ1スプライト11
	SPR_OBJECT_TREASURE,	//お宝スプライト
	SPR_ALL_NUM,			//スプライトの数
};


//スプライト構造体
struct Sprite {
	HGRP texture;	//テキスチャ
	RECT rect;		//テキスチャの読み込み位置
};


//スプライトデータ
extern Sprite g_sprite[SPR_ALL_NUM];


//スプライトデータの初期化
void InitializeSprite();

//スプライト切り出し位置の取得
RECT GetSpriteRect(const SPR_ID sprId, const int num);

