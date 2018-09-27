#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"
#include "Mediator.h"


//�v���g�^�C�v�錾
extern void LoadGuideData(const StageId stageId, Guide guide[]);


Guide g_guide[GUIDE_MAX];		//�K�C�h�I�u�W�F�N�g



//�K�C�h�̏�����
void InitializeGuide() {

	//�f�[�^�̏�����
	memset(g_guide, 0, sizeof(g_guide));

	//�K�C�h�f�[�^�̓ǂݍ���
	LoadGuideData(GetSelectStage(), g_guide);
	
	//���W�̐ݒ�
	int i;
	for (i = 0; i < GUIDE_MAX; i++) {
		if (g_guide[i].state) {
			MulVector2DF(g_guide[i].pos, MAPCHIP_SIZE);
			AddVector2DF(g_guide[i].pos, Vector2DF{ MAPCHIP_SIZE_HALF,MAPCHIP_SIZE_HALF });
		}
	}
}



//�K�C�h�̕`��
void DrawGuide() {
	int i;
	Vector2DF pos;
	for (i = 0; i < GUIDE_MAX; i++) {
		if (g_guide[i].state) {
			pos = g_guide[i].pos;
			SubVector2DF(pos, OrderGetCameraOffset());
			DrawFormatStringFToHandle(pos.x - GetDrawFormatStringWidthToHandle(g_guide[i].font, "%s", g_guide[i].text) / 2,
				pos.y, g_guide[i].color, g_guide[i].font, "%s", g_guide[i].text);
		}
	}
}

