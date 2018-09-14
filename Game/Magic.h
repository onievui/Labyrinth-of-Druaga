#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�����X�^�[�̖��@�̃v���g�^�C�v�̏�����
void InitializePrototypeMagic(Magic proto_magic[]);

//�����@�̍X�V
void UpdateMagicWhite(Magic *magic);

//�Ζ��@�̍X�V
void UpdateMagicGreen(Magic *magic);

//�����@�̕`��
void DrawMagicWhite(Magic *magic);

//�Ζ��@�̕`��
void DrawMagicGreen(Magic *magic);

//�����@�̕ǏՓˏ���
BOOL CollisionMagicWhite(Magic *magic);

//�Ζ��@�̕ǏՓˏ���
BOOL CollisionMagicGreen(Magic *magic);

//�����@�̏���
void DestroyMagicWhite(Magic *magic);

//�Ζ��@�̏���
void DestroyMagicGreen(Magic *magic);



