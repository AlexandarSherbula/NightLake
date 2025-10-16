struct VSInput
{
    float2 position : aPosition; // Matches input layout semantic
};

struct VSOutput
{
    float4 position : SV_POSITION; // Required for the pipeline
};

VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.position = float4(input.position, 0.0f, 1.0f);
    return output;
}

struct PSInput
{
    float4 position : SV_POSITION;
};

float4 PSMain(PSInput input) : SV_TARGET
{
    return float4(0.0f, 0.0f, 1.0f, 1.0f); // Blue
}