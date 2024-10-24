#include "Vector2D.h"
template <typename T>

T Vector2D<T>::operator*(Vector2D<T> other) const
{
	return x * other.x + y * other.y;
}

template <typename T>
Vector2D<T> Vector2D<T>::operator +(Vector2D<T> other) const
{
	return Vector2D<T>(x + other.x, y + other.y);
}

template <typename T>
Vector2D<T> Vector2D<T>::operator -(Vector2D<T> other) const
{
	return Vector2D<T>(x - other.x, y - other.y);
}

template <typename T>
Vector2D<T> Vector2D<T>::operator *(T scalar) const
{
	return Vector2D<T>(x * scalar, y * scalar);
}