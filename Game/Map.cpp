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
#include "GameDefine.h"
#include "Mediator.h"



//定数の定義
#define MAP_OFFSET_X	(32)	//マップのオフセット
#define MAP_OFFSET_Y	(32)	//マップのオフセット



//プロトタイプ宣言



//グローバル変数の宣言
Map g_map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];	//マップ構造体
MapAll g_mapall;							//マップ全体の構造体
int g_map_width, g_map_height;				//マップの縦横幅
Vector2DF g_camera_offset;					//カメラのオフセット




//マップの初期化
void InitializeMap() {
	int i, j;
	int map_data[MAP_WIDTH_MAX*MAP_HEIGHT_MAX];
	int player_pos[2];
	Vector2DF player_pos2;

	//マップデータの読み込み
	LoadMapData(GetSelectStage(), map_data, &g_map_width, &g_map_height, player_pos);

	//プレイヤーの初期座標を設定する
	player_pos2.x = (float)(player_pos[0] * MAPCHIP_SIZE + MAP_OFFSET_X);
	player_pos2.y = (float)(player_pos[1] * MAPCHIP_SIZE + MAP_OFFSET_Y);
	OrderSetPlayerPos(player_pos2);


	//マップデータの初期化
	for (i = 0; i < g_map_width; i++) {
		for (j = 0; j < g_map_height; j++) {
			int knd = map_data[i + j*g_map_width];
			if (knd == 0) {
				g_map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_1 + (i % 2));
			}
			else {
				g_map[i][j].knd = (SPR_ID)(SPR_MAPCHIP1_2 + knd);
			}
			g_map[i][j].pos = Vector2DF{ (float)(i*MAPCHIP_SIZE + MAP_OFFSET_X),(float)(j*MAPCHIP_SIZE + MAP_OFFSET_Y) };
			g_map[i][j].graphp = GraphP{ &g_sprite[g_map[i][j].knd],1.0,0.0 };
		}
	}
	g_mapall.map = g_map;

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
	else if (g_map_width*MAPCHIP_SIZE - pl.x < SCREEN_CENTER_X) {
		g_camera_offset.x = (float)(g_map_width*MAPCHIP_SIZE - SCREEN_WIDTH);
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
	else if (g_map_height*MAPCHIP_SIZE - pl.y < SCREEN_CENTER_Y) {
		g_camera_offset.y = (float)(g_map_height*MAPCHIP_SIZE - SCREEN_HEIGHT);
	}
	//プレイヤーが真ん中にいる場合
	else {
		g_camera_offset.y = (float)(pl.y - SCREEN_CENTER_Y);
	}
	
}

//マップの描画
void DrawMap() {
	int i, j;
	for (i = 0; i < g_map_width; i++) {
		for (j = 0; j < g_map_height; j++) {
			DrawGraphicToMapP(g_map[i][j].pos, &g_map[i][j].graphp);
		}
	}
}


//マップを取得する
MapAll GetMap() {
	return g_mapall;
}

//指定した座標が通過不可マスかどうか
BOOL IsMapPosWall(float x, float y) {
	int ix = (int)(x / MAPCHIP_SIZE);
	int iy = (int)(y / MAPCHIP_SIZE);
	//範囲外かどうか
	if (ix < 0 || ix >= g_map_width ||
		iy < 0 || iy >= g_map_height) {
		return FALSE;
	}
	//通過可能マスかどうか
	if (g_map[ix][iy].knd <= SPR_MAPCHIP1_1 + 1) {
		return FALSE;
	}
	return TRUE;
}

//カメラのオフセットを取得する
Vector2DF GetCameraOffset() {
	return g_camera_offset;
}





