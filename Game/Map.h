//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Map.h
//!
//! @brief  �}�b�v�֘A�̃w�b�_�t�@�C��
//!
//! @date   2018/08/
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

#pragma once


//�w�b�_�t�@�C���̓ǂݍ���
#include "GameObjectStruct.h"



//�}�b�v�̏�����
void InitializeMap();

//�}�b�v�̕`��
void DrawMap();

//�}�b�v���擾����
MapAll GetMap();

//�w�肵�����W���ʉߕs�}�X���ǂ���
BOOL IsMapPosWall(float x, float y);



