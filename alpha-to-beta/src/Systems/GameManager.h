#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <Systems/SystemManager.h>
#include <Graphics/SpriteBatch.h>

// TODO: GTFO
#include <Resources/ResourceHolderDef.h>

class GameManager: public SystemManager
{
public:
	GameManager(SpriteBatch& spriteBatch);

	virtual void update(float dt) final;
	virtual void render() final;
	virtual void dispose() final;

protected:
	virtual void configure() final;
	virtual void initialize() final;

private:
	SpriteBatch m_spriteBatch;
	// TODO: GTFO
	TextureHolder m_textureHolder;

};

#endif // GAME_MANAGER_H