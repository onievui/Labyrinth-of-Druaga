#pragma once




// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "SceneStageSelect.h"
#include "Mediator.h"




//定数の定義
#define ICON_DEF_X	((float)(SCREEN_WIDTH / 10))	//ステージアイコンの初期X座標
#define ICON_DEF_Y	((float)(SCREEN_HEIGHT / 5))	//ステージアイコンの初期Y座標

#define COLOR_BLUE2 ((unsigned int)(0xFF0040FF))	//青色2


// グローバル変数の定義 ====================================================

GameObject g_stageselect_back_object;	//背景オブジェクト
int g_select_stage;				//選択中のステージ番号
AllClearData *g_view_clear_data;	//クリアデータ



// 関数の宣言 ==============================================================
void InitializeStageSelect(void);  // ステージセレクトシーンの初期化処理
void UpdateStageSelect(void);      // ステージセレクトシーンの更新処理
void RenderStageSelect(void);      // ステージセレクトシーンの描画処理
void FinalizeStageSelect(void);    // ステージセレクトシーンの終了処理
BOOL IsSelectableStage(int i);




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

	//前回のステージにカーソルを合わせる
	g_select_stage = GetSelectStage();
	if (!~g_select_stage)
		g_select_stage = 0;

	//BGMの再生
	SetBGM(BGM_SELECT);

	//クリアデータの読み込み
	OrderLoadClearData();
	//クリアデータの取得
	g_view_clear_data = GetAllClearData();
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
			g_select_stage += g_select_stage % 5 ? -1 : 4;
			if (!IsSelectableStage(g_select_stage)) {
				g_select_stage += g_select_stage % 5 != 4 ? 1 : -4;
			}
		}
		break;
	//右が押されている
	case 2:
		if (CheckStateKey(KEY_INPUT_RIGHT) % CURSOR_SPEED == 1) {
			g_select_stage += g_select_stage % 5 != 4 ? 1 : -4;
			if (!IsSelectableStage(g_select_stage)) {
				g_select_stage += g_select_stage % 5 ? -1 : 4;
			}
		}
		break;
	//上が押されている
	case 3:
		if (CheckStateKey(KEY_INPUT_UP) % CURSOR_SPEED == 1) {
			if (g_select_stage > 4) {
				g_select_stage -= 5;
				if (!IsSelectableStage(g_select_stage)) {
					g_select_stage += 5;
				}
			}
		}
		break;
	//下が押されている
	case 4:
		if (CheckStateKey(KEY_INPUT_DOWN) % CURSOR_SPEED == 1) {
			if (g_select_stage < STAGE_NUM - 5) {
				g_select_stage += 5;
				if (!IsSelectableStage(g_select_stage)) {
					g_select_stage -= 5;
				}
			}
		}
		break;
	default:
		MessageBox(NULL, "ステージ選択のキー入力で不正な値が渡されました", "", MB_OK);
		break;

	}

	// Xキーでプレイ画面に遷移
	if (CheckHitKeyDown(KEY_INPUT_X)) {
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
	int i;
	Vector2DF pos = { ICON_DEF_X,ICON_DEF_Y };
	char name[20];
	char time[20];
	for (i = 0; i < STAGE_NUM; i++) {
		//未クリア状態なら
		if (!g_view_clear_data->clear_data[i].is_clear) {
			//枠の描画
			DrawBoxAA(pos.x - 60, pos.y - 40, pos.x + 60, pos.y + 40, COLOR_BLACK, TRUE);

			//文字の描画
			//選択できないステージは表示しない
			if (IsSelectableStage(i)) {
				sprintf(name, "%d - %d", i / 5 + 1, i % 5 + 1);
				DrawFormatStringFToHandle(pos.x - GetDrawFormatStringWidthToHandle(g_font_g30, "%s", name) / 2.0f,
					pos.y - 10, COLOR_WHITE, g_font_g30, "%s", name);
			}
		}
		//クリア状態なら
		else {
			//枠の描画
			DrawBoxAA(pos.x - 60, pos.y - 40, pos.x + 60, pos.y + 40, COLOR_BLUE2, TRUE);

			//文字の描画
			sprintf(name, "%d - %d", i / 5 + 1, i % 5 + 1);
			DrawFormatStringFToHandle(pos.x - GetDrawFormatStringWidthToHandle(g_font_g30, "%s", name) / 2.0f,
				pos.y - 25, COLOR_WHITE, g_font_g30, "%s", name);
			sprintf(time, "%d.%02d", g_view_clear_data->clear_data[i].second, g_view_clear_data->clear_data[i].decimal);
			DrawFormatStringFToHandle(pos.x - GetDrawFormatStringWidthToHandle(g_font_g30, "%s", time) / 2.0f,
				pos.y + 10, COLOR_WHITE, g_font_g30, "%s", time);
		}

		//座標をずらす
		if (i % 5 != 4) {
			pos.x += SCREEN_WIDTH * 4 / 20;
		}
		else {
			pos.x = ICON_DEF_X;
			pos.y += SCREEN_HEIGHT * 4 / 20;
		}
	}

	//選択中のステージを表すカーソルの表示
	pos.x = ICON_DEF_X + (SCREEN_WIDTH  * 4 / 20)*(g_select_stage % 5);
	pos.y = ICON_DEF_Y + (SCREEN_HEIGHT * 4 / 20)*(g_select_stage / 5);
	DrawBoxAA(pos.x - 70, pos.y - 50, pos.x + 70, pos.y + 50, COLOR_RED, FALSE, 3);

	//残りステージ・合計タイムの表示
	pos.x = (float)(SCREEN_CENTER_X);
	pos.y = (float)(SCREEN_HEIGHT * 7 /8);
	int count = GetClearStageNum();
	//残り2つ以上
	if (count < STAGE_NUM - 1) {
		sprintf(time, "%d STAGES LEFT", STAGE_NUM - count);
	}
	//残り1つ
	else if (count == STAGE_NUM - 1) {
		sprintf(time, "%d STAGE LEFT", 1);
	}
	//全ステージクリア
	else {
		sprintf(time, "TOTAL : %d.%02d", g_view_clear_data->total_second, g_view_clear_data->total_decimal);
	}	
	DrawFormatStringFToHandle(pos.x - GetDrawFormatStringWidthToHandle(g_font_g60, "%s", time) / 2.0f,
		pos.y + 10, COLOR_YELLOW, g_font_g60, "%s", time);
	
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
	//BGMを止める
	StopBGM(BGM_SELECT);
}


//選択できるステージかどうか
BOOL IsSelectableStage(int i) {
	int j = i;
	if (i == 0) {
		j = 1;
	}
	if(!g_view_clear_data->clear_data[j - 1].is_clear && i % 5) {
		return FALSE;
	}
	return TRUE;
}







