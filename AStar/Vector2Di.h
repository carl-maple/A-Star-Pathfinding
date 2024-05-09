#pragma once

#include "Types.h"

struct SVector2Di
{
	constexpr SVector2Di() {};

	constexpr SVector2Di(int16 InX, int16 InY)
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

	const int32 INVALID_INDEX = -1;

	int32 x = INVALID_INDEX;
	int32 y = INVALID_INDEX;
};

