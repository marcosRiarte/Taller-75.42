#pragma once

struct vector2D
{
	vector2D() {}
	
	vector2D(float  x, float y) : x(x), y(y) {}	

	/// Establecer coordenadas.
	void Set(float  x_, float  y_) { x = x_; y = y_; }	

	/// Leer un elemento por índice.
	float operator () (int i) const
	{
		return (&x)[i];
	}

	/// Escribir un elemento por índice.
	float& operator () (int i)
	{
		return (&x)[i];
	}

	/// Sumar con otro vector.
	void operator += (const vector2D& v)
	{
		x += v.x; y += v.y;
	}

	/// Sustraer un vector de este vector.
	void operator -= (const vector2D& v)
	{
		x -= v.x; y -= v.y;
	}

	///Multiplicar por un escalar.
	void operator *= (float a)
	{
		x *= a; y *= a;
	}	

	///Multiplicar por un escalar.
	vector2D operator * (float a)
	{
		vector2D vectorNuevo = vector2D(x*a, y*a);
		return vectorNuevo;
	}

	///Dividir por un escalar.
	void operator /= (float a)
	{
		if (a != 0)
			x /= a; y /= a;
	}

	/// Longitud al cuadrado
	float Cuadrado() const
	{
		return x * x + y * y;
	}
	
	/// Modulo del vector
	float Modulo() const
	{
		return sqrtf(x*x + y*y);
	}

	/// Convierte a vector unitario y devuelve el largo o módulo.
	float Normalizar()
	{
		float largo = Modulo();
		if (largo < FLT_EPSILON)
			return 0.0f;

		float invLargo = 1.0f / largo;
		x *= invLargo;
		y *= invLargo;

		return largo;
	}

	vector2D Negativo()
	{
		return vector2D(-x, -y);
	}

	float x, y;
};

