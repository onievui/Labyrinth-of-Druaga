#pragma once


//公開関数の宣言


//プレイシーンの初期化処理
void InitializePlay(void);

//プレイシーンの更新処理
void UpdatePlay(void);

//プレイシーンの描画処理
void RenderPlay(void);

//プレイシーンの終了処理
void FinalizePlay(void);

//ステージ失敗への移行
void RequestStageFailed(void);

//ステージクリアへの移行
void RequestStageClear(void);

