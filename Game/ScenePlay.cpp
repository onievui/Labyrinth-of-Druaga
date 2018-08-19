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
#include "Treasure.h"
#include "Collision.h"
#include "Shader.h"
#include "Mediator.h"




// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================
int g_count;			//シーンが開始してからのカウント数
int g_play_state;		//プレイシーンの状態
int g_select_mode;		//コンティニュー確認画面での選択状態
int g_wait_time;		//コンティニューの確認を表示するまでの待ち時間


// 関数の宣言 ==============================================================
void InitializePlay(void);  // プレイシーンの初期化処理
void UpdatePlay(void);      // プレイシーンの更新処理
void RenderPlay(void);      // プレイシーンの描画処理
void FinalizePlay(void);    // プレイシーンの終了処理
void PlayProcess();
void PauseProcess();
void StageFailedProcess();




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

	//お宝の初期化
	InitializeTreasure();

	//マップの初期化
	InitializeMap();

	//当たり判定の初期化
	InitializeCollision();

	//カウンタの初期化
	g_count = 0;

	//状態の初期化
	g_play_state = 0;
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
	case 0:
		PlayProcess();
		break;
	//ポーズ状態
	case 1:
		
		break;
	//ゲーム失敗状態
	case 2:
		
		break;
	//ステージクリア状態
	case 3:
		
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
	//マップの描画
	DrawMap();

	//お宝の描画
	DrawTreasure();

	//プレイヤーの描画
	DrawPlayer();

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
	
}

//ステージ失敗処理
void StageFailedProcess() 
{
	
}

//ステージクリアへの移行
void RequestStageClear() 
{
	
}

//ステージクリア処理
void StageClearProcess() 
{

}
