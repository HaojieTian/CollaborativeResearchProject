#pragma once

#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include "nodes/DistanceFieldData.hpp"
#include "ShaderManager.hpp"
#include "Window.hpp"

struct Branch
{
	std::string m_sc;
	std::vector<Branch> m_branches;
};

namespace hsitho
{
  class SceneWindow : public GLWindow
  {
	public:
    SceneWindow(QWidget *_parent);
		~SceneWindow();

    void initializeGL();
    void paintGL();

	private:
		std::string recurseNodeTree(std::shared_ptr<Node> _node, Vec4f _t);
    std::shared_ptr<ShaderManager> m_shaderMan;
		Node *m_outputNode;
		QOpenGLVertexArrayObject *m_vao;
    QOpenGLBuffer m_vbo;

  public slots:
    virtual void nodeChanged(std::unordered_map<QUuid, std::shared_ptr<Node>> _nodes);
  };
}
