//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   sound.cpp
//!
//! @brief  �T�E���h�֘A�̏���
//!
//! @date   2018/
//__/__/__/__/__/__/__/__/__/__/_S_/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


//�w�b�_�[�t�@�C���̓ǂݍ���
#include "Sound.h"



//�O���[�o���ϐ��̐錾

//�T�E���h�t���O
BOOL g_se_flag[SE_ALL_NUM];
BOOL g_bgm_flag[BGM_ALL_NUM];
BOOL g_continue_flag[BGM_ALL_NUM];





//----------------------------------------------------------------------
//! @brief ����������
//!
//! @param[in] �Ȃ�
//!
//! @return�@�Ȃ�
//----------------------------------------------------------------------
void ResetSounds() {
	for (int i = 0; i < SE_ALL_NUM; i++)
		g_se_flag[i] = FALSE;
	for (int i = 0; i < BGM_ALL_NUM; i++)
		g_bgm_flag[i] = FALSE;
	for (int i = 0; i < BGM_ALL_NUM; i++)
		g_continue_flag[i] = FALSE;
}


//----------------------------------------------------------------------
//! @brief ���ʉ��Đ�
//!
//! @param[in] �Ȃ�
//!
//! @return�@�Ȃ�
//----------------------------------------------------------------------
void PlaySE() {
	for (int i = 0; i < SE_ALL_NUM; i++) {
		if (g_se_flag[i]) {
			PlaySoundMem(g_se[i], DX_PLAYTYPE_BACK);
			g_se_flag[i] = FALSE;
		}
	}
}


//----------------------------------------------------------------------
//! @brief BGM�Đ�
//!
//! @param[in] �Ȃ�
//!
//! @return�@�Ȃ�
//----------------------------------------------------------------------
void PlayBGM() {
	for (int i = 0; i < BGM_ALL_NUM; i++) {
		if (g_bgm_flag[i]) {
			PlaySoundMem(g_bgm[i], DX_PLAYTYPE_LOOP, !g_continue_flag[i]);
			g_bgm_flag[i] = FALSE;
			if (g_continue_flag[i])
				g_continue_flag[i] = FALSE;
		}
	}
}

//���ʉ��̍Đ��t���O��TRUE�ɂ���
void SetSE(SE_ID se_Id) {

	//�G���[�`�F�b�N
	if (se_Id < 0 || se_Id >= SE_ALL_NUM) {
		MessageBox(NULL, "���ʉ��̍Đ��ŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_se_flag[se_Id] = TRUE;
}

//���ʉ����~����
void StopSE(SE_ID se_Id) {
	StopSoundMem(g_se[se_Id]);
}

//BGM�̍Đ��t���O��TRUE�ɂ���
void SetBGM(BGM_ID bgm_Id) {

	//�G���[�`�F�b�N
	if (bgm_Id < 0 || bgm_Id >= BGM_ALL_NUM) {
		MessageBox(NULL, "BGM�̍Đ��ŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_bgm_flag[bgm_Id] = TRUE;
}

//BGM���~����
void StopBGM(BGM_ID bgm_Id) {
	StopSoundMem(g_bgm[bgm_Id]);
}

//BGM���~�߂��Ƃ��납��Đ�����
void ContinueBGM(BGM_ID bgm_Id) {

	//�G���[�`�F�b�N
	if (bgm_Id < 0 || bgm_Id >= BGM_ALL_NUM) {
		MessageBox(NULL, "BGM�̓r���Đ��ŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}
	g_continue_flag[bgm_Id] = TRUE;
	g_bgm_flag[bgm_Id] = TRUE;
}


