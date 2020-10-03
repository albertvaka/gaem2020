#include "bounds.h"

#include "window.h"

void Bounds::Draw(uint8_t r, uint8_t g, uint8_t b) const
{
    Window::DrawPrimitive::Rectangle(*this, 1, r, g, b);
}


void CircleBounds::Draw(uint8_t r, uint8_t g, uint8_t b) const
{
    Window::DrawPrimitive::Circle(*this, 1, r, g, b);
}

void RotableBounds::Draw(uint8_t r, uint8_t g, uint8_t b) const
{
    Window::DrawPrimitive::Line(TL.x, TL.y, TR.x, TR.y, 1, r, g, b);
    Window::DrawPrimitive::Line(BL.x, BL.y, BR.x, BR.y, 1, r, g, b);
    Window::DrawPrimitive::Line(TL.x, TL.y, BL.x, BL.y, 1, r, g, b);
    Window::DrawPrimitive::Line(TR.x, TR.y, BR.x, BR.y, 1, r, g, b);
}