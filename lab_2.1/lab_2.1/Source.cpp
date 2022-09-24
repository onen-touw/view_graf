#include <SDL.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
//#include <SDL_image>

using std::cout;
using std::endl;

// Const
const int WIDTH = 1500; //������
const int HEIGHT = 1000; //������
const int axis_step = 50;  //��� �� ��� ��
const int axis_risk_size = 30; //������ ����� �� ��
const float smooth_lvl = .01f;

//��������� ��� �������� �� 0�, 0�
struct coord
{
	float x_transmit;
	float y_transmit;
};
coord base_coord;
//�������� ���������� �������� �� 0�, 0�
coord get_coord(float x, float y, coord base_coord) {
	
	base_coord.x_transmit = x * axis_step + WIDTH / 2;
	base_coord.y_transmit = -y * axis_step + HEIGHT / 2;

	return base_coord;
}

//�-��� ��������� ������� ���������
void draw_CK(SDL_Renderer* render, int axis_step, int axis_risk_size) {
	//����� ����� �� BlueViolet
	SDL_SetRenderDrawColor(render, 148, 0, 211, 0xFF);

	//��� �
	SDL_RenderDrawLine(render, 0, HEIGHT/2, WIDTH, HEIGHT / 2);

	//��� �
	SDL_RenderDrawLine(render, WIDTH/2, 0, WIDTH/2, HEIGHT);

	//����� �� 0�
	for (int i = 0; i < WIDTH; i+= axis_step)
	{
		SDL_RenderDrawLine(render, i, HEIGHT / 2 - axis_risk_size / 2, i, HEIGHT / 2 + axis_risk_size / 2);
	}

	//����� �� 0�
	for (int i = 0; i < HEIGHT; i+= axis_step)
	{
		SDL_RenderDrawLine(render, WIDTH/2 - axis_risk_size / 2, i, WIDTH / 2 + axis_risk_size / 2, i);
	}

}

int main(int argc, char* argv[])
{

	//������������� ������� 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init Error: %s", SDL_GetError());
		return 1;
	}
	else
	{
		printf("ready");
	}

	//�������� ������� window
	SDL_Window* win = SDL_CreateWindow("Function", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (win == nullptr) {
		printf("SDL_CreateWindow Error: %s", SDL_GetError());
		return 1;
	}

	//�������� ������� render
	SDL_Renderer* render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (render == nullptr) {
		printf("SDL_CreateRenderer Error: %s", SDL_GetError());
		return 1;
	}

	//�������� ������� event
	SDL_Event event;

	//���� ������ ����
	bool proc = true;


	while (proc)
	{
		while (SDL_PollEvent(&event))
		{
			//������������ �������� ���� ����� ������ "�����"
			if (event.type == SDL_QUIT)
			{
				proc = false;
			}

			//������������� ����� ���������
			SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);

			//������� ������
			SDL_RenderClear(render);

			// ������ ��
			draw_CK(render, axis_step, axis_risk_size);

			//����� ����� �� RED
			SDL_SetRenderDrawColor(render, 255, 0, 0, 0xFF);

			for (float x = -WIDTH / 2; x < WIDTH / 2; x += smooth_lvl)
			{
				//float y = pow(x, 2); �-��� ��������

				// �-��� �������
				float y = (1 / x) + 2 * sin(x);
				SDL_RenderDrawPoint(render, get_coord(x, NAN, base_coord).x_transmit, get_coord(NAN, y, base_coord).y_transmit);
			}

			//�������������� backbuffer
			SDL_RenderPresent(render);
		} 
	}
	return 0;
}