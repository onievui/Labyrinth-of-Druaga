//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sprite.h
//!
//! @brief  �X�v���C�g�f�[�^�̃w�b�_�t�@�C��
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "Load.h"



//�X�v���C�g��ID
enum SPR_ID {
	SPR_LOGO1,				//���S�X�v���C�g1
	SPR_LOGO2,				//���S�X�v���C�g2
	SPR_TITLE,				//�^�C�g���X�v���C�g
	SPR_TITLE_BG,			//�^�C�g���w�i�X�v���C�g
	SPR_STAGESELECT_BG,		//�X�e�[�W�Z���N�g�w�i�X�v���C�g
	SPR_STAGESELECT_ICON,	//�X�e�[�W�Z���N�g�A�C�R���X�v���C�g
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