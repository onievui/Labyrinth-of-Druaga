//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Graphic.h
//!
//! @brief  �O���t�B�b�N�f�[�^�̃w�b�_�t�@�C��
//!
//! @date   2018/08/13
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�[�t�@�C���̓ǂݍ���
#include "Sprite.h"
#include "Vector2DF.h"



//graphic�\����
struct Graph {
	Sprite sprite;
	float exrate;
	float angle;

};

//graphic�\���́i�|�C���^�Łj
struct GraphP {
	Sprite *sprite;
	float exrate;
	float angle;

};

//�X�v���C�g�̕`��
void DrawGraphic(const Vector2DF pos, Graph *tex);

//�O���t�B�b�N�̕`��i�|�C���^�Łj
void DrawGraphicP(const Vector2DF pos, GraphP *tex);

//�}�b�v�ɑ΂���O���t�B�b�N�̕`��
void DrawGraphicToMap(Vector2DF pos, Graph *tex);

//�}�b�v�ɑ΂���O���t�B�b�N�̕`��i�|�C���^�Łj
void DrawGraphicToMapP(Vector2DF pos, GraphP *tex);


