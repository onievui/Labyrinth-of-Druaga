#pragma once




// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "SceneStageSelect.h"
#include "Mediator.h"




// グローバル変数の定義 ====================================================

GameObject g_stageselect_back_object;	//背景オブジェクト
GameObject g_stageselect_icon_object;	//ステージアイコンオブジェクト

int g_select_stage;				//選択中のステージ番号




// 関数の宣言 ==============================================================
void InitializeStageSelect(void);  // ステージセレクトシーンの初期化処理
void UpdateStageSelect(void);      // ステージセレクトシーンの更新処理
void RenderStageSelect(void);      // ステージセレクトシーンの描画処理
void FinalizeStageSelect(void);    // ステージセレクトシーンの終了処理




 // 関数の定義 ==============================================================
 //----------------------------------------------------------------------
 //! @brief ステージセレクトシーンの初期化処理
 //!
 //! @param[in] なし
 //!
 //! @return なし
 //----------------------------------------------------------------------
void InitializeStageSelect(void)
{
	//背景オブジェクトの初期化
	g_stageselect_back_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_stageselect_back_object.vel = Vector2DF{ 0,0 };
	g_stageselect_back_object.state = 1;
	g_stageselect_back_object.speed = 0;
	g_stageselect_back_object.angle = 0;
	g_stageselect_back_object.graph = Graph{ &g_sprite[SPR_STAGESELECT_BG] , 1.0f, 0.0f };

	//アイコンオブジェクトの初期化
	g_stageselect_icon_object.pos = Vector2DF{ (float)(SCREEN_WIDTH * 7 / 10),(float)(SCREEN_CENTER_Y) };
	g_stageselect_icon_object.vel = Vector2DF{ 0,0 };
	g_stageselect_icon_object.state = 1;
	g_stageselect_icon_object.speed = 0;
	g_stageselect_icon_object.angle = 0;
	g_stageselect_icon_object.graph = Graph{ &g_sprite[SPR_STAGESELECT_ICON] , 1.0f, 0.0f };
}



//----------------------------------------------------------------------
//! @brief ステージセレクトシーンの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateStageSelect(void)
{
	//ステージの選択
	

	// Xキーでプレイ画面に遷移
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		//StopBGM(BGM_1);
		//SetSE(SE_DECISION);
		SetSelectStage((StageId)g_select_stage);
		RequestScene(SCENE_PLAY);
	}
}



//----------------------------------------------------------------------
//! @brief ステージセレクトシーンの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderStageSelect(void)
{
	//ステージセレクト背景の描画
	DrawGraphic(g_stageselect_back_object.pos, &g_stageselect_back_object.graph);

	//選択するステージ名の表示
	

	
}



//----------------------------------------------------------------------
//! @brief ステージセレクトシーンの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeStageSelect(void)
{

}










