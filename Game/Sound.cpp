//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   sound.cpp
//!
//! @brief  サウンド関連の処理
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/_S_/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


//ヘッダーファイルの読み込み
#include "Sound.h"



//グローバル変数の宣言

//サウンドフラグ
BOOL g_se_flag[SE_ALL_NUM];
BOOL g_bgm_flag[BGM_ALL_NUM];
BOOL g_continue_flag[BGM_ALL_NUM];





//----------------------------------------------------------------------
//! @brief 音声初期化
//!
//! @param[in] なし
//!
//! @return　なし
//----------------------------------------------------------------------
void ResetSounds() {
	for (int i = 0; i < SE_ALL_NUM; i++)
		g_se_flag[i] = FALSE;
	for (int i = 0; i < BGM_ALL_NUM; i++)
		g_bgm_flag[i] = FALSE;
	for (int i = 0; i < BGM_ALL_NUM; i++)
		g_continue_flag[i] = FALSE;
}


//----------------------------------------------------------------------
//! @brief 効果音再生
//!
//! @param[in] なし
//!
//! @return　なし
//----------------------------------------------------------------------
void PlaySE() {
	for (int i = 0; i < SE_ALL_NUM; i++) {
		if (g_se_flag[i]) {
			PlaySoundMem(g_se[i], DX_PLAYTYPE_BACK);
			g_se_flag[i] = FALSE;
		}
	}
}


//----------------------------------------------------------------------
//! @brief BGM再生
//!
//! @param[in] なし
//!
//! @return　なし
//----------------------------------------------------------------------
void PlayBGM() {
	for (int i = 0; i < BGM_ALL_NUM; i++) {
		if (g_bgm_flag[i]) {
			PlaySoundMem(g_bgm[i], DX_PLAYTYPE_LOOP, !g_continue_flag[i]);
			g_bgm_flag[i] = FALSE;
			if (g_continue_flag[i])
				g_continue_flag[i] = FALSE;
		}
	}
}

//効果音の再生フラグをTRUEにする
void SetSE(SE_ID se_Id) {

	//エラーチェック
	if (se_Id < 0 || se_Id >= SE_ALL_NUM) {
		MessageBox(NULL, "効果音の再生で不正な値が渡されました", "", MB_OK);
		return;
	}

	g_se_flag[se_Id] = TRUE;
}

//効果音を停止する
void StopSE(SE_ID se_Id) {
	StopSoundMem(g_se[se_Id]);
}

//BGMの再生フラグをTRUEにする
void SetBGM(BGM_ID bgm_Id) {

	//エラーチェック
	if (bgm_Id < 0 || bgm_Id >= BGM_ALL_NUM) {
		MessageBox(NULL, "BGMの再生で不正な値が渡されました", "", MB_OK);
		return;
	}

	g_bgm_flag[bgm_Id] = TRUE;
}

//BGMを停止する
void StopBGM(BGM_ID bgm_Id) {
	StopSoundMem(g_bgm[bgm_Id]);
}

//BGMを止めたところから再生する
void ContinueBGM(BGM_ID bgm_Id) {

	//エラーチェック
	if (bgm_Id < 0 || bgm_Id >= BGM_ALL_NUM) {
		MessageBox(NULL, "BGMの途中再生で不正な値が渡されました", "", MB_OK);
		return;
	}
	g_continue_flag[bgm_Id] = TRUE;
	g_bgm_flag[bgm_Id] = TRUE;
}


