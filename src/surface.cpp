#include "hdr/surface.hpp"

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QtMath>

Surface::Surface(std::vector<C3Vec> Vertices, std::vector<C3Vec> Normals, std::vector<unsigned int> Indices, C3Vec Color)
{
    m_Positions = Vertices;
    m_Normals = Normals;
    m_RGB = Color;
    m_Indices = Indices;
}

Surface::Surface(const Surface& s)
{
    m_Positions = s.m_Positions;
    m_Normals = s.m_Normals;
    m_RGB = s.m_RGB;
    m_Indices = s.m_Indices;
}

Surface Surface::operator=(const Surface& s)
{
    Surface newSurface(s.m_Positions, s.m_Normals, s.m_Indices, s.m_RGB);

    return newSurface;
}

void Surface::Render(QOpenGLShaderProgram * shaderProgram)
{
        m_ShaderProgram = shaderProgram;
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

        m_VAO.create();
        QOpenGLVertexArrayObject::Binder vaoBinder(&m_VAO);

        m_PosVBO = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_PosVBO.create();
        m_PosVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_NormVBO = QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
        m_NormVBO.create();
        m_NormVBO.setUsagePattern(QOpenGLBuffer::StaticDraw);

        m_EBO = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
        m_EBO.create();
        f->glEnableVertexAttribArray(0);
        f->glEnableVertexAttribArray(1);


        m_PosVBO.bind();
        m_PosVBO.allocate(m_Positions.data(), static_cast<int>(m_Positions.size()*3*sizeof(double)));
        f->glVertexAttribPointer(0,3, GL_DOUBLE, GL_FALSE, 3*sizeof(double), nullptr);

        m_NormVBO.bind();
        m_NormVBO.allocate(m_Normals.data(), static_cast<int>(m_Normals.size()*3*sizeof(double)));
        f->glVertexAttribPointer(1,3, GL_DOUBLE, GL_FALSE, 3*sizeof(double), nullptr);

        m_EBO.bind();
        m_EBO.allocate(&m_Indices[0], static_cast<int>(m_Indices.size()*sizeof(unsigned int)));

        m_VAO.release();
}

void Surface::Draw(C3Vec lightColor, C3Vec lightPos)
{
    int coLoc = m_ShaderProgram->uniformLocation("objectColor");
    m_ShaderProgram->setUniformValue(coLoc, static_cast<float>(m_RGB.GetX()), static_cast<float>(m_RGB.GetY()), static_cast<float>(m_RGB.GetZ()));

    int lightCPos = m_ShaderProgram->uniformLocation("lightColor");
    m_ShaderProgram->setUniformValue(lightCPos, static_cast<float>(lightColor.GetX()), static_cast<float>(lightColor.GetY()), static_cast<float>(lightColor.GetZ()));

    int lightPPos = m_ShaderProgram->uniformLocation("lightPos");
    m_ShaderProgram->setUniformValue(lightPPos, static_cast<float>(lightPos.GetX()), static_cast<float>(lightPos.GetY()), static_cast<float>(lightPos.GetZ()));

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_VAO);
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glDrawElements(GL_TRIANGLES, static_cast<int>(m_Indices.size()), GL_UNSIGNED_INT, nullptr);
}
