//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#pragma once



// ヘッダファイルの読み込み ================================================
#include "GameMain.h"

#include <assert.h>

#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneStageSelect.h"
#include "ScenePlay.h"
#include "SceneResult.h"

#include "Shader.h"

#include "Mediator.h"


// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================
SceneId g_active_scene;	// 現在実行中のシーン
SceneId g_next_scene;	// 次のシーン


//各シーンの初期化処理の関数ポインタ
void(*g_initialize_scene[SCENE_NUM])(void) = {
	 InitializeLogo,
	 InitializeTitle,
	 InitializeStageSelect,
	 InitializePlay,
	 InitializeResult
};

//各シーンの更新処理の関数ポインタ
void(*g_update_scene[SCENE_NUM])(void) = {
	UpdateLogo,
	UpdateTitle,
	UpdateStageSelect,
	UpdatePlay,
	UpdateResult
};

//各シーンの描画処理の関数ポインタ
void(*g_render_scene[SCENE_NUM])(void) = {
	RenderLogo,
	RenderTitle,
	RenderStageSelect,
	RenderPlay,
	RenderResult
};

//各シーンの終了処理の関数ポインタ
void(*g_finalize_scene[SCENE_NUM])(void) = {
	FinalizeLogo,
	FinalizeTitle,
	FinalizeStageSelect,
	FinalizePlay,
	FinalizeResult
};




// 関数の宣言 ==============================================================
// 公開関数
void InitializeGame(void);  // ゲームの初期化処理
void UpdateGame(void);      // ゲームの更新処理
void RenderGame(void);      // ゲームの描画処理
void FinalizeGame(void);    // ゲームの終了処理

void RequestScene(const SceneId sceneId);	 // シーンの変更要求

// 非公開関数
void InitializeScene(const SceneId sceneId);  // シーンの初期化処理
void UpdateScene(const SceneId sceneId);      // シーンの更新処理
void RenderScene(const SceneId sceneId);      // シーンの描画処理
void FinalizeScene(const SceneId sceneId);    // シーンの終了処理





// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeGame(void)
{
	//リソースの読み込み、初期化
	LoadResources();
	InitializeSprite();
	
	//シェーダーの初期化
	InitializeShader();

	//初期シーン状態のセット
	g_active_scene = SCENE_NONE;
	g_next_scene = SCENE_LOGO;

	//Mediatorの初期化
	InitializeMediator();
	
}



//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//キー入力の更新
	if (GetHitKeyStateAll_2() != 0) {
		MessageBox(NULL, "キー入力に失敗しました", "", MB_OK);
	}

	//音声フラグのリセット
	ResetSounds();


	// シーン変更が必要かどうかをチェック
	if (g_next_scene != SCENE_NONE) {
		FinalizeScene(g_active_scene);	//今のシーンの終了処理を行う
		InitializeScene(g_next_scene);	//新しいシーンの初期化処理を行う
		g_active_scene = g_next_scene;	//シーンの選択状態を反映させる
		g_next_scene = SCENE_NONE;
	}

	//活動中のシーンを描画
	UpdateScene(g_active_scene);

	
	//音声の再生
	PlaySE();
	PlayBGM();

}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderGame(void)
{
	//シェーダーの描画準備
	UseShaderCheck();

	RenderScene(g_active_scene);

	//シェーダーの描画
	UseShader();
	
}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	FinalizeScene(g_active_scene);

	FinalizeShader();

	DeleteResources();

}


// シーンの変更要求
void RequestScene(const SceneId sceneId)
{
	g_next_scene = sceneId;
}


// シーンの初期化処理
void InitializeScene(SceneId sceneId)
{
	//意図しないシーンが呼ばれたときにエラー処理を行う
	if (sceneId < SCENE_NONE || sceneId >= SCENE_NUM) {
		assert(FALSE);
		return;
	}

	//シーンが未選択でなければシーンの初期化処理を行う
	if (sceneId != SCENE_NONE) {
		(g_initialize_scene[sceneId])();
	}
}


// シーンの更新処理
void UpdateScene(const SceneId sceneId)
{
	//意図しないシーンが呼ばれたときにエラー処理を行う
	if (sceneId < SCENE_NONE || sceneId >= SCENE_NUM) {
		assert(FALSE);
		return;
	}

	//シーンが未選択でなければシーンの更新処理を行う
	if (sceneId != SCENE_NONE) {
		g_update_scene[sceneId]();
	}
}


// シーンの描画処理
void RenderScene(const SceneId sceneId)
{
	//意図しないシーンが呼ばれたときにエラー処理を行う
	if (sceneId < SCENE_NONE || sceneId >= SCENE_NUM) {
		assert(FALSE);
		return;
	}

	//シーンが未選択でなければシーンの描画処理を行う
	if (sceneId != SCENE_NONE) {
		g_render_scene[sceneId]();
	}
}


// シーンの終了処理
void FinalizeScene(const SceneId sceneId)
{
	//意図しないシーンが呼ばれたときにエラー処理を行う
	if (sceneId < SCENE_NONE || sceneId >= SCENE_NUM) {
		assert(FALSE);
		return;
	}

	//シーンが未選択でなければシーンの終了処理を行う
	if (sceneId != SCENE_NONE) {
		g_finalize_scene[sceneId]();
	}
}

