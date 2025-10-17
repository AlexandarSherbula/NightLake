struct VS_INPUT
{
    float3 inPos : aPosition;
    float4 inColor : aColor;
    float2 inTexCoord : aTexCoord;
};

struct VS_OUTPUT
{
    float4 outPos : SV_POSITION;
    float4 outColor : COLOR;
    float2 outTexCoord : TEXCOORD0;
};

VS_OUTPUT VSMain(VS_INPUT input)
{
    VS_OUTPUT output;
    output.outPos = float4(input.inPos, 1.0);
    output.outColor = input.inColor;
    output.outTexCoord = input.inTexCoord;
    return output;
}

struct PS_INPUT
{
    float4 inPos : SV_POSITION;
    float4 inColor : COLOR;
    float2 inTexCoord : TEXCOORD;
};

Texture2D objTexture[32] : TEXTURE : register(t0);
SamplerState objSampler : SAMPLER : register(s0);

float4 PSMain(PS_INPUT input) : SV_TARGET
{
    float4 pixel = objTexture[0].Sample(objSampler, input.inTexCoord) * input.inColor;
    return pixel;
}