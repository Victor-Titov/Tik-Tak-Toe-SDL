#include<iostream>
#include<SDL.h>
#include<fstream>

#undef main
using namespace std;

SDL_Window* MainWindow;
SDL_Renderer* MainRenderer;


void improveRenderer() {
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);


	auto desktopWidh = DM.w;
	auto desktopHeight = DM.h;
	if (SDL_SetWindowFullscreen(MainWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0) {
		cout << "SDL Renderer imprude failed" << SDL_GetError();
	}

	SDL_RenderSetLogicalSize(MainRenderer, 1920, 1200);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");


}


SDL_Texture* getPicture(string fileName) {
	SDL_Surface* loadingSurface = SDL_LoadBMP(fileName.c_str());

	SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(MainRenderer, loadingSurface);
	if (tempTexture == nullptr) {
		loadingSurface = SDL_LoadBMP("img\\Error.bmp");
		tempTexture = SDL_CreateTextureFromSurface(MainRenderer, loadingSurface);
		SDL_RenderCopy(MainRenderer, tempTexture, NULL, NULL);

		SDL_RenderPresent(MainRenderer);
		SDL_FreeSurface(loadingSurface);

		while (true);

		
	}

	SDL_FreeSurface(loadingSurface);
	return tempTexture;
}

bool mousePosCheck(SDL_Rect rect, int mx, int my) {
	if (mx >= rect.x && mx <= rect.x + rect.w && my>=rect.y &&my<=rect.y+rect.h) {
		return true;
	}
	return false;

}
int main(int argc, char* argv[]){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	MainWindow = SDL_CreateWindow("First SDL Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1200, 0);
	


	MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_PRESENTVSYNC);


	//improve Renderer
	improveRenderer();
	//SDL_RenderDrawLine(MainRenderer, 480, 360, 480, 720);
	SDL_RenderPresent(MainRenderer);
	while (true);



	return 0;
}