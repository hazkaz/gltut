#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include <stack>
#include <string>
#include <glm/glm.hpp>

namespace Framework
{
	float DegToRad(float fAngDeg);

	GLuint CreateShader(GLenum eShaderType,
		const std::string &strShaderFile, const std::string &strShaderName);
	GLuint LoadShader(GLenum eShaderType, const std::string &strShaderFilename);
	GLuint CreateProgram(const std::vector<GLuint> &shaderList);

	struct MeshData;

	class Mesh
	{
	public:
		Mesh(const std::string &strFilename);
		~Mesh();

		void Render();
		void Render(const std::string &strMeshName);
		void DeleteObjects();

	private:
		MeshData *m_pData;
	};

	class MatrixStack
	{
	public:
		MatrixStack()
			: m_currMat(1.0f)
		{
		}

		const glm::mat4 &Top()
		{
			return m_currMat;
		}

		void Rotate(glm::vec3 &axisOfRotation, float fAngDeg);
		void RotateX(float fAngDeg);
		void RotateY(float fAngDeg);
		void RotateZ(float fAngDeg);

		void Scale(const glm::vec3 &scaleVec);
		void Scale(float fScaleX, float fScaleY, float fScaleZ) {Scale(glm::vec3(fScaleX, fScaleY, fScaleZ));}
		void Translate(const glm::vec3 &offsetVec);
		void Translate(float fTransX, float fTransY, float fTransZ) {Translate(glm::vec3(fTransX, fTransY, fTransZ));}

		void ApplyMatrix(const glm::mat4 &theMatrix);
		void SetMatrix(const glm::mat4 &theMatrix);
		void SetIdentity();
		void Perspective(float fDegFOV, float fAspectRatio, float fZNear, float fZFar);

	private:
		glm::mat4 m_currMat;
		std::stack<glm::mat4> m_matrices;

		friend class MatrixStackPusher;

		void Push()
		{
			m_matrices.push(m_currMat);
		}

		void Pop()
		{
			m_currMat = m_matrices.top();
			m_matrices.pop();
		}
	};

	class MatrixStackPusher
	{
	public:
		MatrixStackPusher(MatrixStack &matrixStack)
			: m_stack(matrixStack)
		{
			m_stack.Push();
		}

		~MatrixStackPusher()
		{
			m_stack.Pop();
		}

	private:
		MatrixStack &m_stack;

		//Declared but not defined, so that it cannot be copy constructed.
		MatrixStackPusher(const MatrixStackPusher &);
		//Declared but not defined, so that it cannot be copy assigned.
		MatrixStackPusher &operator=(const MatrixStackPusher &);
	};
}

#endif //FRAMEWORK_H
