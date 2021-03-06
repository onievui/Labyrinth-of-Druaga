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
//#define MAP_OFFSET_X	(32)	//マップのオフセット
//#define MAP_OFFSET_Y	(32)	//マップのオフセット


//プロトタイプ宣言
extern void LoadMapData(const StageId stageId, MapData *mapdata);	//マップデータの読み込み (Load.cpp)


//グローバル変数の宣言
MapData g_mapdata;				//マップ情報の構造体
Vector2DF g_camera_offset;		//カメラのオフセット


//マップの初期化
void InitializeMap() {
	int i, j;

	//マップデータの初期化
	memset(&g_mapdata, 0, sizeof(g_mapdata));

	//マップデータの読み込み
	LoadMapData(GetSelectStage(), &g_mapdata);

	//プレイヤーの初期座標を設定する
	MulVector2DF(g_mapdata.player_pos, MAPCHIP_SIZE);
	AddVector2DF(g_mapdata.player_pos, Vector2DF{ MAPCHIP_SIZE_HALF,MAPCHIP_SIZE_HALF });
	OrderSetPlayerPos(g_mapdata.player_pos);
	OrderSetPlayerDirection(g_mapdata.player_is_left);
	//プレイヤーの召喚可能なモンスターを設定する
	OrderSetPlayerSummonable(g_mapdata.summonable);
	//プレイヤーのSPを設定する
	OrderSetPlayerSp(g_mapdata.player_sp);

	for (i = 0; i < MONSTER_LIST_MAX; i++) {
		if (g_mapdata.monster_list[i].is_use) {
			//モンスターの初期座標を設定する
			MulVector2DF(g_mapdata.monster_list[i].pos, MAPCHIP_SIZE);
			AddVector2DF(g_mapdata.monster_list[i].pos, Vector2DF{ MAPCHIP_SIZE_HALF,MAPCHIP_SIZE_HALF });
			//召喚モンスターの生成
			if (g_mapdata.monster_list[i].type == 0) {
				OrderSetMinion(&g_mapdata.monster_list[i]);
			}
			//敵モンスターの生成
			else {
				OrderCreateEnemy(&g_mapdata.monster_list[i]);
			}
		}
		else {
			break;
		}
	}
	

	//お宝の初期座標を設定する
	MulVector2DF(g_mapdata.treasure_pos, MAPCHIP_SIZE);
	AddVector2DF(g_mapdata.treasure_pos, Vector2DF{ MAPCHIP_SIZE_HALF,MAPCHIP_SIZE_HALF });
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
			g_mapdata.map[i][j].pos = Vector2DF{ (float)(i*MAPCHIP_SIZE + MAPCHIP_SIZE_HALF),(float)(j*MAPCHIP_SIZE + MAPCHIP_SIZE_HALF) };
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

//指定した座標をマップ座標に変換する
void GetMapPosWithPos(Vector2DF pos, int *x, int *y) {
	*x = (int)(pos.x / MAPCHIP_SIZE);
	*y = (int)(pos.y / MAPCHIP_SIZE);
}

//指定したマップ座標を座標に変換する
Vector2DF GetPosWithMapPos(int x, int y) {
	Vector2DF ret;
	ret.x = (float)(x*MAPCHIP_SIZE + MAPCHIP_SIZE_HALF);
	ret.y = (float)(y*MAPCHIP_SIZE + MAPCHIP_SIZE_HALF);
	return ret;
}

//指定した座標が通過不可マスかどうか
BOOL IsWallWithPos(float x, float y) {
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

//マップ外にいるかの判定
BOOL IsOutsideMap(Vector2DF *pos, RectF *col) {
	if (
		pos->x + col->right<0 ||
		pos->x + col->left> g_mapdata.width*MAPCHIP_SIZE ||
		pos->y + col->bottom < 0 ||
		pos->y + col->top > g_mapdata.height*MAPCHIP_SIZE
		) {
		return TRUE;
	}
	return FALSE;
}

//画面下にいるかの判定
BOOL IsUnderMap(Vector2DF *pos, RectF *col) {
	if (pos->y + col->top > g_mapdata.height*MAPCHIP_SIZE) {
		return TRUE;
	}
	return FALSE;
}

//画面横にはみ出ないようにする
void ClampMap(Vector2DF *pos, RectF *col) {
	if (pos->x + col->left < 0) {
		pos->x = -col->left;
	}
	else if (pos->x + col->right > g_mapdata.width*MAPCHIP_SIZE) {
		pos->x = g_mapdata.width*MAPCHIP_SIZE - col->right;
	}
}
