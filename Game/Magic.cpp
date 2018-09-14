#pragma once



//ヘッダファイルの読み込み
#include "GameObjectStruct.h"



//定数の定義
#define WHITE_MAGIC_SPEED	(12)	//白魔法の速度
#define GREEN_MAGIC_SPEED	(8)		//緑魔法の速度

#define WHITE_MAGIC_POWER	(1)		//白魔法のダメージ量
#define GREEN_MAGIC_POWER	(1)		//緑魔法のダメージ量


//モンスターの魔法のプロトタイプの初期化
void InitializePrototypeMagic(Magic proto_magic[]) {

	//白魔法
	proto_magic[MAGIC_WHITE] =
	{
		MAGIC_WHITE,
		1,
		{ 0,0 },
		{ -25,-20,25,16 },
		{ WHITE_MAGIC_SPEED,0 },
		WHITE_MAGIC_POWER,
		{ g_sprite[SPR_STD_MAGIC],1.0,0.0 },
		20,
		0
	};
	proto_magic[MAGIC_WHITE].graph.sprite.rect = GetSpriteRect(SPR_STD_MAGIC, proto_magic[MAGIC_WHITE].sprite_num);

	//緑魔法
	proto_magic[MAGIC_GREEN] =
	{
		MAGIC_GREEN,
		1,
		{ 0,0 },
		{ -25,-20,25,16 },
		{ GREEN_MAGIC_SPEED,0 },
		GREEN_MAGIC_POWER,
		{ g_sprite[SPR_STD_MAGIC],1.0,0.0 },
		23,
		0
	};
	proto_magic[MAGIC_GREEN].graph.sprite.rect = GetSpriteRect(SPR_STD_MAGIC, proto_magic[MAGIC_GREEN].sprite_num);

}


//白魔法の更新
void UpdateMagicWhite(Magic *magic) {

	//移動量を座標に足す
	AddVector2DF(magic->pos, magic->vel);

	magic->anime_count++;
}

//緑魔法の更新
void UpdateMagicGreen(Magic *magic) {

	//移動量を座標に足す
	AddVector2DF(magic->pos, magic->vel);

	magic->anime_count++;

}

//白魔法の描画
void DrawMagicWhite(Magic *magic) {
	if (magic->anime_count % 30 < 15)
		DrawGraphicToMap(magic->pos, &magic->graph);
	else
		DrawTurnGraphicToMap(magic->pos, &magic->graph);
	/*Vector2DF pos = magic->pos;
	SubVector2DF(pos, OrderGetCameraOffset());
	RectF rect = { pos.x + magic->col.left,
	pos.y + magic->col.top,
	pos.x + magic->col.right,
	pos.y + magic->col.bottom };
	DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_BLUE, 0);*/
}

//緑魔法の描画
void DrawMagicGreen(Magic *magic) {
	if (magic->anime_count % 30 < 15)
		DrawGraphicToMap(magic->pos, &magic->graph);
	else
		DrawTurnGraphicToMap(magic->pos, &magic->graph);
}

//白魔法の壁衝突処理
BOOL CollisionMagicWhite(Magic *magic) {
	//白魔法は壁に衝突すると消える
	return TRUE;
}

//緑魔法の壁衝突処理
BOOL CollisionMagicGreen(Magic *magic) {
	//緑魔法は壁を貫通する
	return FALSE;
}

//白魔法の消滅
void DestroyMagicWhite(Magic *magic) {
	magic->state = 0;
}

//緑魔法の消滅
void DestroyMagicGreen(Magic *magic) {
	magic->state = 0;
}




