//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sprite.h
//!
//! @brief  スプライトデータのヘッダファイル
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダファイルの読み込み
#include "Load.h"



//スプライトのID
enum SPR_ID {
	SPR_LOGO1,				//ロゴスプライト1
	SPR_LOGO2,				//ロゴスプライト2
	SPR_TITLE,				//タイトルスプライト
	SPR_TITLE_BG,			//タイトル背景スプライト
	SPR_STAGESELECT_BG,		//ステージセレクト背景スプライト
	SPR_STAGESELECT_ICON,	//ステージセレクトアイコンスプライト
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