#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�萔�̒�`
#define ORB_GET_ANIMATE_SPEED		(5)		//�I�[�u�擾�G�t�F�N�g�̃A�j���[�V�����Ԋu



//�G�t�F�N�g�̃v���g�^�C�v�̏�����
void InitializePrototypeEffect(Effect proto_effect[]) {

	//�I�[�u�擾�G�t�F�N�g�̃v���g�^�C�v
	proto_effect[EFFECT_GET_ORB] =
	{
		EFFECT_GET_ORB,
		1,
		0,
		{ 0,0 },
		{ -20,-20,20,20 },
		{ 0,0 },
		0,
		{ g_sprite[SPR_STD_EFFECT1],0.6f,0.0 },
		0,
	};
	proto_effect[EFFECT_GET_ORB].graph.sprite.rect = GetSpriteRect(SPR_STD_EFFECT1, proto_effect[EFFECT_GET_ORB].sprite_num);

	
}


//�I�[�u�擾�G�t�F�N�g�̍X�V
BOOL UpdateEffectGetOrb(Effect *effect) {


	//�A�j���[�V�������s��
	if (effect->count%ORB_GET_ANIMATE_SPEED == ORB_GET_ANIMATE_SPEED - 1) {
		effect->sprite_num++;
		//�X�v���C�g�̕ύX
		if (effect->sprite_num < 3) {
			effect->graph.sprite.rect = GetSpriteRect(SPR_STD_EFFECT1, effect->sprite_num);
		}
		//�G�t�F�N�g�̏���
		else {
			return FALSE;
		}
	}


	effect->count++;

	return TRUE;
}

//�I�[�u�擾�G�t�F�N�g�̕`��
void DrawEffectGetOrb(Effect *effect) {

	//���X�ɓ����ɂ���
	float t = effect->count*1.0f / (ORB_GET_ANIMATE_SPEED * 3);
	t = t*t*t;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * (1-t)));
	DrawGraphicToMap(effect->pos, &effect->graph);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//�I�[�u�擾�G�t�F�N�g�̏���
void DestroyEffectGetOrb(Effect *effect) {
	effect->state = 0;
}

