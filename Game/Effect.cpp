#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�G�t�F�N�g�̃v���g�^�C�v�̏�����
void InitializePrototypeEffect(Effect proto_effect[]) {

	//
	proto_effect[EFFECT_GET_ORB] =
	{
		EFFECT_GET_ORB,
		1,
		0,
		{ 0,0 },
		{ 0,0 },
		0,
		{ g_sprite[SPR_STD_EFFECT1],1.0,0.0 },
		0,
	};
	proto_effect[EFFECT_GET_ORB].graph.sprite.rect = GetSpriteRect(SPR_STD_EFFECT1, proto_effect[EFFECT_GET_ORB].sprite_num);

	
}


//�I�[�u�擾�G�t�F�N�g�̍X�V
void UpdateEffectGetOrb(Effect *effect) {

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(effect->pos, effect->vel);

	effect->state++;
}

//�I�[�u�擾�G�t�F�N�g�̕`��
void DrawEffectGetOrb(Effect *effect) {
	DrawGraphicToMap(effect->pos, &effect->graph);
}



