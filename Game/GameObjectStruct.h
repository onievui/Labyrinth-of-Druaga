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
#include "RectF.h"
#include "Sprite.h"



// 基本オブジェクトデータ
struct GameObject {
	Vector2DF pos;		//座標
	Vector2DF vel;		//移動量
	int state;			//状態
	float speed;		//速度
	float angle;		//角度
	Graph graph;		//表示画像情報
};

//マップ構造体
struct Map {
	SPR_ID knd;			//種類
	Vector2DF pos;		//座標
	GraphP graphp;		//画像
};

// プレイヤー構造体
struct Player {
	int state;			//状態
	Vector2DF pos;		//座標
	RectF col;			//当たり判定の相対座標
	Vector2DF vel;		//移動量
	float speed;		//移動速度
	BOOL is_left;		//左向きかどうか
	Graph graph;		//表示画像情報
	int sprite_num;		//スプライト番号
	int anime_count;	//アニメーション用カウンタ
};
