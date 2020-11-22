module; 

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include "SDL_gpu.h"

export module bounds;

import vec;
import window;

export struct CircleBounds;

export struct Bounds
{
    float left, top;
    float width, height;

    inline constexpr Bounds(float x, float y, float w, float h) : left(x), top(y), width(w), height(h) { }
    inline constexpr Bounds() : Bounds(-1,-1,0,0) { }
    inline constexpr Bounds(const vec& topleft, const vec& size) : Bounds(topleft.x, topleft.y, size.x, size.y) {}
    inline constexpr explicit Bounds(const vec& size) : Bounds(0,0,size.x,size.y) { }
    inline constexpr explicit Bounds(const vec& pos, const vec& size, const vec& origin) : Bounds(pos.x, pos.y, size.x, size.y) {
        left -= origin.x;
        top -= origin.y;
    }

    [[nodiscard]] inline static constexpr Bounds fromCenter(const vec& center, const vec& size) { return Bounds(center - size/2, size); }

    [[nodiscard]] inline GPU_Rect AsRect() {
        return GPU_Rect{ left, top, width, height };
    }

    //Expands arround the center by a factor
    [[nodiscard]] inline Bounds operator*(float f)
	{
        vec center = Center();
        Bounds ret = *this;
        ret.width *= f;
        ret.height *= f;
        ret.SetCenter(center);
        return ret;
    }

    [[nodiscard]] inline constexpr vec Center() const
	{
		return vec(left + width/2, top + height/2);
	}

    [[nodiscard]] inline constexpr float Area() const
    {
        return width * height;
    }

    inline void SetCenter(float x, float y)
	{
        left = x - width/2;
        top = y - height/2;
    }

    inline void SetCenter(const vec& center)
	{
        SetCenter(center.x, center.y);
    }

    inline void SetTopLeft(float x, float y)
    {
        left = x;
        top = y;
    }

    inline void SetTopLeft(const vec& center)
    {
        SetTopLeft(center.x, center.y);
    }

    void Draw(uint8_t r = 255, uint8_t g = 0, uint8_t b = 0) const 
    {
        Window::DrawPrimitive::Rectangle(*this, 1, r, g, b);
    }

    [[nodiscard]] inline constexpr float Top() const
	{
        return top;
    }

    [[nodiscard]] inline constexpr float Bottom() const
	{
        return top + height;
    }

    [[nodiscard]] inline constexpr float Left() const
	{
        return left;
    }

    [[nodiscard]] inline constexpr float Right() const
	{
        return left + width;
    }

    [[nodiscard]] inline constexpr vec TopLeft() const {
        return vec(Left(), Top());
    }

    [[nodiscard]] inline constexpr vec TopRight() const {
        return vec(Right(), Top());
    }

    [[nodiscard]] inline constexpr vec BottomLeft() const {
        return vec(Left(), Bottom());
    }

    [[nodiscard]] inline constexpr vec BottomRight() const {
        return vec(Right(), Bottom());
    }

    [[nodiscard]] inline bool Contains(float x, float y) const
    {
        if (x < left) return false;
        if (x >= left + width) return false;
        if (y < top) return false;
        if (y >= top + height) return false;
        return true;
    }

    [[nodiscard]] inline bool Contains(const vec& point) const
	{
        return Contains(point.x, point.y);
    }

    [[nodiscard]] inline bool Contains(const Bounds& b) const
    {
        if (b.left < left) return false;
        if (b.left+b.width >= left + width) return false;
        if (b.top < top) return false;
        if (b.top+ b.height >= top + height) return false;
        return true;
    }

    [[nodiscard]] inline constexpr vec Size() const {
        return vec(width, height);
    }

    [[nodiscard]] inline vec ClosesPointInBounds(const vec& target) const;
    [[nodiscard]] inline float DistanceSq(const Bounds& a) const;
    [[nodiscard]] inline float DistanceSq(const CircleBounds& a) const;
    [[nodiscard]] inline float Distance(const Bounds& a) const;
    [[nodiscard]] inline float Distance(const CircleBounds& a) const;

    //TODO
    //void ExpandToInclude(vec point);

};

export struct CircleBounds
{
    inline constexpr CircleBounds(const vec& pos, float radius) : pos(pos), radius(radius) {}
    vec pos;
    float radius;

    void Draw(uint8_t r = 255, uint8_t g = 0, uint8_t b = 0) const {
        Window::DrawPrimitive::Circle(*this, 1, r, g, b);
    }

    [[nodiscard]] inline const vec& Center() const { return pos; }

    [[nodiscard]] inline float DistanceSq(const Bounds& a) const { return a.DistanceSq(*this); }
    [[nodiscard]] inline float Distance(const Bounds& a) const { return a.Distance(*this); }
    
    [[nodiscard]] inline float DistanceSq(const CircleBounds& a) const {
        return a.pos.DistanceSq(this->pos) - (a.radius + this->radius) * (a.radius + this->radius);
    }
    [[nodiscard]] inline float Distance(const CircleBounds& a) const {
        return a.pos.Distance(this->pos) - (a.radius + this->radius);
    }
};

inline float Bounds::DistanceSq(const Bounds& a) const {
    float sqrDist = 0;
    if (a.Right() < this->left) {
        float d = a.Right() - this->left;
        sqrDist += d * d;
    } else if (a.left > this->Right()) {
        float d = a.left - this->Right();
        sqrDist += d * d;
    }
    if (a.Bottom() < this->top) {
        float d = a.Bottom() - this->top;
        sqrDist += d * d;
    }
    else if (a.top > this->Bottom()) {
        float d = a.top - this->Bottom();
        sqrDist += d * d;
    }
    return sqrDist;
}

inline vec Bounds::ClosesPointInBounds(const vec& target) const {
    vec distance = this->Center() - target;
    distance.Clamp(-this->Size() / 2, this->Size() / 2);
    vec closestPoint = this->Center() - distance;
    return closestPoint;
}

inline float Bounds::DistanceSq(const CircleBounds& a) const {
    vec closestPoint = ClosesPointInBounds(a.pos);
    //closestPoint.Debuggerino();
    return closestPoint.DistanceSq(a.pos) - (a.radius * a.radius);
}

inline float Bounds::Distance(const Bounds& a) const
{
    return sqrt(DistanceSq(a));
}

inline float Bounds::Distance(const CircleBounds& a) const
{
    return sqrt(DistanceSq(a));
}

export inline std::ostream& operator<<(std::ostream& os, const Bounds& rhs)
{
    os << " " << rhs.left << " " << rhs.top << " " << rhs.width << " " << rhs.height;
    return os;
}
