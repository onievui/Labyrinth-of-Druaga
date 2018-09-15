#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "SceneStageSelect.h"
#include "Mediator.h"




//�萔�̒�`
#define ICON_DEF_X	((float)(SCREEN_WIDTH / 10))	//�X�e�[�W�A�C�R���̏���X���W
#define ICON_DEF_Y	((float)(SCREEN_HEIGHT / 5))	//�X�e�[�W�A�C�R���̏���Y���W

#define COLOR_BLUE2 ((unsigned int)(0xFF0040FF))	//�F2


// �O���[�o���ϐ��̒�` ====================================================

GameObject g_stageselect_back_object;	//�w�i�I�u�W�F�N�g
int g_select_stage;				//�I�𒆂̃X�e�[�W�ԍ�
AllClearData *g_view_clear_data;	//�N���A�f�[�^



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

	//�O��̃X�e�[�W�ɃJ�[�\�������킹��
	g_select_stage = GetSelectStage();
	if (!~g_select_stage)
		g_select_stage = 0;

	//BGM�̍Đ�
	SetBGM(BGM_SELECT);

	//�N���A�f�[�^�̓ǂݍ���
	OrderLoadClearData();
	//�N���A�f�[�^�̎擾
	g_view_clear_data = GetAllClearData();
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
			g_select_stage += g_select_stage % 5 ? -1 : 4;
		}
		break;
	//�E��������Ă���
	case 2:
		if (CheckStateKey(KEY_INPUT_RIGHT) % CURSOR_SPEED == 1) {
			g_select_stage += g_select_stage % 5 != 4 ? 1 : -4;
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
	int i;
	Vector2DF pos = { ICON_DEF_X,ICON_DEF_Y };
	char name[64];
	for (i = 0; i < STAGE_NUM; i++) {
		//���N���A��ԂȂ�
		if (!g_view_clear_data->clear_data[i].is_clear) {
			//�g�̕`��
			DrawBoxAA(pos.x - 60, pos.y - 40, pos.x + 60, pos.y + 40, COLOR_BLUE2, TRUE);

			//�����̕`��
			sprintf(name, "%d - %d", i / 5 + 1, i % 5 + 1);
			DrawFormatStringFToHandle(pos.x - GetDrawFormatStringWidthToHandle(g_font_g30, "%s", name) / 2.0f,
				pos.y - 10, COLOR_WHITE, g_font_g30, "%s", name);
		}
		//�N���A��ԂȂ�
		else {
			//�g�̕`��
			DrawBoxAA(pos.x - 60, pos.y - 40, pos.x + 60, pos.y + 40, COLOR_BLACK, TRUE);

			//�����̕`��
			sprintf(name, "%d - %d", i / 5 + 1, i % 5 + 1);
			DrawFormatStringFToHandle(pos.x - GetDrawFormatStringWidthToHandle(g_font_g30, "%s", name) / 2.0f,
				pos.y - 10, COLOR_WHITE, g_font_g30, "%s", name);
		}

		//���W�����炷
		if (i % 5 != 4) {
			pos.x += SCREEN_WIDTH * 4 / 20;
		}
		else {
			pos.x = ICON_DEF_X;
			pos.y += SCREEN_HEIGHT * 4 / 20;
		}
	}

	//�I�𒆂̃X�e�[�W��\���J�[�\���̕\��
	pos.x = ICON_DEF_X + (SCREEN_WIDTH  * 4 / 20)*(g_select_stage % 5);
	pos.y = ICON_DEF_Y + (SCREEN_HEIGHT * 4 / 20)*(g_select_stage / 5);
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
	//BGM���~�߂�
	StopBGM(BGM_SELECT);
}










