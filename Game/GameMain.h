//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム関連のヘッダファイル
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once
#include "Graphic.h"
#include "GameObjectStruct.h"
#include "GameDefine.h"
#include "GameEnum.h"
#include "Key.h"
#include "Sound.h"



// 定数の定義 ==============================================================

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




// 関数の宣言 ==============================================================

// ゲームの初期化処理
void InitializeGame(void);

// ゲームの更新処理
void UpdateGame(void);

// ゲームの描画処理
void RenderGame(void);

// ゲームの終了処理
void FinalizeGame(void);

// シーンの変更要求
void RequestScene(const SceneId sceneId);


