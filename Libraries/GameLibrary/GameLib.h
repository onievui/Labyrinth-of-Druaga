//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameLib.h
//!
//! @brief  �Q�[������p���C�u�����̃w�b�_�t�@�C��
//!
//! @date   2015/6/10
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <DxLib.h>




// �^�̒�` ================================================================
typedef int HGRP;    // �O���t�B�b�N�n���h��     
typedef int HSND;    // �T�E���h�n���h��
typedef int HFNT;    // �t�H���g�n���h��
typedef int HNET;    // �l�b�g���[�N�n���h�� 


// �萔�̒�` ==============================================================

#define EXIT_KEY (KEY_INPUT_ESCAPE)    // �����I���L�[


// <�F�R�[�h(�W���J���[16�F)> ----------------------------------------------
enum ColorCode : unsigned int
{
	COLOR_BLACK = 0xFF000000,    // ���F
	COLOR_NAVY = 0xFF000080,    // �Z���F
	COLOR_GREEN = 0xFF008000,    // �ΐF
	COLOR_TEAL = 0xFF008080,    // �ΐF
	COLOR_MAROON = 0xFF800000,    // �}���[���F
	COLOR_PURPLE = 0xFF800080,    // ���F
	COLOR_OLIVE = 0xFF808000,    // �I���[�u�F
	COLOR_GRAY = 0xFF808080,    // �D�F
	COLOR_SILVER = 0xFFC0C0C0,    // ��F
	COLOR_BLUE = 0xFF0000FF,    // �F
	COLOR_LIME = 0xFF00FF00,    // ���C���O���[���F
	COLOR_AQUA = 0xFF00FFFF,    // ���F
	COLOR_RED = 0xFFFF0000,    // �ԐF
	COLOR_FUCHSIA = 0xFFFF00FF,    // �Ԏ��F
	COLOR_YELLOW = 0xFFFFFF00,    // ���F
	COLOR_WHITE = 0xFFFFFFFF,    // ���F
};
