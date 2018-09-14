//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneTitle.cpp
//!
//! @brief  �^�C�g���V�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2018/08/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "SceneTitle.h"



// �O���[�o���ϐ��̒�` ====================================================

GameObject g_title_object;	//�^�C�g���I�u�W�F�N�g
GameObject g_bg_object;		//�w�i�I�u�W�F�N�g



// �֐��̐錾 ==============================================================
void InitializeTitle(void);  // �^�C�g���V�[���̏���������
void UpdateTitle(void);      // �^�C�g���V�[���̍X�V����
void RenderTitle(void);      // �^�C�g���V�[���̕`�揈��
void FinalizeTitle(void);    // �^�C�g���V�[���̏I������




// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �^�C�g���V�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeTitle(void)
{
	//�^�C�g���I�u�W�F�N�g�̏�����
	g_title_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_title_object.vel = Vector2DF{ 0,0 };
	g_title_object.state = 1;
	g_title_object.speed = 0;
	g_title_object.angle = 0;
	g_title_object.graph = Graph{ g_sprite[SPR_TITLE] , 1.0f, 0.0f };

	//�w�i�I�u�W�F�N�g�̏�����
	g_bg_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_bg_object.vel = Vector2DF{ 0,0 };
	g_bg_object.state = 1;
	g_bg_object.speed = 0;
	g_bg_object.angle = 0;
	g_bg_object.graph = Graph{ g_sprite[SPR_BG] , 1.0f, 0.0f };

	//BGM�̍Đ�
	SetBGM(BGM_TITLE);
}



//----------------------------------------------------------------------
//! @brief �^�C�g���V�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateTitle(void)
{
	// X�L�[�ŃX�e�[�W�Z���N�g��ʂɑJ��
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		RequestScene(SCENE_STAGESELECT);
		//SetSE(SE_DECISION);
	}
}



//----------------------------------------------------------------------
//! @brief �^�C�g���V�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderTitle(void)
{
	//�w�i�̕`��
	DrawGraphic(g_bg_object.pos, &g_bg_object.graph);

	//�^�C�g���̕`��
	DrawGraphic(g_title_object.pos, &g_title_object.graph);

	//�L�[���͂̑���
	DrawFormatStringFToHandle(	SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g40, "START [X] KEY") / 2.0f, 
								SCREEN_CENTER_Y + 220, COLOR_YELLOW, g_font_g40, "START [X] KEY");
}



//----------------------------------------------------------------------
//! @brief �^�C�g���V�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeTitle(void)
{
	//BGM���~�߂�
	StopBGM(BGM_TITLE);
}
