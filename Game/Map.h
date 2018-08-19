//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Map.h
//!
//! @brief  マップ関連のヘッダファイル
//!
//! @date   2018/08/18
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

//指定した座標が通過不可マスかどうか
BOOL IsMapPosWall(float x, float y);

//カメラのオフセットを取得する
Vector2DF GetCameraOffset();


