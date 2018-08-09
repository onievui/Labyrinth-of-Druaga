//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Graphic.h
//!
//! @brief  �O���t�B�b�N�f�[�^�̃w�b�_�t�@�C��
//!
//! @date   2018/06/19
//!
//! @author �i�˗E��
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

//�X�v���C�g�̕`��
void DrawGraphic(const Vector2DF pos, Graph *tex);


