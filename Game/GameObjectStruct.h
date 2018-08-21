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
#include "GameDefine.h"
#include "GameEnum.h"



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

//�}�b�v�S�̂̍\����
struct MapData {
	Map map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];	//�e�}�X�̏��
	int width;								//�}�b�v�̉���
	int height;								//�}�b�v�̏c��
	Vector2DF player_init_pos;				//�v���C���[�̏������W
	Vector2DF treasure_pos;					//����̍��W
};

// �v���C���[�\����
struct Player {
	PlayerState state;	//���
	Vector2DF pos;		//���W
	RectF col;			//�����蔻��̑��΍��W
	Vector2DF vel;		//�ړ���
	BOOL is_left;		//���������ǂ���
	BOOL is_ground;		//�n�ʂɐڂ��Ă��邩�ǂ���
	Graph graph;		//�\���摜���
	int sprite_num;		//�X�v���C�g�ԍ�
	int anime_count;	//�A�j���[�V�����p�J�E���^
};

//����\����
struct Treasure {
	int state;		//���
	Vector2DF pos;	//���W
	RectF col;		//�����蔻��̑��΍��W
	Vector2DF vel;	//�ړ���
	Graph graph;	//�\���摜���
};

//���������X�^�[�\����
struct Minion {
	MinionPattern knd;	//���
	int state;			//���
	int hp;				//�̗�
	Vector2DF pos;		//���W
	RectF col;			//�����蔻��̑��΍��W
	Vector2DF vel;		//�ړ���
	BOOL is_left;		//���������ǂ���
	Graph graph;		//�\���摜���
	int sprite_num;		//�X�v���C�g�ԍ�
	int anime_count;	//�A�j���[�V�����p�J�E���^
	int summon_time;	//�����ɂ����鎞��
};

//������`�̏Փ˔���p�\����
struct BoxCollider {
	int *state;			//�I�u�W�F�N�g�̏��
	Vector2DF *pos;		//���W
	RectF *col;			//�����蔻��̑��΍��W
	Vector2DF *vel;		//���x
};


