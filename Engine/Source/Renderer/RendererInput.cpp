#include "aio_pch.hpp"
#include "RendererInput.hpp"
#include "Renderer.hpp"

namespace aio
{
    Ref<VertexBuffer> QuadRenderer::vertexBuffer = nullptr;
    Ref<IndexBuffer>  QuadRenderer::indexBuffer = nullptr;
    Ref<VertexInput>  QuadRenderer::vertexInput = nullptr;
    Ref<Shader>       QuadRenderer::shader = nullptr;
    Ref<Texture>      QuadRenderer::WhiteTexture = nullptr;

    uint32_t QuadRenderer::QuadCount = 0;
    uint32_t QuadRenderer::IndexCount = 0;
    uint32_t QuadRenderer::TextureSlotIndex = 0;
    uint32_t QuadRenderer::DrawingCount = 0;

    std::array<uint32_t, QuadRenderer::MaxTextureSlots> QuadRenderer::TextureIDs = { 0 };

    QuadVertex* QuadRenderer::CurrentVertexPtr = nullptr;
    QuadVertex* QuadRenderer::baseVertexBuffer = nullptr;

    void QuadRenderer::Init()
    {
        const uint32_t maxVertexCount = 4 * MaxQuadsPerBatch;
        const uint32_t maxIndexCount = 6 * MaxQuadsPerBatch;

        baseVertexBuffer = new QuadVertex[maxVertexCount];

        uint32_t* indices = new uint32_t[maxIndexCount];

        int32_t indexOffset = 0;
        for (size_t i = 0; i < MaxQuadsPerBatch; i++)
        {
            indices[i * 6 + 0] = 0 + indexOffset;
            indices[i * 6 + 1] = 1 + indexOffset;
            indices[i * 6 + 2] = 2 + indexOffset;
            indices[i * 6 + 3] = 2 + indexOffset;
            indices[i * 6 + 4] = 3 + indexOffset;
            indices[i * 6 + 5] = 0 + indexOffset;

            indexOffset += 4;
        }
        vertexInput = VertexInput::Create();
        vertexBuffer = VertexBuffer::Create(maxVertexCount * sizeof(QuadVertex));
        indexBuffer = IndexBuffer::Create(indices, maxIndexCount);
        delete[] indices;

        BufferLayout layout =
        {
            {ShaderDataType::Float3, "aPosition" },
            {ShaderDataType::Float4, "aColor"    },
            {ShaderDataType::Float2, "aTexCoord" },
            {ShaderDataType::Int,    "aTexIndex" }
        };

        vertexBuffer->SetLayout(layout);
        vertexInput->SetVertexBuffer(vertexBuffer);
        vertexInput->SetIndexBuffer(indexBuffer);

        shader = Shader::Create(ASSETS_DIRECTORY / "shaders" / "Quad.slang", vertexInput);

        TextureSpecification texSpec;

        WhiteTexture = Texture::Create(texSpec);
        TextureIDs[TextureSlotIndex] = WhiteTexture->GetID();
        TextureSlotIndex++;
    }

    void QuadRenderer::StartNewBatch()
    {
        QuadCount = 0;
        IndexCount = 0;
        TextureSlotIndex = 1;
        DrawingCount = 0;

        CurrentVertexPtr = baseVertexBuffer;
    }

    void QuadRenderer::SubmitBatch()
    {
        if (QuadCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)CurrentVertexPtr - (uint8_t*)baseVertexBuffer);
            vertexBuffer->SetData(baseVertexBuffer, dataSize);

            vertexInput->Bind();
            shader->Bind();
            WhiteTexture->Bind(0);

            Renderer::Backend()->DrawIndexed(IndexCount);
            DrawingCount++;
            Renderer::Stats.DrawQuad++;

            WhiteTexture->Unbind();
            shader->Unbind();
            vertexInput->Unbind();
        }
        StartNewBatch();
    }

    void QuadRenderer::End()
    {
        delete[] baseVertexBuffer;
    }
}