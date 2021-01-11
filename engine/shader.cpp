#include "shader.h"

#include "debug.h"

#include "SDL_gpu.h"
#include "window.h"

#include <SDL_rwops.h>

// We want to read shader files using SDL_RWops for consistency with all the other asset files
// This helper class makes sure we cleanup after ourselves using RAII
struct RWopsFileReader {
	char* contents;
	RWopsFileReader(const char* path) {
		SDL_RWops* rwops = SDL_RWFromFile(path, "r");

		if (rwops == NULL) {
			contents = nullptr;
			return;
		}

		SDL_RWseek(rwops, 0, SEEK_SET);
		size_t length = SDL_RWseek(rwops, 0, SEEK_END);
		SDL_RWseek(rwops, 0, SEEK_SET);
		contents = (char*)SDL_malloc(length+1); //+1 to later add a null-terminator
		size_t read = SDL_RWread(rwops, contents, 1, length);
		SDL_RWclose(rwops);

		if (read != length) {
			SDL_free(contents);
			contents = nullptr;
		}

		contents[length] = 0; //null-terminate
	}
	~RWopsFileReader() {
		if (contents != nullptr) {
			SDL_free(contents);
		}
	}
};

void Shader::loadAndAttach(GPU_ShaderEnum type, const char* path) {

	std::stringstream source;
	GPU_Renderer* renderer = GPU_GetCurrentRenderer();
	if (renderer->shader_language == GPU_LANGUAGE_GLSL)
	{
		if (renderer->max_shader_version >= 330) {
			source << "#version 330\n";
		} else {
			source << "#version 130\n";
		}
	}
	else if (renderer->shader_language == GPU_LANGUAGE_GLSLES)
	{
		if (renderer->max_shader_version >= 300) {
			source << "#version 300 es\n";
		} else {
			source << "#version 200 es\n";
		}

		if (type == GPU_FRAGMENT_SHADER) {
			source << "#ifdef GL_FRAGMENT_PRECISION_HIGH\n\
precision highp float;\n\
#else\n\
precision mediump float;\n\
#endif\n\
precision mediump int;\n";
		} else {
			source << "precision highp float;\nprecision mediump int;\n";
		}
	}

	int prefix_lines = 0;
	for (char c : source.str()) {
		if (c == '\n') prefix_lines++;
	}

	RWopsFileReader shaderfile(path);
	if (shaderfile.contents == nullptr) {
		Debug::out << "Could not read shader from '" << path << "': " << SDL_GetError();
		return;
	}

	source << shaderfile.contents;

	int id = GPU_CompileShader(type, source.str().c_str());
	if (id == 0) {
		Debug::out << path << " failed to compile";
		Debug::out << "Note: Following line numbers offset by: " << prefix_lines;
		Debug::out << "--error begin--";
		Debug::out << GPU_GetShaderMessage() << "--error end--";
	}
	GPU_AttachShader(program, id);
}

void Shader::Load(const char* vertex_path, const char* geometry_path, const char* fragment_path) {
	uniforms.clear();
	program = GPU_CreateShaderProgram();
	if (vertex_path) {
		loadAndAttach(GPU_ShaderEnum::GPU_VERTEX_SHADER, vertex_path);
	} else {
		GPU_AttachShader(program, Window::screenTarget->context->default_textured_vertex_shader_id);
	}
	if (geometry_path) {
		loadAndAttach(GPU_ShaderEnum::GPU_GEOMETRY_SHADER, geometry_path);
	}
	if (fragment_path) {
		loadAndAttach(GPU_ShaderEnum::GPU_FRAGMENT_SHADER, fragment_path);
	} else {
		GPU_AttachShader(program, Window::screenTarget->context->default_textured_fragment_shader_id);
	}

	std::stringstream paths;
	if (vertex_path) {
		paths << vertex_path << " ";
	}
	if (geometry_path) {
		paths << geometry_path << " ";
	}
	if (fragment_path) {
		paths << fragment_path << " ";
	}
	shaderFilePaths = paths.str();

	if (GPU_LinkShaderProgram(program) == GPU_FALSE) {
		Debug::out << shaderFilePaths << " failed to link";
		Debug::out << "--error begin--";
		Debug::out << GPU_GetShaderMessage() << "--error end--";
	}
	block = GPU_LoadShaderBlock(program, "gpu_Vertex", "gpu_TexCoord", "gpu_Color", "gpu_ModelViewProjectionMatrix");
}

int Shader::GetUniformLocation(const char* name, bool warnIfNotFound) {
	std::map<std::string, int>::const_iterator it = uniforms.find(name);
	if (it != uniforms.end()) {
		return it->second;
	}
	else {
		int location = GPU_GetUniformLocation(program, name);
		uniforms.insert(std::make_pair(name, location));
		if (location == -1 && warnIfNotFound) {
			Debug::out << "Uniform \"" << name << "\" not found in shader: " << shaderFilePaths;
		}

		return location;
	}
}
