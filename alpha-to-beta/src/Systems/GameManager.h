#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <Systems/WorldManager.h>
#include <Graphics/SpriteBatch.h>
#include <Entities/Level.h>

// Fwd defs
class RenderSystem;
class MovementSystem;


class GameManager: public WorldManager
{
public:
	GameManager(SpriteBatch& spriteBatch);
	virtual ~GameManager();

	virtual void update(float delta) final;
	virtual void render() final;
	//virtual void dispose() final;
	virtual void initialize() final;

private:
	SpriteBatch m_spriteBatch;

	RenderSystem* m_renderSystem;
	MovementSystem* m_movementSystem;
	std::shared_ptr<Level> m_level;
};

#endif // GAME_MANAGER_H