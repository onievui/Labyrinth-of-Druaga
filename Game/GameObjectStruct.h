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
#include "GameDefine.h"
#include "GameEnum.h"



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

//マップ全体の構造体
struct MapData {
	Map map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];	//各マスの情報
	int width;								//マップの横幅
	int height;								//マップの縦幅
	Vector2DF player_init_pos;				//プレイヤーの初期座標
	Vector2DF treasure_pos;					//お宝の座標
};

// プレイヤー構造体
struct Player {
	PlayerState state;	//状態
	Vector2DF pos;		//座標
	RectF col;			//当たり判定の相対座標
	Vector2DF vel;		//移動量
	BOOL is_left;		//左向きかどうか
	BOOL is_ground;		//地面に接しているかどうか
	Graph graph;		//表示画像情報
	int sprite_num;		//スプライト番号
	int anime_count;	//アニメーション用カウンタ
};

//お宝構造体
struct Treasure {
	int state;		//状態
	Vector2DF pos;	//座標
	RectF col;		//当たり判定の相対座標
	Vector2DF vel;	//移動量
	Graph graph;	//表示画像情報
};

//召喚モンスター構造体
struct Minion {
	MinionPattern knd;	//種類
	int state;			//状態
	int hp;				//体力
	Vector2DF pos;		//座標
	RectF col;			//当たり判定の相対座標
	Vector2DF vel;		//移動量
	BOOL is_left;		//左向きかどうか
	Graph graph;		//表示画像情報
	int sprite_num;		//スプライト番号
	int anime_count;	//アニメーション用カウンタ
	int summon_time;	//召喚にかかる時間
};

//動く矩形の衝突判定用構造体
struct BoxCollider {
	int *state;			//オブジェクトの状態
	Vector2DF *pos;		//座標
	RectF *col;			//当たり判定の相対座標
	Vector2DF *vel;		//速度
};


