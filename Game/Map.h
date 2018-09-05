//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Map.h
//!
//! @brief  マップ関連のヘッダファイル
//!
//! @date   2018/08/23
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//マップの初期化
void InitializeMap();

//カメラのオフセットを計算する
void UpdateCameraOffset();

//マップの描画
void DrawMap();

//マップを取得する
MapData GetMap();

//指定した座標をマップ座標に変換する
void GetMapPosWithPos(Vector2DF pos, int *x, int *y);

//指定したマップ座標を座標に変換する
Vector2DF GetPosWithMapPos(int x, int y);

//指定した座標が通過不可マスかどうか
BOOL IsWallWithPos(float x, float y);

//カメラのオフセットを取得する
Vector2DF GetCameraOffset();

//マップ外にいるかの判定
BOOL IsOutsideMap(Vector2DF *pos, RectF *col);

//画面下にいるかの判定
BOOL IsUnderMap(Vector2DF *pos, RectF *col);


