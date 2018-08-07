//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Graphic.cpp
//!
//! @brief  グラフィックデータの処理
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#pragma once

//ヘッダーファイルの読み込み
#include "Graphic.h"



//グラフィックの描画
void DrawGraphic(const Vector2DF pos, Graph *tex) {
	Sprite sprite = *(tex->sprite);
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, true);
	
}




