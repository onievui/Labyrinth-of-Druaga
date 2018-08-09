//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Key.cpp
//!
//! @brief  �L�[�{�[�h�֘A�̏���
//!
//! @date   2018/08/08
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
	int i;
	for (i = 0; i<256; i++) {
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
	int later = 0;

	//�e�L�[�̓��͏��
	int key_state1, key_state2;

	key_state1 = CheckStateKey(Handle1);
	key_state2 = CheckStateKey(Handle2);


	if (key_state1 > 0) {	//��Ԗڂ�������Ă�����
		if (key_state2 > 0 && key_state2 < key_state1) {		//��Ԗڂ���ɉ�����Ă�����
			later = 2;
		}
		else {
			later = 1;
		}
	}
	else if (key_state2 > 0) {	//��Ԗڂ�������Ă�����
		later = 2;
	}

	return later;
}

//----------------------------------------------------------------------
//! @brief �S�̓���̃L�[�̌ォ�牟����Ă���ق��𔻕ʂ���
//!
//! @param[in]	Handle1 ����̃L�[1�̃}�N��
//!				Handle2 ����̃L�[2�̃}�N��
//!				Handle3 ����̃L�[3�̃}�N��
//!				Handle3 ����̃L�[4�̃}�N��
//!
//! @return�@longer 0:�������������Ă��Ȃ� 1:��P���� 2:��Q���� 3:��R���� 4:��S����
//----------------------------------------------------------------------
int CheckStateKeyLater4(unsigned char Handle1, unsigned char Handle2, unsigned char Handle3, unsigned char Handle4) {

	//�f�t�H���g�͉���������Ă��Ȃ����
	int later = 0;

	//�{�^���������ꂽ����
	int shortest = 999999;

	//�e�L�[�̓��͏��
	int key_state[4];

	key_state[0] = CheckStateKey(Handle1);
	key_state[1] = CheckStateKey(Handle2);
	key_state[2] = CheckStateKey(Handle3);
	key_state[3] = CheckStateKey(Handle4);

	int i;
	for (i = 0; i < 4; i++) {
		if (key_state[i] && key_state[i] < shortest) {
			later = i + 1;
			shortest = key_state[i];
		}
	}
	
	return later;
}