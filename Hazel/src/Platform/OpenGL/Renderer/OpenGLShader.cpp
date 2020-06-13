#include "HZpch.h"
#include "OpenGLShader.h"

#include<fstream>

#include<glad/glad.h>

#include<glm/gtc/type_ptr.hpp>

namespace Hazel
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
		
		HZ_CORE_ASSERT(false, "Unkown shder type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		HZ_PROFILE_FUNCTION();

		std::string program = ReadFile(filepath);
		auto shaderSources = PreProcess(program);
		Compile(shaderSources);

		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
		size_t lastDot = filepath.rfind('.');
		size_t count = (lastDot == std::string::npos) ? filepath.size() - lastSlash : lastDot - lastSlash;

		m_Name = filepath.substr(lastSlash, count);
	}
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
		:m_Name(name)
	{
		HZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}
	OpenGLShader::~OpenGLShader()
	{
		HZ_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}
	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		HZ_PROFILE_FUNCTION();

		std::string result;
		std::ifstream fin;
		fin.open(filepath, std::ios::in | std::ios::binary);

		if (fin)
		{
			fin.seekg(0, std::ios::end);
			size_t size = fin.tellg();
			if (size != -1)
			{
				result.resize(size);
				fin.seekg(0, std::ios::beg);
				fin.read(&result[0], size);
				fin.close();
			}
		else
		{
			HZ_CORE_ERROR("Could not read from file '{0}'", filepath);
		}
	}
		else HZ_CORE_ERROR("Could not open the file: {0}", filepath);

		return result;
	}
	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& program)
	{
		HZ_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = program.find(typeToken);
		while (pos != std::string::npos)
		{
			size_t eol = program.find_first_of("\r\n", pos);
			HZ_CORE_ASSERT(eol != std::string::npos, "Syntax error!");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = program.substr(begin, eol - begin);
			HZ_CORE_ASSERT(ShaderTypeFromString(type) != 0, "Invaild shader type specified!");

			size_t nextLinePos = program.find_first_not_of("\r\n", eol);
			pos = program.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] =
				program.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? program.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}
	void OpenGLShader::Bind() const
	{
		HZ_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind() const
	{
		HZ_PROFILE_FUNCTION();

		glUseProgram(0);
	}
	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}
	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}
	void OpenGLShader::SetUniformFloat(const std::string& name, float value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat(name, value);
	}
	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}
	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		HZ_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}
	void OpenGLShader::UploadUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}
	void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}
	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, value.x, value.y);
	}
	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, value.x, value.y, value.z);
	}
	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
	void OpenGLShader::Compile(std::unordered_map<GLenum, std::string> shaderSources)
	{
		HZ_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		HZ_CORE_ASSERT(shaderSources.size() <= 2, "Over Max. Number of Shaders!");
		std::array<GLenum, 2> glShaderIDs;

		int glShadreIDIndex = 0;

		for (auto& key : shaderSources)
		{
			GLenum shaderType = key.first;
			const std::string& source = key.second;
			
			GLuint shader = glCreateShader(shaderType);

			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			// Compile the vertex shader
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(shader);

				HZ_CORE_ERROR("{0}", infoLog.data());
				HZ_CORE_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShadreIDIndex++] = shader;
		}
		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : glShaderIDs) glDeleteShader(id);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Shader Link failure!");

			// In this simple program, we'll just leave
			return;
		}

		// Always detach shaders after a successful link.
		for (auto id : glShaderIDs) glDetachShader(program, id);

		m_RendererID = program;

	}
}