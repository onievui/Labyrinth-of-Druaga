//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScenePlay.cpp
//!
//! @brief  �v���C�V�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2018/08/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "ScenePlay.h"
#include "Map.h"
#include "Player.h"
#include "MinionManager.h"
#include "Treasure.h"
#include "Collision.h"
#include "Shader.h"
#include "Mediator.h"




// �萔�̒�` ==============================================================

//�v���C�V�[���̏��
enum ScenePlayState {
	PLAY_STATE_PLAY,	//�v���C���
	PLAY_STATE_PAUSE,	//�|�[�Y���
	PLAY_STATE_FAILED,	//�X�e�[�W���s���
	PLAY_STATE_CLEAR,	//�X�e�[�W�N���A���
};



// �O���[�o���ϐ��̒�` ====================================================
int g_count;					//�V�[�����J�n���Ă���̃J�E���g��
ScenePlayState g_play_state;	//�v���C�V�[���̏��
int g_select_mode;				//�|�[�Y/���g���C�m�F��ʂł̑I�����
int g_wait_time;				//���̏�Ԃֈڍs���邽�߂̑҂�����


// �֐��̐錾 ==============================================================
void InitializePlay(void);  // �v���C�V�[���̏���������
void UpdatePlay(void);      // �v���C�V�[���̍X�V����
void RenderPlay(void);      // �v���C�V�[���̕`�揈��
void FinalizePlay(void);    // �v���C�V�[���̏I������
void PlayProcess();
void PauseProcess();
void StageFailedProcess();
void StageClearProcess();




// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �v���C�V�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializePlay(void)
{
	//�v���C���[�̏�����
	InitializePlayer();

	//���������X�^�[�̏�����
	InitializeMinions();

	//����̏�����
	InitializeTreasure();

	//�}�b�v�̏�����
	InitializeMap();

	//�����蔻��̏�����
	InitializeCollision();

	//�J�E���^�̏�����
	g_count = 0;

	//��Ԃ̏�����
	g_play_state = PLAY_STATE_PLAY;
	g_select_mode = 0;
	g_wait_time = 0;
}



//----------------------------------------------------------------------
//! @brief �v���C�V�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdatePlay(void)
{

	switch (g_play_state) {
	//�v���C���
	case PLAY_STATE_PLAY:
		PlayProcess();
		break;
	//�|�[�Y���
	case PLAY_STATE_PAUSE:
		PauseProcess();
		break;
	//�Q�[�����s���
	case PLAY_STATE_FAILED:
		StageFailedProcess();
		break;
	//�X�e�[�W�N���A���
	case PLAY_STATE_CLEAR:
		StageClearProcess();
		break;
	default:
		MessageBox(NULL, "�v���C�V�[���̏�Ԃŕs���Ȓl���n����܂���", "", MB_OK);
		break;
	}


}



//----------------------------------------------------------------------
//! @brief �v���C�V�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderPlay(void)
{
	BOOL is_change_bright = FALSE;

	//�|�[�Y/���g���C�m�F��ʂł͈Â�����
	if (g_play_state == PLAY_STATE_PAUSE || (g_play_state == PLAY_STATE_FAILED && g_wait_time == 0)) {
		SetDrawBright(70, 70, 70);
		is_change_bright = TRUE;
	}

	//�}�b�v�̕`��
	DrawMap();

	//����̕`��
	DrawTreasure();

	//���������X�^�[�̕`��
	DrawMinions();

	//�v���C���[�̕`��
	DrawPlayer();

	//SP�Ə����\�ȃ����X�^�[�̃��X�g�̕`��
	DrawPlayerUI();

	//��ʂ̖��邳��߂�
	if (is_change_bright) {
		SetDrawBright(255, 255, 255);

		//���g���C�m�F��ʂȂ�I������\������
		if (g_play_state == PLAY_STATE_FAILED && g_wait_time == 0) {
			Vector2DF pos = { (float)SCREEN_CENTER_X/2,(float)SCREEN_CENTER_Y };
			DrawBoxAA(pos.x - 120, pos.y - 80, pos.x + 120, pos.y + 80, COLOR_AQUA, TRUE);
			DrawFormatStringFToHandle(pos.x - 105, pos.y - 30, COLOR_RED, g_font_g70, "RETRY");
			pos.x += SCREEN_CENTER_X;
			DrawBoxAA(pos.x - 120, pos.y - 80, pos.x + 120, pos.y + 80, COLOR_AQUA, TRUE);
			DrawFormatStringFToHandle(pos.x - 120, pos.y - 30, COLOR_PURPLE, g_font_g70, "GIVE UP");
			
			pos.x = g_select_mode == 0 ? SCREEN_CENTER_X / 2 : pos.x;
			DrawBoxAA(pos.x - 140, pos.y - 100, pos.x + 140, pos.y + 100, COLOR_RED, FALSE, 6);
		}

	}	

}



//----------------------------------------------------------------------
//! @brief �v���C�V�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizePlay(void)
{

}

//�v���C����
void PlayProcess() 
{
	//�v���C���[�̍X�V
	UpdatePlayer();

	//���������X�^�[�̍X�V
	UpdateMinions();

	//����̍X�V
	UpdateTreasure();

	//�����蔻��̍X�V
	UpdateCollision();
	
	//�J�����̃I�t�Z�b�g�̍X�V
	UpdateCameraOffset();

	g_count++;
}

//�|�[�Y��ʏ���
void PauseProcess() 
{

}

//�X�e�[�W���s��Ԃւ̈ڍs
void RequestStageFailed() 
{
	//�X�e�[�W���s��Ԃֈڍs
	g_play_state = PLAY_STATE_FAILED;
	//2�b�ԑ҂�
	g_wait_time = 120;
	//�J�[�\���̏�����
	g_select_mode = 0;
}

//�X�e�[�W���s����
void StageFailedProcess() 
{
	//�X�e�[�W���s���̉��o
	if (g_wait_time) {

		//�v���C���[�̍X�V
		UpdatePlayer();

		//�J�����̃I�t�Z�b�g�̍X�V
		UpdateCameraOffset();

		g_wait_time--;
	}
	//���g���C�m�F
	else {
		//���E�L�[�ŃJ�[�\���ړ�
		if (CheckHitKeyDown(KEY_INPUT_LEFT) || CheckHitKeyDown(KEY_INPUT_RIGHT)) {
			g_select_mode = 1 - g_select_mode;
		}
		//Z�L�[��X�L�[�őI��
		if (CheckHitKeyDown(KEY_INPUT_Z) || CheckHitKeyDown(KEY_INPUT_X)) {
			//���g���C�Ȃ�V�[���v���C����蒼��
			if (g_select_mode == 0) {
				SetSelectStage(GetSelectStage());
				RequestScene(SCENE_PLAY);
			}
			//�M�u�A�b�v�Ȃ�X�e�[�W�Z���N�g�ɖ߂�
			else {
				RequestScene(SCENE_STAGESELECT);
			}
		}
	}
}

//�X�e�[�W�N���A�ւ̈ڍs
void RequestStageClear() 
{
	//�N���A�^�C���̋L�^
	SetClearTime(g_count);
	//�N���A��Ԃֈڍs
	g_play_state = PLAY_STATE_CLEAR;
	//3�b�ԑ҂�
	g_wait_time = 180;
}

//�X�e�[�W�N���A����
void StageClearProcess() 
{
	if (g_wait_time) {

		//�v���C���[�̍X�V
		UpdatePlayer();

		//�����蔻��̍X�V
		UpdateCollision();

		//�J�����̃I�t�Z�b�g�̍X�V
		UpdateCameraOffset();

		g_wait_time--;
	}
	else {
		//�҂����Ԃ��I������烊�U���g��ʂֈڍs
		RequestScene(SCENE_RESULT);
	}
}
