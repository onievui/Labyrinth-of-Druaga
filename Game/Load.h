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
	GRP_BG,					//�w�i�摜
	GRP_STAGESELECT_BG,		//�X�e�[�W�Z���N�g�w�i
	GRP_STAGESELECT_ICON,	//�X�e�[�W�Z���N�g�A�C�R��
	GRP_GIL,				//�v���C���[�摜
	GRP_SWORD,				//���摜
	GRP_MONSTER,			//�����X�^�[�摜
	GRP_DRAGON,				//�h���S���摜
	GRP_FIRE,				//�h���S���̉��摜
	GRP_MAGIC,				//�����X�^�[���@�摜
	GRP_MAPCHIP1,			//�}�b�v�`�b�v�摜1
	GRP_OBJECT_OTHER,		//���̑��I�u�W�F�N�g�摜
	GRP_ALL_NUM,			//�ǂݍ��މ摜�t�@�C���̐�
};

//���ʉ���ID
enum SE_ID {
	SE_START,			//�X�e�[�W�J�n���ʉ�
	SE_CLEAR,			//�X�e�[�W�N���A���ʉ�
	SE_HIGHSCORE,		//�n�C�X�R�A���ʉ�
	SE_PAUSE,			//�|�[�Y���ʉ�
	SE_MISS,			//�~�X���ʉ�
	SE_WALK,			//�������ʉ�
	SE_SWORD,			//�����ʉ�
	SE_SUMMON,			//�������ʉ�
	SE_FIRE,			//�h���S���̉����ʉ�
	SE_MINION_STRIKE,	//���������X�^�[���Ō��ʉ�
	SE_MAGIC,			//�G�̖��@���ʉ�
	SE_ENEMY_STRIKE,	//�G�����X�^�[���Ō��ʉ�
	SE_ALL_NUM,			//�ǂݍ��ތ��ʉ��t�@�C���̐�
};

//BGM��ID
enum BGM_ID {
	BGM_TITLE,		//�^�C�g��BGM
	BGM_SELECT,		//�X�e�[�W�Z���N�gBGM
	BGM_INGAME,		//�v���C��BGM
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
extern HFNT g_font_g50;
extern HFNT g_font_g60;
extern HFNT g_font_g70;

//���\�[�X�̓ǂݍ���
void LoadResources();

//���\�[�X�̉��
void DeleteResources();
