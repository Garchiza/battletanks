#include "ShaderProgramm.h"
namespace rend {
	ShaderProgramm::ShaderProgramm(const std::string& vertexShader, const std::string& fragmentShader) {
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)){
			std::cerr << "VERTEX SHADER Compile-time error";
			return;
		}
		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
			std::cerr << "FRAGMENT SHADER Compile-time error";
			glDeleteShader(vertexShaderID);
			return;
		}

		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infolog[1024];
			glGetShaderInfoLog(m_ID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Link-time error:\n" << infolog << "\n";
		}
		else {
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	bool ShaderProgramm::createShader(const std::string& source, const GLenum ShaderType, GLuint& ShaderID) {
		ShaderID = glCreateShader(ShaderType);
		const char* code = source.c_str();
		glShaderSource(ShaderID, 1, &code, nullptr);
		glCompileShader(ShaderID);

		GLint success;
		glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			GLchar infolog[1024];
			glGetShaderInfoLog(ShaderID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Compile-time error:\n" << infolog << "\n";
			return 0;
		}
		return 1;
	}
	ShaderProgramm::~ShaderProgramm() {
		glDeleteProgram(m_ID);
	}
	void ShaderProgramm::use() const {
		glUseProgram(m_ID);
	}
	ShaderProgramm& ShaderProgramm::operator=(ShaderProgramm&& ShaderProgramm) noexcept {
		glDeleteProgram(m_ID);
		m_ID = ShaderProgramm.m_ID;
		m_isCompiled = ShaderProgramm.m_isCompiled;

		ShaderProgramm.m_ID = 0;
		ShaderProgramm.m_isCompiled = 0;
		return *this;
	}
	ShaderProgramm::ShaderProgramm(ShaderProgramm&& ShaderProgramm) noexcept {
		m_ID = ShaderProgramm.m_ID;
		m_isCompiled = ShaderProgramm.m_isCompiled;

		ShaderProgramm.m_ID = 0;
		ShaderProgramm.m_isCompiled = 0;
	}
}