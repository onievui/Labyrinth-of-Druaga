#pragma once




//�w�b�_�t�@�C���̓ǂݍ���
#include "Mediator.h"




//�O���[�o���ϐ��̐錾
static StageId g_select_stage;	//�I�𒆂̃X�e�[�W




//�O���[�o���ϐ��̏�����
void InitializeMediator() {
	g_select_stage = (StageId)-1;
	
}

//�I�𒆂̃X�e�[�W�̐ݒ�
void SetSelectStage(StageId stageId) {
	g_select_stage = stageId;
}

//�I�𒆂̃X�e�[�W�̎擾
StageId GetSelectStage() {
	return g_select_stage;
}

