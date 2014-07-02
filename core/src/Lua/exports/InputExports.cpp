#include <Lua/exports/InputExports.h>
#include <Lua/LuaStateManager.h>

#include <Utils/Logger.h>

#include <SFML/Window/Keyboard.hpp>

namespace InternalScriptExports
{

const char* KEYTABLE_NAME = "keys";

void registerKeyTable()
{
	LuaStateManager* pStateManager = LuaStateManager::get();
	CORE_ASSERT(pStateManager != nullptr);

	LuaPlus::LuaState* pLuaState = pStateManager->getLuaState();
	
	// Ensure object is nil
	CORE_ASSERT(pStateManager->getGlobalVars().Lookup(KEYTABLE_NAME).IsNil());

	// Register keys
	LuaPlus::LuaObject& keys = pStateManager->getGlobalVars().CreateTable(KEYTABLE_NAME);

	// Letters
	keys.SetInteger("a", sf::Keyboard::A);
	keys.SetInteger("b", sf::Keyboard::B);
	keys.SetInteger("c", sf::Keyboard::C);
	keys.SetInteger("d", sf::Keyboard::D);
	keys.SetInteger("e", sf::Keyboard::E);
	keys.SetInteger("f", sf::Keyboard::F);
	keys.SetInteger("g", sf::Keyboard::G);
	keys.SetInteger("h", sf::Keyboard::H);
	keys.SetInteger("i", sf::Keyboard::I);
	keys.SetInteger("j", sf::Keyboard::J);
	keys.SetInteger("k", sf::Keyboard::K);
	keys.SetInteger("l", sf::Keyboard::L);
	keys.SetInteger("m", sf::Keyboard::M);
	keys.SetInteger("n", sf::Keyboard::N);
	keys.SetInteger("o", sf::Keyboard::O);
	keys.SetInteger("p", sf::Keyboard::P);
	keys.SetInteger("q", sf::Keyboard::Q);
	keys.SetInteger("r", sf::Keyboard::R);
	keys.SetInteger("s", sf::Keyboard::S);
	keys.SetInteger("t", sf::Keyboard::T);
	keys.SetInteger("u", sf::Keyboard::U);
	keys.SetInteger("v", sf::Keyboard::V);
	keys.SetInteger("w", sf::Keyboard::W);
	keys.SetInteger("x", sf::Keyboard::X);
	keys.SetInteger("y", sf::Keyboard::Y);
	keys.SetInteger("z", sf::Keyboard::Z);

	// Numbers
	keys.SetInteger("num0", sf::Keyboard::Num0);
	keys.SetInteger("num1", sf::Keyboard::Num1);
	keys.SetInteger("num2", sf::Keyboard::Num2);
	keys.SetInteger("num3", sf::Keyboard::Num3);
	keys.SetInteger("num4", sf::Keyboard::Num4);
	keys.SetInteger("num5", sf::Keyboard::Num5);
	keys.SetInteger("num6", sf::Keyboard::Num6);
	keys.SetInteger("num7", sf::Keyboard::Num7);
	keys.SetInteger("num8", sf::Keyboard::Num8);
	keys.SetInteger("num9", sf::Keyboard::Num9);

	// Numpad
	keys.SetInteger("numpad0", sf::Keyboard::Numpad0);
	keys.SetInteger("numpad1", sf::Keyboard::Numpad1);
	keys.SetInteger("numpad2", sf::Keyboard::Numpad2);
	keys.SetInteger("numpad3", sf::Keyboard::Numpad3);
	keys.SetInteger("numpad4", sf::Keyboard::Numpad4);
	keys.SetInteger("numpad5", sf::Keyboard::Numpad5);
	keys.SetInteger("numpad6", sf::Keyboard::Numpad6);
	keys.SetInteger("numpad7", sf::Keyboard::Numpad7);
	keys.SetInteger("numpad8", sf::Keyboard::Numpad8);
	keys.SetInteger("numpad9", sf::Keyboard::Numpad9);

	// F*
	keys.SetInteger("f1", sf::Keyboard::F1);
	keys.SetInteger("f2", sf::Keyboard::F2);
	keys.SetInteger("f3", sf::Keyboard::F3);
	keys.SetInteger("f4", sf::Keyboard::F4);
	keys.SetInteger("f5", sf::Keyboard::F5);
	keys.SetInteger("f6", sf::Keyboard::F6);
	keys.SetInteger("f7", sf::Keyboard::F7);
	keys.SetInteger("f8", sf::Keyboard::F8);
	keys.SetInteger("f9", sf::Keyboard::F9);
	keys.SetInteger("f10", sf::Keyboard::F10);
	keys.SetInteger("f11", sf::Keyboard::F11);
	keys.SetInteger("f12", sf::Keyboard::F12);

	// Specials
	keys.SetInteger("escape",		sf::Keyboard::Escape);
	keys.SetInteger("lcontrol",		sf::Keyboard::LControl);
	keys.SetInteger("lshift",		sf::Keyboard::LShift);
	keys.SetInteger("lalt",			sf::Keyboard::LAlt);
	keys.SetInteger("lsystem",		sf::Keyboard::LSystem);
	keys.SetInteger("rcontrol",		sf::Keyboard::RControl);
	keys.SetInteger("rshift",		sf::Keyboard::RShift);
	keys.SetInteger("ralt",			sf::Keyboard::RAlt);
	keys.SetInteger("rsystem",		sf::Keyboard::RSystem);
	keys.SetInteger("menu",			sf::Keyboard::Menu);
	keys.SetInteger("lbracket",		sf::Keyboard::LBracket);
	keys.SetInteger("rbracket",		sf::Keyboard::RBracket);
	keys.SetInteger("semicolon",	sf::Keyboard::SemiColon);
	keys.SetInteger("comma",		sf::Keyboard::Comma);
	keys.SetInteger("period",		sf::Keyboard::Period);
	keys.SetInteger("quote",		sf::Keyboard::Quote);
	keys.SetInteger("slash",		sf::Keyboard::Slash);
	keys.SetInteger("backslash",	sf::Keyboard::BackSlash);
	keys.SetInteger("tilde",		sf::Keyboard::Tilde);
	keys.SetInteger("equal",		sf::Keyboard::Equal);
	keys.SetInteger("dash",			sf::Keyboard::Dash);
	keys.SetInteger("space",		sf::Keyboard::Space);
	keys.SetInteger("return",		sf::Keyboard::Return);
	keys.SetInteger("backspace",	sf::Keyboard::BackSpace);
	keys.SetInteger("tab",			sf::Keyboard::Tab);
	keys.SetInteger("pageup",		sf::Keyboard::PageUp);
	keys.SetInteger("pagedown",		sf::Keyboard::PageDown);
	keys.SetInteger("end",			sf::Keyboard::End);
	keys.SetInteger("home",			sf::Keyboard::Home);
	keys.SetInteger("insert",		sf::Keyboard::Insert);
	keys.SetInteger("delete",		sf::Keyboard::Delete);
	keys.SetInteger("add",			sf::Keyboard::Add);
	keys.SetInteger("subtract",		sf::Keyboard::Subtract);
	keys.SetInteger("multiply",		sf::Keyboard::Multiply);
	keys.SetInteger("divide",		sf::Keyboard::Divide);

	// Arrow keys
	keys.SetInteger("left", sf::Keyboard::Left);
	keys.SetInteger("right", sf::Keyboard::Right);
	keys.SetInteger("up", sf::Keyboard::Up);
	keys.SetInteger("down", sf::Keyboard::Down);

	// Pause
	keys.SetInteger("pause", sf::Keyboard::Pause);
}

void unregisterKeyTable()
{
	LuaStateManager* pStateManager = LuaStateManager::get();

	LuaPlus::LuaObject& keys = pStateManager->getGlobalVars().Lookup(KEYTABLE_NAME);
	CORE_ASSERT(keys.IsTable());

	// Set for collection
	keys.AssignNil(pStateManager->getLuaState());
}

bool isKeyPressed(int keyCode)
{
	return sf::Keyboard::isKeyPressed((sf::Keyboard::Key) keyCode);
}

}