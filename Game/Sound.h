

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �萔�̒�` ==============================================================
#include "Load.h"




// �ϐ��̐錾 ==============================================================

extern BOOL g_se_flag[SE_ALL_NUM];		//���ʉ��p�t���O
extern BOOL g_bgm_flag[BGM_ALL_NUM];	//BGM�p�t���O



// �֐��̐錾 ==============================================================


//����������
void ResetSounds(void);

//���ʉ��Đ�
void PlaySE(void);

//BGM�Đ�
void PlayBGM(void);

//���ʉ��̍Đ��t���O��true�ɂ���
void SetSE(SE_ID se_Id);

//���ʉ����~����
void StopSE(SE_ID se_Id);

//BGM�̍Đ��t���O��true�ɂ���
void SetBGM(BGM_ID bgm_Id);

//BGM���~����
void StopBGM(BGM_ID bgm_Id);

//BGM���~�߂��Ƃ��납��Đ�����
void ContinueBGM(BGM_ID bgm_Id);

//�S�Ă̌��ʉ���BGM���~�߂�
void StopAllSound();


