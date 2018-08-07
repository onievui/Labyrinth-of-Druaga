//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Vector2DF.cpp
//!
//! @brief  二次ベクトルデータの処理
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//ヘッダーファイルの読み込み
#include "Vector2DF.h"
#include <math.h>


//移動量計算
void CalcVector2DF(Vector2DF &vel, const float &speed, const float &angle) {
	vel.x = cosf(angle)*speed;
	vel.y = sinf(angle)*speed;
}

//二次ベクトルの加算
void AddVector2DF(Vector2DF &vec1, const Vector2DF &vec2) {
	vec1.x += vec2.x;
	vec1.y += vec2.y;
}

//二次ベクトルの減算
void SubVector2DF(Vector2DF &vec1, const Vector2DF &vec2) {
	vec1.x -= vec2.x;
	vec1.y -= vec2.y;
}

//二次ベクトルにスカラーを掛ける
void  MulVector2DF(Vector2DF &vec, const float &mul) {
	vec.x *= mul;
	vec.y *= mul;
}

//4つの二次ベクトルに各要素ずつ代入
void SetVector2DF4(Vector2DF vec[], float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	vec[0].x = x1;
	vec[0].y = y1;
	vec[1].x = x2;
	vec[1].y = y2;
	vec[2].x = x3;
	vec[2].y = y3;
	vec[3].x = x4;
	vec[3].y = y4;
}

