#pragma once




// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "SceneStageSelect.h"
#include "Mediator.h"



//定数の定義
#define CURSOR_SPEED	(15)	//カーソルを動かす時間の間隔



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
	g_stageselect_back_object.graph = Graph{ g_sprite[SPR_BG] , 1.0f, 0.0f };

	//アイコンオブジェクトの初期化
	g_stageselect_icon_object.pos = Vector2DF{ (float)(SCREEN_WIDTH * 1 / 10),(float)(SCREEN_HEIGHT / 5) };
	g_stageselect_icon_object.vel = Vector2DF{ 0,0 };
	g_stageselect_icon_object.state = 1;
	g_stageselect_icon_object.speed = 0;
	g_stageselect_icon_object.angle = 0;
	g_stageselect_icon_object.graph = Graph{ g_sprite[SPR_STAGESELECT_ICON] , 1.0f, 0.0f };

	g_select_stage = 0;
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
	switch (CheckStateKeyLater4(KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP, KEY_INPUT_DOWN)) {
	//何も押されていない
	case 0:
		break;
	//左が押されている
	case 1:
		if (CheckStateKey(KEY_INPUT_LEFT) % CURSOR_SPEED == 1) {
			if (g_select_stage > 0) {
				g_select_stage--;
			}
		}
		break;
	//右が押されている
	case 2:
		if (CheckStateKey(KEY_INPUT_RIGHT) % CURSOR_SPEED == 1) {
			if (g_select_stage < STAGE_NUM - 1) {
				g_select_stage++;
			}
		}
		break;
	//上が押されている
	case 3:
		if (CheckStateKey(KEY_INPUT_UP) % CURSOR_SPEED == 1) {
			if (g_select_stage > 4) {
				g_select_stage -= 5;
			}
		}
		break;
	//下が押されている
	case 4:
		if (CheckStateKey(KEY_INPUT_DOWN) % CURSOR_SPEED == 1) {
			if (g_select_stage < STAGE_NUM - 5) {
				g_select_stage += 5;
			}
		}
		break;
	default:
		MessageBox(NULL, "ステージ選択のキー入力で不正な値が渡されました", "", MB_OK);
		break;

	}

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
	Vector2DF pos = g_stageselect_icon_object.pos;
	for (int i = 0; i < STAGE_NUM; i++) {
		//DrawGraphic(pos, &g_stageselect_back_object.graph);
		DrawBoxAA(pos.x - 60, pos.y - 40, pos.x + 60, pos.y + 40, COLOR_BLUE, TRUE);

		pos.x += SCREEN_WIDTH * 4 / 20;
	}

	//選択中のステージを表すカーソルの表示
	pos.x = g_stageselect_icon_object.pos.x + (SCREEN_WIDTH * 4 / 20)*(g_select_stage % 5);
	pos.y = g_stageselect_icon_object.pos.y + (SCREEN_WIDTH * 4 / 20)*(g_select_stage / 5);
	DrawBoxAA(pos.x - 70, pos.y - 50, pos.x + 70, pos.y + 50, COLOR_RED, FALSE, 3);
	
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










