//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Map.cpp
//!
//! @brief  マップ関連の処理
//!
//! @date   2018/08/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//ヘッダーファイルの読み込み
#include "GameObjectStruct.h"



//定数の定義
#define MAP_WIDTH_NUM	(12)	//マップの横幅
#define MAP_HEIGHT_NUM	(9)		//マップの縦幅

#define MAPCHIP_SIZE		(64)	//マップチップの大きさ
#define MAPCHIP_SIZE_HALF	(32)	//マップチップの大きさの半分

#define MAP_OFFSET_X	(32)	//マップのオフセット
#define MAP_OFFSET_Y	(32)	//マップのオフセット



//プロトタイプ宣言



//グローバル変数の宣言
Map g_map[MAP_WIDTH_NUM][MAP_HEIGHT_NUM];


//マップの初期化
void InitializeMap() {
	int i, j;
	for (i = 0; i < MAP_WIDTH_NUM; i++) {
		for (j = 0; j < MAP_HEIGHT_NUM; j++) {
			g_map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_1 + GetRand(10));
			g_map[i][j].pos = Vector2DF{ (float)(i*MAPCHIP_SIZE + MAP_OFFSET_X),(float)(j*MAPCHIP_SIZE + MAP_OFFSET_Y) };
			g_map[i][j].graphp = GraphP{ &g_sprite[g_map[i][j].knd],1.0,0.0 };
		}
	}
}



//マップの描画
void DrawMap() {
	int i, j;
	for (i = 0; i < MAP_WIDTH_NUM; i++) {
		for (j = 0; j < MAP_HEIGHT_NUM; j++) {
			DrawGraphicP(g_map[i][j].pos, &g_map[i][j].graphp);
		}
	}
}

