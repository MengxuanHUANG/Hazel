#include "HZpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include<glm/gtc/matrix_transform.hpp>

namespace Hazel
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> Shader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* s_Data;

	inline glm::mat4 Renderer2D::GetTransform(const glm::vec3& position, const glm::vec2& size, float rotation)
	{
		if (rotation == 0.0f)
		{
			return glm::translate(glm::mat4(1.0f), position)
					*glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		}
		else
		{
			return glm::translate(glm::mat4(1.0f), position)
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
				* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		}
	}


	void Renderer2D::Init()
	{
		HZ_PROFILE_FUNCTION();

		s_Data = new Renderer2DStorage();

		s_Data->VertexArray = VertexArray::Create();
		float square[5 * 4] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		s_Data->VertexArray = VertexArray::Create();
		Ref<VertexBuffer> squareVB;
		squareVB = Hazel::VertexBuffer::Create(square, sizeof(square));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ Hazel::ShaderDataType::Float2, "a_TextCoord" }
		};
		squareVB->SetLayout(layout);
		s_Data->VertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		s_Data->VertexArray->AddIndexBuffer(squareIB);

		uint32_t whiteTextureData = 0xffffffff;

		s_Data->WhiteTexture = Texture2D::Create(1, 1);
		s_Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data->Shader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data->Shader->Bind();
		s_Data->Shader->SetUniformInt("u_Texture", 0);
	}
	void Renderer2D::ShutDown()
	{
		HZ_PROFILE_FUNCTION();

		delete s_Data;
	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		HZ_PROFILE_FUNCTION();

		s_Data->Shader->Bind();
		s_Data->Shader->SetUniformMat4("u_ViewProjection", camera.GetViewProjMatrix());
	}
	void Renderer2D::EndScene()
	{
		HZ_PROFILE_FUNCTION();
	}
	//Pure Color
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawQuad({position.x, position.y, 0.0f}, size, rotation, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		HZ_PROFILE_FUNCTION();

		s_Data->Shader->SetUniformFloat4("u_Color", color);
		s_Data->Shader->SetUniformFloat("u_TilingFactor", 1.0f);
		s_Data->WhiteTexture->Bind();

		s_Data->Shader->SetUniformMat4("u_Transform", GetTransform(position, size, rotation));

		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray);
	}
	//Pure Texture
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor)
	{
		HZ_PROFILE_FUNCTION();

		//Set u_Color
		s_Data->Shader->SetUniformFloat4("u_Color", glm::vec4(1.0f));
		s_Data->Shader->SetUniformFloat("u_TilingFactor", tilingFactor);
		//Bind the texture
		texture->Bind();

		s_Data->Shader->SetUniformMat4("u_Transform", GetTransform(position, size, rotation));

		s_Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(s_Data->VertexArray);
	}
}