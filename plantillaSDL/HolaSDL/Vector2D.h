#pragma once
template <typename T>
class Vector2D
{
	private:
		T x, y;

	public:
		Vector2D() : x(), y() {}
		Vector2D(T x, T y) : x(x), y(y) {}
		T getX() const { return x; }
		T getY() const { return y; }

		Vector2D<T> operator +(Vector2D<T> other) const;
		Vector2D<T> operator -(Vector2D<T> other) const;
		
		T operator *(Vector2D<T> other) const;
		Vector2D<T> operator *(T scalar) const;
		Vector2D<T> operator *(Vector2D<T> other) const;

		void Set(T newX, T newY)
		{
			x = newX;
			y = newY;
		}
};

template <typename T>
using Point2D = Vector2D<T>;