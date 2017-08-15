/******************************************************************************************
*	Chili DirectX Framework Version 16.10.01											  *
*	Mat2.h																				  *
*	Copyright 2016 PlanetChili <http://www.planetchili.net>								  *
*																						  *
*	This file is part of The Chili DirectX Framework.									  *
*																						  *
*	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
*	it under the terms of the GNU General Public License as published by				  *
*	the Free Software Foundation, either version 3 of the License, or					  *
*	(at your option) any later version.													  *
*																						  *
*	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
*	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
*	GNU General Public License for more details.										  *
*																						  *
*	You should have received a copy of the GNU General Public License					  *
*	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
******************************************************************************************/
#pragma once

#include "Vec4.h"

template <typename T>
class _Mat4
{
public:
	_Mat4& operator=(const _Mat4& rhs)
	{
		memcpy(elements, rhs.elements, sizeof(elements));
		return *this;
	}
	_Mat4& operator*=(T rhs)
	{
		for (auto& row : elements)
		{
			for (T& e : row)
			{
				e *= rhs;
			}
		}
		return *this;
	}
	_Mat4 operator*(T rhs) const
	{
		_Mat4 result = *this;
		return result *= rhs;
	}
	_Mat4 operator*(const _Mat4& rhs) const
	{
		_Mat4 result;
		for (size_t j = 0; j < 4; j++)
		{
			for (size_t k = 0; k < 4; k++)
			{
				T sum = (T)0.0;
				for (size_t i = 0; i < 4; i++)
				{
					sum += elements[j][i] * rhs.elements[i][k];
				}
				result.elements[j][k] = sum;
			}
		}
		return result;
	}

	static _Mat4 Identity()
	{
		return {
			(T)1.0, (T)0.0, (T)0.0, (T)0.0,
			(T)0.0, (T)1.0, (T)0.0, (T)0.0,
			(T)0.0, (T)0.0, (T)1.0, (T)0.0,
			(T)0.0, (T)0.0, (T)0.0, (T)1.0
		};
	}
	static _Mat4 Scaling(T scale)
	{
		return
		{
			 scale, (T)0.0, (T)0.0, (T)0.0,
			(T)0.0,  scale, (T)0.0, (T)0.0,
			(T)0.0, (T)0.0,  scale, (T)0.0,
			(T)0.0, (T)0.0, (T)0.0, (T)1.0
		};
	}
	static _Mat4 RotationZ(T angle)
	{
		T sinAngle = sin(angle);
		T cosAngle = cos(angle);

		return
		{
			 cosAngle, sinAngle, (T)0.0, (T)0.0,
			-sinAngle, cosAngle, (T)0.0, (T)0.0,
			   (T)0.0,   (T)0.0, (T)1.0, (T)0.0,
			   (T)0.0,   (T)0.0, (T)0.0, (T)1.0
		};
	}
	static _Mat4 RotationY(T angle)
	{
		const T sinAngle = sin(angle);
		const T cosAngle = cos(angle);
		return
		{
			cosAngle, (T)0.0,-sinAngle, (T)0.0,
			  (T)0.0, (T)1.0,   (T)0.0, (T)0.0,
			sinAngle, (T)0.0, cosAngle, (T)0.0,
			(T)0.0,   (T)0.0,   (T)0.0, (T)1.0
		};
	}
	static _Mat4 RotationX(T angle)
	{
		const T sinAngle = sin(angle);
		const T cosAngle = cos(angle);
		return
		{
			(T)1.0,    (T)0.0,   (T)0.0, (T)0.0,
			(T)0.0,  cosAngle, sinAngle, (T)0.0,
			(T)0.0, -sinAngle, cosAngle, (T)0.0,
			(T)0.0,    (T)0.0,   (T)0.0, (T)1.0
		};
	}
public:
	// [ row ][ col ]
	T elements[4][4];
};

template<typename T>
_Vec4<T>& operator*=(_Vec4<T>& lhs, const _Mat4<T>& rhs)
{
	return lhs = lhs * rhs;
}

//template<typename T>
//_Vec4<T> operator*(const _Vec4<T>& lhs, const _Mat4<T>& rhs)
//{
//	return
//	{
//		lhs.x * rhs.elements[0][0] + lhs.y * rhs.elements[1][0] + lhs.z * rhs.elements[2][0],
//		lhs.x * rhs.elements[0][1] + lhs.y * rhs.elements[1][1] + lhs.z * rhs.elements[2][1],
//		lhs.x * rhs.elements[0][2] + lhs.y * rhs.elements[1][2] + lhs.z * rhs.elements[2][2]
//	};
//}

typedef _Mat4<float> Mat4;
typedef _Mat4<double> Mad4;