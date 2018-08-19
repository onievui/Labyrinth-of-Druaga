//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Map.cpp
//!
//! @brief  マップ関連の処理
//!
//! @date   2018/08/18
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once

//ヘッダーファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"


//定数の定義
#define MAP_OFFSET_X	(32)	//マップのオフセット
#define MAP_OFFSET_Y	(32)	//マップのオフセット


//プロトタイプ宣言
extern void LoadMapData(const StageId stageId, MapData *mapdata);	//マップデータの読み込み (Load.cpp)


//グローバル変数の宣言
MapData g_mapdata;				//マップ情報の構造体
Vector2DF g_camera_offset;		//カメラのオフセット


//マップの初期化
void InitializeMap() {
	int i, j;

	//マップデータの読み込み
	LoadMapData(GetSelectStage(), &g_mapdata);

	//プレイヤーの初期座標を設定する
	MulVector2DF(g_mapdata.player_init_pos, MAPCHIP_SIZE);
	AddVector2DF(g_mapdata.player_init_pos, Vector2DF{ MAP_OFFSET_X,MAP_OFFSET_Y });
	OrderSetPlayerPos(g_mapdata.player_init_pos);

	//お宝の初期座標を設定する
	MulVector2DF(g_mapdata.treasure_pos, MAPCHIP_SIZE);
	AddVector2DF(g_mapdata.treasure_pos, Vector2DF{ MAP_OFFSET_X,MAP_OFFSET_Y });
	OrderSetTreasurePos(g_mapdata.treasure_pos);


	//マップデータの初期化
	for (i = 0; i < g_mapdata.width; i++) {
		for (j = 0; j < g_mapdata.height; j++) {
			if (g_mapdata.map[i][j].knd == 0) {
				g_mapdata.map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_1 + (i % 2));
			}
			else {
				g_mapdata.map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_2 + g_mapdata.map[i][j].knd);
			}
			g_mapdata.map[i][j].pos = Vector2DF{ (float)(i*MAPCHIP_SIZE + MAP_OFFSET_X),(float)(j*MAPCHIP_SIZE + MAP_OFFSET_Y) };
			g_mapdata.map[i][j].graphp = GraphP{ &g_sprite[g_mapdata.map[i][j].knd],1.0,0.0 };
		}
	}


	//オフセットの初期化
	g_camera_offset = { 0,0 };
}

//カメラのオフセットを計算する
void UpdateCameraOffset() {
	//プレイヤー座標の取得
	Vector2DF pl = OrderGetPlayerPos();

	//プレイヤーが左に寄っている場合
	if (pl.x < SCREEN_CENTER_X) {
		g_camera_offset.x = 0;
	}
	//プレイヤーが右に寄っている場合
	else if (g_mapdata.width*MAPCHIP_SIZE - pl.x < SCREEN_CENTER_X) {
		g_camera_offset.x = (float)(g_mapdata.width*MAPCHIP_SIZE - SCREEN_WIDTH);
	}
	//プレイヤーが真ん中にいる場合
	else {
		g_camera_offset.x = (float)(pl.x - SCREEN_CENTER_X);
	}

	//プレイヤーが上に寄っている場合
	if (pl.y < SCREEN_CENTER_Y) {
		g_camera_offset.y = 0;
	}
	//プレイヤーが下に寄っている場合
	else if (g_mapdata.height*MAPCHIP_SIZE - pl.y < SCREEN_CENTER_Y) {
		g_camera_offset.y = (float)(g_mapdata.height*MAPCHIP_SIZE - SCREEN_HEIGHT);
	}
	//プレイヤーが真ん中にいる場合
	else {
		g_camera_offset.y = (float)(pl.y - SCREEN_CENTER_Y);
	}
	
}

//マップの描画
void DrawMap() {
	int i, j;
	for (i = 0; i < g_mapdata.width; i++) {
		for (j = 0; j < g_mapdata.height; j++) {
			DrawGraphicToMapP(g_mapdata.map[i][j].pos, &g_mapdata.map[i][j].graphp);
		}
	}
}


//マップを取得する
MapData GetMap() {
	return g_mapdata;
}

//指定した座標が通過不可マスかどうか
BOOL IsMapPosWall(float x, float y) {
	int ix = (int)(x / MAPCHIP_SIZE);
	int iy = (int)(y / MAPCHIP_SIZE);
	//範囲外かどうか
	if (ix < 0 || ix >= g_mapdata.width ||
		iy < 0 || iy >= g_mapdata.height) {
		return FALSE;
	}
	//通過可能マスかどうか
	if (g_mapdata.map[ix][iy].knd <= SPR_MAPCHIP1_1 + 1) {
		return FALSE;
	}
	return TRUE;
}

//カメラのオフセットを取得する
Vector2DF GetCameraOffset() {
	return g_camera_offset;
}



