#pragma once

namespace text_mode
{
	struct cell
	{
		char character;
		byte attributes;
		
		cell(char character, byte attributes) : character(character), attributes(attributes)
		{
		}
		
		cell()
		{
		}
	};

}
