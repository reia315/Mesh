#pragma once
#pragma once

#include "Matrix4.h"
#include "SimpleMesh.h"

class SimpleMeshShader
	: public SimpleMesh::Shader
{
public:

	SimpleMeshShader(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	~SimpleMeshShader();

	void load(const std::string& fileName);

	void world(const Matrix4& mat);

	void view(const Matrix4& mat);

	void projection(const Matrix4& mat);

	void clear();

	virtual void begin() override;

	virtual void end() override;

	virtual void material(const SimpleMesh::Material& material) override;

	SimpleMeshShader(const SimpleMeshShader& other) = delete;
	SimpleMeshShader& operator = (const SimpleMeshShader& other) = delete;

private:

	ID3D11Device* m_device{ nullptr };
	ID3D11DeviceContext* m_deviceContext{ nullptr };
	ID3D11Buffer* m_constantBuffer{ nullptr };
	ID3D11VertexShader* m_vertexShader{ nullptr };
	ID3D11PixelShader* m_pixelShader{ nullptr };
	ID3D11InputLayout* m_vertexLayout{ nullptr };

	struct BufferData
	{
		Matrix4 world;

		Matrix4 view;

		Matrix4 projection;
	};

	BufferData m_data;
};