//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Key.cpp
//!
//! @brief  �L�[�{�[�h�֘A�̏���
//!
//! @date   2018/06/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �O���[�o���ϐ��̒�` ====================================================

//�L�[�{�[�h�̓��͏�Ԃ��i�[����
static unsigned int g_stateKey[256];

static int g_stateKeyUp[256];

// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �L�[�{�[�h�̂��ׂẴL�[�̉�����ԁA���̓t���[�������擾����
//!
//! @param[in] �Ȃ�
//!
//! @return�@0:����I�� 1:�ُ�I��
//----------------------------------------------------------------------
int GetHitKeyStateAll_2() {
	char GetHitKeyStateAll_Key[256];
	GetHitKeyStateAll(GetHitKeyStateAll_Key);
	for (int i = 0; i<256; i++) {
		if (GetHitKeyStateAll_Key[i] == 1) {
			g_stateKey[i]++;
			g_stateKeyUp[i] = 0;
		}
		else {
			if (g_stateKey[i] > 0)
				g_stateKeyUp[i] = 1;
			else
				g_stateKeyUp[i] = 0;

			g_stateKey[i] = 0;
		}
	}
	return 0;
}

//----------------------------------------------------------------------
//! @brief ����̃L�[�̓��͏�Ԃ�Ԃ�
//!
//! @param[in]	Handle ����̃L�[�̃}�N��
//!
//! @return�@g_statekey[Handle] ����̃L�[�̓��̓t���[����
//----------------------------------------------------------------------
int CheckStateKey(unsigned char Handle) {
	return g_stateKey[Handle];
}


//----------------------------------------------------------------------
//! @brief ����̃L�[�������Ă��Ȃ���Ԃ��牟�������ǂ�����Ԃ�
//!
//! @param[in]	Handle ����̃L�[�̃}�N��
//!
//! @return�@0:�����Ă��Ȃ� 1:������
//----------------------------------------------------------------------
int CheckHitKeyDown(unsigned char Handle) {
	return g_stateKey[Handle] == 1 ? 1 : 0;
}


//----------------------------------------------------------------------
//! @brief ����̃L�[����������Ԃ��痣�������ǂ�����Ԃ�
//!
//! @param[in]	Handle ����̃L�[�̃}�N��
//!
//! @return�@0:�����Ă��Ȃ� 1:������
//----------------------------------------------------------------------
int CheckHitKeyUp(unsigned char Handle) {
	return g_stateKeyUp[Handle];
}


//----------------------------------------------------------------------
//! @brief �Q�̓���̃L�[�̌ォ�牟����Ă���ق��𔻕ʂ���
//!
//! @param[in]	Handle1 ����̃L�[1�̃}�N��
//!				Handle2 ����̃L�[2�̃}�N��
//!
//! @return�@longer 0:�ǂ����������Ă��Ȃ� 1:��P���� 2:��Q����
//----------------------------------------------------------------------
int CheckStateKeyLater(unsigned char Handle1, unsigned char Handle2) {

	//�f�t�H���g�͉���������Ă��Ȃ����
	int longer = 0;

	if (CheckStateKey(Handle1) > 0) {	//����������Ă�����
		if (CheckStateKey(Handle2) > 0 && CheckStateKey(Handle2) < CheckStateKey(Handle1)) {		//�E����ɉ�����Ă�����
			longer = 2;
		}
		else {
			longer = 1;
		}
	}
	else if (CheckStateKey(Handle2) > 0) {	//�E��������Ă�����
		longer = 2;
	}

	return longer;
}