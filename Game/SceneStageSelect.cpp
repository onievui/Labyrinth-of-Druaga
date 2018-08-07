#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "SceneStageSelect.h"
#include "Mediator.h"




// �O���[�o���ϐ��̒�` ====================================================

GameObject g_stageselect_back_object;	//�w�i�I�u�W�F�N�g
GameObject g_stageselect_icon_object;	//�X�e�[�W�A�C�R���I�u�W�F�N�g

int g_select_stage;				//�I�𒆂̃X�e�[�W�ԍ�




// �֐��̐錾 ==============================================================
void InitializeStageSelect(void);  // �X�e�[�W�Z���N�g�V�[���̏���������
void UpdateStageSelect(void);      // �X�e�[�W�Z���N�g�V�[���̍X�V����
void RenderStageSelect(void);      // �X�e�[�W�Z���N�g�V�[���̕`�揈��
void FinalizeStageSelect(void);    // �X�e�[�W�Z���N�g�V�[���̏I������




 // �֐��̒�` ==============================================================
 //----------------------------------------------------------------------
 //! @brief �X�e�[�W�Z���N�g�V�[���̏���������
 //!
 //! @param[in] �Ȃ�
 //!
 //! @return �Ȃ�
 //----------------------------------------------------------------------
void InitializeStageSelect(void)
{
	//�w�i�I�u�W�F�N�g�̏�����
	g_stageselect_back_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_stageselect_back_object.vel = Vector2DF{ 0,0 };
	g_stageselect_back_object.state = 1;
	g_stageselect_back_object.speed = 0;
	g_stageselect_back_object.angle = 0;
	g_stageselect_back_object.graph = Graph{ &g_sprite[SPR_STAGESELECT_BG] , 1.0f, 0.0f };

	//�A�C�R���I�u�W�F�N�g�̏�����
	g_stageselect_icon_object.pos = Vector2DF{ (float)(SCREEN_WIDTH * 7 / 10),(float)(SCREEN_CENTER_Y) };
	g_stageselect_icon_object.vel = Vector2DF{ 0,0 };
	g_stageselect_icon_object.state = 1;
	g_stageselect_icon_object.speed = 0;
	g_stageselect_icon_object.angle = 0;
	g_stageselect_icon_object.graph = Graph{ &g_sprite[SPR_STAGESELECT_ICON] , 1.0f, 0.0f };
}



//----------------------------------------------------------------------
//! @brief �X�e�[�W�Z���N�g�V�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateStageSelect(void)
{
	//�X�e�[�W�̑I��
	

	// X�L�[�Ńv���C��ʂɑJ��
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		//StopBGM(BGM_1);
		//SetSE(SE_DECISION);
		SetSelectStage((StageId)g_select_stage);
		RequestScene(SCENE_PLAY);
	}
}



//----------------------------------------------------------------------
//! @brief �X�e�[�W�Z���N�g�V�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderStageSelect(void)
{
	//�X�e�[�W�Z���N�g�w�i�̕`��
	DrawGraphic(g_stageselect_back_object.pos, &g_stageselect_back_object.graph);

	//�I������X�e�[�W���̕\��
	

	
}



//----------------------------------------------------------------------
//! @brief �X�e�[�W�Z���N�g�V�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeStageSelect(void)
{

}










