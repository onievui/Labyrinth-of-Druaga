#pragma once


//�O���Ɍ��J����񋓑̂̒�`



// �V�[��ID
enum SceneId {
	SCENE_NONE = -1,	//�V�[�����I��
	SCENE_LOGO,			//���S�V�[��
	SCENE_TITLE,		//�^�C�g���V�[��
	SCENE_STAGESELECT,	//�X�e�[�W�Z���N�g�V�[��
	SCENE_PLAY,			//�v���C�V�[��
	SCENE_RESULT,		//���U���g�V�[��
	SCENE_NUM,			//���I�����܂܂Ȃ��V�[����
};

//�X�e�[�W�̎��
enum StageId {
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	STAGE_NUM,
};

//�v���C���[�̏��
enum PlayerState {
	PLAYER_STATE_DEAD,		//���ɏ��
	PLAYER_STATE_STAND,		//�������
	PLAYER_STATE_JUMP,		//�W�����v���
	PLAYER_STATE_SUMMON,	//�������
	PLAYER_STATE_CLEAR,		//�N���A���
	PLAYER_STATE_NUM,		//�v���C���[�̏�Ԃ̎�ސ�
};

//���������X�^�[�̎��
enum MinionPattern {
	MINION_SLIME,	//�X���C��
	MINION_GHOST,	//�S�[�X�g
	MINION_PATTERN_NUM,		//���������X�^�[�̎�ސ�
};





