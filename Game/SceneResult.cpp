//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneResult.cpp
//!
//! @brief  �v���C�V�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2018/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "SceneResult.h"
#include "Mediator.h"


// �萔�̒�` ==============================================================




// �O���[�o���ϐ��̒�` ====================================================
GameObject g_result_back_object;	//�w�i�I�u�W�F�N�g



// �֐��̐錾 ==============================================================
void InitializeResult(void);  // �v���C�V�[���̏���������
void UpdateResult(void);      // �v���C�V�[���̍X�V����
void RenderResult(void);      // �v���C�V�[���̕`�揈��
void FinalizeResult(void);    // �v���C�V�[���̏I������




// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief ���U���g�V�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeResult(void)
{
	//�w�i�I�u�W�F�N�g�̏�����
	g_result_back_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_result_back_object.vel = Vector2DF{ 0,0 };
	g_result_back_object.state = 1;
	g_result_back_object.speed = 0;
	g_result_back_object.angle = 0;
	g_result_back_object.graph = Graph{ g_sprite[SPR_BG] , 1.0f, 0.0f };

	//SetBGM(BGM_1);

	

	

}



//----------------------------------------------------------------------
//! @brief ���U���g�V�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateResult(void)
{
	// X�L�[�ŃX�e�[�W�Z���N�g��ʂɑJ��
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		RequestScene(SCENE_STAGESELECT);
		//SetSE(SE_DECISION);
	}
}



//----------------------------------------------------------------------
//! @brief ���U���g�V�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderResult(void)
{
	//���U���g�w�i�̕`��
	DrawGraphic(g_result_back_object.pos, &g_result_back_object.graph);

	//�N���A�^�C���̕\��
	int time = GetClearTime();
	DrawFormatStringFToHandle(SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g70, "TIME %.2f", time / 60.0f) / 2.0f,
		SCREEN_CENTER_Y - 50, COLOR_YELLOW, g_font_g70, "TIME %.2f", time / 60.0f);
	//�L�[���͂̑���
	DrawFormatStringFToHandle(SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g40, "Press [X] Key") / 2.0f,
		SCREEN_CENTER_Y + 100, COLOR_WHITE, g_font_g40, "Press [X] Key");
	
}



//----------------------------------------------------------------------
//! @brief ���U���g�V�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeResult(void)
{

}
