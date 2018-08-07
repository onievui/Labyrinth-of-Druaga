#pragma once





//シェーダーリスト
enum ShaderPattern {
	SH_PATTERN_WAIPU_A,	//ワイプエフェクト（隠す）
	SH_PATTERN_WAIPU_B,	//ワイプエフェクト（出す）
	SH_PATTERN_NUM,		//シェーダーの種類数
};




//シェーダーの初期化
void InitializeShader();

//シェーダーを使用中かを確認
BOOL UseShaderCheck();

//シェーダー処理
void UseShader();

//シェーダーのセット
void SetShader(ShaderPattern shader);

//シェーダーの終了処理
void FinalizeShader();



