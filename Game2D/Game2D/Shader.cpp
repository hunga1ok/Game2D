#include "Shader.h"

Shader::Shader(GLuint shaderId, char * fileVertexShader, char * fileFragmentShader)
{
	m_iID = shaderId;
	Init(fileVertexShader, fileFragmentShader);
}
Shader::~Shader()
{
	glDeleteProgram(m_iProgram);
	glDeleteShader(m_iVertexShader);
	glDeleteShader(m_iFragmentShader);
}

void Shader::Init(char * fileVertexShader, char * fileFragmentShader)
{

	m_iVertexShader = esLoadShader(GL_VERTEX_SHADER, fileVertexShader);

	if (m_iVertexShader == 0)
		return;

	m_iFragmentShader = esLoadShader(GL_FRAGMENT_SHADER, fileFragmentShader);

	if (m_iFragmentShader == 0)
	{
		glDeleteShader(m_iVertexShader);
		return;
	}

	m_iProgram = esLoadProgram(m_iVertexShader, m_iFragmentShader);

	//finding location of uniforms / attributes
	m_iPositionAttribute = glGetAttribLocation(m_iProgram, "a_position");
	m_iUVAttribute= glGetAttribLocation(m_iProgram, "a_uv");
	m_iMatrixUniform = glGetUniformLocation(m_iProgram, "u_MVP");
	m_iTimeUniform = glGetUniformLocation(m_iProgram, "u_time");
	m_iAnimationuniform = glGetUniformLocation(m_iProgram, "u_animation");

	GLint temp = glGetUniformLocation(m_iProgram, "u_texture");
	if (temp != -1)
	{
		m_vTextureUniforms.push_back(temp);
	}
	temp = glGetUniformLocation(m_iProgram, "u_texture2");
	if (temp != -1)
	{
		m_vTextureUniforms.push_back(temp);
	}
	temp = glGetUniformLocation(m_iProgram, "u_texture3");
	if (temp != -1)
	{
		m_vTextureUniforms.push_back(temp);
	}
	temp = glGetUniformLocation(m_iProgram, "u_blendTexture");
	if (temp != -1)
	{
		m_vTextureUniforms.push_back(temp);
	}
}
void Shader::SetID(GLuint shaderId)
{
	this->m_iID = shaderId;
}
GLuint Shader::GetID() const
{
	return this->m_iID;
}
GLuint Shader::GetProgram() const
{
	return m_iProgram;
}
GLint Shader::GetPositionAttribute() const
{
	return m_iPositionAttribute;
}

GLint Shader::GetMatrixUniform() const
{
	return m_iMatrixUniform;
}
GLint Shader::GetUVAttribute() const
{
	return m_iUVAttribute;
}
GLint Shader::GetTimeUniform() const
{
	return m_iTimeUniform;
}

GLint Shader::GetAnimationuniform() const
{
	return m_iAnimationuniform;
}

vector<GLuint> Shader::GetTextureUniforms() const
{
	return m_vTextureUniforms;
}


