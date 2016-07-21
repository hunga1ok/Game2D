#pragma once
#include "Utilities/utilities.h"
#include "Globals.h"
#include "Vertex.h"
#include "stdio.h"
#include "AnimationProperties.h"
#include  <vector>
class Model
{
public:
	Model();
	Model(char* fileName, GLuint modelId);
	Model(AnimationProperties index, GLuint modelId);

	~Model();

	GLuint GetID() const;
	void SetID(GLuint modelId);
	GLuint GetVboId()const;
	GLuint GetIdoId()const;
	GLuint GetIndicesNumber()const;
	AnimationProperties GetIndex();


	void LoadModel(char * fileName);
	void LoadModel(AnimationProperties index);
	void LoadModel(std::vector<AnimationProperties> indexs);
	void UpdateUV(AnimationProperties index) const;
	void BufferVBO();
	void BufferIBO();
	void CleanBuffer() const;
private:
	GLuint m_iID, m_iVboId, m_iIboId;
	Vertex* m_verticesList;
	GLuint* m_iIndicesList;
	GLuint m_iVeticesNumber;
	GLuint m_iIndicesNumber;
	AnimationProperties m_Index;
};