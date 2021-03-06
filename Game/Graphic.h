//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Graphic.h
//!
//! @brief  グラフィックデータのヘッダファイル
//!
//! @date   2018/08/13
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

//graphic構造体（ポインタ版）
struct GraphP {
	Sprite *sprite;
	float exrate;
	float angle;

};

//スプライトの描画
void DrawGraphic(const Vector2DF pos, Graph *tex);

//グラフィックの描画（ポインタ版）
void DrawGraphicP(const Vector2DF pos, GraphP *tex);

//マップに対するグラフィックの描画
void DrawGraphicToMap(Vector2DF pos, Graph *tex);

//マップに対する左右反転グラフィックの描画
void DrawTurnGraphicToMap(Vector2DF pos, Graph *tex);

//マップに対するグラフィックの描画（ポインタ版）
void DrawGraphicToMapP(Vector2DF pos, GraphP *tex);


