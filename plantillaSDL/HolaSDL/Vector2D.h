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

		Vector2D<T> operator +(Vector2D<T> other) const
		{
			return Vector2D<T>(x + other.x, y + other.y);
		}

		Vector2D<T> operator +=(Vector2D<T> other)
		{
			Vector2D temp = Vector2D<T>(x + other.x, y + other.y);
			this->Set(temp.getX(), temp.getY());
			return temp;
		}

		Vector2D<T> operator -(Vector2D<T> other) const
		{
			return Vector2D<T>(x - other.x, y - other.y);
		}
		
		Vector2D<T> operator *(Vector2D<T> other) const
		{
			return Vector2D<T>(x * other.x, y * other.y);
		}

		Vector2D<T> operator *(T scalar) const
		{
			return Vector2D<T>(x * scalar, y * scalar);
		}

		void Set(T newX, T newY)
		{
			x = newX;
			y = newY;
		}

		void setX(T newX)
		{
			x = newX;
		}

		void setY(T newY)
		{
			y = newY;
		}
};