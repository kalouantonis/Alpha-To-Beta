#ifndef QSFML_CANVAS_H
#define QSFML_CANVAS_H

#include <QWidget>
#include <QTimer>

#include <SFML/Graphics/RenderWindow.hpp>

class QSFMLCanvas: public QWidget, public sf::RenderWindow
{
	Q_OBJECT

public:
	QSFMLCanvas(QWidget* parent, const QPoint& position,
		const QSize& size, unsigned int frameTime = 0);
	virtual ~QSFMLCanvas();
	
protected:
	virtual void onInit() = 0;
	virtual void onRender() = 0;

private:
	virtual QPaintEngine* paintEngine() const final;
	virtual void showEvent(QShowEvent*) final;
	virtual void paintEvent(QPaintEvent*) final;
	virtual void closeEvent(QCloseEvent*) final;

	QTimer m_timer;
	bool m_initialized;
};

#endif // QSFML_CANVAS_H