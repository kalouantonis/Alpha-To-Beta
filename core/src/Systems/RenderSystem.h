#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <entityx/System.h>
#include <Graphics/SpriteBatch.h>

class RenderSystem: public entityx::System<RenderSystem>
{
public:
	RenderSystem(SpriteBatch& spriteBatch);

	void update(entityx::ptr<entityx::EntityManager> es,
		entityx::ptr<entityx::EventManager> event, float dt) override;

private:
	SpriteBatch m_spriteBatch;
};

#endif // RENDER_SYSTEM_H