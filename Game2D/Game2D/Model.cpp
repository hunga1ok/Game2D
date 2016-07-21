#include "Model.h"
Model::Model()
{
}
Model::Model(char* fileName, GLuint modelId)
{
	LoadModel(fileName);
	SetID(modelId);
	BufferVBO();
	BufferIBO();
}

Model::Model(AnimationProperties index, GLuint modelId)
{
	LoadModel(index);
	SetID(modelId);
	BufferVBO();
	BufferIBO();
	m_Index = index;
}

Model::~Model()
{
	CleanBuffer();
}
GLuint Model::GetID() const
{
	return this->m_iID;
}
void Model::SetID(GLuint modelId)
{
	this->m_iID = modelId;
}
GLuint Model::GetVboId() const
{
	return m_iVboId;
}

GLuint Model::GetIdoId() const
{
	return m_iIboId;
}
GLuint Model::GetIndicesNumber() const
{
	return m_iIndicesNumber;
}

AnimationProperties Model::GetIndex()
{
	return m_Index;
}

void Model::LoadModel(char* fileName)
{
	FILE *f;
	f = fopen(fileName, "r");
	if (f)
	{
		fscanf(f, "NrVertices: %d\n", &(this->m_iVeticesNumber));
		this->m_verticesList = new Vertex[this->m_iVeticesNumber];
		GLfloat posx, posy, posz, normx, normy, normz, binormx, binormy, binormz, tgtx, tgty, tgtz, uvx, uvy;

		for (GLuint i = 0; i < this->m_iVeticesNumber; i++)
		{
			fscanf(f, "%*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\n",
				&posx, &posy, &posz, &normx, &normy, &normz, &binormx, &binormy, &binormz, &tgtx, &tgty, &tgtz, &uvx, &uvy);
			Vertex v;
			v.position = Vector3(posx, posy, posz);
			v.normal = Vector3(normx, normy, normz);
			v.binormal = Vector3(binormx, binormy, binormz);
			v.tangent = Vector3(tgtx, tgty, tgtz);
			v.uv = Vector2(uvx, uvy);
			this->m_verticesList[i] = v;
		}
		fscanf(f, "NrIndices: %d\n", &(this->m_iIndicesNumber));
		this->m_iIndicesList = new GLuint[this->m_iIndicesNumber];
		GLuint a, b, c, count = 0;
		for (GLuint i = 0; i < (this->m_iIndicesNumber / 3); i++)
		{
			fscanf(f, " %*d.    %d,    %d,    %d", &a, &b, &c);
			this->m_iIndicesList[count++] = a;
			this->m_iIndicesList[count++] = b;
			this->m_iIndicesList[count++] = c;
		}
	}
	else
	{
		printf("Error opening file %s", fileName);
	}
}

void Model::LoadModel(AnimationProperties index)
{
	m_iVeticesNumber = 4;
	m_iIndicesNumber = 6;
	m_verticesList = new Vertex[m_iVeticesNumber];
	m_iIndicesList = new GLuint[m_iIndicesNumber];

	m_verticesList[0].position = Vector3(-1, 1, 0);
	m_verticesList[1].position = Vector3(1, 1, 0);
	m_verticesList[2].position = Vector3(-1, -1, 0);
	m_verticesList[3].position = Vector3(1, -1, 0);

	UpdateUV(index);

	m_iIndicesList[0] = 0;
	m_iIndicesList[1] = 1;
	m_iIndicesList[2] = 2;
	m_iIndicesList[3] = 1;
	m_iIndicesList[4] = 2;
	m_iIndicesList[5] = 3;
}

void Model::LoadModel(std::vector<AnimationProperties> index)
{
	m_iVeticesNumber = index.size() * 4;
	m_iIndicesNumber = index.size() * 4;
	m_verticesList = new Vertex[m_iVeticesNumber];
	m_iIndicesList = new GLuint[m_iIndicesNumber];
	int c = 0;
	for (auto i = 0; i < index.size(); i++)
	{
//		m_verticesList[c].position = Vector3(-1, 1, 0);
//		m_verticesList[c+1].position = Vector3(1, 1, 0);
//		m_verticesList[c+2].position = Vector3(-1, -1, 0);
//		m_verticesList[c+3].position = Vector3(1, -1, 0);
		m_verticesList[c].position = Vector3(-1, 0, 0);
		m_verticesList[c + 1].position = Vector3(0, 0, 0);
		m_verticesList[c + 2].position = Vector3(-1, -1, 0);
		m_verticesList[c + 3].position = Vector3(0, -1, 0);

		m_verticesList[c].uv = Vector2(index[i].spriteX*1.0f / index[i].textureW, 1 - index[i].spriteY*1.0f / index[i].textureH);
		m_verticesList[c+1].uv = Vector2((index[i].spriteX + index[i].spriteW)*1.0f / index[i].textureW, 1 - index[i].spriteY*1.0f / index[i].textureH);
		m_verticesList[c+2].uv = Vector2(index[i].spriteX*1.0f / index[i].textureW, 1 - (index[i].spriteY + index[i].spriteH)*1.0f / index[i].textureH);
		m_verticesList[c+3].uv = Vector2((index[i].spriteX + index[i].spriteW)*1.0f / index[i].textureW, 1 - (index[i].spriteY + index[i].spriteH)*1.0f / index[i].textureH);
		c += 4;
	}
//	int k = 0;
//	for (auto i = 0; i < m_iIndicesNumber; i++)
//	{
//		if ((i-3)%6==0)
//		{
//			k++;
//		}
//		m_iIndicesList[i] = i - 2 * k;
//	}
	for (int i = 0; i < m_iIndicesNumber; i++)
	{
		m_iIndicesList[i] = i;
	}
}

void Model::UpdateUV(AnimationProperties index) const
{
	m_verticesList[0].uv = Vector2(index.spriteX*1.0f / index.textureW, 1 - index.spriteY*1.0f / index.textureH);
	m_verticesList[1].uv = Vector2((index.spriteX + index.spriteW)*1.0f / index.textureW, 1 - index.spriteY*1.0f / index.textureH);
	m_verticesList[2].uv = Vector2(index.spriteX*1.0f / index.textureW, 1 - (index.spriteY + index.spriteH)*1.0f / index.textureH);
	m_verticesList[3].uv = Vector2((index.spriteX + index.spriteW)*1.0f / index.textureW, 1 - (index.spriteY + index.spriteH)*1.0f / index.textureH);
}

void Model::BufferVBO()
{
	glGenBuffers(1, &(this->m_iVboId));
	glBindBuffer(GL_ARRAY_BUFFER, this->m_iVboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*this->m_iVeticesNumber, this->m_verticesList, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Model::BufferIBO()
{
	glGenBuffers(1, &(this->m_iIboId));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_iIboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*this->m_iIndicesNumber, this->m_iIndicesList, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void  Model::CleanBuffer() const
{
	glDeleteBuffers(1, &(this->m_iVboId));
	glDeleteBuffers(1, &(this->m_iIboId));
	delete[] this->m_iIndicesList;
	delete[] this->m_verticesList;
}



