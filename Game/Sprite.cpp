//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Sprite.cpp
//!
//! @brief  �X�v���C�g�f�[�^�̏���
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "Load.h"
#include "Sprite.h"

//�X�v���C�g�f�[�^
Sprite g_sprite[SPR_ALL_NUM];

//�X�v���C�g�f�[�^�̏�����
void InitializeSprite() {
	int i;
	g_sprite[SPR_LOGO1]        = Sprite{ g_texture[GRP_LOGO1],       RECT{ 0,  0, 256, 256 } };
	g_sprite[SPR_LOGO2]        = Sprite{ g_texture[GRP_LOGO2],       RECT{ 0,  0, 640, 480 } };
	g_sprite[SPR_TITLE]        = Sprite{ g_texture[GRP_TITLE],       RECT{ 0,  0, 800, 600 } };
	g_sprite[SPR_BG]           = Sprite{ g_texture[GRP_BG],          RECT{ 0,  0, 800, 600 } };
	g_sprite[SPR_STD_GIL]      = Sprite{ g_texture[GRP_GIL],         RECT{ 8,  8,  64,  64 } };
	g_sprite[SPR_STD_SWORD]    = Sprite{ g_texture[GRP_SWORD],       RECT{ 8,  8,  96,  96 } };
	g_sprite[SPR_DELETE_ICON]  = Sprite{ g_texture[GRP_DELETE_ICON], RECT{ 0,  0,  64,  64 } };
	g_sprite[SPR_STD_MONSTER]  = Sprite{ g_texture[GRP_MONSTER],     RECT{ 8,  8,  64,  64 } };
	g_sprite[SPR_STD_DRAGON]   = Sprite{ g_texture[GRP_DRAGON],      RECT{ 8,  8,  96,  64 } };
	g_sprite[SPR_STD_FIRE]     = Sprite{ g_texture[GRP_FIRE],        RECT{ 8,  8, 256,  64 } };
	g_sprite[SPR_STD_MAGIC]    = Sprite{ g_texture[GRP_MAGIC],       RECT{ 8,  8,  64,  64 } };
	for (i = 0; i < 11; i++) {
		g_sprite[SPR_MAPCHIP1_1 + i] = Sprite{ g_texture[GRP_MAPCHIP1],  RECT{ 4 + i*(64 + 4),  4,  64,  64 } };
	}
	g_sprite[SPR_OBJECT_TREASURE] = Sprite{ g_texture[GRP_OBJECT_OTHER], RECT{ 8 + 2*(64 + 8),  8,  64,  64 } };
	g_sprite[SPR_STD_EFFECT1]     = Sprite{ g_texture[GRP_EFFECT1],      RECT{ 8,  8,  64,  64 } };
}

//�X�v���C�g�؂�o���ʒu�̎擾
RECT GetSpriteRect(const SPR_ID sprId, const int num) {

	RECT rect = { 0,0,0,0 };

	//�X�v���C�g�̎�ނŕ���
	switch (sprId) {

	//�v���C���[�X�v���C�g
	case SPR_STD_GIL:
		rect = RECT{ 8 + num*(64 + 8),8,64,64 };
		break;
	//���X�v���C�g
	case SPR_STD_SWORD:
		rect = RECT{ 8 + (num % 8)*(96 + 8),8 + (num / 8)*(96 + 8),96,96 };
		break;
	//�����X�^�[�X�v���C�g
	case SPR_STD_MONSTER:
		rect = RECT{ 8 + (num % 12)*(64 + 8),8 + (num / 12)*(64 + 8),64,64 };
		break;
	//�h���S���X�v���C�g
	case SPR_STD_DRAGON:
		rect = RECT{ 8 + (num % 12)*(96 + 8),8 + (num / 12)*(64 + 8),96,64 };
		break;
	//�h���S���̉��X�v���C�g
	case SPR_STD_FIRE:
		rect = RECT{ 8, 8 + num*(64 + 8),256,64 };
		break;
	//�����X�^�[�̖��@�X�v���C�g
	case SPR_STD_MAGIC:
		rect = RECT{ 8 + (num % 4)*(64 + 8),8 + (num / 4)*(64 + 8),64,64 };
		break;
	//�G�t�F�N�g1�X�v���C�g
	case SPR_STD_EFFECT1:
		rect = RECT{ 8 + (num % 4)*(64 + 8),8 + (num / 4)*(64 + 8),64,64 };
		break;
	default:
		MessageBox(NULL, "�X�v���C�g�̐؂�o���ʒu�̎擾�ŕs���Ȓl���n����܂���", "", MB_OK);
		break;
	}

	return rect;
}

