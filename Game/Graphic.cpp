//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Graphic.cpp
//!
//! @brief  �O���t�B�b�N�f�[�^�̏���
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "Graphic.h"



//�O���t�B�b�N�̕`��
void DrawGraphic(const Vector2DF pos, Graph *tex) {
	Sprite sprite = *(tex->sprite);
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, true);
	
}




