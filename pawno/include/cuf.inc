/*
	Copyright (c) 2012 cosmy

	Permission is hereby granted, free of charge, to any person
	obtaining a copy of this software and associated documentation
	files (the "Software"), to deal in the Software without
	restriction, including without limitation the rights to use,
	copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the
	Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be
	included in all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	OTHER DEALINGS IN THE SOFTWARE.
*/

// Portions from yom

// For comptibility
#define CONSOLE_DEFAULT			0x0000 | 0x0007
#define CONSOLE_GREY			0x0000 | 0x0008
#define CONSOLE_BLUE			0x0001 | 0x0008
#define CONSOLE_GREEN			0x0002 | 0x0008
#define CONSOLE_LIGHTBLUE		0x0003 | 0x0008
#define CONSOLE_RED				0x0004 | 0x0008
#define CONSOLE_PINK			0x0005 | 0x0008
#define CONSOLE_YELLOW			0x0006 | 0x0008
#define CONSOLE_WHITE			0x0007 | 0x0008

#define BACKGROUND_GREY		    0x0000 | 0x0080
#define BACKGROUND_BLUE		    0x0010 | 0x0080
#define BACKGROUND_GREEN	    0x0020 | 0x0080
#define BACKGROUND_LIGHTBLUE	0x0030 | 0x0080
#define BACKGROUND_RED		    0x0040 | 0x0080
#define BACKGROUND_PINK		    0x0050 | 0x0080
#define BACKGROUND_YELLOW	    0x0060 | 0x0080	
#define BACKGROUND_WHITE	    0x0070 | 0x0080	

native SetConsoleTextColors(colors);
native GetConsoleTextColors();

native SetConsoleCursorPos(x, y);
native GetConsoleCursorPos(&x, &y);

#pragma unused g_console_colors
new g_console_colors;

enum e_console_color
{
    BLACK,
    BLUE,
    GREEN,
    AQUA,
    RED,
    PURPLE,
    YELLOW,
    WHITE,
    GRAY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTAQUA,
    LIGHTRED,
    LIGHTPURLE,
    LIGHTYELLOW,
    BRIGHTWHITE
}

/* printc(colors, const string[]) */
#define printc(%1,%2); \
{\
    g_console_colors = GetConsoleTextColors();\
    SetConsoleTextColors(%1);\
    print(%2);\
    SetConsoleTextColors(g_console_colors);\
}

/* printfc(colors, const format[], {Float,_}:...) */
#define printfc(%1,%2); \
{\
    g_console_colors = GetConsoleTextColors();\
    SetConsoleTextColors(%1);\
    printf(%2);\
    SetConsoleTextColors(g_console_colors);\
}

/* GetConsoleForegroundColor() */
#define GetConsoleForegroundColor() \
    (GetConsoleTextColors() & 0xF)

/* GetConsoleBackgroundColor() */
#define GetConsoleBackgroundColor() \
    (GetConsoleTextColors() >> 4 & 0xF)

/* SetConsoleForegroundColor(e_console_color:color) */
#define SetConsoleForegroundColor(%1) \
    SetConsoleTextColors(GetConsoleBackgroundColor() << 4 | _:%1)

/* SetConsoleBackgroundColor(e_console_color:color) */
#define SetConsoleBackgroundColor(%1) \
    SetConsoleTextColors(_:%1 << 4 | GetConsoleForegroundColor())

/* SetConsoleColors(e_console_color:foreground, e_console_color:background) */
#define SetConsoleColors(%1,%2) \
    SetConsoleTextColors(_:%2 << 4 | _:%1)
