#include "assets.h"

#include "window.h"
#include "asset_load.h"

void Assets::LoadAll() {

    spritesheet = LoadImage("data/spritesheet.png");

    font_30 = LoadFont("data/PressStart2P.ttf", 30);
    font_30_outline = LoadFontOutline("data/PressStart2P.ttf", 30, 3);

    tintShader.Load(nullptr, nullptr, "data/tint.frag");
  
}
