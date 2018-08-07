

// 多重インクルードの防止 ==================================================
#pragma once




// 定数の定義 ==============================================================
#include "Load.h"




// 変数の宣言 ==============================================================

extern bool g_se_flag[SE_ALL_NUM];		//効果音用フラグ
extern bool g_bgm_flag[BGM_ALL_NUM];	//BGM用フラグ



// 関数の宣言 ==============================================================


//音声初期化
void ResetSounds(void);

//効果音再生
void PlaySE(void);

//BGM再生
void PlayBGM(void);

//効果音の再生フラグをtrueにする
void SetSE(SE_ID se_Id);

//BGMの再生フラグをtrueにする
void SetBGM(BGM_ID bgm_Id);

//BGMを停止する
void StopBGM(BGM_ID bgm_Id);

