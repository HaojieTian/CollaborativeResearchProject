#include <QCoreApplication>
#include <QPainter>

#include "Window.hpp"

namespace hsitho
{
	GLWindow::GLWindow(QWindow *parent) :
		QWindow(parent),
		m_update_pending(false),
		m_animating(false),
		m_context(nullptr),
		m_device(nullptr)
	{
		setSurfaceType(QWindow::OpenGLSurface);
	}

	void GLWindow::render(QPainter *painter)
	{
		Q_UNUSED(painter);
	}

	void GLWindow::initialize()
	{
		glClearColor(1.f, 1.f, 1.f, 1.0f);
	}

	void GLWindow::render()
	{
		if(!m_device) {
			m_device = new QOpenGLPaintDevice;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		m_device->setSize(size());

		QPainter painter(m_device);
		render(&painter);
	}

	void GLWindow::renderLater()
	{
		if(!m_update_pending) {
			m_update_pending = true;
			QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
		}
	}

	void GLWindow::renderNow()
	{
		if(!isExposed()) {
			return;
		}

		bool needsInitialize = false;

		if(!m_context) {
			m_context = new QOpenGLContext(this);
			m_context->setFormat(requestedFormat());
			m_context->create();

			needsInitialize = true;
		}

		m_context->makeCurrent(this);

		if(needsInitialize) {
			initializeOpenGLFunctions();
			initialize();
		}

		render();

		m_context->swapBuffers(this);

		if(m_animating) {
			renderLater();
		}
	}

	void GLWindow::setAnimating(bool animating)
	{
		m_animating = animating;

		if(animating) {
			renderLater();
		}
	}

	bool GLWindow::event(QEvent *event)
	{
		switch (event->type()) {
			case QEvent::UpdateRequest: {
				m_update_pending = false;
				renderNow();
				return true;
			} break;
			default: {
				return QWindow::event(event);
			}
		}
	}

	void GLWindow::exposeEvent(QExposeEvent *event)
	{
		Q_UNUSED(event);

		if (isExposed())
				renderNow();
	}
}
