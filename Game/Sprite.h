//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sprite.h
//!
//! @brief  �X�v���C�g�f�[�^�̃w�b�_�t�@�C��
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�X�v���C�g��ID
//�X�v���C�g�������������ɕ����g�p���Ȃ��ꍇ�͊�X�v���C�g���g���A���I�ɐ؂�o���ʒu���擾����
enum SPR_ID {
	SPR_LOGO1,				//���S�X�v���C�g1
	SPR_LOGO2,				//���S�X�v���C�g2
	SPR_TITLE,				//�^�C�g���X�v���C�g
	SPR_BG,					//�w�i�X�v���C�g
	SPR_STAGESELECT_BG,		//�X�e�[�W�Z���N�g�w�i�X�v���C�g
	SPR_STAGESELECT_ICON,	//�X�e�[�W�Z���N�g�A�C�R���X�v���C�g
	SPR_STD_GIL,			//�v���C���[��X�v���C�g
	SPR_STD_SWORD,			//����X�v���C�g
	SPR_STD_MONSTER,		//�����X�^�[��X�v���C�g
	SPR_MAPCHIP1_1,			//�}�b�v�`�b�v1�X�v���C�g1
	SPR_MAPCHIP1_2,			//�}�b�v�`�b�v1�X�v���C�g2
	SPR_MAPCHIP1_3,			//�}�b�v�`�b�v1�X�v���C�g3
	SPR_MAPCHIP1_4,			//�}�b�v�`�b�v1�X�v���C�g4
	SPR_MAPCHIP1_5,			//�}�b�v�`�b�v1�X�v���C�g5
	SPR_MAPCHIP1_6,			//�}�b�v�`�b�v1�X�v���C�g6
	SPR_MAPCHIP1_7,			//�}�b�v�`�b�v1�X�v���C�g7
	SPR_MAPCHIP1_8,			//�}�b�v�`�b�v1�X�v���C�g8
	SPR_MAPCHIP1_9,			//�}�b�v�`�b�v1�X�v���C�g9
	SPR_MAPCHIP1_10,		//�}�b�v�`�b�v1�X�v���C�g10
	SPR_MAPCHIP1_11,		//�}�b�v�`�b�v1�X�v���C�g11
	SPR_OBJECT_TREASURE,	//����X�v���C�g
	SPR_ALL_NUM,			//�X�v���C�g�̐�
};


//�X�v���C�g�\����
struct Sprite {
	HGRP texture;	//�e�L�X�`��
	RECT rect;		//�e�L�X�`���̓ǂݍ��݈ʒu
};


//�X�v���C�g�f�[�^
extern Sprite g_sprite[SPR_ALL_NUM];


//�X�v���C�g�f�[�^�̏�����
void InitializeSprite();

//�X�v���C�g�؂�o���ʒu�̎擾
RECT GetSpriteRect(const SPR_ID sprId, const int num);

