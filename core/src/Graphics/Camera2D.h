/*
 * Camera2D.h
 *
 *  Created on: Feb 8, 2014
 *      Author: slacker
 */

#ifndef CAMERA2D_H_
#define CAMERA2D_H_

#include <SFMLPtrDef.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/View.hpp>

#include <memory>

class Camera2D
{
public:
    Camera2D(sf::RenderTargetPtr renderTarget);
    
    explicit Camera2D(sf::RenderTargetPtr renderTarget,
                      float frustrumWidth, float frustrumHeight);

    explicit Camera2D(sf::RenderTargetPtr renderTarget,
                      const sf::View& view);
	~Camera2D();

    // Called on resize event
    void resize(const sf::Vector2u& size);
    sf::Vector2f pointToWorld(const sf::Vector2i& point) const;


    void setRotation(float amount);
    float getRotation() const;
    void rotate(float amount);

    const sf::Vector2f& getSize() { return m_view.getSize(); }

    sf::Vector2f getCenter() const;
    void setCenter(const sf::Vector2f &origin);
    void move(float x, float y);

    void zoom(float factor);
    float getZoom() const { return m_zoom; }

private:
    // Update camera. Called when variables change
    void updateTarget();

    sf::RenderTargetPtr m_pRenderTarget;
    sf::View m_view;

    float m_zoom;
};

typedef std::shared_ptr<Camera2D> Camera2DPtr;

#endif /* CAMERA2D_H_ */
