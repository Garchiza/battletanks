#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <sstream>
#include <fstream>

namespace rend {
	class ShaderProgramm;
}

class ResourceManager {
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator= (const ResourceManager&) = delete;
	ResourceManager& operator= (ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	std::shared_ptr<rend::ShaderProgramm> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<rend::ShaderProgramm> getShaderProgram(const std::string& shaderName);
private:
	std::string getFileString(const std::string& relFilePath) const;
	typedef std::map<std::string, std::shared_ptr<rend::ShaderProgramm>> ShaderProgramsMap;
	ShaderProgramsMap m_shaderPrograms;

	std::string m_path;
};