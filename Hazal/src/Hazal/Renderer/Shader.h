#pragma once

#include <string>

namespace Hazal {

	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
	private:
		uint32_t m_RendererID;
	};
}