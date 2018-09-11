#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"




//���������X�^�[�̃v���g�^�C�v�̏�����
void InitializePrototypeMinion(Minion proto_minion[], SummonData s_data[]);

//�X���C���̍X�V
void UpdateMinionSlime(Minion *minion);

//�S�[�X�g�̍X�V
void UpdateMinionGhost(Minion *minion);

//�N�I�b�N�X�̍X�V
void UpdateMinionQuox(Minion *minion);

//�X���C���̕`��
void DrawMinionSlime(Minion *minion);

//�S�[�X�g�̕`��
void DrawMinionGhost(Minion *minion);

//�N�I�b�N�X�̕`��
void DrawMinionQuox(Minion *minion);

//�X���C���̃_���[�W����
BOOL DamageMinionSlime(Minion *minion, int power);

//�S�[�X�g�̃_���[�W����
BOOL DamageMinionGhost(Minion *minion, int power);

//�N�I�b�N�X�̃_���[�W����
BOOL DamageMinionQuox(Minion *minion, int power);

//�X���C���̏���
void DestroyMinionSlime(Minion *minion, SummonData *s_dat);

//�S�[�X�g�̏���
void DestroyMinionGhost(Minion *minion, SummonData *s_dat);

//�N�I�b�N�X�̏���
void DestroyMinionQuox(Minion *minion, SummonData *s_dat);

