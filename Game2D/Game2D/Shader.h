#pragma once
#include "Utilities/utilities.h"
#include <vector>
using namespace std;
class Shader
{
public:
	Shader(GLuint shaderId, char * fileVertexShader, char * fileFragmentShader);
	~Shader();

	void SetID(GLuint shaderId);
	GLuint GetID() const;
	GLuint GetProgram() const;
	GLint GetPositionAttribute() const; 
	GLint GetMatrixUniform() const;
	GLint GetUVAttribute() const;
	GLint GetTimeUniform() const;
	GLint GetAnimationuniform() const;
	vector<GLuint> GetTextureUniforms() const;

	void Init(char * fileVertexShader, char * fileFragmentShader);

private:
	GLuint m_iID;
	GLuint m_iProgram, m_iVertexShader, m_iFragmentShader;
	GLint m_iPositionAttribute, m_iUVAttribute, m_iMatrixUniform, m_iTimeUniform;
	GLint m_iAnimationuniform;
	vector<GLuint> m_vTextureUniforms;
};
