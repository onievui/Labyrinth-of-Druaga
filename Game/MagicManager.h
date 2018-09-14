#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�G�̖��@�̏�����
void InitializeMagics();

//�G�̖��@�̐���
BOOL CreateMagic(MagicPattern knd, Vector2DF *pos, BOOL isLeft);

//�G�̖��@�̍X�V
void UpdateMagics();

//�G�̖��@�̕`��
void DrawMagics();

//�G�̖��@�̓����蔻��̐ݒ�
void SetMagicsCollider(BoxCollider collider[]);

//�G�̖��@�̕ǏՓˏ���
BOOL CollisionMagic(int i);

//�G�̖��@�̏���
void DestroyMagic(int i);

//�G�̖��@�̃_���[�W�ʂ̎擾
int GetMagicPower(int i);


