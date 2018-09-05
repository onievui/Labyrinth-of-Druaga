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
	Vector2DF player_pos;					//�v���C���[�̏������W
	int player_sp;							//�v���C���[�̏���SP
	Vector2DF treasure_pos;					//����̍��W
	BOOL summonable[MINION_PATTERN_NUM];	//�����ł��郂���X�^�[�̎��
};

// �v���C���[�\����
struct Player {
	PlayerState state;	//���
	Vector2DF pos;		//���W
	RectF col;			//�����蔻��̑��΍��W
	Vector2DF vel;		//�ړ���
	Vector2DF *ride;	//����Ă���I�u�W�F�N�g�̑��x
	BOOL is_left;		//���������ǂ���
	BOOL is_ground;		//�n�ʂɐڂ��Ă��邩�ǂ���
	BOOL ground_flag;	//�}�b�v�ɒ��n�������ǂ���
	Graph graph;		//�\���摜���
	int sp;				//�����ɕK�v�ȃ|�C���g
	int sprite_num;		//�X�v���C�g�ԍ�
	int anime_count;	//�A�j���[�V�����p�J�E���^
};

//�����\�ȃ����X�^�[�̃��X�g�\����
struct SummonableList {
	BOOL is_use;			//�g�p�t���O
	MinionPattern knd;		//���
	Graph graph;			//�\���摜���
};

//�����X�^�[�̏����͈͏��\����
struct SummonAreaData {
	BOOL is_available;	//�����\���ǂ���
	int state;			//�\�����
	MinionPattern knd;	//�I�����Ă��鏢�������X�^�[
	Vector2DF pos;		//���W
	RectF area;			//�͈�
	BOOL is_left;		//����
};

//����\����
struct Treasure {
	int state;			//���
	Vector2DF pos;		//���W
	RectF col;			//�����蔻��̑��΍��W
	Vector2DF vel;		//�ړ���
	Vector2DF *ride;	//����Ă���I�u�W�F�N�g�̑��x
	BOOL is_ground;		//�n�ʂɐڂ��Ă��邩�ǂ���
	Graph graph;		//�\���摜���
};

//�����X�^�[�����p�f�[�^
struct SummonData {
	int cost;
	int time;
};

//���������X�^�[�\����
struct Minion {
	MinionPattern knd;	//���
	int state;			//���
	int hp;				//�̗�
	Vector2DF pos;		//���W
	RectF col;			//�����蔻��̑��΍��W
	Vector2DF vel;		//�ړ���
	Vector2DF *ride;	//����Ă���I�u�W�F�N�g�̑��x
	BOOL is_left;		//���������ǂ���
	BOOL is_ground;		//�n�ʂɐڂ��Ă��邩�ǂ���
	BOOL ground_flag;	//�}�b�v�ɒ��n�������ǂ���
	Graph graph;		//�\���摜���
	int sprite_num;		//�X�v���C�g�ԍ�
	int anime_count;	//�A�j���[�V�����p�J�E���^
	SummonData s_dat;	//�����p�f�[�^
};

//������`�̏Փ˔���p�\����
struct BoxCollider {
	int *state;			//�I�u�W�F�N�g�̏��
	Vector2DF *pos;		//���W
	RectF *col;			//�����蔻��̑��΍��W
	Vector2DF *vel;		//���x
	Vector2DF **ride;	//����Ă���I�u�W�F�N�g�̑��x
	BOOL *is_ground;	//�n�ʂɐڂ��Ă��邩�ǂ���
	BOOL *ground_flag;	//�}�b�v�ɒ��n�������ǂ���
};


