#ifndef _INPUT_EXPORTS_H_
#define _INPUT_EXPORTS_H_

namespace InternalScriptExports
{
void registerKeyTable();
bool isKeyPressed(int keyCode);
void unregisterKeyTable();
}

#endif