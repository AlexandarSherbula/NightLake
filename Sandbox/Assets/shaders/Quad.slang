float4 GetSampledTexture(float2 texCoord, int texIndex = 0);

struct VS_INPUT
{
    float3 inPos : aPosition;
    float4 inColor : aColor;
    float2 inTexCoord : aTexCoord;
    int inTexIndex : aTexIndex;
};

struct Camera
{
    float4x4 mvp;
}

ConstantBuffer<Camera> camera : register(b0);
Texture2D textures[32] : register(t0);
SamplerState samplerState : register(s0);

struct VS_OUTPUT
{
    float4 outPos : SV_Position;
    float4 outColor : COLOR;
    float2 outTexCoord : TEXCOORD0;
    int outTexIndex : TEXCOORD1;
};

[shader("vertex")]
VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;
    output.outPos = mul(float4(input.inPos, 1.0), camera.mvp);
    output.outColor = input.inColor;
    output.outTexCoord = input.inTexCoord;
    output.outTexIndex = input.inTexIndex;
    return output;
}

[shader("pixel")]
float4 PSMain(VS_OUTPUT input) : SV_Target
{
    return GetSampledTexture(input.outTexCoord, input.outTexIndex) * input.outColor;
}