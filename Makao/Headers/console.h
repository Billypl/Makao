#pragma once
#include <cstdlib>

// HACK: Kolory
// Nie można używać biblioteki "windows.h",
// więc posługuję się znakami ANSI, które
// również potrafią zmieniać kolory

// nie zawsze działają i czasami w konsoli pojawiają
// się dziwne znaczki, jeśli nie, zakomentować poniższą linijkę
#define COLORS

#ifdef COLORS

// KOLORY TEKSTU
#define BLACK_F		"\x1b[30m"
#define RED_F		"\x1b[31m"
#define GREEN_F		"\x1b[32m"
#define YELLOW_F	"\x1b[33m"
#define BLUE_F		"\x1b[34m"
#define MAGENTA_F	"\x1b[35m"
#define CYAN_F		"\x1b[36m"
#define WHITE_F		"\x1b[37m"
#define DEFAULT_F	"\x1b[39m"

// KOLORY TŁA
#define BLACK_B		"\x1b[40m"
#define RED_B		"\x1b[41m"
#define GREEN_B		"\x1b[42m"
#define YELLOW_B	"\x1b[43m"
#define BLUE_B		"\x1b[44m"
#define MAGENTA_B	"\x1b[45m"
#define CYAN_B		"\x1b[46m"
#define WHITE_B		"\x1b[47m"
#define DEFAULT_B	"\x1b[49m"

#else

#define BLACK_F		""
#define RED_F		""
#define GREEN_F		""
#define YELLOW_F	""
#define BLUE_F		""
#define MAGENTA_F	""
#define CYAN_F		""
#define WHITE_F		""
#define DEFAULT_F	""

#define BLACK_B		""
#define RED_B		""
#define GREEN_B		""
#define YELLOW_B	""
#define BLUE_B		""
#define MAGENTA_B	""
#define CYAN_B		""
#define WHITE_B		""
#define DEFAULT_B	""

#endif


inline void cls() { system("cls||clear"); }

