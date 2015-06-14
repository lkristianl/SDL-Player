#include <SDL.h>
#include <iostream>
#include <vector>
#include <sstream>

//Prototypes
bool init();
bool loadFrames(int);
void play(int);
void close();

//Global vars
const int SCR_W = 500;
const int SCR_H = 282;

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
std::vector<SDL_Surface *> gFrames;

int main(int argc, char* argv[]){
	int frames = 10;

	init();
	loadFrames(frames);
	play(frames);

	system("PAUSE");
	return 0;
}

bool init(){
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		printf("Could not initialize SDL! \nSDL error: %s\n", SDL_GetError());
		return false;
	}
	else{
		//Create window
		gWindow = SDL_CreateWindow("SDL Window", 200, 200, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
		if (gWindow == NULL){
			printf("Could not create window! \nSDL error: %s\n", SDL_GetError());
			return false;
		}
		else{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return true;
}

bool loadFrames(int frames){
	for (int i = 0; i < frames; i++){
		std::stringstream file;
		file << "Frames\\" << i + 1 << ".bmp";
		gFrames.vector::push_back(SDL_LoadBMP(file.str().c_str()));
		if (gFrames[i] == NULL){
			printf("SDL error: %s\n", SDL_GetError());
			return false;
		}
	}
	return true;
}

void play(int frames){
	int currentFrame = 0;
	do{
		SDL_BlitSurface(gFrames[currentFrame], NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
		currentFrame++;
		if (currentFrame > frames - 1) currentFrame = 0;
	} while (1);

}

void close(){
	for (int i = 0; i < gFrames.size(); i++){
		SDL_FreeSurface(gFrames[i]);
		gFrames[i] = NULL;
	}

	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}