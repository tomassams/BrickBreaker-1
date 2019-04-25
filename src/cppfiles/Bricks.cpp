#include "../header/Bricks.h"

void Bricks:: InitializeBricks(int top)
{
	brickVector.clear();

	int horizontalSpacing = top;

	for (int i = 0; i < brickY; i++)
	{
		int verticalSpacing = 10;
		for (int j = 0; j < brickX; j++)
		{
			brickVector.emplace_back(verticalSpacing, horizontalSpacing, brickY-i);
			verticalSpacing += 88;
		}
		horizontalSpacing += 40;
	}
}
