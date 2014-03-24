#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <Systems/WorldManager.h>
#include <Graphics/SpriteBatch.h>

// Fwd defs
class RenderSystem;
class MovementSystem;

// TODO: GTFO
#include <Resources/ResourceHolderDef.h>

class GameManager: public WorldManager
{
public:
	GameManager(SpriteBatch& spriteBatch);
	virtual ~GameManager() {}

	virtual void update(float delta) final;
	virtual void render() final;
	virtual void dispose() final;
	virtual void initialize() final;

private:
	SpriteBatch m_spriteBatch;
	// TODO: GTFO
	TextureHolder m_textureHolder;

	RenderSystem* m_renderSystem;
	MovementSystem* m_movementSystem;
};

#endif // GAME_MANAGER_H