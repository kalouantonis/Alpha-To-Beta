/*
 * Camera2D.cpp
 *
 *  Created on: Feb 8, 2014
 *      Author: slacker
 */

#include <SFML/Graphics/RenderTarget.hpp>
#include <Graphics/Camera2D.h>

#include <SFML/OpenGL.hpp>

Camera2D::Camera2D(sf::RenderTargetPtr renderTarget)
    : m_pRenderTarget(renderTarget)
    , m_zoom(1.f)
{
    m_view = m_pRenderTarget->getView();

    updateTarget();
}

Camera2D::Camera2D(sf::RenderTargetPtr renderTarget, float frustrumWidth, float frustrumHeight)
    : m_pRenderTarget(renderTarget)
{
    m_view = m_pRenderTarget->getView();
    m_view.setViewport(sf::FloatRect(0, 0, frustrumWidth, frustrumHeight));

    resize(m_pRenderTarget->getSize());

    updateTarget();
}


Camera2D::Camera2D(sf::RenderTargetPtr renderTarget, const sf::View &view)
    : m_pRenderTarget(renderTarget)
    , m_view(view)
{
    updateTarget();
}

Camera2D::~Camera2D()
{
}

void Camera2D::resize(const sf::Vector2u& size)
{
    m_view.setSize(size.x, size.y);
    // Center camera
    m_view.setCenter(size.x / 2.f, size.y / 2.f);
    // Convert to cartesian coords
    updateTarget();
}

sf::Vector2f Camera2D::pointToWorld(const sf::Vector2i& point) const
{
    return m_pRenderTarget->mapPixelToCoords(point);
}

void Camera2D::move(float x, float y)
{
    m_view.move(x, y);
    updateTarget();
}

void Camera2D::setRotation(float amount)
{
    m_view.setRotation(amount);
    updateTarget();
}

float Camera2D::getRotation() const
{
    return m_view.getRotation();
}

void Camera2D::rotate(float amount)
{
    m_view.rotate(amount);
    updateTarget();
}

void Camera2D::updateTarget()
{
    m_pRenderTarget->setView(m_view);
}

sf::Vector2f Camera2D::getCenter() const
{
    return m_view.getCenter();
}

void Camera2D::setCenter(const sf::Vector2f &origin)
{
    m_view.setCenter(origin);
    updateTarget();
}

void Camera2D::zoom(float factor)
{
    // Store factor for getter
    m_zoom *= factor;
    m_view.zoom(factor);
    updateTarget();
}



