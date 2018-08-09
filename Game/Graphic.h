//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Graphic.h
//!
//! @brief  グラフィックデータのヘッダファイル
//!
//! @date   2018/06/19
//!
//! @author 永戸勇希
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダーファイルの読み込み
#include "Sprite.h"
#include "Vector2DF.h"



//graphic構造体
struct Graph {
	Sprite sprite;
	float exrate;
	float angle;

};

//スプライトの描画
void DrawGraphic(const Vector2DF pos, Graph *tex);


