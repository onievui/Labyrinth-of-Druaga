//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneLogo.cpp
//!
//! @brief  ���S�V�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "SceneLogo.h"


// �O���[�o���ϐ��̒�` ====================================================
int g_logo_state;	//���S�V�[���̏��
int g_logo_count;	//���S�V�[���̌o�ߎ���

GameObject g_logo_object1;	//���S�I�u�W�F�N�g1
GameObject g_logo_object2;	//���S�I�u�W�F�N�g2



// �֐��̐錾 ==============================================================
void InitializeLogo(void);  // ���S�V�[���̏���������
void UpdateLogo(void);      // ���S�V�[���̍X�V����
void RenderLogo(void);      // ���S�V�[���̕`�揈��
void FinalizeLogo(void);    // ���S�V�[���̏I������




// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief ���S�V�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeLogo(void)
{
	g_logo_state = 0;
	g_logo_count = 0;
	
	//���S�I�u�W�F�N�g1�̏�����
	g_logo_object1.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_logo_object1.vel = Vector2DF{ 0,0 };
	g_logo_object1.state = 1;
	g_logo_object1.speed = 0;
	g_logo_object1.angle = 0;
	g_logo_object1.graph = Graph{ &g_sprite[SPR_LOGO2] , 1.0f, 0.0f };

	//���S�I�u�W�F�N�g2�̏�����
	g_logo_object2.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_logo_object2.vel = Vector2DF{ 0,0 };
	g_logo_object2.state = 1;
	g_logo_object2.speed = 0;
	g_logo_object2.angle = 0;
	g_logo_object2.graph = Graph{ &g_sprite[SPR_LOGO1] , 1.0f, 0.0f };
	
}



//----------------------------------------------------------------------
//! @brief ���S�V�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateLogo(void)
{
	//X�L�[�ŃX�L�b�v
	if (CheckHitKeyDown(KEY_INPUT_X)) {
		g_logo_count = 180;
		g_logo_state = 2;
	}

	//���S�\�����ԓ��Ȃ�J�E���^�𑝂₷
	if (g_logo_count < 180) {
		g_logo_count++;
	}
	//1�ڂ̃��S���\�����I�������2�ڂ�\������
	else if (g_logo_state == 0) {
		g_logo_count = 0;
		g_logo_state = 1;
	}
	//�^�C�g���V�[���ɑJ�ڂ���
	else {
		RequestScene(SCENE_TITLE);
	}
}



//----------------------------------------------------------------------
//! @brief ���S�V�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderLogo(void)
{
	//���S�I�u�W�F�N�g�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255*(g_logo_count/90.0f)));
	if (g_logo_state == 0) {
		DrawGraphic(g_logo_object1.pos, &g_logo_object1.graph);
	}
	else if (g_logo_state == 1) {
		DrawGraphic(g_logo_object2.pos, &g_logo_object2.graph);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}



//----------------------------------------------------------------------
//! @brief ���S�V�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeLogo(void)
{

}
