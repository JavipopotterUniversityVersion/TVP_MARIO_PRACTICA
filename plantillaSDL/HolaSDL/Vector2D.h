#pragma once
template <typename T>
class Vector2D
{
	private:
		T x, y;

	public:
		Vector2D(T x, T y) : x(x), y(y) {}
		T getX() const { return x; }
		T getY() const { return y; }

		Vector2D<T> operator +(Vector2D<T> other) const;
		Vector2D<T> operator -(Vector2D<T> other) const;
		
		T operator *(Vector2D<T> other) const;
		Vector2D<T> operator *(T scalar) const;
		Vector2D<T> operator *(Vector2D<T> other) const;
};

template <typename T>
using Point2D = Vector2D<T>;