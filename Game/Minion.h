#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"




//召喚モンスターのプロトタイプの初期化
void InitializePrototypeMinion(Minion proto_minion[]);

//スライムの更新
void UpdateMinionSlime(Minion *minion);

//ゴーストの更新
void UpdateMinionGhost(Minion *minion);

//スライムの描画
void DrawMinionSlime(Minion *minion);

//ゴーストの描画
void DrawMinionGhost(Minion *minion);

//スライムのダメージ処理
void DamageMinionSlime(Minion *minion, int power);

//ゴーストのダメージ処理
void DamageMinionGhost(Minion *minion, int power);

//スライムの消滅
void DestroyMinionSlime(Minion *minion);

//ゴーストの消滅
void DestroyMinionGhost(Minion *minion);


