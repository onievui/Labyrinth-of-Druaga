//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   sound.cpp
//!
//! @brief  �T�E���h�֘A�̏���
//!
//! @date   2018/06/05
//!
//! @author �i�˗E��
//__/__/__/__/__/__/__/__/__/__/_S_/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


//�w�b�_�[�t�@�C���̓ǂݍ���
#include "Sound.h"



//�O���[�o���ϐ��̐錾

//�T�E���h�t���O
bool g_se_flag[SE_ALL_NUM];
bool g_bgm_flag[BGM_ALL_NUM];




//----------------------------------------------------------------------
//! @brief ����������
//!
//! @param[in] �Ȃ�
//!
//! @return�@�Ȃ�
//----------------------------------------------------------------------
void ResetSounds() {
	for (int i = 0; i < SE_ALL_NUM; i++)
		g_se_flag[i] = false;
	for (int i = 0; i < BGM_ALL_NUM; i++)
		g_bgm_flag[i] = false;
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
			g_se_flag[i] = false;
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
			PlaySoundMem(g_bgm[i], DX_PLAYTYPE_LOOP);
			g_bgm_flag[i] = false;
		}
	}
}

//���ʉ��̍Đ��t���O��true�ɂ���
void SetSE(SE_ID se_Id) {

	//�G���[�`�F�b�N
	if (se_Id < 0 || se_Id >= SE_ALL_NUM) {
		MessageBox(NULL, "���ʉ��̍Đ��ŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_se_flag[se_Id] = true;
}


//BGM�̍Đ��t���O��true�ɂ���
void SetBGM(BGM_ID bgm_Id) {

	//�G���[�`�F�b�N
	if (bgm_Id < 0 || bgm_Id >= BGM_ALL_NUM) {
		MessageBox(NULL, "BGM�̍Đ��ŕs���Ȓl���n����܂���", "", MB_OK);
		return;
	}

	g_bgm_flag[bgm_Id] = true;
}

//BGM���~����
void StopBGM(BGM_ID bgm_Id) {
	StopSoundMem(g_bgm[bgm_Id]);
}


