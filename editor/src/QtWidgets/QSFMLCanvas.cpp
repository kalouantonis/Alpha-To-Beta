#include <QtWidgets/QSFMLCanvas.h>

#ifdef Q_WS_X11
	#include <Qt/qx11info_x11.h>
	#include <X11/Xlib.h>
#endif

QSFMLCanvas::QSFMLCanvas(QWidget* parent, const QPoint& position, 
	const QSize& size, unsigned int frameTime)
	: QWidget(parent)
	, m_initialized(false)
{
	// Setup states to allow direct rendering in to the widget
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_OpaquePaintEvent);
	setAttribute(Qt::WA_NoSystemBackground);

	// Set strong focus for grabbing keyboard events
	setFocusPolicy(Qt::StrongFocus);

	// Setup the widget geometry
	move(position);
	resize(size);

	// setup the timer
	m_timer.setInterval(frameTime);	
}

QSFMLCanvas::~QSFMLCanvas()
{
}

void QSFMLCanvas::showEvent(QShowEvent*)
{
	if(!m_initialized)
	{
		// Under x11 we need to flush the view commands to the server to ensure
		// that SFML will get an updated view
#ifdef Q_WS_X11
		XFlush(QX11Info::display());
#endif

		// Create render window using system handle
		sf::RenderWindow::create(winId());

		// Let the derived class to its initialization
		this->onInit();

		// setup the timer to repaint on timeout
		connect(&m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
		m_timer.start();

		m_initialized = true;
	}
}

QPaintEngine* QSFMLCanvas::paintEngine() const
{
	// Notify qt that we will be using a custom render engine
	return NULL;
}

void QSFMLCanvas::paintEvent(QPaintEvent*)
{
	sf::RenderWindow::clear();

	// Let the derived class render its stuff
	this->onRender();

	// Display on screen
	sf::RenderWindow::display();	
}

void QSFMLCanvas::closeEvent(QCloseEvent*)
{
	sf::RenderWindow::close();
}