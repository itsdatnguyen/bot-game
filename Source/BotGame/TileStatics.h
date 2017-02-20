#pragma once


class TileStatics
{
public:
	// with a hexagon scale of 0.86602540378, the spacing between hexagons become 150 and 75 for x and y respectively
	static constexpr float HexagonScale = 0.86602540378f;

	// The spacing between two hexagons
	static constexpr int TileSpacing = 150;

	// The spacing between two hexagons x wise
	static constexpr int TileSpacingX = 150;

	// The spacing between two hexagons y wise
	static constexpr int TileSpacingY = 130;
};