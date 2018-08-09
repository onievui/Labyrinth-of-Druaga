#pragma once



//�w�b�_�t�@�C���̓ǂݍ���
#include "GameMain.h"
#include "Shader.h"
#include "GameObjectStruct.h"




//�O���[�o���ϐ��̐錾
int g_timer;					//�V�F�[�_�[�p�^�C�}�[

int g_shader_state;				//�V�F�[�_�[�̏��
ShaderPattern now_shader;		//���ݎg�p���̃V�F�[�_�[

int g_third_screen;				//�V�F�[�_�[�p���
int g_fourth_screen;			//�V�F�[�_�[�p���2

GameObject g_waipu_object;		//���C�v�G�t�F�N�g�p�I�u�W�F�N�g

VERTEX2DSHADER vertex[4];		//�V�F�[�_�p���_



//�v���g�^�C�v�錾
void UpdateShader();
void DrawShader();




//�V�F�[�_�[�̏�����
void InitializeShader() {

	g_timer = 0;
	g_shader_state = 0;
	g_third_screen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_fourth_screen = MakeScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

	//�w�i�I�u�W�F�N�g�̏�����
	g_waipu_object.pos = Vector2DF{ (float)(SCREEN_CENTER_X),(float)(SCREEN_CENTER_Y) };
	g_waipu_object.vel = Vector2DF{ 0,0 };
	g_waipu_object.state = 1;
	g_waipu_object.speed = 0;
	g_waipu_object.angle = 0;
	//g_waipu_object.graph = Graph{ g_sprite[******] , 1.0f, 0.0f };

	int i;
	for (i = 0; i < 4; i++) {
		vertex[i].pos = VGet((i % 2)*(float)(SCREEN_WIDTH), (i / 2)*(float)(SCREEN_HEIGHT), 0);
		vertex[i].rhw = 1.0f;
		vertex[i].dif = GetColorU8(255, 255, 255, 255);
		vertex[i].spc = GetColorU8(0, 0, 0, 0);
		vertex[i].u = vertex[i].su = (float)(i % 2);
		vertex[i].v = vertex[i].sv = (float)(i / 2);

	}

}

//�V�F�[�_�[���g�p�������m�F
BOOL UseShaderCheck() {
	if (g_shader_state) {
		switch (now_shader) {
		case SH_PATTERN_WAIPU_A:
			SetDrawScreen(g_third_screen);
			ClearDrawScreen();
			break;
		case SH_PATTERN_WAIPU_B:
			SetDrawScreen(g_third_screen);
			ClearDrawScreen();
			break;
		}
		return TRUE;
	}
	return FALSE;
}

//�V�F�[�_�[����
void UseShader() {
	UpdateShader();
	DrawShader();
}

//�V�F�[�_�[�̍X�V
void UpdateShader() {
	if (g_shader_state) {
		float t;
		switch (now_shader) {
		//�����郏�C�v�G�t�F�N�g
		case SH_PATTERN_WAIPU_A:
			SetDrawScreen(g_fourth_screen);
			ClearDrawScreen();
			t = (180 - g_timer)/18.0f;
			DrawRectExtendGraphF(g_waipu_object.pos.x - t * 600, g_waipu_object.pos.y - t * 450, 
				g_waipu_object.pos.x + t * 600, g_waipu_object.pos.y + t * 450,
				g_waipu_object.graph.sprite.rect.left, g_waipu_object.graph.sprite.rect.top, 
				g_waipu_object.graph.sprite.rect.right, g_waipu_object.graph.sprite.rect.bottom,
				g_waipu_object.graph.sprite.texture, TRUE);
			SetDrawScreen(DX_SCREEN_BACK);
			SetUseTextureToShader(0, g_third_screen);
			SetUseTextureToShader(1, g_fourth_screen);
			//3�b�ŏI��
			if (g_timer == 180) {
				g_shader_state = 0;
				
			}
			break;
		//����郏�C�v�G�t�F�N�g
		case SH_PATTERN_WAIPU_B:
			SetDrawScreen(g_fourth_screen);
			ClearDrawScreen();
			t = g_timer / 18.0f;
			DrawRectExtendGraphF(g_waipu_object.pos.x - t * 600, g_waipu_object.pos.y - t * 450, 
				g_waipu_object.pos.x + t * 600, g_waipu_object.pos.y + t * 450,
				g_waipu_object.graph.sprite.rect.left, g_waipu_object.graph.sprite.rect.top, 
				g_waipu_object.graph.sprite.rect.right, g_waipu_object.graph.sprite.rect.bottom,
				g_waipu_object.graph.sprite.texture, TRUE);
			SetDrawScreen(DX_SCREEN_BACK);
			SetUseTextureToShader(0, g_third_screen);
			SetUseTextureToShader(1, g_fourth_screen);
			//3�b�ŏI��
			if (g_timer == 180) {
				g_shader_state = 0;
			}
			break;
		}

		g_timer++;
	}
}

//�V�F�[�_�[��`��
void DrawShader() {
	if (g_shader_state) {
		SetUsePixelShader(g_shader[now_shader]);
		DrawPrimitive2DToShader(vertex, 4, DX_PRIMTYPE_TRIANGLESTRIP);
	}
}

//�V�F�[�_�[�̃Z�b�g
void SetShader(ShaderPattern shader) {
	switch (shader) {
	case SH_PATTERN_WAIPU_A:
		now_shader = shader;
		g_shader_state = 1;
		g_timer = 0;
		break;
	case SH_PATTERN_WAIPU_B:
		now_shader = shader;
		g_shader_state = 1;
		g_timer = 0;
		break;
	default:
		MessageBox(NULL, "�V�F�[�_�[�̎g�p�ŕs���Ȓl���n����܂���", "", MB_OK);
		break;
	}
}

//�V�F�[�_�[�̏I������
void FinalizeShader() {
	//�V�F�[�_�[�p�}�X�N�̍폜
	DeleteMask(g_third_screen);
	DeleteMask(g_fourth_screen);
}





