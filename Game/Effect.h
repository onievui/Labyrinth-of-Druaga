#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�G�t�F�N�g�̃v���g�^�C�v�̏�����
void InitializePrototypeEffect(Effect proto_effect[]);

//�I�[�u�擾�G�t�F�N�g�̍X�V
BOOL UpdateEffectGetOrb(Effect *effect);

//�I�[�u�擾�G�t�F�N�g�̕`��
void DrawEffectGetOrb(Effect *effect);

//�I�[�u�擾�G�t�F�N�g�̏���
void DestroyEffectGetOrb(Effect *effect);


