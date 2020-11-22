#pragma once

#include <functional>

#include "entity.h"
#include "selfregister.h"

import bounds;

// Boxes with box
inline bool Collide(const Bounds& a, const Bounds& b) {
    return (a.left < b.left + b.width &&
        a.left + a.width > b.left &&
        a.top < b.top + b.height &&
        a.top + a.height > b.top);
}
// Circle with circle
inline bool Collide(const CircleBounds& a, const CircleBounds& b)
{
    return a.DistanceSq(b) < 0;
}

// Circle with box
inline bool Collide(const CircleBounds& a, const Bounds& b)
{
    return b.DistanceSq(a) < 0;
}
inline bool Collide(const Bounds& a, const CircleBounds& b)
{
    return b.DistanceSq(a) < 0;
}


// Entities
inline bool Collide(const BoxEntity* a, const BoxEntity* b) {
    return Collide(a->bounds(), b->bounds());
}
inline bool Collide(const CircleEntity* a, const CircleEntity* b) {
    return Collide(a->bounds(), b->bounds());
}
inline bool Collide(const CircleEntity* a, const BoxEntity* b) {
    return Collide(a->bounds(), b->bounds());
}

// Calls callback for each pair of colliding objects
template <typename A, typename B, typename F>
void CollideAll(const std::vector<A*>& setA, const std::vector<B*>& setB, F callback)
{
    size_t sa = setA.size();
    for (size_t i = 0; i < sa; ++i)
    {
        A* a = setA[i];
        size_t sb = setB.size();
        for (size_t j = 0; j < sb; ++j)
        {
            B* b = setB[j];
            if ((void*)a == (void*)b) continue;
            if (Collide(a, b))
            {
                callback(a, b);
            }
        }
    }
}

// Calls callback for each pair of colliding objects
template <typename T, typename F>
void CollideSelf(const std::vector<T*>& setA, F callback)
{
    size_t sa = setA.size();
    for (size_t i = 0; i < sa; ++i)
    {
        T* a = setA[i];
        for (size_t j = i+1; j < sa; ++j)
        {
            T* b = setA[j];
            if (Collide(a, b))
            {
                callback(a, b);
            }
        }
    }
}

template <typename T>
struct SelfColliding
{
    T* collidingWith = (T*)0xCACA0BAD; // If you see this value you forgot to call SelfCollide

    static void SelfCollide()
    {
        const std::vector<T*>& setA = T::GetAll();
        size_t sa = setA.size();
        for (size_t i = 0; i < sa; ++i) {
            setA[i]->collidingWith = nullptr;
        }
        for (size_t i = 0; i < sa; ++i)
        {
            T* a = setA[i];
            for (size_t j = i + 1; j < sa; ++j)
            {
                T* b = setA[j];
                if (Collide(a, b))
                {
                    a->collidingWith = b;
                    b->collidingWith = a;
                    break;
                }
            }
        }
    }
};
