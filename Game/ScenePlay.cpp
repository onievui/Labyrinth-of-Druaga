//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScenePlay.cpp
//!
//! @brief  プレイシーン関連のソースファイル
//!
//! @date   2018/08/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "ScenePlay.h"
#include "Map.h"
#include "Player.h"
#include "MinionManager.h"
#include "Treasure.h"
#include "Collision.h"
#include "Shader.h"
#include "Mediator.h"




// 定数の定義 ==============================================================

//プレイシーンの状態
enum ScenePlayState {
	PLAY_STATE_PLAY,	//プレイ状態
	PLAY_STATE_PAUSE,	//ポーズ状態
	PLAY_STATE_FAILED,	//ステージ失敗状態
	PLAY_STATE_CLEAR,	//ステージクリア状態
};



// グローバル変数の定義 ====================================================
int g_count;					//シーンが開始してからのカウント数
ScenePlayState g_play_state;	//プレイシーンの状態
int g_select_mode;				//ポーズ/リトライ確認画面での選択状態
int g_wait_time;				//次の状態へ移行するための待ち時間


// 関数の宣言 ==============================================================
void InitializePlay(void);  // プレイシーンの初期化処理
void UpdatePlay(void);      // プレイシーンの更新処理
void RenderPlay(void);      // プレイシーンの描画処理
void FinalizePlay(void);    // プレイシーンの終了処理
void PlayProcess();
void PauseProcess();
void StageFailedProcess();
void StageClearProcess();




// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief プレイシーンの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializePlay(void)
{
	//プレイヤーの初期化
	InitializePlayer();

	//召喚モンスターの初期化
	InitializeMinions();

	//お宝の初期化
	InitializeTreasure();

	//マップの初期化
	InitializeMap();

	//当たり判定の初期化
	InitializeCollision();

	//カウンタの初期化
	g_count = 0;

	//状態の初期化
	g_play_state = PLAY_STATE_PLAY;
	g_select_mode = 0;
	g_wait_time = 0;
}



//----------------------------------------------------------------------
//! @brief プレイシーンの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdatePlay(void)
{

	switch (g_play_state) {
	//プレイ状態
	case PLAY_STATE_PLAY:
		PlayProcess();
		break;
	//ポーズ状態
	case PLAY_STATE_PAUSE:
		PauseProcess();
		break;
	//ゲーム失敗状態
	case PLAY_STATE_FAILED:
		StageFailedProcess();
		break;
	//ステージクリア状態
	case PLAY_STATE_CLEAR:
		StageClearProcess();
		break;
	default:
		MessageBox(NULL, "プレイシーンの状態で不正な値が渡されました", "", MB_OK);
		break;
	}


}



//----------------------------------------------------------------------
//! @brief プレイシーンの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderPlay(void)
{
	BOOL is_change_bright = FALSE;

	//ポーズ/リトライ確認画面では暗くする
	if (g_play_state == PLAY_STATE_PAUSE || (g_play_state == PLAY_STATE_FAILED && g_wait_time == 0)) {
		SetDrawBright(70, 70, 70);
		is_change_bright = TRUE;
	}

	//マップの描画
	DrawMap();

	//お宝の描画
	DrawTreasure();

	//召喚モンスターの描画
	DrawMinions();

	//プレイヤーの描画
	DrawPlayer();

	//SPと召喚可能なモンスターのリストの描画
	DrawPlayerUI();

	//画面の明るさを戻す
	if (is_change_bright) {
		SetDrawBright(255, 255, 255);

		//リトライ確認画面なら選択肢を表示する
		if (g_play_state == PLAY_STATE_FAILED && g_wait_time == 0) {
			Vector2DF pos = { (float)SCREEN_CENTER_X/2,(float)SCREEN_CENTER_Y };
			DrawBoxAA(pos.x - 120, pos.y - 80, pos.x + 120, pos.y + 80, COLOR_AQUA, TRUE);
			DrawFormatStringFToHandle(pos.x - 105, pos.y - 30, COLOR_RED, g_font_g70, "RETRY");
			pos.x += SCREEN_CENTER_X;
			DrawBoxAA(pos.x - 120, pos.y - 80, pos.x + 120, pos.y + 80, COLOR_AQUA, TRUE);
			DrawFormatStringFToHandle(pos.x - 120, pos.y - 30, COLOR_PURPLE, g_font_g70, "GIVE UP");
			
			pos.x = g_select_mode == 0 ? SCREEN_CENTER_X / 2 : pos.x;
			DrawBoxAA(pos.x - 140, pos.y - 100, pos.x + 140, pos.y + 100, COLOR_RED, FALSE, 6);
		}

	}	

}



//----------------------------------------------------------------------
//! @brief プレイシーンの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizePlay(void)
{

}

//プレイ処理
void PlayProcess() 
{
	//プレイヤーの更新
	UpdatePlayer();

	//召喚モンスターの更新
	UpdateMinions();

	//お宝の更新
	UpdateTreasure();

	//当たり判定の更新
	UpdateCollision();
	
	//カメラのオフセットの更新
	UpdateCameraOffset();

	g_count++;
}

//ポーズ画面処理
void PauseProcess() 
{

}

//ステージ失敗状態への移行
void RequestStageFailed() 
{
	//ステージ失敗状態へ移行
	g_play_state = PLAY_STATE_FAILED;
	//2秒間待つ
	g_wait_time = 120;
	//カーソルの初期化
	g_select_mode = 0;
}

//ステージ失敗処理
void StageFailedProcess() 
{
	//ステージ失敗時の演出
	if (g_wait_time) {

		//プレイヤーの更新
		UpdatePlayer();

		//カメラのオフセットの更新
		UpdateCameraOffset();

		g_wait_time--;
	}
	//リトライ確認
	else {
		//左右キーでカーソル移動
		if (CheckHitKeyDown(KEY_INPUT_LEFT) || CheckHitKeyDown(KEY_INPUT_RIGHT)) {
			g_select_mode = 1 - g_select_mode;
		}
		//ZキーかXキーで選択
		if (CheckHitKeyDown(KEY_INPUT_Z) || CheckHitKeyDown(KEY_INPUT_X)) {
			//リトライならシーンプレイをやり直す
			if (g_select_mode == 0) {
				SetSelectStage(GetSelectStage());
				RequestScene(SCENE_PLAY);
			}
			//ギブアップならステージセレクトに戻る
			else {
				RequestScene(SCENE_STAGESELECT);
			}
		}
	}
}

//ステージクリアへの移行
void RequestStageClear() 
{
	//クリアタイムの記録
	SetClearTime(g_count);
	//クリア状態へ移行
	g_play_state = PLAY_STATE_CLEAR;
	//3秒間待つ
	g_wait_time = 180;
}

//ステージクリア処理
void StageClearProcess() 
{
	if (g_wait_time) {

		//プレイヤーの更新
		UpdatePlayer();

		//当たり判定の更新
		UpdateCollision();

		//カメラのオフセットの更新
		UpdateCameraOffset();

		g_wait_time--;
	}
	else {
		//待ち時間が終わったらリザルト画面へ移行
		RequestScene(SCENE_RESULT);
	}
}
