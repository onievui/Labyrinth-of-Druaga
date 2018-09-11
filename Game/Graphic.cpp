//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Graphic.cpp
//!
//! @brief  グラフィックデータの処理
//!
//! @date   2018/08/13
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#pragma once

//ヘッダーファイルの読み込み
#include "Graphic.h"
#include "Mediator.h"



//グラフィックの描画
void DrawGraphic(const Vector2DF pos, Graph *tex) {
	Sprite sprite = tex->sprite;
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE);
	
}

//グラフィックの描画（ポインタ版）
void DrawGraphicP(const Vector2DF pos, GraphP *tex) {
	Sprite sprite = *(tex->sprite);
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE);

}

//マップに対するグラフィックの描画
void DrawGraphicToMap(Vector2DF pos, Graph *tex) {
	SubVector2DF(pos, OrderGetCameraOffset());
	Sprite sprite = tex->sprite;
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE);

}

//マップに対する左右反転グラフィックの描画
void DrawTurnGraphicToMap(Vector2DF pos, Graph *tex) {
	SubVector2DF(pos, OrderGetCameraOffset());
	Sprite sprite = tex->sprite;
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE, TRUE);

}

//マップに対するグラフィックの描画（ポインタ版）
void DrawGraphicToMapP(Vector2DF pos, GraphP *tex) {
	SubVector2DF(pos, OrderGetCameraOffset());
	Sprite sprite = *(tex->sprite);
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE);

}


