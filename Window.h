#pragma once
#include <SDL.h>
#include <iostream>

class Window
{
public : 
	
	

	Window(int width, int height, std::string name) :
		_width(width), _height(height), _name(name)
	{
		_closed = !Init();
	}

	~Window()
	{
		SDL_DestroyRenderer(_renderer);
		SDL_DestroyWindow(_window);
		SDL_Quit();
	}

	void PollEvents()
	{
		SDL_Event event;

		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case (SDL_QUIT):
				_closed = true;
				break;
			}
		}
	}


	void Clear() const
	{

		SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
		SDL_RenderClear(_renderer);
	}

	void Update() const
	{
		SDL_RenderPresent(_renderer);
	}
	inline SDL_Renderer* getRenderer() const { return _renderer; }
	int getWidth() { return _width; }
	int getHeight() { return _height; }

private :

	bool Init()
	{
		if (SDL_Init(SDL_INIT_VIDEO != 0))
		{
			std::cerr << "SDL Initialization failed\n";
			return 0;
		}

		_window = SDL_CreateWindow(
			_name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			_width, _height,
			0
		);

		if (_window == nullptr)
		{
			std::cerr << "Failed to create window\n";
			return 0;
		}

		_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

		if (_renderer == nullptr)
		{
			std::cerr << "Failed to create renderer\n";
			return 0;
		}

		return true;
	}


private :
	
	int _width = 1280;
	int _height = 800;

	std::string _name;
public:
	bool _closed = false; 

private:
	SDL_Window* _window = nullptr; 
	SDL_Renderer* _renderer = nullptr;
};

