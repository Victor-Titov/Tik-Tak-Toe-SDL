#include<iostream>
#include<SDL.h>
#include<fstream>

#undef main
using namespace std;

SDL_Window* MainWindow;
SDL_Renderer* MainRenderer;
int grid[3][3];
int left_valid_moves = 9;
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
		SDL_RenderCopy(MainRenderer, tempTexture, nullptr, nullptr);

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



void drawGrid(SDL_Renderer* MainRenderer) {
	
	SDL_SetRenderDrawColor(MainRenderer, 255, 255, 255, 255);
	
	SDL_RenderDrawLine(MainRenderer, 0, 0, 0, 600);
	SDL_RenderDrawLine(MainRenderer, 600, 0, 600, 600);
	SDL_RenderDrawLine(MainRenderer, 0, 0, 600, 0);
	SDL_RenderDrawLine(MainRenderer, 0, 600, 600, 600);

	SDL_RenderDrawLine(MainRenderer, 0, 200, 600, 200);
	SDL_RenderDrawLine(MainRenderer, 0, 400, 600, 400);

	SDL_RenderDrawLine(MainRenderer, 200, 0, 200, 600);
	SDL_RenderDrawLine(MainRenderer, 400, 0, 400, 600);
}
void drawBackgound(SDL_Renderer* MainRenderer) {
	SDL_SetRenderDrawColor(MainRenderer, 0, 0, 0, 255);
	SDL_RenderClear(MainRenderer);

}

int winCheck(int lpmx, int lpmy, int lpmp) {
	grid[lpmx][lpmy] = lpmp;
	left_valid_moves--;
	if (grid[lpmx][0] == grid[lpmx][1] && grid[lpmx][1] == grid[lpmx][2]) {
		return lpmp;
	}
	if (grid[0][lpmy] == grid[1][lpmy] && grid[1][lpmy] == grid[2][lpmy]) {
		return lpmp;
	}

	if (lpmx == lpmy) {
		if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) {
			return lpmp;
		}
	}

	if (lpmx == 2 - lpmy) {
		if (grid[2][0] == grid[1][1] && grid[1][1] == grid[0][2]) {
			return lpmp;
		}
	}

	if (left_valid_moves == 0) {
		return 3;
	}

	return 0;

}


int main(int argc, char* argv[]){
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	MainWindow = SDL_CreateWindow("First SDL Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 601, 601, 0);


	MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_PRESENTVSYNC);


	//improve Renderer
	improveRenderer();
	SDL_SetRenderDrawColor(MainRenderer, 255, 255, 255, 200);
	
	drawGrid(MainRenderer);


	drawBackgound(MainRenderer);
	

	drawBackgound(MainRenderer);


	
	drawBackgound(MainRenderer);


	SDL_RenderPresent(MainRenderer);
	SDL_Event sdlEvent;
	bool isRunning = true;
	SDL_Rect rect = { 0,0,600,600 };
	SDL_Rect dstRect = { 0,0,200,200 };
	SDL_Texture* greenSquare=getPicture("img\\GreenSquare.bmp");
	SDL_Texture* xTexture = getPicture("img\\xche.bmp");
	SDL_Texture* cTexture = getPicture("img\\circle.bmp");
	SDL_Rect xRect = { 0, 0, 200, 200 };
	SDL_Rect cRect = { 0, 0, 200, 200 };
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
				if (msx > 2) {msx = 2;}
				if (msy > 2) {msy = 2;}
				cout << msx << ' ' << msy << endl;
				dstRect.x = msx * 200;
				dstRect.y = msy * 200;
				SDL_RenderCopy(MainRenderer, greenSquare, nullptr, &dstRect);
				drawGrid(MainRenderer);
				SDL_RenderPresent(MainRenderer);
				
				SDL_RenderClear(MainRenderer);
				drawBackgound(MainRenderer);

			case SDL_BUTTON_LEFT:
				xTexture = getPicture("img\\xche.bmp");
				msx = sdlEvent.motion.x/200;
				msy = sdlEvent.motion.y/200;
				xRect.x = msx * 200;
				xRect.y = msy * 200;
				SDL_RenderCopy(MainRenderer, xTexture, nullptr, &xRect);
				drawGrid(MainRenderer);
				SDL_RenderPresent(MainRenderer);
				SDL_DestroyTexture(xTexture);

			case SDL_BUTTON_RIGHT:
				xTexture = getPicture("img\\circle.bmp");
				msx = sdlEvent.motion.x / 200;
				msy = sdlEvent.motion.y / 200;
				cRect.x = msx * 200;
				cRect.y = msy * 200;
				SDL_RenderCopy(MainRenderer, cTexture, nullptr, &cRect);
				drawGrid(MainRenderer);
				SDL_RenderPresent(MainRenderer);
				SDL_DestroyTexture(cTexture);


			default: break;
			}
		}


	}
	
	return 0;
}