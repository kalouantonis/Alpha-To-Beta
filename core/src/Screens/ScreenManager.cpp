#include <Screens/ScreenManager.h>
#include <Screens/IScreen.h>

#include <Utils/Logger.h>
#include <assert.h>

// Allocator /////////////////////////////////////////////////////////
void _deleter(IScreen* p)
{
    CORE_DEBUG("Disposing screen...");
    p->dispose();
    CORE_DEBUG("Deleting screen...");
    delete p;
}

UScreenPtr make_screen(IScreen* screen)
{
    return UScreenPtr(screen, _deleter);
}
//////////////////////////////////////////////////////////////////////

void ScreenManager::push(UScreenPtr pScreen)
{
    // Transform ownership to manager
    m_screenStack.push_back(std::move(pScreen));
    assert(m_screenStack.back()->init() != false);
}

void ScreenManager::change(UScreenPtr pScreen)
{
    if(!m_screenStack.empty())
    {
        // If same screen, return
        if(pScreen == m_screenStack.back())
            return;

        // Dispose items and remove
        m_screenStack.pop_back();
    }

    this->push(std::move(pScreen));
}

void ScreenManager::pop()
{
    if(!m_screenStack.empty())
    {
        m_screenStack.pop_back();
    }
}

void ScreenManager::update(float deltaTime)
{
    if(!m_screenStack.empty())
        m_screenStack.back()->update(deltaTime);
}

void ScreenManager::render()
{
   if(!m_screenStack.empty())
       m_screenStack.back()->render();
}

void ScreenManager::pollInput(const sf::Event &event)
{
    if(!m_screenStack.empty())
        m_screenStack.back()->pollInput(event);
}

void ScreenManager::resize(const sf::Vector2u &size)
{
    if(!m_screenStack.empty())
        m_screenStack.back()->resize(size);
}

void ScreenManager::dispose()
{
    if(!m_screenStack.empty())
    {
        m_screenStack.clear();
    }
}

