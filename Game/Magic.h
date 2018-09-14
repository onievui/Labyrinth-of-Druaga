#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//モンスターの魔法のプロトタイプの初期化
void InitializePrototypeMagic(Magic proto_magic[]);

//白魔法の更新
void UpdateMagicWhite(Magic *magic);

//緑魔法の更新
void UpdateMagicGreen(Magic *magic);

//白魔法の描画
void DrawMagicWhite(Magic *magic);

//緑魔法の描画
void DrawMagicGreen(Magic *magic);

//白魔法の壁衝突処理
BOOL CollisionMagicWhite(Magic *magic);

//緑魔法の壁衝突処理
BOOL CollisionMagicGreen(Magic *magic);

//白魔法の消滅
void DestroyMagicWhite(Magic *magic);

//緑魔法の消滅
void DestroyMagicGreen(Magic *magic);



