#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QtMath>
#include <QMouseEvent>

#include <vector>

#include "hdr/C3Vec.hpp"
#include "hdr/surface.hpp"

class openglwidget : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit 	openglwidget(QWidget *parent = nullptr);
    void		initializeGL();
    void		paintGL();
    void		resizeGL(int width, int height);
    void		cleanup();
    void		draw_surfaces(std::vector<Surface>);
    void		mousePressEvent(QMouseEvent *event);
    void		mouseMoveEvent(QMouseEvent *event);
    void		wheelEvent(QWheelEvent *event);
    void		set_background_color(double r, double g, double b);

private:
    QOpenGLShaderProgram 				*m_ShaderProgram;
    QOpenGLBuffer						m_VBO;
    QOpenGLVertexArrayObject 			m_VAO;
    QMatrix4x4							m_Projection;
    QMatrix4x4							m_Camera;
    QMatrix4x4							m_World;

    float 								m_Scale;

    QVector2D							m_LastPos;
    QQuaternion							m_Rotation;
    std::vector<QOpenGLShaderProgram*> 	m_ShaderPrograms;
    std::vector<Surface>				m_Surfaces;

public slots:
};

#endif // OPENGLWIDGET_H
