//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Load.h
//!
//! @brief  ���\�[�X�̃w�b�_�t�@�C��
//!
//! @date   2018/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once




//�萔�̒�`

//�摜��ID
enum GRP_ID {
	GRP_LOGO1,				//���S�摜1
	GRP_LOGO2,				//���S�摜2
	GRP_TITLE,				//�^�C�g���摜
	GRP_TITLE_BG,			//�^�C�g���w�i
	GRP_STAGESELECT_BG,		//�X�e�[�W�Z���N�g�w�i
	GRP_STAGESELECT_ICON,	//�X�e�[�W�Z���N�g�A�C�R��
	GRP_ALL_NUM,			//�ǂݍ��މ摜�t�@�C���̐�
};

//���ʉ���ID
enum SE_ID {
	SE_NULL,		//���̌��ʉ�
	SE_ALL_NUM,		//�ǂݍ��ތ��ʉ��t�@�C���̐�
};

//BGM��ID
enum BGM_ID {
	BGM_NULL,		//����BGM
	BGM_ALL_NUM,	//�ǂݍ���BGM�t�@�C���̐�
};

//�V�F�[�_�[��ID
enum SHADER_ID {
	SHA_WAIPU,		//���C�v�V�F�[�_�[
	SHA_ALL_NUM,	//�ǂݍ��ރV�F�[�_�[�̐�
};

//�O���[�o���ϐ��̐錾
extern HGRP g_texture[GRP_ALL_NUM];
extern HSND g_se[SE_ALL_NUM];
extern HSND g_bgm[BGM_ALL_NUM];
extern int g_shader[SHA_ALL_NUM];
extern HFNT g_font_g30;
extern HFNT g_font_g40;
extern HFNT g_font_g70;
extern HFNT g_font_g150;

//���\�[�X�̓ǂݍ���
void LoadResources();

//���\�[�X�̉��
void DeleteResources();
