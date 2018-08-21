#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"




//���������X�^�[�̃v���g�^�C�v�̏�����
void InitializePrototypeMinion(Minion proto_minion[]);

//�X���C���̍X�V
void UpdateMinionSlime(Minion *minion);

//�S�[�X�g�̍X�V
void UpdateMinionGhost(Minion *minion);

//�X���C���̕`��
void DrawMinionSlime(Minion *minion);

//�S�[�X�g�̕`��
void DrawMinionGhost(Minion *minion);

//�X���C���̃_���[�W����
void DamageMinionSlime(Minion *minion, int power);

//�S�[�X�g�̃_���[�W����
void DamageMinionGhost(Minion *minion, int power);

//�X���C���̏���
void DestroyMinionSlime(Minion *minion);

//�S�[�X�g�̏���
void DestroyMinionGhost(Minion *minion);


