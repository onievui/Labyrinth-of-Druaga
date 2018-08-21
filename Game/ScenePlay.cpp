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
int g_select_mode;				//�R���e�B�j���[�m�F��ʂł̑I�����
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
	//�}�b�v�̕`��
	DrawMap();

	//����̕`��
	DrawTreasure();

	//���������X�^�[�̕`��
	DrawMinions();

	//�v���C���[�̕`��
	DrawPlayer();

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
	
}

//�X�e�[�W���s����
void StageFailedProcess() 
{
	
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

		//�J�����̃I�t�Z�b�g�̍X�V
		UpdateCameraOffset();

		g_wait_time--;
	}
	else {
		//�҂����Ԃ��I������烊�U���g��ʂֈڍs
		RequestScene(SCENE_RESULT);
	}
}
