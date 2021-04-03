#ifndef SURFACE_HPP
#define SURFACE_HPP

#include <vector>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include "hdr/C3Vec.hpp"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class Surface
{

    public:
        Surface(std::vector<C3Vec> Vertices, std::vector<C3Vec> Normals, std::vector<unsigned int> m_Indices, C3Vec Color);
        Surface(const Surface&);

        void	Render(QOpenGLShaderProgram*);
        void	Draw(C3Vec lightColor, C3Vec lightPos);
        QOpenGLShaderProgram*	get_shader_program() {return m_ShaderProgram;}

        Surface operator=(const Surface&);

    private:
        C3Vec						m_RGB;
        std::vector<C3Vec>			m_Positions, m_Normals;
        std::vector<unsigned int>	m_Indices;

        QOpenGLShaderProgram		*m_ShaderProgram;
        QOpenGLVertexArrayObject	m_VAO;
        QOpenGLBuffer				m_PosVBO, m_NormVBO, m_EBO;
};

#endif // SURFACE_HPP
