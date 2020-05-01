#pragma once

#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"
#include "Texture2D.h"
#include <vector>
#include <string>
#include <d3d11.h>

class SimpleMesh
{
public:

	struct Material
	{
		Color ambient;
		Color diffuse;
		Color specular;
		Color emission;
		float shiniess;
		char textureFileName[128];
		Texture2D* texture;
	};

	struct Subset
	{
		int material;
		int start;
		int count;
	};

	struct Vertex
	{
		Vector3 point;
		Vector3 normal;
		Vector2 texcoord;
	};

	class Shader
	{
	public:

		virtual ~Shader() = default;

		virtual void begin() = 0;

		virtual void end() = 0;

		virtual void material(const SimpleMesh::Material& material) = 0;
	};

public:

	SimpleMesh(ID3D11Device* device, ID3D11DeviceContext* deviceContext);

	~SimpleMesh();

	void load(const std::string& fileName);

	void draw(SimpleMesh::Shader& shader) const;

	void clear();

	SimpleMesh(const SimpleMesh& other) = delete;
	SimpleMesh& operator = (const SimpleMesh& other) = delete;

private:

	ID3D11Buffer* createBuffer(UINT bind, UINT size, const void* data);

private:

	ID3D11Device* m_device{ nullptr };

	ID3D11DeviceContext* m_deviceContext{ nullptr };

	std::vector<Material> m_materials;

	std::vector<Subset> m_subsets;

	ID3D11Buffer* m_indices{ nullptr };

	ID3D11Buffer* m_vertices{ nullptr };
};