#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
//#include <SDL_image>

using std::cout;
using std::endl;

// Const
const int WIDTH = 1500; //ширина
const int HEIGHT = 1000; //высота
const int axis_step = 50;  //Шаг по оси СК
const int axis_risk_size = 30; //Размер риски на СК
const float smooth_lvl = .01f;

//структура для смещения по 0Х, 0У
struct coord
{
	float x_transmit;
	float y_transmit;
};
coord base_coord;
//получить координаты смещения по 0Х, 0У
coord get_coord(float x, float y, coord base_coord) {
	
	base_coord.x_transmit = x * axis_step + WIDTH / 2;
	base_coord.y_transmit = -y * axis_step + HEIGHT / 2;

	return base_coord;
}

//ф-ция рисования системы координат
void draw_CK(SDL_Renderer* render, int axis_step, int axis_risk_size) {
	//смена цвета на BlueViolet
	SDL_SetRenderDrawColor(render, 148, 0, 211, 0xFF);

	//ось Х
	SDL_RenderDrawLine(render, 0, HEIGHT/2, WIDTH, HEIGHT / 2);

	//ось У
	SDL_RenderDrawLine(render, WIDTH/2, 0, WIDTH/2, HEIGHT);

	//риски по 0Х
	for (int i = 0; i < WIDTH; i+= axis_step)
	{
		SDL_RenderDrawLine(render, i, HEIGHT / 2 - axis_risk_size / 2, i, HEIGHT / 2 + axis_risk_size / 2);
	}

	//риски по 0У
	for (int i = 0; i < HEIGHT; i+= axis_step)
	{
		SDL_RenderDrawLine(render, WIDTH/2 - axis_risk_size / 2, i, WIDTH / 2 + axis_risk_size / 2, i);
	}

}

int main(int argc, char* argv[])
{

	//инициализация модулей 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s", SDL_GetError());
		return 1;
	}
	else
	{
		printf("ready");
	}

	//создание объекта window
	SDL_Window* win = SDL_CreateWindow("Function", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		printf("SDL_CreateWindow Error: %s", SDL_GetError());
		return 1;
	}

	//создание объекта render
	SDL_Renderer* render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == nullptr) {
		printf("SDL_CreateRenderer Error: %s", SDL_GetError());
		return 1;
	}

	//создание объекта event
	SDL_Event event;

	//флаг работы окна
	bool proc = true;


	while (proc)
	{
		while (SDL_PollEvent(&event))
		{
			//отслеживание закрытия окна через кнопку "Крест"
			if (event.type == SDL_QUIT)
			{
				proc = false;
			}

			//инициализация цвета рисования
			SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);

			//очистка буфера
			SDL_RenderClear(render);

			// Рисуем СК
			draw_CK(render, axis_step, axis_risk_size);

			//смена цвета на RED
			SDL_SetRenderDrawColor(render, 255, 0, 0, 0xFF);

			for (float x = -WIDTH / 2; x < WIDTH / 2; x += smooth_lvl)
			{
				//float y = pow(x, 2); ф-ция проверки

				// ф-ция графика
				float y = (1 / x) + 2 * sin(x);
				SDL_RenderDrawPoint(render, get_coord(x, NAN, base_coord).x_transmit, get_coord(NAN, y, base_coord).y_transmit);
			}

			//скомпонованный backbuffer
			SDL_RenderPresent(render);
		} 
	}
	return 0;
}