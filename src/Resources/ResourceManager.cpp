#include "ResourceManager.h"
#include "../Renderer/ShaderProgramm.h"

ResourceManager::ResourceManager(const std::string& executablePath) {
	std::size_t found = executablePath.find_last_of("/\\");
	m_path = executablePath.substr(0, found);
}
std::string ResourceManager::getFileString(const std::string& relFilePath) const {
	std::ifstream f;
	f.open(m_path + "/" + relFilePath.c_str(), std::ios::in | std::ios::binary);
	if (!f.is_open()) {
		std::cout << "Failed to pen file: " << m_path << "/" << relFilePath.c_str() << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

std::shared_ptr<rend::ShaderProgramm> ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath) {
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty()) {
		std::cout << "Vertex shader path is empty!" << std::endl;
		return nullptr;
	}
	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty()) {
		std::cout << "Fragment shader path is empty!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<rend::ShaderProgramm>& newShader = m_shaderPrograms.emplace(shaderName, std::make_shared<rend::ShaderProgramm>(vertexString, fragmentString)).first->second;
	if (newShader->isCompiled()) {
		return newShader;
	}
	std::cout << "Cant load shader programm :{";
	std::cout << "\nVertex: " << vertexPath << "\nFragment: " << fragmentPath << std::endl;
	return nullptr;
}

std::shared_ptr<rend::ShaderProgramm> ResourceManager::getShaderProgram(const std::string& shaderName) {
	ShaderProgramsMap::const_iterator it = m_shaderPrograms.find(shaderName);
	if (it != m_shaderPrograms.end()) {
		return it->second;
	}
	std::cout << "Can not find shader program: " << shaderName << std::endl;
	return nullptr;
}