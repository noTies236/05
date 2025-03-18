#include <glad/glad.h>

namespace Pipeline {
	std::string LoadShaderAsString(const std::string& fileName);
	void		VertexSpecification();
	GLuint		CompileShaderProgram(GLuint type, const std::string& source);
	GLuint		CreateShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
	void		GraphcisPipiline();
	void        PreDraw();
	void        Draw();
}