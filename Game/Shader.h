#pragma once





//�V�F�[�_�[���X�g
enum ShaderPattern {
	SH_PATTERN_WAIPU_A,	//���C�v�G�t�F�N�g�i�B���j
	SH_PATTERN_WAIPU_B,	//���C�v�G�t�F�N�g�i�o���j
	SH_PATTERN_NUM,		//�V�F�[�_�[�̎�ސ�
};




//�V�F�[�_�[�̏�����
void InitializeShader();

//�V�F�[�_�[���g�p�������m�F
BOOL UseShaderCheck();

//�V�F�[�_�[����
void UseShader();

//�V�F�[�_�[�̃Z�b�g
void SetShader(ShaderPattern shader);

//�V�F�[�_�[�̏I������
void FinalizeShader();



