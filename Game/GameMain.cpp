//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  �Q�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/


#pragma once



// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"

#include <assert.h>

#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneStageSelect.h"
#include "ScenePlay.h"
#include "SceneResult.h"

#include "Shader.h"

#include "Mediator.h"


// �萔�̒�` ==============================================================




// �O���[�o���ϐ��̒�` ====================================================
SceneId g_active_scene;	// ���ݎ��s���̃V�[��
SceneId g_next_scene;	// ���̃V�[��


//�e�V�[���̏����������̊֐��|�C���^
void(*g_initialize_scene[SCENE_NUM])(void) = {
	 InitializeLogo,
	 InitializeTitle,
	 InitializeStageSelect,
	 InitializePlay,
	 InitializeResult
};

//�e�V�[���̍X�V�����̊֐��|�C���^
void(*g_update_scene[SCENE_NUM])(void) = {
	UpdateLogo,
	UpdateTitle,
	UpdateStageSelect,
	UpdatePlay,
	UpdateResult
};

//�e�V�[���̕`�揈���̊֐��|�C���^
void(*g_render_scene[SCENE_NUM])(void) = {
	RenderLogo,
	RenderTitle,
	RenderStageSelect,
	RenderPlay,
	RenderResult
};

//�e�V�[���̏I�������̊֐��|�C���^
void(*g_finalize_scene[SCENE_NUM])(void) = {
	FinalizeLogo,
	FinalizeTitle,
	FinalizeStageSelect,
	FinalizePlay,
	FinalizeResult
};




// �֐��̐錾 ==============================================================
// ���J�֐�
void InitializeGame(void);  // �Q�[���̏���������
void UpdateGame(void);      // �Q�[���̍X�V����
void RenderGame(void);      // �Q�[���̕`�揈��
void FinalizeGame(void);    // �Q�[���̏I������

void RequestScene(const SceneId sceneId);	 // �V�[���̕ύX�v��

// ����J�֐�
void InitializeScene(const SceneId sceneId);  // �V�[���̏���������
void UpdateScene(const SceneId sceneId);      // �V�[���̍X�V����
void RenderScene(const SceneId sceneId);      // �V�[���̕`�揈��
void FinalizeScene(const SceneId sceneId);    // �V�[���̏I������





// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �Q�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeGame(void)
{
	//���\�[�X�̓ǂݍ��݁A������
	LoadResources();
	InitializeSprite();
	
	//�V�F�[�_�[�̏�����
	InitializeShader();

	//�����V�[����Ԃ̃Z�b�g
	g_active_scene = SCENE_NONE;
	g_next_scene = SCENE_LOGO;

	//Mediator�̏�����
	InitializeMediator();
	
}



//----------------------------------------------------------------------
//! @brief �Q�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//�L�[���͂̍X�V
	if (GetHitKeyStateAll_2() != 0) {
		MessageBox(NULL, "�L�[���͂Ɏ��s���܂���", "", MB_OK);
	}

	//�����t���O�̃��Z�b�g
	ResetSounds();


	// �V�[���ύX���K�v���ǂ������`�F�b�N
	if (g_next_scene != SCENE_NONE) {
		FinalizeScene(g_active_scene);	//���̃V�[���̏I���������s��
		InitializeScene(g_next_scene);	//�V�����V�[���̏������������s��
		g_active_scene = g_next_scene;	//�V�[���̑I����Ԃ𔽉f������
		g_next_scene = SCENE_NONE;
	}

	//�������̃V�[����`��
	UpdateScene(g_active_scene);

	
	//�����̍Đ�
	PlaySE();
	PlayBGM();

}



//----------------------------------------------------------------------
//! @brief �Q�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderGame(void)
{
	//�V�F�[�_�[�̕`�揀��
	UseShaderCheck();

	RenderScene(g_active_scene);

	//�V�F�[�_�[�̕`��
	UseShader();
	
}



//----------------------------------------------------------------------
//! @brief �Q�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	FinalizeScene(g_active_scene);

	FinalizeShader();

	DeleteResources();

}


// �V�[���̕ύX�v��
void RequestScene(const SceneId sceneId)
{
	g_next_scene = sceneId;
}


// �V�[���̏���������
void InitializeScene(SceneId sceneId)
{
	//�Ӑ}���Ȃ��V�[�����Ă΂ꂽ�Ƃ��ɃG���[�������s��
	if (sceneId < SCENE_NONE || sceneId >= SCENE_NUM) {
		assert(FALSE);
		return;
	}

	//�V�[�������I���łȂ���΃V�[���̏������������s��
	if (sceneId != SCENE_NONE) {
		(g_initialize_scene[sceneId])();
	}
}


// �V�[���̍X�V����
void UpdateScene(const SceneId sceneId)
{
	//�Ӑ}���Ȃ��V�[�����Ă΂ꂽ�Ƃ��ɃG���[�������s��
	if (sceneId < SCENE_NONE || sceneId >= SCENE_NUM) {
		assert(FALSE);
		return;
	}

	//�V�[�������I���łȂ���΃V�[���̍X�V�������s��
	if (sceneId != SCENE_NONE) {
		g_update_scene[sceneId]();
	}
}


// �V�[���̕`�揈��
void RenderScene(const SceneId sceneId)
{
	//�Ӑ}���Ȃ��V�[�����Ă΂ꂽ�Ƃ��ɃG���[�������s��
	if (sceneId < SCENE_NONE || sceneId >= SCENE_NUM) {
		assert(FALSE);
		return;
	}

	//�V�[�������I���łȂ���΃V�[���̕`�揈�����s��
	if (sceneId != SCENE_NONE) {
		g_render_scene[sceneId]();
	}
}


// �V�[���̏I������
void FinalizeScene(const SceneId sceneId)
{
	//�Ӑ}���Ȃ��V�[�����Ă΂ꂽ�Ƃ��ɃG���[�������s��
	if (sceneId < SCENE_NONE || sceneId >= SCENE_NUM) {
		assert(FALSE);
		return;
	}

	//�V�[�������I���łȂ���΃V�[���̏I���������s��
	if (sceneId != SCENE_NONE) {
		g_finalize_scene[sceneId]();
	}
}

