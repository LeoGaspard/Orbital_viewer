#include "hdr/openglwidget.h"

openglwidget::openglwidget(QWidget *parent) : QOpenGLWidget(parent)
{
    m_Scale = 0.06f;
}

void openglwidget::initializeGL()
{
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &openglwidget::cleanup);

    glClearColor(0.2f,0.3f,0.3f,1.0f);

    m_ShaderPrograms.push_back(new QOpenGLShaderProgram);
    m_ShaderPrograms[0]->addShaderFromSourceFile(QOpenGLShader::Vertex,"shaders/shader.vs");
    m_ShaderPrograms[0]->addShaderFromSourceFile(QOpenGLShader::Fragment,"shaders/shader.fs");
    m_ShaderPrograms[0]->bindAttributeLocation("aPos",0);
    m_ShaderPrograms[0]->bindAttributeLocation("aNorm",1);
    m_ShaderPrograms[0]->link();
    m_ShaderPrograms[0]->bind();
}

void openglwidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);


    for(unsigned int i=0;i<m_Surfaces.size();i++)
    {
        m_Surfaces[i].get_shader_program()->bind();
        m_Surfaces[i].Draw(C3Vec(1.0,1.0,1.0),C3Vec(4.0,0.0,0.2));
    }
    QMatrix4x4 model;
    model.rotate(m_Rotation);
    model.scale(QVector3D(m_Scale,m_Scale,m_Scale));

    QMatrix4x4 view;
    view.translate(QVector3D(0.0f,0.0f,-3.0f));

    QMatrix4x4 projection;
    projection.perspective(90.0f, 4.0f/3.0f, 0.1f, 100.0f);

    int modelLoc = m_ShaderPrograms[0]->uniformLocation("model");
    m_ShaderPrograms[0]->setUniformValue(modelLoc, model);
    int viewLoc = m_ShaderPrograms[0]->uniformLocation("view");
    m_ShaderPrograms[0]->setUniformValue(viewLoc, view);
    int projectionLoc = m_ShaderPrograms[0]->uniformLocation("projection");
    m_ShaderPrograms[0]->setUniformValue(projectionLoc, projection);
}

void openglwidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glScalef(height *1.f/width, 1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
}

void openglwidget::cleanup()
{
    makeCurrent();
    doneCurrent();
}

void openglwidget::wheelEvent(QWheelEvent *event)
{
    m_Scale += event->angleDelta().y()*0.0005f;
    if(m_Scale < 0.001f)
    {
        m_Scale = 0.001f;
    }
    update();
}

void openglwidget::set_background_color(double r, double g, double b)
{
    makeCurrent();
    glClearColor(static_cast<float>(r),static_cast<float>(g),static_cast<float>(b),1.0f);
    update();
}

void openglwidget::mousePressEvent(QMouseEvent *event)
{
    m_LastPos = QVector2D(event->localPos());
}

void openglwidget::mouseMoveEvent(QMouseEvent *event)
{
    QVector2D diff = QVector2D(event->localPos()) - m_LastPos;
    QVector3D n = QVector3D(diff.y(),diff.x(),0.0f).normalized();
    float acc = diff.length()/2.0f;
    QVector3D rotationAxis = n;
    m_Rotation = QQuaternion::fromAxisAndAngle(rotationAxis,acc)*m_Rotation;
    m_LastPos = QVector2D(event->localPos());
    update();
}

void openglwidget::draw_surfaces(std::vector<Surface> s)
{
    makeCurrent();
    m_Surfaces.clear();

    m_Surfaces = s;

    for(unsigned int i=0; i<m_Surfaces.size(); i++)
    {
        m_Surfaces[i].Render(m_ShaderPrograms[0]);
    }
    paintGL();
}

