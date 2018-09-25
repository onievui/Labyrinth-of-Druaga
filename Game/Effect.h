#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//エフェクトのプロトタイプの初期化
void InitializePrototypeEffect(Effect proto_effect[]);

//オーブ取得エフェクトの更新
BOOL UpdateEffectGetOrb(Effect *effect);

//オーブ取得エフェクトの描画
void DrawEffectGetOrb(Effect *effect);

//オーブ取得エフェクトの消滅
void DestroyEffectGetOrb(Effect *effect);


