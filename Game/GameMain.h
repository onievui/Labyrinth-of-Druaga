//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//!
//! @date   2018/08/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once
#include "Graphic.h"
#include "GameObjectStruct.h"
#include "GameDefine.h"
#include "GameEnum.h"
#include "Key.h"
#include "Sound.h"



// �萔�̒�` ==============================================================

// <�V�X�e��> ----------------------------------------------------------
#define GAME_TITLE "�h���A�[�K�̖��{"        // �Q�[���^�C�g��


// <���> --------------------------------------------------------------
#define SCREEN_WIDTH    (800)                  // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (600)                  // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)




// �֐��̐錾 ==============================================================

// �Q�[���̏���������
void InitializeGame(void);

// �Q�[���̍X�V����
void UpdateGame(void);

// �Q�[���̕`�揈��
void RenderGame(void);

// �Q�[���̏I������
void FinalizeGame(void);

// �V�[���̕ύX�v��
void RequestScene(const SceneId sceneId);


