//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   sound.cpp
//!
//! @brief  サウンド関連の処理
//!
//! @date   2018/06/05
//!
//! @author 永戸勇希
//__/__/__/__/__/__/__/__/__/__/_S_/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


//ヘッダーファイルの読み込み
#include "Sound.h"



//グローバル変数の宣言

//サウンドフラグ
bool g_se_flag[SE_ALL_NUM];
bool g_bgm_flag[BGM_ALL_NUM];




//----------------------------------------------------------------------
//! @brief 音声初期化
//!
//! @param[in] なし
//!
//! @return　なし
//----------------------------------------------------------------------
void ResetSounds() {
	for (int i = 0; i < SE_ALL_NUM; i++)
		g_se_flag[i] = false;
	for (int i = 0; i < BGM_ALL_NUM; i++)
		g_bgm_flag[i] = false;
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
			g_se_flag[i] = false;
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
			PlaySoundMem(g_bgm[i], DX_PLAYTYPE_LOOP);
			g_bgm_flag[i] = false;
		}
	}
}

//効果音の再生フラグをtrueにする
void SetSE(SE_ID se_Id) {

	//エラーチェック
	if (se_Id < 0 || se_Id >= SE_ALL_NUM) {
		MessageBox(NULL, "効果音の再生で不正な値が渡されました", "", MB_OK);
		return;
	}

	g_se_flag[se_Id] = true;
}


//BGMの再生フラグをtrueにする
void SetBGM(BGM_ID bgm_Id) {

	//エラーチェック
	if (bgm_Id < 0 || bgm_Id >= BGM_ALL_NUM) {
		MessageBox(NULL, "BGMの再生で不正な値が渡されました", "", MB_OK);
		return;
	}

	g_bgm_flag[bgm_Id] = true;
}

//BGMを停止する
void StopBGM(BGM_ID bgm_Id) {
	StopSoundMem(g_bgm[bgm_Id]);
}


