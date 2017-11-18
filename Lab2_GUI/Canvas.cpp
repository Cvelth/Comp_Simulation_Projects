#include "Canvas.hpp"
#define _USE_MATH_DEFINES
#include "Math.h"
#include <QMatrix4x4>
Canvas::Canvas(QWidget *parent)	: QOpenGLWidget(parent), m_projection(nullptr), was_initialized(false) {
	insertNet(std::make_shared<Net>(1.f));
}
Canvas::~Canvas() {
	if (m_projection) delete m_projection;
}
void Canvas::insertNet(NetType const net) {
	m_nets.insert(std::make_pair(net, std::make_tuple(false, 0, 0, 0)));
}
constexpr size_t Size = 24;
constexpr size_t Coords = 2;
float res[Size * Coords];
void Canvas::initializeNets() {
	for (auto& it : m_nets)
		if (!std::get<0>(it.second)) {
			glGenBuffers(1, &std::get<1>(it.second));
			glBindBuffer(GL_ARRAY_BUFFER, std::get<1>(it.second));
			size_t i = 0;
			for (float f = 0.f; f <= M_PI * 2.1f; f += M_PI / Size * 2) {
				res[i++] = 0.3f * cosf(f);
				res[i++] = 0.3f * sinf(f);
			}
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Size * Coords, res, GL_STATIC_DRAW);
			std::get<0>(it.second) = true;
		}
}
void Canvas::draw(std::pair<NetType const, NetInfo>& net) {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, std::get<1>(net.second));
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*) 0);

	glDrawArrays(GL_LINE_LOOP, 0, Size);
	glDisableVertexAttribArray(0);
}

const char* vertex_source = ""
	"#version 330 core\n"
	""
	"layout(location = 0) in vec2 position;"
	""
	"out vec3 fragment_color;"
	""
	"uniform mat4 projection;"
	"uniform vec3 color;"
	"uniform vec2 translation;"
	""
	"void main(){"
	"	gl_Position = projection * vec4(position + translation, 0.0, 1.0);"
	"	fragment_color = color;"
	"}";
const char* fragment_source = ""
"#version 330 core\n"
	""
	"in vec3 fragment_color;"
	"out vec3 color;"
	""
	"void main() {"
	"	color = fragment_color;"
	"}";
GLuint Canvas::compileSource(ShaderType type, const char* sourceText) {
	const GLchar* source = static_cast<const GLchar*>(sourceText);
	if (source == "") throw std::exception("The source string or file is empty.");

	GLuint id;
	if (type == ShaderType::Vertex)
		id = glCreateShader(GL_VERTEX_SHADER);
	else if (type == ShaderType::Fragment)
		id = glCreateShader(GL_FRAGMENT_SHADER);
	else
		throw std::exception("Enum class ShaderType seems to be broken.");

	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);

	GLint isCompiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

	if (!isCompiled) {
		GLsizei len;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetShaderInfoLog(id, len, &len, log);
		throw std::exception(("Shader compilation error: " + std::string(log)).c_str());
		delete[] log;
	}
	return id;
}
GLuint Canvas::link(const std::initializer_list<GLuint>& shaders) {
	if (shaders.size() == 0u)
		throw std::exception("There is no shaders to attach");

	GLuint id = glCreateProgram();

	for (auto shader : shaders)
		glAttachShader(id, shader);

	glLinkProgram(id);

	GLint isLinked;
	glGetProgramiv(id, GL_LINK_STATUS, &isLinked);
	if (!isLinked) {
		GLsizei len;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(id, len, &len, log);
		throw std::exception(("Program linking error: " + std::string(log)).c_str());
		delete[] log;
	}
	return id;
}
void Canvas::initializeGL() {
	initializeOpenGLFunctions();
	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);
	glLineWidth(1.5);

	m_program = link({compileSource(ShaderType::Vertex, vertex_source),
						  compileSource(ShaderType::Fragment, fragment_source)});
	glUseProgram(m_program);

	GLint loc = glGetUniformLocation(m_program, "color");
	if (loc != -1) {
		glUniform3f(loc, 1.f, 0.f, 0.f);
	} else
		throw std::exception("Something wrong with uniform allocation.");

	was_initialized = true;
	resizeGL(width(), height());
}
void Canvas::resizeGL(int w, int h) {
	if (was_initialized) {
		glViewport(0, 0, w, h);
		if (m_projection) delete m_projection;
		m_projection = new QMatrix4x4();
		auto ar = float(w) / h;
		m_projection->ortho(
			ar > 1.f ? -ar : -1.f,
			ar > 1.f ? ar : 1.f,
			+1.f / (ar > 1.f ? 1.f : ar),
			-1.f / (ar > 1.f ? 1.f : ar),
			-1.f, +1.f
		);

		GLint loc = glGetUniformLocation(m_program, "projection");
		if (loc != -1) {
			glUniformMatrix4fv(loc, 1, false, m_projection->data());
		} else
			throw std::exception("Something wrong with uniform allocation.");
	}
}
void Canvas::paintGL() {
	initializeNets();

	glClear(GL_COLOR_BUFFER_BIT);
	for (auto& it : m_nets)
		draw(it);
}