#pragma once
#include <string>
#include <iostream>
#include <glad/glad.h>
namespace rend {
	class ShaderProgramm {
	public:
		ShaderProgramm(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgramm();
		bool isCompiled() { return m_isCompiled; }
		void use() const;

		ShaderProgramm() = delete;
		ShaderProgramm(ShaderProgramm&) = delete;
		ShaderProgramm& operator = (const ShaderProgramm&) = delete;
		ShaderProgramm& operator = (ShaderProgramm&& ShaderProgramm) noexcept;
		ShaderProgramm (ShaderProgramm&& ShaderProgramm) noexcept;
	private:
		bool createShader(const std::string& source, const GLenum ShaderType, GLuint& ShaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	};
}