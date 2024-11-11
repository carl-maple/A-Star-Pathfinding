#pragma once

#include "Types.h"

struct SVector2Di
{
	constexpr SVector2Di() {};

	constexpr SVector2Di(int32 InX, int32 InY)
		: x(InX), y(InY) {}

	SVector2Di operator+(const SVector2Di& InOther) const
	{
		return SVector2Di(x + InOther.x, y + InOther.y);
	}

	SVector2Di operator+=(const SVector2Di& InOther)
	{
		x += InOther.x;
		y += InOther.y;
	}

	void operator=(const SVector2Di& InOther)
	{
		x = InOther.x;
		y = InOther.y;
	}

	int32 x = 0;
	int32 y = 0;
};

