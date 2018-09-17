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
int g_second;						//�N���A�^�C���̕b
int g_decimal;						//�N���A�^�C���̕b�i�����j
BOOL g_is_highscore;				//�n�C�X�R�A���ǂ���
AllClearData *g_old_clear_data;		//�N���A�f�[�^



// �֐��̐錾 ==============================================================
void InitializeResult(void);  // �v���C�V�[���̏���������
void UpdateResult(void);      // �v���C�V�[���̍X�V����
void RenderResult(void);      // �v���C�V�[���̕`�揈��
void FinalizeResult(void);    // �v���C�V�[���̏I������

void ChangeGetClearTime();
void UpdateHighscore();




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
	
	//�N���A�f�[�^�̎擾
	g_old_clear_data = GetAllClearData();

	//�N���A�^�C���̎擾�A�ϊ�
	ChangeGetClearTime();
	
	//�n�C�X�R�A�X�V����
	UpdateHighscore();

	//�n�C�X�R�A�Ȃ���ʉ���炷
	if (g_is_highscore) {
		SetSE(SE_HIGHSCORE);
	}
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

	//�n�C�X�R�A�Ȃ�\������
	if (g_is_highscore) {
		DrawFormatStringFToHandle(SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g70, "HIGH SCORE!") / 2.0f,
			SCREEN_CENTER_Y - 165, COLOR_RED, g_font_g70, "HIGH SCORE!");
	}

	//�N���A�^�C���̕\��
	DrawFormatStringFToHandle(SCREEN_CENTER_X - GetDrawFormatStringWidthToHandle(g_font_g70, "TIME %d.%02d", g_second,g_decimal) / 2.0f,
		SCREEN_CENTER_Y - 50, COLOR_YELLOW, g_font_g70, "TIME %d.%02d", g_second, g_decimal);
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


//�N���A�^�C���̎擾�A�ϊ�
void ChangeGetClearTime() {

	int time = GetClearTime();
	char time_s[10], input[5];
	sprintf(time_s, "%.2f", time / 60.0f);
	int i = 0, j = 0, knd = 0;
	//���������Ə��������ɕ�����
	while (1) {
		for (j = 0; j<5; j++) {
			input[j] = time_s[i + j];	//1�����擾����
			if (input[j] == '.' || input[j] == '\0') {	//�s���I�h�����s�Ȃ炻���܂ł𕶎���Ƃ���
				input[j] = '\0';
				break;
			}
		}
		if (knd == 0) {
			g_second = atoi(input);
		}
		else {
			g_decimal = atoi(input);
			break;
		}
		i = j + 1;
		knd++;
	}
}


//�n�C�X�R�A�X�V����
void UpdateHighscore() {																																																																																																		

	StageId id = GetSelectStage();
	g_is_highscore = FALSE;

	//�n�C�X�R�A�Ȃ�
	if (g_old_clear_data->clear_data[id].second == 0 ||
		g_second * 100 + g_decimal <
		g_old_clear_data->clear_data[id].second * 100 + g_old_clear_data->clear_data[id].decimal) {
		
		//�X�R�A���X�V����
		g_old_clear_data->clear_data[id].second = g_second;
		g_old_clear_data->clear_data[id].decimal = g_decimal;

		//�S�X�e�[�W�N���A���Ă���Ȃ獇�v�X�R�A���X�V����
		g_old_clear_data->clear_data[id].is_clear = TRUE;
		if (GetClearStageNum() == STAGE_NUM) {
			int i;
			g_old_clear_data->total_second = 0;
			g_old_clear_data->total_decimal = 0;
			for (i = 0; i < STAGE_NUM; i++) {
				g_old_clear_data->total_second += g_old_clear_data->clear_data[i].second;
				g_old_clear_data->total_decimal += g_old_clear_data->clear_data[i].decimal;
			}
			g_old_clear_data->total_second += g_old_clear_data->total_decimal / 100;
			g_old_clear_data->total_decimal = g_old_clear_data->total_decimal % 100;
		}

		//�X�R�A�̔��f
		OrderWriteClearData();

		//�n�C�X�R�A��Ԃɂ���
		g_is_highscore = TRUE;
	}
}