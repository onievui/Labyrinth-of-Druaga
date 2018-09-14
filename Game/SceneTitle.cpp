//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneTitle.cpp
//!
//! @brief  タイトルシーン関連のソースファイル
//!
//! @date   2018/08/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "SceneTitle.h"



// グローバル変数の定義 ====================================================

GameObject g_title_object;	//タイトルオブジェクト
GameObject g_bg_object;		//背景オブジェクト



// 関数の宣言 ==============================================================
void InitializeTitle(void);  // タイトルシーンの初期化処理
void UpdateTitle(void);      // タイトルシーンの更新処理
void RenderTitle(void);      // タイトルシーンの描画処理
void FinalizeTitle(void);    // タイトルシーンの終了処理




// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief タイトルシーンの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeTitle(void)
{
	//タイトルオブジェクトの初期化
	g_title_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_title_object.vel = Vector2DF{ 0,0 };
	g_title_object.state = 1;
	g_title_object.speed = 0;
	g_title_object.angle = 0;
	g_title_object.graph = Graph{ g_sprite[SPR_TITLE] , 1.0f, 0.0f };

	//背景オブジェクトの初期化
	g_bg_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_bg_object.vel = Vector2DF{ 0,0 };
	g_bg_object.state = 1;
	g_bg_object.speed = 0;
	g_bg_object.angle = 0;
	g_bg_object.graph = Graph{ g_sprite[SPR_BG] , 1.0f, 0.0f };

	//BGMの再生
	SetBGM(BGM_TITLE);
}



//----------------------------------------------------------------------
//! @brief タイトルシーンの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateTitle(void)
{
	// Xキーでステージセレクト画面に遷移
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		RequestScene(SCENE_STAGESELECT);
		//SetSE(SE_DECISION);
	}
}



//----------------------------------------------------------------------
//! @brief タイトルシーンの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderTitle(void)
{
	//背景の描画
	DrawGraphic(g_bg_object.pos, &g_bg_object.graph);

	//タイトルの描画
	DrawGraphic(g_title_object.pos, &g_title_object.graph);

	//キー入力の促し
	DrawFormatStringFToHandle(	SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g40, "START [X] KEY") / 2.0f, 
								SCREEN_CENTER_Y + 220, COLOR_YELLOW, g_font_g40, "START [X] KEY");
}



//----------------------------------------------------------------------
//! @brief タイトルシーンの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeTitle(void)
{
	//BGMを止める
	StopBGM(BGM_TITLE);
}
