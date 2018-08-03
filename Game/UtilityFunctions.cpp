#include "UtilityFunctions.h"

void formatText(Text* text, int x, int y, Color fillColor, Color outlineColor, bool outline)
{
	text->setFillColor(fillColor);
	if (outline)
	{
		text->setOutlineThickness(3);
		text->setOutlineColor(outlineColor);
	}
	text->setPosition(x, y);
}