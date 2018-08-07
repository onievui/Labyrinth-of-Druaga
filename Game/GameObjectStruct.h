//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameObjectStruct.h
//!
//! @brief  ゲームオブジェクトの定義
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#pragma once


//ヘッダーファイルの読み込み
#include "Graphic.h"
#include "Vector2DF.h"
#include "Sprite.h"



// 基本オブジェクトデータ
struct GameObject {
	Vector2DF pos;		//座標
	Vector2DF vel;		//移動量
	int state;		//状態
	float speed;	//速度
	float angle;	//角度
	Graph graph;	//表示画像情報
};
