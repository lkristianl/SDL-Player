#include <SDL.h>
#include <iostream>
#include <vector>
#include <sstream>

//Prototypes
bool init();
bool loadFrames(int);
int	 mainHandle(int);
void close();

//Global vars
const int SCR_W = 500;
const int SCR_H = 282;

//Create the display window container, windows screen, and the buffer (vector).
SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
std::vector<SDL_Surface *> gFrames;

int main(int argc, char* argv[]){
	int frames = 10;
	
	init();
	loadFrames(frames);
	mainHandle(frames);
	close();

	system("PAUSE");
	return 0;
}

//The main handle for the window.
//Handles user events and display frames.
int mainHandle(int frames){
	int currentFrame = 0;

	SDL_Event e;
	while (true){
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT) return 0;
		}

		//Display frame
		SDL_BlitSurface(gFrames[currentFrame], NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
		currentFrame++;
		if (currentFrame > frames - 1) currentFrame = 0; //Loop frames
		SDL_Delay(1000 / 30); //Regulate FPS
	}
}

//Initialize SDL video and create window.
//Returns true if successfully initialized.
bool init(){
	if (SDL_Init(SDL_INIT_VIDEO) == -1){
		printf("SDL error: %s\n", SDL_GetError());
		return false;
	}
	else{
		gWindow = SDL_CreateWindow("SDL Window", 200, 200, SCR_W, SCR_H, SDL_WINDOW_SHOWN);
		if (gWindow == NULL){
			printf("SDL error: %s\n", SDL_GetError());
			return false;
		}
		else{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}
	return true;
}

//Load the BMP images in memory, frames are held as pointers to the SDL_Surface that contains them.
//Returns true if successfully loaded in memory.
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

//Destroys everything.
void close(){
	for (int i = 0; i < gFrames.size(); i++){
		SDL_FreeSurface(gFrames[i]);
		gFrames[i] = NULL;
	}

	SDL_DestroyWindow(gWindow);
	SDL_Quit();
}