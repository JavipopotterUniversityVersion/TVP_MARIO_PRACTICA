#include "Vector2D.h"



template <typename T> Vector2D<T> Vector2D<T>::operator +(Vector2D<T> other) const
{
	return Vector2D<T>(x + other.x, y + other.y);
}

template <typename T> Vector2D<T> Vector2D<T>::operator +=(Vector2D<T> other) const
{
	Vector2D temp = Vector2D<T>(x + other.x, y + other.y);
	x = temp.x;
	y = temp.y;
	return temp;
}

template <typename T> Vector2D<T> Vector2D<T>::operator -(Vector2D<T> other) const
{
	return Vector2D<T>(x - other.x, y - other.y);
}

template <typename T> Vector2D<T> Vector2D<T>::operator *(T scalar) const
{
	return Vector2D<T>(x * scalar, y * scalar);
}

template <typename T> Vector2D<T> Vector2D<T>::operator *(Vector2D<T> other) const
{
	return Vector2D<T>(x * other.x, y * other.y);
}