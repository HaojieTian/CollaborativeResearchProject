#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <fstream>

#include <glm/glm.hpp>

#include "nodes/DistanceFieldData.hpp"
#include "ShaderManager.hpp"
#include "Window.hpp"

/// \file SceneWindow.hpp
/// \brief Simple OpenGL window that handles the rendering of our SDF scene
/// \authors Teemu Lindborg & Phil Gifford
/// \version 1.0
/// \date 22/01/17 Updated to NCCA Coding standard
/// Revision History :
/// Initial Version 05/10/16

namespace hsitho
{
  class SceneWindow : public GLWindow
  {
  public:
    ///
    /// \brief SceneWindow Default ctor
    /// \param _parent MainWindow class to which the window is rendered to
    ///
    SceneWindow(QWidget *_parent);
    ///
    /// \brief SceneWindow Default dtor
    ///
    ~SceneWindow();

    ///
    /// \brief initializeGL Qt function, used to initialise OpenGL and the scene
    ///
    void initializeGL();
    ///
    /// \brief paintGL Main draw loop, used to render the screen quad and to pass required attributes and uniforms to the shader
    ///
    void paintGL();

    ///
    /// \brief mousePressEvent Event triggered when a mouse button is clicked
    /// \param _event QMouseEvent containing the details of the mouse press
    ///
		void mousePressEvent(QMouseEvent *_event);
    ///
    /// \brief mouseMoveEvent Event triggered when a mouse is moved
    /// \param _event Event containing the details of the mouse movement
    ///
		void mouseMoveEvent(QMouseEvent *_event);
    ///
    /// \brief wheelEvent Event trigger whend the mouse wheel is scrolled
    /// \param _event Details about the mousewheel event
    ///
		void wheelEvent(QWheelEvent *_event);

  private:
    ///
    /// \brief recurseNodeTree Recursed the node tree starting from the distance node, ignores anything that's not connected to the distance node
    /// \param _node Current node being traversed
    /// \param _t Current transformation matrix, passed down the recursion
    /// \param portIndex Index of an output port, used for traversing collapsed nodes
    /// \param _cp Current copy number, used to pass the which iteration the node belongs to when using a copy-node
    /// \return returns the shader code generated by the tree traversal
    ///
		std::string recurseNodeTree(std::shared_ptr<Node> _node, Mat4f _t, PortIndex portIndex = 0, unsigned int _cp = 0);

    ///
    /// \brief m_shaderMan Instance of the shader manager
    ///
    std::shared_ptr<ShaderManager> m_shaderMan;
    ///
    /// \brief m_outputNode Pointer to the distance-node
    ///
    Node *m_outputNode;
    ///
    /// \brief m_vao Vertex array object for the screen quad
    ///
    QOpenGLVertexArrayObject *m_vao;
    ///
    /// \brief m_vbo Vertex buffer object for the screen quad
    ///
    QOpenGLBuffer m_vbo;

    ///
    /// \brief m_shaderStart The first part of the shader code, prepended to the node tree shader code
    ///
    std::string m_shaderStart;
    ///
    /// \brief m_shaderEnd The last part of the shader code, appended to the node tree shader code
    ///
    std::string m_shaderEnd;

    ///
    /// \brief m_cam Scene camera location
    ///
		glm::vec4 m_cam;
    ///
    /// \brief m_camU Scene camera up vector
    ///
		glm::vec3 m_camU;
    ///
    /// \brief m_camL Scene camera left vector
    ///
		glm::vec3 m_camL;
    ///
    /// \brief m_camDist Distance of the camera from the origin
    ///
		float m_camDist;

    ///
    /// \brief m_origX Used to calculate the rotation of the camera when moved
    ///
		int m_origX;
    ///
    /// \brief m_origY Used to calculate the rotation of the camera when moved
    ///
		int m_origY;

  public slots:
    ///
    /// \brief nodeChanged Slot that's signalled when the scene needs to be recompiled, e.g. the node tree traversed and new shader code generated.
    /// \param _nodes List of all the nodes in the scene
    ///
    virtual void nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes);
  };
}
