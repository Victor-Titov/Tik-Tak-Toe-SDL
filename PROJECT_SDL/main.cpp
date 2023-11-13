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

	SDL_RenderSetLogicalSize(MainRenderer, 601, 601);
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
	
	MainWindow = SDL_CreateWindow("First SDL Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 601, 601, 0);
	


	MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_PRESENTVSYNC);


	//improve Renderer
	improveRenderer();
	SDL_SetRenderDrawColor(MainRenderer, 255, 255, 255, 200);

	SDL_RenderDrawLine(MainRenderer, 0, 0, 0, 600);
	SDL_RenderDrawLine(MainRenderer, 600, 0, 600, 600);
	SDL_RenderDrawLine(MainRenderer, 0, 0, 600, 0);
	SDL_RenderDrawLine(MainRenderer, 0, 600, 600, 600);
	
	SDL_RenderDrawLine(MainRenderer, 0, 200, 600, 200);
	SDL_RenderDrawLine(MainRenderer, 0, 400, 600, 400);

	SDL_RenderDrawLine(MainRenderer, 200, 0, 200, 600);
	SDL_RenderDrawLine(MainRenderer, 400, 0, 400, 600);
	
	
	SDL_RenderPresent(MainRenderer);
	SDL_Event sdlEvent;
	bool isRunning = true;
	SDL_Rect rect = { 0,0,600,600 };
	SDL_Rect dstRect = { 0,0,200,200 };
	SDL_Texture* greenSquare=getPicture("img\\GreenSquare.bmp");
	int msx, msy;
	while (isRunning) {
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT:isRunning = false; break;
			case SDL_KEYDOWN:
				if (sdlEvent.key.keysym.scancode == SDL_Scancode(41)) {
					isRunning = false;
				}
				break;

			case SDL_MOUSEMOTION:
				msx = sdlEvent.motion.x/200;
				msy = sdlEvent.motion.y/200;
				cout << msx << ' ' << msy << endl;
				dstRect.x = msx * 200;
				dstRect.y = msy * 200;
				SDL_RenderCopy(MainRenderer, greenSquare, NULL, &dstRect);
				SDL_RenderPresent(MainRenderer);
				SDL_RenderClear(MainRenderer);
				

			default:break;
			}
		}


	}
	
	return 0;
}