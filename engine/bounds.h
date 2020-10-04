#pragma once

#ifndef _USE_MATH_DEFINES 
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#include "vec.h"
#include "SDL_gpu.h"

struct CircleBounds;

struct Bounds
{
    float left, top;
    float width, height;

    constexpr Bounds(float x, float y, float w, float h) : left(x), top(y), width(w), height(h) { }
    constexpr Bounds() : Bounds(-1,-1,0,0) { }
    constexpr Bounds(const vec& topleft, const vec& size) : Bounds(topleft.x, topleft.y, size.x, size.y) {}
    constexpr explicit Bounds(const vec& size) : Bounds(0,0,size.x,size.y) { }
    constexpr explicit Bounds(const vec& pos, const vec& size, const vec& origin) : Bounds(pos.x, pos.y, size.x, size.y) {
        left -= origin.x;
        top -= origin.y;
    }

    [[nodiscard]] static constexpr Bounds fromCenter(const vec& center, const vec& size) { return Bounds(center - size/2, size); }

    [[nodiscard]] GPU_Rect AsRect() {
        return GPU_Rect{ left, top, width, height };
    }

    //Expands arround the center by a factor
    [[nodiscard]] Bounds operator*(float f)
	{
        vec center = Center();
        Bounds ret = *this;
        ret.width *= f;
        ret.height *= f;
        ret.SetCenter(center);
        return ret;
    }

    [[nodiscard]] constexpr vec Center() const
	{
		return vec(left + width/2, top + height/2);
	}

    [[nodiscard]] constexpr float Area() const
    {
        return width * height;
    }

    void SetCenter(float x, float y)
	{
        left = x - width/2;
        top = y - height/2;
    }

    void SetCenter(const vec& center)
	{
        SetCenter(center.x, center.y);
    }

    void SetTopLeft(float x, float y)
    {
        left = x;
        top = y;
    }

    void SetTopLeft(const vec& center)
    {
        SetTopLeft(center.x, center.y);
    }

    void Draw(uint8_t r = 255, uint8_t g = 0, uint8_t b = 0) const;

    [[nodiscard]] constexpr float Top() const
	{
        return top;
    }

    [[nodiscard]] constexpr float Bottom() const
	{
        return top + height;
    }

    [[nodiscard]] constexpr float Left() const
	{
        return left;
    }

    [[nodiscard]] constexpr float Right() const
	{
        return left + width;
    }

    [[nodiscard]] constexpr vec TopLeft() const {
        return vec(Left(), Top());
    }

    [[nodiscard]] constexpr vec TopRight() const {
        return vec(Right(), Top());
    }

    [[nodiscard]] constexpr vec BottomLeft() const {
        return vec(Left(), Bottom());
    }

    [[nodiscard]] constexpr vec BottomRight() const {
        return vec(Right(), Bottom());
    }

    [[nodiscard]] bool Contains(const vec& point) const
	{
        if (point.x < left) return false;
        if (point.x >= left+width) return false;
        if (point.y < top) return false;
        if (point.y >= top+height) return false;
		return true;
    }

    [[nodiscard]] bool Contains(const Bounds& b) const
    {
        if (b.left < left) return false;
        if (b.left+b.width >= left + width) return false;
        if (b.top < top) return false;
        if (b.top+ b.height >= top + height) return false;
        return true;
    }

    [[nodiscard]] constexpr vec Size() const {
        return vec(width, height);
    }

    [[nodiscard]] vec ClosesPointInBounds(const vec& target) const;
    [[nodiscard]] float DistanceSq(const Bounds& a) const;
    [[nodiscard]] float DistanceSq(const CircleBounds& a) const;
    [[nodiscard]] float Distance(const Bounds& a) const;
    [[nodiscard]] float Distance(const CircleBounds& a) const;

    //TODO
    //void ExpandToInclude(vec point);

};

struct RotableBounds : public Bounds
{
    vec TL, TR, BL, BR;
    float angle = 0.0f;

    RotableBounds() {}

    RotableBounds(const Bounds& b)
        : Bounds(b)
    {
        TL = b.TopLeft();
        TR = b.TopRight();
        BL = b.BottomLeft();
        BR = b.BottomRight();
    }

    RotableBounds(const Bounds& b, float angle) 
        : Bounds(b)
        , angle(angle)
    {
        UpdateCorners();
    }

    RotableBounds(float x, float y, float w, float h, float angle)
        : Bounds(x, y, w, h)
        , angle(angle)
    { 
        UpdateCorners();
    }

    void UpdateCorners()
    {
        TL = vec(left, top);
        TR = vec(left + width, top);
        BL = vec(left, top + height);
        BR = vec(left + width, top + height);

        float s = sin(angle * M_PI / 180.0f);
        float c = cos(angle * M_PI / 180.0f);

        {
            TR = TR - TL;
            float TR_x = TR.x * c - TR.y * s;
            float TR_y = TR.x * s + TR.y * c;
            TR.x = TR_x;
            TR.y = TR_y;
            TR = TR + TL;
        }

        {
            BL = BL - TL;
            float BL_x = BL.x * c - BL.y * s;
            float BL_y = BL.x * s + BL.y * c;
            BL.x = BL_x;
            BL.y = BL_y;
            BL = BL + TL;
        }

        {
            BR = BR - TL;
            float BR_x = BR.x * c - BR.y * s;
            float BR_y = BR.x * s + BR.y * c;
            BR.x = BR_x;
            BR.y = BR_y;
            BR = BR + TL;
        }
    }


    void Draw(uint8_t r = 255, uint8_t g = 0, uint8_t b = 0) const;

    //https://www.gamedev.net/tutorials/programming/general-and-gameplay-programming/2d-rotated-rectangle-collision-r2604/
    bool Collision(const RotableBounds& rb)
    {
        vec Axis1(this->TR.x - this->TL.x, this->TR.y - this->TL.y);
        {
            float ax1_tl_a_k = (this->TL.x * Axis1.x + this->TL.y * Axis1.y) / (Axis1.x * Axis1.x + Axis1.y * Axis1.y);
            vec ax1_tl_a = Axis1 * ax1_tl_a_k;

            float ax1_tr_a_k = (this->TR.x * Axis1.x + this->TR.y * Axis1.y) / (Axis1.x * Axis1.x + Axis1.y * Axis1.y);
            vec ax1_tr_a = Axis1 * ax1_tr_a_k;


            float ax1_tl_b_k = (rb.TL.x * Axis1.x + rb.TL.y * Axis1.y) / (Axis1.x * Axis1.x + Axis1.y * Axis1.y);
            vec ax1_tl_b(ax1_tl_b_k * Axis1.x, ax1_tl_b_k * Axis1.y);

            float ax1_tr_b_k = (rb.TR.x * Axis1.x + rb.TR.y * Axis1.y) / (Axis1.x * Axis1.x + Axis1.y * Axis1.y);
            vec ax1_tr_b(ax1_tr_b_k * Axis1.x, ax1_tr_b_k * Axis1.y);

            float ax1_bl_b_k = (rb.BL.x * Axis1.x + rb.BL.y * Axis1.y) / (Axis1.x * Axis1.x + Axis1.y * Axis1.y);
            vec ax1_bl_b(ax1_bl_b_k * Axis1.x, ax1_bl_b_k * Axis1.y);

            float ax1_br_b_k = (rb.BR.x * Axis1.x + rb.BR.y * Axis1.y) / (Axis1.x * Axis1.x + Axis1.y * Axis1.y);
            vec ax1_br_b(ax1_br_b_k * Axis1.x, ax1_br_b_k * Axis1.y);


            float ax1_tl_a_sc = ax1_tl_a.x * Axis1.x + ax1_tl_a.y * Axis1.y;
            float ax1_tr_a_sc = ax1_tr_a.x * Axis1.x + ax1_tr_a.y * Axis1.y;

            float ax1_tl_b_sc = ax1_tl_b.x * Axis1.x + ax1_tl_b.y * Axis1.y;
            float ax1_tr_b_sc = ax1_tr_b.x * Axis1.x + ax1_tr_b.y * Axis1.y;
            float ax1_bl_b_sc = ax1_bl_b.x * Axis1.x + ax1_bl_b.y * Axis1.y;
            float ax1_br_b_sc = ax1_br_b.x * Axis1.x + ax1_br_b.y * Axis1.y;

            float min_a = ax1_tl_a_sc;
            if (ax1_tr_a_sc < min_a) min_a = ax1_tr_a_sc;

            float max_a = ax1_tl_a_sc;
            if (ax1_tr_a_sc > max_a) max_a = ax1_tr_a_sc;

            float min_b = ax1_tl_b_sc;
            if (ax1_tr_b_sc < min_b) min_b = ax1_tr_b_sc;
            if (ax1_bl_b_sc < min_b) min_b = ax1_bl_b_sc;
            if (ax1_br_b_sc < min_b) min_b = ax1_br_b_sc;

            float max_b = ax1_tl_b_sc;
            if (ax1_tr_b_sc > max_b) max_b = ax1_tr_b_sc;
            if (ax1_bl_b_sc > max_b) max_b = ax1_bl_b_sc;
            if (ax1_br_b_sc > max_b) max_b = ax1_br_b_sc;

            bool overlap = false;
            if ((min_b <= max_a) && (max_b >= min_a)) overlap = true;

            if (!overlap)
            {
                return false;
            }
        }

        vec Axis2(this->TR.x - this->BR.x, this->TR.y - this->BR.y);
        {
            float ax1_tl_a_k = (this->TL.x * Axis2.x + this->TL.y * Axis2.y) / (Axis2.x * Axis2.x + Axis2.y * Axis2.y);
            vec ax1_tl_a = Axis2 * ax1_tl_a_k;

            float ax1_br_a_k = (this->BR.x * Axis2.x + this->BR.y * Axis2.y) / (Axis2.x * Axis2.x + Axis2.y * Axis2.y);
            vec ax1_br_a = Axis2 * ax1_br_a_k;


            float ax1_tl_b_k = (rb.TL.x * Axis2.x + rb.TL.y * Axis2.y) / (Axis2.x * Axis2.x + Axis2.y * Axis2.y);
            vec ax1_tl_b(ax1_tl_b_k * Axis2.x, ax1_tl_b_k * Axis2.y);

            float ax1_tr_b_k = (rb.TR.x * Axis2.x + rb.TR.y * Axis2.y) / (Axis2.x * Axis2.x + Axis2.y * Axis2.y);
            vec ax1_tr_b(ax1_tr_b_k * Axis2.x, ax1_tr_b_k * Axis2.y);

            float ax1_bl_b_k = (rb.BL.x * Axis2.x + rb.BL.y * Axis2.y) / (Axis2.x * Axis2.x + Axis2.y * Axis2.y);
            vec ax1_bl_b(ax1_bl_b_k * Axis2.x, ax1_bl_b_k * Axis2.y);

            float ax1_br_b_k = (rb.BR.x * Axis2.x + rb.BR.y * Axis2.y) / (Axis2.x * Axis2.x + Axis2.y * Axis2.y);
            vec ax1_br_b(ax1_br_b_k * Axis2.x, ax1_br_b_k * Axis2.y);


            float ax1_tl_a_sc = ax1_tl_a.x * Axis2.x + ax1_tl_a.y * Axis2.y;
            float ax1_br_a_sc = ax1_br_a.x * Axis2.x + ax1_br_a.y * Axis2.y;

            float ax1_tl_b_sc = ax1_tl_b.x * Axis2.x + ax1_tl_b.y * Axis2.y;
            float ax1_tr_b_sc = ax1_tr_b.x * Axis2.x + ax1_tr_b.y * Axis2.y;
            float ax1_bl_b_sc = ax1_bl_b.x * Axis2.x + ax1_bl_b.y * Axis2.y;
            float ax1_br_b_sc = ax1_br_b.x * Axis2.x + ax1_br_b.y * Axis2.y;

            float min_a = ax1_tl_a_sc;
            if (ax1_br_a_sc < min_a) min_a = ax1_br_a_sc;

            float max_a = ax1_tl_a_sc;
            if (ax1_br_a_sc > max_a) max_a = ax1_br_a_sc;

            float min_b = ax1_tl_b_sc;
            if (ax1_tr_b_sc < min_b) min_b = ax1_tr_b_sc;
            if (ax1_bl_b_sc < min_b) min_b = ax1_bl_b_sc;
            if (ax1_br_b_sc < min_b) min_b = ax1_br_b_sc;

            float max_b = ax1_tl_b_sc;
            if (ax1_tr_b_sc > max_b) max_b = ax1_tr_b_sc;
            if (ax1_bl_b_sc > max_b) max_b = ax1_bl_b_sc;
            if (ax1_br_b_sc > max_b) max_b = ax1_br_b_sc;

            bool overlap = false;
            if ((min_b <= max_a) && (max_b >= min_a)) overlap = true;

            if (!overlap)
            {
                return false;
            }
        }


        vec Axis3(rb.TL.x - rb.BL.x, rb.TL.y - rb.BL.y);
        {
            float ax1_tl_a_k = (this->TL.x * Axis3.x + this->TL.y * Axis3.y) / (Axis3.x * Axis3.x + Axis3.y * Axis3.y);
            vec ax1_tl_a = Axis3 * ax1_tl_a_k;

            float ax1_tr_a_k = (this->TR.x * Axis3.x + this->TR.y * Axis3.y) / (Axis3.x * Axis3.x + Axis3.y * Axis3.y);
            vec ax1_tr_a = Axis3 * ax1_tr_a_k;

            float ax1_br_a_k = (this->BR.x * Axis3.x + this->BR.y * Axis3.y) / (Axis3.x * Axis3.x + Axis3.y * Axis3.y);
            vec ax1_br_a = Axis3 * ax1_br_a_k;

            float ax1_bl_a_k = (this->BL.x * Axis3.x + this->BL.y * Axis3.y) / (Axis3.x * Axis3.x + Axis3.y * Axis3.y);
            vec ax1_bl_a = Axis3 * ax1_bl_a_k;


            float ax1_tl_b_k = (rb.TL.x * Axis3.x + rb.TL.y * Axis3.y) / (Axis3.x * Axis3.x + Axis3.y * Axis3.y);
            vec ax1_tl_b(ax1_tl_b_k * Axis3.x, ax1_tl_b_k * Axis3.y);

            float ax1_bl_b_k = (rb.BL.x * Axis3.x + rb.BL.y * Axis3.y) / (Axis3.x * Axis3.x + Axis3.y * Axis3.y);
            vec ax1_bl_b(ax1_bl_b_k * Axis3.x, ax1_bl_b_k * Axis3.y);

            float ax1_tl_a_sc = ax1_tl_a.x * Axis3.x + ax1_tl_a.y * Axis3.y;
            float ax1_tr_a_sc = ax1_tr_a.x * Axis3.x + ax1_tr_a.y * Axis3.y;
            float ax1_bl_a_sc = ax1_bl_a.x * Axis3.x + ax1_bl_a.y * Axis3.y;
            float ax1_br_a_sc = ax1_br_a.x * Axis3.x + ax1_br_a.y * Axis3.y;

            float ax1_tl_b_sc = ax1_tl_b.x * Axis3.x + ax1_tl_b.y * Axis3.y;
            float ax1_bl_b_sc = ax1_bl_b.x * Axis3.x + ax1_bl_b.y * Axis3.y;

            float min_a = ax1_tl_a_sc;
            if (ax1_tr_a_sc < min_a) min_a = ax1_tr_a_sc;
            if (ax1_bl_a_sc < min_a) min_a = ax1_bl_a_sc;
            if (ax1_br_a_sc < min_a) min_a = ax1_br_a_sc;


            float max_a = ax1_tl_a_sc;
            if (ax1_tr_a_sc > max_a) max_a = ax1_tr_a_sc;
            if (ax1_bl_a_sc > max_a) max_a = ax1_bl_a_sc;
            if (ax1_br_a_sc > max_a) max_a = ax1_br_a_sc;


            float min_b = ax1_tl_b_sc;
            if (ax1_bl_b_sc < min_b) min_b = ax1_bl_b_sc;

            float max_b = ax1_tl_b_sc;
            if (ax1_bl_b_sc > max_b) max_b = ax1_bl_b_sc;

            bool overlap = false;
            if ((min_b <= max_a) && (max_b >= min_a)) overlap = true;

            if (!overlap)
            {
                return false;
            }
        }


        vec Axis4(rb.TL.x - rb.TR.x, rb.TL.y - rb.TR.y);
        {
            float ax1_tl_a_k = (this->TL.x * Axis4.x + this->TL.y * Axis4.y) / (Axis4.x * Axis4.x + Axis4.y * Axis4.y);
            vec ax1_tl_a = Axis4 * ax1_tl_a_k;

            float ax1_tr_a_k = (this->TR.x * Axis4.x + this->TR.y * Axis4.y) / (Axis4.x * Axis4.x + Axis4.y * Axis4.y);
            vec ax1_tr_a = Axis4 * ax1_tr_a_k;

            float ax1_br_a_k = (this->BR.x * Axis4.x + this->BR.y * Axis4.y) / (Axis4.x * Axis4.x + Axis4.y * Axis4.y);
            vec ax1_br_a = Axis4 * ax1_br_a_k;

            float ax1_bl_a_k = (this->BL.x * Axis4.x + this->BL.y * Axis4.y) / (Axis4.x * Axis4.x + Axis4.y * Axis4.y);
            vec ax1_bl_a = Axis4 * ax1_bl_a_k;


            float ax1_tl_b_k = (rb.TL.x * Axis4.x + rb.TL.y * Axis4.y) / (Axis4.x * Axis4.x + Axis4.y * Axis4.y);
            vec ax1_tl_b(ax1_tl_b_k * Axis4.x, ax1_tl_b_k * Axis4.y);

            float ax1_tr_b_k = (rb.TR.x * Axis4.x + rb.TR.y * Axis4.y) / (Axis4.x * Axis4.x + Axis4.y * Axis4.y);
            vec ax1_tr_b(ax1_tr_b_k * Axis4.x, ax1_tr_b_k * Axis4.y);


            float ax1_tl_a_sc = ax1_tl_a.x * Axis4.x + ax1_tl_a.y * Axis4.y;
            float ax1_tr_a_sc = ax1_tr_a.x * Axis4.x + ax1_tr_a.y * Axis4.y;
            float ax1_bl_a_sc = ax1_bl_a.x * Axis4.x + ax1_bl_a.y * Axis4.y;
            float ax1_br_a_sc = ax1_br_a.x * Axis4.x + ax1_br_a.y * Axis4.y;

            float ax1_tl_b_sc = ax1_tl_b.x * Axis4.x + ax1_tl_b.y * Axis4.y;
            float ax1_tr_b_sc = ax1_tr_b.x * Axis4.x + ax1_tr_b.y * Axis4.y;

            float min_a = ax1_tl_a_sc;
            if (ax1_tr_a_sc < min_a) min_a = ax1_tr_a_sc;
            if (ax1_bl_a_sc < min_a) min_a = ax1_bl_a_sc;
            if (ax1_br_a_sc < min_a) min_a = ax1_br_a_sc;


            float max_a = ax1_tl_a_sc;
            if (ax1_tr_a_sc > max_a) max_a = ax1_tr_a_sc;
            if (ax1_bl_a_sc > max_a) max_a = ax1_bl_a_sc;
            if (ax1_br_a_sc > max_a) max_a = ax1_br_a_sc;


            float min_b = ax1_tl_b_sc;
            if (ax1_tr_b_sc < min_b) min_b = ax1_tr_b_sc;

            float max_b = ax1_tl_b_sc;
            if (ax1_tr_b_sc > max_b) max_b = ax1_tr_b_sc;

            bool overlap = false;
            if ((min_b <= max_a) && (max_b >= min_a)) overlap = true;

            if (!overlap)
            {
                return false;
            }
        }


        return true;
        
    }
};


struct CircleBounds
{
    constexpr CircleBounds(const vec& pos, float radius) : pos(pos), radius(radius) {}
    vec pos;
    float radius;

    void Draw(uint8_t r = 255, uint8_t g = 0, uint8_t b = 0) const;

    [[nodiscard]] const vec& Center() const { return pos; }

    [[nodiscard]] float DistanceSq(const Bounds& a) const { return a.DistanceSq(*this); }
    [[nodiscard]] float Distance(const Bounds& a) const { return a.Distance(*this); }
    
    [[nodiscard]] float DistanceSq(const CircleBounds& a) const {
        return a.pos.DistanceSq(this->pos) - (a.radius + this->radius) * (a.radius + this->radius);
    }
    [[nodiscard]] float Distance(const CircleBounds& a) const { 
        return a.pos.Distance(this->pos) - (a.radius + this->radius);
    }
};

inline float Bounds::DistanceSq(const Bounds& a) const 
{
    float sqrDist = 0;

    if (a.Right() < this->left) 
    {
        float d = a.Right() - this->left;
        sqrDist += d * d;
    } 
    else if (a.left > this->Right()) 
    {
        float d = a.left - this->Right();
        sqrDist += d * d;
    }

    if (a.Bottom() < this->top) 
    {
        float d = a.Bottom() - this->top;
        sqrDist += d * d;
    }
    else if (a.top > this->Bottom()) 
    {
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

inline std::ostream& operator<<(std::ostream& os, const Bounds& rhs)
{
    os << " " << rhs.left << " " << rhs.top << " " << rhs.width << " " << rhs.height;
    return os;
}
