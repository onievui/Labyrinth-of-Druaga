#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�萔�̒�`
#define WHITE_MAGIC_SPEED	(12)	//�����@�̑��x
#define GREEN_MAGIC_SPEED	(8)		//�Ζ��@�̑��x

#define WHITE_MAGIC_POWER	(1)		//�����@�̃_���[�W��
#define GREEN_MAGIC_POWER	(1)		//�Ζ��@�̃_���[�W��


//�����X�^�[�̖��@�̃v���g�^�C�v�̏�����
void InitializePrototypeMagic(Magic proto_magic[]) {

	//�����@
	proto_magic[MAGIC_WHITE] =
	{
		MAGIC_WHITE,
		1,
		{ 0,0 },
		{ -25,-20,25,16 },
		{ WHITE_MAGIC_SPEED,0 },
		WHITE_MAGIC_POWER,
		{ g_sprite[SPR_STD_MAGIC],1.0,0.0 },
		20,
		0
	};
	proto_magic[MAGIC_WHITE].graph.sprite.rect = GetSpriteRect(SPR_STD_MAGIC, proto_magic[MAGIC_WHITE].sprite_num);

	//�Ζ��@
	proto_magic[MAGIC_GREEN] =
	{
		MAGIC_GREEN,
		1,
		{ 0,0 },
		{ -25,-20,25,16 },
		{ GREEN_MAGIC_SPEED,0 },
		GREEN_MAGIC_POWER,
		{ g_sprite[SPR_STD_MAGIC],1.0,0.0 },
		23,
		0
	};
	proto_magic[MAGIC_GREEN].graph.sprite.rect = GetSpriteRect(SPR_STD_MAGIC, proto_magic[MAGIC_GREEN].sprite_num);

}


//�����@�̍X�V
void UpdateMagicWhite(Magic *magic) {

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(magic->pos, magic->vel);

	magic->anime_count++;
}

//�Ζ��@�̍X�V
void UpdateMagicGreen(Magic *magic) {

	//�ړ��ʂ����W�ɑ���
	AddVector2DF(magic->pos, magic->vel);

	magic->anime_count++;

}

//�����@�̕`��
void DrawMagicWhite(Magic *magic) {
	if (magic->anime_count % 30 < 15)
		DrawGraphicToMap(magic->pos, &magic->graph);
	else
		DrawTurnGraphicToMap(magic->pos, &magic->graph);
	/*Vector2DF pos = magic->pos;
	SubVector2DF(pos, OrderGetCameraOffset());
	RectF rect = { pos.x + magic->col.left,
	pos.y + magic->col.top,
	pos.x + magic->col.right,
	pos.y + magic->col.bottom };
	DrawBoxAA(rect.left, rect.top, rect.right, rect.bottom, COLOR_BLUE, 0);*/
}

//�Ζ��@�̕`��
void DrawMagicGreen(Magic *magic) {
	if (magic->anime_count % 30 < 15)
		DrawGraphicToMap(magic->pos, &magic->graph);
	else
		DrawTurnGraphicToMap(magic->pos, &magic->graph);
}

//�����@�̕ǏՓˏ���
BOOL CollisionMagicWhite(Magic *magic) {
	//�����@�͕ǂɏՓ˂���Ə�����
	return TRUE;
}

//�Ζ��@�̕ǏՓˏ���
BOOL CollisionMagicGreen(Magic *magic) {
	//�Ζ��@�͕ǂ��ђʂ���
	return FALSE;
}

//�����@�̏���
void DestroyMagicWhite(Magic *magic) {
	magic->state = 0;
}

//�Ζ��@�̏���
void DestroyMagicGreen(Magic *magic) {
	magic->state = 0;
}




