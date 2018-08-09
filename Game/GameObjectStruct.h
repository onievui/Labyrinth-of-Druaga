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
#include "RectF.h"
#include "Sprite.h"



// ��{�I�u�W�F�N�g�f�[�^
struct GameObject {
	Vector2DF pos;		//���W
	Vector2DF vel;		//�ړ���
	int state;			//���
	float speed;		//���x
	float angle;		//�p�x
	Graph graph;		//�\���摜���
};

//�}�b�v�\����
struct Map {
	SPR_ID knd;			//���
	Vector2DF pos;		//���W
	GraphP graphp;		//�摜
};

// �v���C���[�\����
struct Player {
	int state;			//���
	Vector2DF pos;		//���W
	RectF col;			//�����蔻��̑��΍��W
	Vector2DF vel;		//�ړ���
	float speed;		//�ړ����x
	BOOL is_left;		//���������ǂ���
	Graph graph;		//�\���摜���
	int sprite_num;		//�X�v���C�g�ԍ�
	int anime_count;	//�A�j���[�V�����p�J�E���^
};
