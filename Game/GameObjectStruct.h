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

//�N���A�f�[�^�\����
struct ClearData {
	BOOL is_clear;		//�N���A�������ǂ���
	int second;			//�b
	int decimal;		//�b�i�����j
};

//�S�X�e�[�W�̃N���A�f�[�^�\����
struct AllClearData {
	ClearData clear_data[STAGE_NUM];	//�N���A�f�[�^
	int total_second;					//�g�[�^���̕b
	int total_decimal;					//�g�[�^���̕b�i�����j
};

//�}�b�v�\����
struct Map {
	SPR_ID knd;			//���
	Vector2DF pos;		//���W
	GraphP graphp;		//�摜
};

//�G�����X�^�[�o���p�f�[�^
struct EnemyList {
	BOOL is_use;		//�g�p���邩�ǂ���
	EnemyPattern knd;	//���
	Vector2DF pos;		//���W
	BOOL is_left;		//���������ǂ���
};

//�}�b�v�S�̂̍\����
struct MapData {
	Map map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];	//�e�}�X�̏��
	int width;								//�}�b�v�̉���
	int height;								//�}�b�v�̏c��
	Vector2DF player_pos;					//�v���C���[�̏������W
	BOOL player_is_left;					//�v���C���[�̏�������
	int player_sp;							//�v���C���[�̏���SP
	Vector2DF treasure_pos;					//����̍��W
	BOOL summonable[MINION_PATTERN_NUM];	//�����ł��郂���X�^�[�̎��
	EnemyList enemy_list[ENEMY_MAX];		//�o������G�̏��
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
	int cost;				//��������̂ɕK�v��SP
	int time;				//�����ɂ����鎞��
	Vector2DF offset;		//�v���C���[���猩�������ʒu�̑��΍��W�i�}�b�v���W�j
	BOOL turn_graph_num;	//�����ŉ摜���ς��Ƃ��̃X�v���C�g�ԍ��̑�����
};

//���������X�^�[�\����
struct Minion {
	MinionPattern knd;		//���
	int state;				//���
	int hp;					//�̗�
	Vector2DF pos;			//���W
	RectF col;				//�����蔻��̑��΍��W
	Vector2DF vel;			//�ړ���
	Vector2DF *ride;		//����Ă���I�u�W�F�N�g�̑��x
	BOOL is_left;			//���������ǂ���
	int collision_state;	//���̕��̂ɂǂ��ڂ��Ă��邩
	BOOL ground_flag;		//�}�b�v�ɒ��n�������ǂ���
	Graph graph;			//�\���摜���
	int sprite_num;			//�X�v���C�g�ԍ�
	int anime_count;		//�A�j���[�V�����p�J�E���^
};

//�h���S���̉��\����
struct Fire {
	int state;				//���
	int count;				//�o�����Ă���̎���
	Vector2DF pos;			//���W
	RectF col;				//�����蔻��̑��΍��W
	Minion *parent;			//�e�I�u�W�F�N�g
	Vector2DF *parent_vel;	//�e�̑��x
	BOOL is_left;			//���������ǂ���	
	Graph graph;			//�\���摜���
	int sprite_num;			//�X�v���C�g�ԍ�
};

//�G�����X�^�[�\����
struct Enemy {
	EnemyPattern knd;		//���
	int state;				//���
	int count;				//�o�����Ă���̎���
	int hp;					//�̗�
	Vector2DF pos;			//���W
	RectF col;				//�����蔻��̑��΍��W
	Vector2DF vel;			//�ړ���
	Vector2DF *ride;		//����Ă���I�u�W�F�N�g�̑��x
	BOOL is_left;			//���������ǂ���
	int collision_state;	//���̕��̂ɂǂ��ڂ��Ă��邩
	BOOL ground_flag;		//�}�b�v�ɒ��n�������ǂ���
	Graph graph;			//�\���摜���
	int sprite_num;			//�X�v���C�g�ԍ�
	int anime_count;		//�A�j���[�V�����p�J�E���^
};

//�����X�^�[�̖��@�\����
struct Magic {
	MagicPattern knd;	//���
	int state;			//���
	Vector2DF pos;		//���W
	RectF col;			//�����蔻��̑��΍��W
	Vector2DF vel;		//���x
	int power;			//�_���[�W��
	Graph graph;		//�摜
	int sprite_num;		//�X�v���C�g�ԍ�
	int anime_count;	//�A�j���[�V�����p�J�E���^

};

//�I�[�u�\����
struct Orb {
	int state;			//���
	int count;			//�o�����Ă���̎���
	Vector2DF pos;		//���W
	RectF col;			//�����蔻��̑��΍��W	
	Vector2DF vel;		//���x
	float angle;		//�p�x
	int sp;				//��SP��
	Graph graph;		//�\���摜���
	int sprite_num;		//�X�v���C�g�ԍ�
};

//�G�t�F�N�g�\����
struct Effect {
	EffectPattern knd;	//���
	int state;			//���
	int count;			//�o�����Ă���̃t���[����
	Vector2DF pos;		//���W
	Vector2DF vel;		//���x
	float angle;		//�p�x
	Graph graph;		//�\���摜���
	int sprite_num;		//�X�v���C�g�ԍ�
};

//������`�̏Փ˔���p�\����
struct BoxCollider {
	int *state;				//�I�u�W�F�N�g�̏��
	Vector2DF *pos;			//���W
	RectF *col;				//�����蔻��̑��΍��W
	Vector2DF *vel;			//���x
	Vector2DF **ride;		//����Ă���I�u�W�F�N�g�̑��x
	BOOL *collision_state;	//���̕��̂ɂǂ��ڂ��Ă��邩
	BOOL *ground_flag;		//�}�b�v�ɒ��n�������ǂ���
};


