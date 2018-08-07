
// �s�N�Z���V�F�[�_�[�̓���
struct PS_INPUT
{
    float4 DiffuseColor       : COLOR0 ;
    float4 SpecularColor      : COLOR1 ;
    float2 TextureCoord0      : TEXCOORD0 ;
    float2 TextureCoord1      : TEXCOORD1 ;
} ;

// �s�N�Z���V�F�[�_�[�̏o��
struct PS_OUTPUT
{
    float4 Output             : COLOR0 ;
} ;

// �`�悷��e�N�X�`��
sampler Texture  : register( s0 ) ;
sampler Texture2 : register( s1 ) ;

PS_OUTPUT main( PS_INPUT PSInput )  //���͒l
{
    PS_OUTPUT PSOutput ;
    float4 TextureColor;
	float4 TextureColor2;
    TextureColor = tex2D( Texture , PSInput.TextureCoord0 );
	TextureColor2 = tex2D(Texture2, PSInput.TextureCoord0);

	if (TextureColor2.r == 0 && TextureColor2.g == 0 && TextureColor2.b == 0) {
		TextureColor.rgb = 0;
	}
    

    PSOutput.Output = TextureColor;
    return PSOutput;
}