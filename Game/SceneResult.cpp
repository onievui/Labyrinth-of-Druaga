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
int g_second;						//クリアタイムの秒
int g_decimal;						//クリアタイムの秒（小数）
BOOL g_is_highscore;				//ハイスコアかどうか
AllClearData *g_old_clear_data;		//クリアデータ



// 関数の宣言 ==============================================================
void InitializeResult(void);  // プレイシーンの初期化処理
void UpdateResult(void);      // プレイシーンの更新処理
void RenderResult(void);      // プレイシーンの描画処理
void FinalizeResult(void);    // プレイシーンの終了処理

void ChangeGetClearTime();
void UpdateHighscore();




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
	
	//クリアデータの取得
	g_old_clear_data = GetAllClearData();

	//クリアタイムの取得、変換
	ChangeGetClearTime();
	
	//ハイスコア更新処理
	UpdateHighscore();

	//ハイスコアなら効果音を鳴らす
	if (g_is_highscore) {
		SetSE(SE_HIGHSCORE);
	}
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

	//ハイスコアなら表示する
	if (g_is_highscore) {
		DrawFormatStringFToHandle(SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g70, "HIGH SCORE!") / 2.0f,
			SCREEN_CENTER_Y - 165, COLOR_RED, g_font_g70, "HIGH SCORE!");
	}

	//クリアタイムの表示
	DrawFormatStringFToHandle(SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g70, "TIME %d.%02d", g_second,g_decimal) / 2.0f,
		SCREEN_CENTER_Y - 50, COLOR_YELLOW, g_font_g70, "TIME %d.%02d", g_second, g_decimal);
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


//クリアタイムの取得、変換
void ChangeGetClearTime() {

	int time = GetClearTime();
	char time_s[10], input[5];
	sprintf(time_s, "%.2f", time / 60.0f);
	int i = 0, j = 0, knd = 0;
	//整数部分と小数部分に分ける
	while (1) {
		for (j = 0; j<5; j++) {
			input[j] = time_s[i + j];	//1文字取得する
			if (input[j] == '.' || input[j] == '\0') {	//ピリオドか改行ならそこまでを文字列とする
				input[j] = '\0';
				break;
			}
		}
		if (knd == 0) {
			g_second = atoi(input);
		}
		else {
			g_decimal = atoi(input);
			break;
		}
		i = j + 1;
		knd++;
	}
}


//ハイスコア更新処理
void UpdateHighscore() {																																																																																																		

	StageId id = GetSelectStage();
	g_is_highscore = FALSE;

	//ハイスコアなら
	if (g_old_clear_data->clear_data[id].second == 0 ||
		g_second * 100 + g_decimal <
		g_old_clear_data->clear_data[id].second * 100 + g_old_clear_data->clear_data[id].decimal) {
		
		//スコアを更新する
		g_old_clear_data->clear_data[id].second = g_second;
		g_old_clear_data->clear_data[id].decimal = g_decimal;

		//全ステージクリアしているなら合計スコアも更新する
		g_old_clear_data->clear_data[id].is_clear = TRUE;
		if (GetClearStageNum() == STAGE_NUM) {
			int i;
			g_old_clear_data->total_second = 0;
			g_old_clear_data->total_decimal = 0;
			for (i = 0; i < STAGE_NUM; i++) {
				g_old_clear_data->total_second += g_old_clear_data->clear_data[i].second;
				g_old_clear_data->total_decimal += g_old_clear_data->clear_data[i].decimal;
			}
			g_old_clear_data->total_second += g_old_clear_data->total_decimal / 100;
			g_old_clear_data->total_decimal = g_old_clear_data->total_decimal % 100;
		}

		//スコアの反映
		OrderWriteClearData();

		//ハイスコア状態にする
		g_is_highscore = TRUE;
	}
}