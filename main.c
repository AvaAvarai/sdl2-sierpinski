#include "SDL.h"
#include <stdio.h>

typedef struct Point
{
	int x;
	int y;
} Point;

void drawLine(SDL_Renderer* renderer, const Point *a, const Point *b)
{
	SDL_RenderDrawLine(renderer, a->x, a->y, b->x, b->y);
}

void drawTriangle(SDL_Renderer* renderer, const Point *a, const Point *b, const Point *c)
{
	drawLine(renderer, a, b);
	drawLine(renderer, a, c);
	drawLine(renderer, b, c);
}

void split(SDL_Renderer* renderer, Point a, Point b, Point c, int n)
{
	if (n > 0)
	{
		drawTriangle(renderer, &a, &b, &c);
		
		Point a1 = a;
		Point b2 = b;
		Point c3 = c;

		Point b1 = {.x = (a.x + b.x) / 2, .y = (a.y + b.y) / 2}; 
		Point c1 = {.x = (a.x + c.x) / 2, .y = (a.y + c.y) / 2};

		Point a2 = {.x = (a.x + b.x) / 2, .y = (a.y + b.y) / 2};
		Point c2 = {.x = (c.x + b.x) / 2, .y = (c.y + b.y) / 2};

		Point a3 = {.x = (a.x + c.x) / 2, .y = (a.y + c.y) / 2};
		Point b3 = {.x = (b.x + c.x) / 2, .y = (b.y + c.y) / 2};

		split(renderer, a1, b1, c1, n-1);
		split(renderer, a2, b2, c2, n-1);
		split(renderer, a3, b3, c3, n-1);
	}
}

int main(int argc, char* argv[])
{
	SDL_Window *window = NULL;
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Cound not initialize: %s\n", SDL_GetError());
		return 1;
	}

	window = SDL_CreateWindow(
		"Sierpinski Triangle",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL
	);

	if (window == NULL)
	{
		fprintf(stderr, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Renderer* renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_bool running = SDL_TRUE;

	SDL_Vertex base_triangle[3];
	base_triangle[0].position.x = 400;
	base_triangle[0].position.y = 150;
	base_triangle[0].color.r = 255;
	base_triangle[0].color.g = 0;
	base_triangle[0].color.b = 0;
	base_triangle[0].color.a = 255;

	base_triangle[1].position.x = 200;
	base_triangle[1].position.y = 450;
	base_triangle[1].color.r = 0;
	base_triangle[1].color.g = 0; 
	base_triangle[1].color.b = 255;
	base_triangle[1].color.a = 255;

	base_triangle[2].position.x = 600;
	base_triangle[2].position.y = 450;
	base_triangle[2].color.r = 0;
	base_triangle[2].color.g = 255;
	base_triangle[2].color.b = 0;
	base_triangle[2].color.a = 255;
	
	SDL_Vertex triangle1[3];
	triangle1[0].position.x = 500;
	triangle1[0].position.y = 300;
	triangle1[0].color.r = 47;
	triangle1[0].color.g = 79;
	triangle1[0].color.b = 79;
	triangle1[0].color.a = 255;

	triangle1[1].position.x = 400;
	triangle1[1].position.y = 450;
	triangle1[1].color.r = 47;
	triangle1[1].color.g = 79;
	triangle1[1].color.b = 79;
	triangle1[1].color.a = 255;

	triangle1[2].position.x = 300;
	triangle1[2].position.y = 300;
	triangle1[2].color.r = 47;
	triangle1[2].color.g = 79;
	triangle1[2].color.b = 79;
	triangle1[2].color.a = 255;

	SDL_SetRenderDrawColor(renderer, 47, 79, 79, 255);
	SDL_RenderClear(renderer);

	Point a = {.x=400, .y=150};
	Point b = {.x=200, .y=450};
	Point c = {.x=600, .y=450};

	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	split(renderer, a, b, c, 12);
	SDL_RenderPresent(renderer);	

	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_KEYDOWN:
					break;
				case SDL_KEYUP:
					switch ( event.key.keysym.sym )
					{
						case SDLK_ESCAPE:
							running = SDL_FALSE;
							break;
					}
					break;
				case SDL_QUIT:
					running = SDL_FALSE;	
					break;
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	
	SDL_Quit();
	return 0;
}
