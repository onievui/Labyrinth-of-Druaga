//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneResult.cpp
//!
//! @brief  プレイシーン関連のソースファイル
//!
//! @date   2018/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "SceneResult.h"
#include "Mediator.h"


// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================
GameObject g_result_back_object;	//背景オブジェクト



// 関数の宣言 ==============================================================
void InitializeResult(void);  // プレイシーンの初期化処理
void UpdateResult(void);      // プレイシーンの更新処理
void RenderResult(void);      // プレイシーンの描画処理
void FinalizeResult(void);    // プレイシーンの終了処理




// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief リザルトシーンの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeResult(void)
{
	//背景オブジェクトの初期化
	g_result_back_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_result_back_object.vel = Vector2DF{ 0,0 };
	g_result_back_object.state = 1;
	g_result_back_object.speed = 0;
	g_result_back_object.angle = 0;
	g_result_back_object.graph = Graph{ g_sprite[SPR_BG] , 1.0f, 0.0f };

	//SetBGM(BGM_1);

	

	

}



//----------------------------------------------------------------------
//! @brief リザルトシーンの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateResult(void)
{
	// Xキーでステージセレクト画面に遷移
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		RequestScene(SCENE_STAGESELECT);
		//SetSE(SE_DECISION);
	}
}



//----------------------------------------------------------------------
//! @brief リザルトシーンの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderResult(void)
{
	//リザルト背景の描画
	DrawGraphic(g_result_back_object.pos, &g_result_back_object.graph);

	//クリアタイムの表示
	int time = GetClearTime();
	DrawFormatStringFToHandle(SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g70, "TIME %.2f", time / 60.0f) / 2.0f,
		SCREEN_CENTER_Y - 50, COLOR_YELLOW, g_font_g70, "TIME %.2f", time / 60.0f);
	//キー入力の促し
	DrawFormatStringFToHandle(SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g40, "Press [X] Key") / 2.0f,
		SCREEN_CENTER_Y + 100, COLOR_WHITE, g_font_g40, "Press [X] Key");
	
}



//----------------------------------------------------------------------
//! @brief リザルトシーンの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeResult(void)
{

}
