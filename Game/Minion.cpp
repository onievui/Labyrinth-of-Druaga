#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"
#include "Mediator.h"
#include <math.h>





//召喚モンスターのプロトタイプの初期化
void InitializePrototypeMinion(Minion proto_minion[]) {

	//スライム
	proto_minion[MINION_SLIME] =
	{
		MINION_SLIME,
		1,
		1,
		{ 0,0 },
		{ -32,-32,32,32 },
		{ 0,0 },
		TRUE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		12,
		0,
		32
	};

	//ゴースト
	proto_minion[MINION_GHOST] =
	{
		MINION_GHOST,
		1,
		1,
		{ 0,0 },
		{ -32,-32,32,32 },
		{ 0,0 },
		TRUE,
		{ g_sprite[SPR_STD_MONSTER],1.0,0.0 },
		66,
		0,
		64
	};
}


//スライムの更新
void UpdateMinionSlime(Minion *minion) {

}

//ゴーストの更新
void UpdateMinionGhost(Minion *minion) {

}

//スライムの描画
void DrawMinionSlime(Minion *minion) {

}

//ゴーストの描画
void DrawMinionGhost(Minion *minion) {

}

//スライムのダメージ処理
void DamageMinionSlime(Minion *minion, int power) {

}

//ゴーストのダメージ処理
void DamageMinionGhost(Minion *minion, int power) {

}

//スライムの消滅
void DestroyMinionSlime(Minion *minion) {

}

//ゴーストの消滅
void DestroyMinionGhost(Minion *minion) {

}



