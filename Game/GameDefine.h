#pragma once


//外部に公開する定数の定義

// <システム> ----------------------------------------------------------
#define GAME_TITLE "ドルアーガの迷宮"        // ゲームタイトル


// <画面> --------------------------------------------------------------
#define SCREEN_WIDTH    (800)                  // 画面の幅[pixel]
#define SCREEN_HEIGHT   (600)                  // 画面の高さ[pixel]

#define SCREEN_TOP      (0)                    // 画面の上端
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // 画面の下端
#define SCREEN_LEFT     (0)                    // 画面の左端
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // 画面の右端

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // 画面の中央(X座標)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // 画面の中央(Y座標)

//マップ関係
#define MAP_WIDTH_MAX	(20)	//マップの最大横幅
#define MAP_HEIGHT_MAX	(20)	//マップの最大縦幅

#define MAPCHIP_SIZE		(64)	//マップチップの大きさ
#define MAPCHIP_SIZE_HALF	(32)	//マップチップの大きさの半分


//フィールド関係
#define FIELD_WIDTH    (MAP_WIDTH_MAX * MAPCHIP_SIZE)                  // フィールドの幅[pixel]
#define FIELD_HEIGHT   (MAP_HEIGHT_MAX * MAPCHIP_SIZE)                 // フィールドの高さ[pixel]

#define FIELD_CENTER_X (FIELD_WIDTH  / 2)    // フィールドの中央(X座標)
#define FIELD_CENTER_Y (FIELD_HEIGHT / 2)    // フィールドの中央(Y座標)


//数学・物理関係
#define PI	(DX_PI_F)	//円周率
#define PI2	(PI * 2)	//円周率*2

#define GRAVITY		(2.0f)	//重力

#define ISLEFT		(1)		//左側に接しているかのマクロ
#define ISRIGHT		(2)		//右側に接しているかのマクロ
#define ISCEILING	(4)		//天井（上側）に接しているかのマクロ
#define ISGROUND	(8)		//地面（下側）に接しているかのマクロ
#define ISTRUE		(16)	//TRUEとISLEFTの競合回避用


//UI関係
#define CURSOR_SPEED	(15)	//カーソルを動かす時間の間隔


//プレイヤー関係
#define PLAYER_MAX	(1)		//プレイヤーの数

#define PLAYER_WALK_SPEED	(5)		//プレイヤーの移動速度
#define PLAYER_JUMP_SPEED	(-22)	//プレイヤーのジャンプ速度


//召喚モンスター関係
#define MINION_MAX	(20)	//召喚できるモンスターの最大数

//ドラゴンの炎関係
#define FIRE_MAX	(5)		//ドラゴンの炎の最大出現数


//お宝関係
#define TREASURE_MAX	(1)		//お宝の数







