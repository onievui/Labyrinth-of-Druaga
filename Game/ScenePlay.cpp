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
#include "Player.h"
#include "Shader.h"
#include "Mediator.h"




// �萔�̒�` ==============================================================




// �O���[�o���ϐ��̒�` ====================================================
int g_count;			//�V�[�����J�n���Ă���̃J�E���g��
int g_play_state;		//�v���C�V�[���̏��
int g_select_mode;		//�R���e�B�j���[�m�F��ʂł̑I�����
int g_wait_time;		//�R���e�B�j���[�̊m�F��\������܂ł̑҂�����


// �֐��̐錾 ==============================================================
void InitializePlay(void);  // �v���C�V�[���̏���������
void UpdatePlay(void);      // �v���C�V�[���̍X�V����
void RenderPlay(void);      // �v���C�V�[���̕`�揈��
void FinalizePlay(void);    // �v���C�V�[���̏I������
void PlayProcess();
void PauseProcess();
void StageFailedProcess();




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

	//�J�E���^�̏�����
	g_count = 0;

	//��Ԃ̏�����
	g_play_state = 0;
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
	case 0:
		PlayProcess();
		break;
	//�|�[�Y���
	case 1:
		
		break;
	//�Q�[�����s���
	case 2:
		
		break;
	//�X�e�[�W�N���A���
	case 3:
		
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
	
}

//�X�e�[�W�N���A����
void StageClearProcess() 
{

}
