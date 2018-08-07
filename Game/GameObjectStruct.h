//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameObjectStruct.h
//!
//! @brief  �Q�[���I�u�W�F�N�g�̒�`
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#pragma once


//�w�b�_�[�t�@�C���̓ǂݍ���
#include "Graphic.h"
#include "Vector2DF.h"
#include "Sprite.h"



// ��{�I�u�W�F�N�g�f�[�^
struct GameObject {
	Vector2DF pos;		//���W
	Vector2DF vel;		//�ړ���
	int state;		//���
	float speed;	//���x
	float angle;	//�p�x
	Graph graph;	//�\���摜���
};
