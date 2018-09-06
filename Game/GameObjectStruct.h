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
	Vector2DF player_pos;					//プレイヤーの初期座標
	int player_sp;							//プレイヤーの初期SP
	Vector2DF treasure_pos;					//お宝の座標
	BOOL summonable[MINION_PATTERN_NUM];	//召喚できるモンスターの種類
};

// プレイヤー構造体
struct Player {
	PlayerState state;	//状態
	Vector2DF pos;		//座標
	RectF col;			//当たり判定の相対座標
	Vector2DF vel;		//移動量
	Vector2DF *ride;	//乗っているオブジェクトの速度
	BOOL is_left;		//左向きかどうか
	BOOL is_ground;		//地面に接しているかどうか
	BOOL ground_flag;	//マップに着地したかどうか
	Graph graph;		//表示画像情報
	int sp;				//召喚に必要なポイント
	int sprite_num;		//スプライト番号
	int anime_count;	//アニメーション用カウンタ
};

//召喚可能なモンスターのリスト構造体
struct SummonableList {
	BOOL is_use;			//使用フラグ
	MinionPattern knd;		//種類
	Graph graph;			//表示画像情報
};

//モンスターの召喚範囲情報構造体
struct SummonAreaData {
	BOOL is_available;	//召喚可能かどうか
	int state;			//表示状態
	MinionPattern knd;	//選択している召喚モンスター
	Vector2DF pos;		//座標
	RectF area;			//範囲
	BOOL is_left;		//向き
};

//お宝構造体
struct Treasure {
	int state;			//状態
	Vector2DF pos;		//座標
	RectF col;			//当たり判定の相対座標
	Vector2DF vel;		//移動量
	Vector2DF *ride;	//乗っているオブジェクトの速度
	BOOL is_ground;		//地面に接しているかどうか
	Graph graph;		//表示画像情報
};

//モンスター召喚用データ
struct SummonData {
	int cost;
	int time;
};

//召喚モンスター構造体
struct Minion {
	MinionPattern knd;		//種類
	int state;				//状態
	int hp;					//体力
	Vector2DF pos;			//座標
	RectF col;				//当たり判定の相対座標
	Vector2DF vel;			//移動量
	Vector2DF *ride;		//乗っているオブジェクトの速度
	BOOL is_left;			//左向きかどうか
	int collision_state;	//他の物体にどう接しているか
	BOOL ground_flag;		//マップに着地したかどうか
	Graph graph;			//表示画像情報
	int sprite_num;			//スプライト番号
	int anime_count;		//アニメーション用カウンタ
	SummonData s_dat;		//召喚用データ
};

//動く矩形の衝突判定用構造体
struct BoxCollider {
	int *state;				//オブジェクトの状態
	Vector2DF *pos;			//座標
	RectF *col;				//当たり判定の相対座標
	Vector2DF *vel;			//速度
	Vector2DF **ride;		//乗っているオブジェクトの速度
	BOOL *collision_state;	//他の物体にどう接しているか
	BOOL *ground_flag;		//マップに着地したかどうか
};


