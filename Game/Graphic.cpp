//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Graphic.cpp
//!
//! @brief  �O���t�B�b�N�f�[�^�̏���
//!
//! @date   2018/08/13
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#pragma once

//�w�b�_�[�t�@�C���̓ǂݍ���
#include "Graphic.h"
#include "Mediator.h"



//�O���t�B�b�N�̕`��
void DrawGraphic(const Vector2DF pos, Graph *tex) {
	Sprite sprite = tex->sprite;
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE);
	
}

//�O���t�B�b�N�̕`��i�|�C���^�Łj
void DrawGraphicP(const Vector2DF pos, GraphP *tex) {
	Sprite sprite = *(tex->sprite);
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE);

}

//�}�b�v�ɑ΂���O���t�B�b�N�̕`��
void DrawGraphicToMap(Vector2DF pos, Graph *tex) {
	SubVector2DF(pos, OrderGetCameraOffset());
	Sprite sprite = tex->sprite;
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE);

}

//�}�b�v�ɑ΂��鍶�E���]�O���t�B�b�N�̕`��
void DrawTurnGraphicToMap(Vector2DF pos, Graph *tex) {
	SubVector2DF(pos, OrderGetCameraOffset());
	Sprite sprite = tex->sprite;
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE, TRUE);

}

//�}�b�v�ɑ΂���O���t�B�b�N�̕`��i�|�C���^�Łj
void DrawGraphicToMapP(Vector2DF pos, GraphP *tex) {
	SubVector2DF(pos, OrderGetCameraOffset());
	Sprite sprite = *(tex->sprite);
	DrawRectRotaGraphF(pos.x, pos.y,
		sprite.rect.left, sprite.rect.top,
		sprite.rect.right, sprite.rect.bottom,
		tex->exrate, tex->angle, sprite.texture, TRUE);

}


