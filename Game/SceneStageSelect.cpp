#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "SceneStageSelect.h"
#include "Mediator.h"



//�萔�̒�`
#define CURSOR_SPEED	(15)	//�J�[�\���𓮂������Ԃ̊Ԋu



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
	g_stageselect_back_object.graph = Graph{ g_sprite[SPR_BG] , 1.0f, 0.0f };

	//�A�C�R���I�u�W�F�N�g�̏�����
	g_stageselect_icon_object.pos = Vector2DF{ (float)(SCREEN_WIDTH * 1 / 10),(float)(SCREEN_HEIGHT / 5) };
	g_stageselect_icon_object.vel = Vector2DF{ 0,0 };
	g_stageselect_icon_object.state = 1;
	g_stageselect_icon_object.speed = 0;
	g_stageselect_icon_object.angle = 0;
	g_stageselect_icon_object.graph = Graph{ g_sprite[SPR_STAGESELECT_ICON] , 1.0f, 0.0f };

	g_select_stage = 0;
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
	switch (CheckStateKeyLater4(KEY_INPUT_LEFT, KEY_INPUT_RIGHT, KEY_INPUT_UP, KEY_INPUT_DOWN)) {
	//����������Ă��Ȃ�
	case 0:
		break;
	//����������Ă���
	case 1:
		if (CheckStateKey(KEY_INPUT_LEFT) % CURSOR_SPEED == 1) {
			if (g_select_stage > 0) {
				g_select_stage--;
			}
		}
		break;
	//�E��������Ă���
	case 2:
		if (CheckStateKey(KEY_INPUT_RIGHT) % CURSOR_SPEED == 1) {
			if (g_select_stage < STAGE_NUM - 1) {
				g_select_stage++;
			}
		}
		break;
	//�オ������Ă���
	case 3:
		if (CheckStateKey(KEY_INPUT_UP) % CURSOR_SPEED == 1) {
			if (g_select_stage > 4) {
				g_select_stage -= 5;
			}
		}
		break;
	//����������Ă���
	case 4:
		if (CheckStateKey(KEY_INPUT_DOWN) % CURSOR_SPEED == 1) {
			if (g_select_stage < STAGE_NUM - 5) {
				g_select_stage += 5;
			}
		}
		break;
	default:
		MessageBox(NULL, "�X�e�[�W�I���̃L�[���͂ŕs���Ȓl���n����܂���", "", MB_OK);
		break;

	}

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
	Vector2DF pos = g_stageselect_icon_object.pos;
	for (int i = 0; i < STAGE_NUM; i++) {
		//DrawGraphic(pos, &g_stageselect_back_object.graph);
		DrawBoxAA(pos.x - 60, pos.y - 40, pos.x + 60, pos.y + 40, COLOR_BLUE, TRUE);

		pos.x += SCREEN_WIDTH * 4 / 20;
	}

	//�I�𒆂̃X�e�[�W��\���J�[�\���̕\��
	pos.x = g_stageselect_icon_object.pos.x + (SCREEN_WIDTH * 4 / 20)*(g_select_stage % 5);
	pos.y = g_stageselect_icon_object.pos.y + (SCREEN_WIDTH * 4 / 20)*(g_select_stage / 5);
	DrawBoxAA(pos.x - 70, pos.y - 50, pos.x + 70, pos.y + 50, COLOR_RED, FALSE, 3);
	
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










