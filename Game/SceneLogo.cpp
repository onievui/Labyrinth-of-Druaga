//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneLogo.cpp
//!
//! @brief  ロゴシーン関連のソースファイル
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "SceneLogo.h"


// グローバル変数の定義 ====================================================
int g_logo_state;	//ロゴシーンの状態
int g_logo_count;	//ロゴシーンの経過時間

GameObject g_logo_object1;	//ロゴオブジェクト1
GameObject g_logo_object2;	//ロゴオブジェクト2



// 関数の宣言 ==============================================================
void InitializeLogo(void);  // ロゴシーンの初期化処理
void UpdateLogo(void);      // ロゴシーンの更新処理
void RenderLogo(void);      // ロゴシーンの描画処理
void FinalizeLogo(void);    // ロゴシーンの終了処理




// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief ロゴシーンの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeLogo(void)
{
	g_logo_state = 0;
	g_logo_count = 0;
	
	//ロゴオブジェクト1の初期化
	g_logo_object1.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_logo_object1.vel = Vector2DF{ 0,0 };
	g_logo_object1.state = 1;
	g_logo_object1.speed = 0;
	g_logo_object1.angle = 0;
	g_logo_object1.graph = Graph{ &g_sprite[SPR_LOGO2] , 1.0f, 0.0f };

	//ロゴオブジェクト2の初期化
	g_logo_object2.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_logo_object2.vel = Vector2DF{ 0,0 };
	g_logo_object2.state = 1;
	g_logo_object2.speed = 0;
	g_logo_object2.angle = 0;
	g_logo_object2.graph = Graph{ &g_sprite[SPR_LOGO1] , 1.0f, 0.0f };
	
}



//----------------------------------------------------------------------
//! @brief ロゴシーンの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateLogo(void)
{
	//Xキーでスキップ
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		g_logo_count = 180;
		g_logo_state = 2;
	}

	//ロゴ表示時間内ならカウンタを増やす
	if (g_logo_count < 180) {
		g_logo_count++;
	}
	//1つ目のロゴが表示し終わったら2つ目を表示する
	else if (g_logo_state == 0) {
		g_logo_count = 0;
		g_logo_state = 1;
	}
	//タイトルシーンに遷移する
	else {
		RequestScene(SCENE_TITLE);
	}
}



//----------------------------------------------------------------------
//! @brief ロゴシーンの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderLogo(void)
{
	//ロゴオブジェクトの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255*(g_logo_count/90.0f)));
	if (g_logo_state == 0) {
		DrawGraphic(g_logo_object1.pos, &g_logo_object1.graph);
	}
	else if (g_logo_state == 1) {
		DrawGraphic(g_logo_object2.pos, &g_logo_object2.graph);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



//----------------------------------------------------------------------
//! @brief ロゴシーンの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeLogo(void)
{

}
