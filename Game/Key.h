//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Key.h
//!
//! @brief  �L�[���͊֘A�̃w�b�_�t�@�C��
//!
//! @date   2018/08/08
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once


// �֐��̐錾 ==============================================================


//�L�[�{�[�h�̂��ׂẴL�[�̉�����ԁA���̓t���[�������擾����
//���̊֐��𖈃t���[���Ăяo���Ȃ��Ɖ��̊֐����g���܂���
int GetHitKeyStateAll_2(void);

//����̃L�[�̓��͏�Ԃ�Ԃ�
int CheckStateKey(unsigned char Handle);

//����̃L�[�������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
int CheckHitKeyDown(unsigned char Handle);

//����̃L�[����������Ԃ��痣�������ǂ�����Ԃ�
int CheckHitKeyUp(unsigned char Handle);

//�Q�̓���̃L�[�̌ォ�牟����Ă���ق��𔻕ʂ���
// return longer 0:�ǂ����������Ă��Ȃ� 1:��P���� 2:��Q����
int CheckStateKeyLater(unsigned char Handle1, unsigned char Handle2);

//�S�̓���̃L�[�̌ォ�牟����Ă���ق��𔻕ʂ���
// return longer 0:�������������Ă��Ȃ� 1 : ��P���� 2 : ��Q���� 3 : ��R���� 4 : ��S����
int CheckStateKeyLater4(unsigned char Handle1, unsigned char Handle2, unsigned char Handle3, unsigned char Handle4);