//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Vector2DF.h
//!
//! @brief  二次ベクトルデータのヘッダファイル
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//二次ベクトル構造体
struct Vector2DF {
	float x;
	float y;

};

//移動量計算
void CalcVector2DF(Vector2DF &vel, const float &speed, const float &angle);

//二次ベクトルの加算
void AddVector2DF(Vector2DF &vec1, const Vector2DF &vec2);

//二次ベクトルの減算
void SubVector2DF(Vector2DF &vec1, const Vector2DF &vec2);

//二次ベクトルにスカラーを掛ける
void  MulVector2DF(Vector2DF &vec, const float &mul);

//4つの二次ベクトルに各要素ずつ代入
void SetVector2DF4(Vector2DF vec[], float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

