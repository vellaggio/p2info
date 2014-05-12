#include "application.h"
#include "utils.h"
#include "image.h"

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(NULL);
}

//Here we have already GL working, so we can create meshes and textures
void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;

	//here add your init stuff
}

//render one frame
void Application::render(void)
{
	// Clear the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//render grid
	Image img( 400, 300);

	/*---- LINIA----*/

	int x0, y0, x1, y1; //punts d'inici i final de la linia 

	x0 = 150;
	y0 = 150;
	x1 = 200;
	y1 = 150;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int x, y;

	//slope |m| <= 1.0;
	if (dx >= dy){
		int d = 2 * dy - dx;
		int ds = 2 * dy;
		int dt = 2 * (dy - dx);

		if (x0 < x1)  { // set the left point to the starting point
			x = x0;
			y = y0;
		}
		else { // exchange the right point to the starting point and left point to the end point
			x = x1;
			y = y1;
			x1 = x0;
			y1 = y0;
		}
		img.setPixel(x, y, Color::RED); // activate the starting point
		while (x < x1) {
			if (d < 0)
				d += ds;
			else {
				if (y < y1) {
					y++;
					d += dt;
				}
				else {
					y--;
					d += dt;
				}
			}
			x++;
			img.setPixel(x, y, Color::RED);
		}
	}
	else {


		//slope |m| > 1.0;
		int d = 2 * dx - dy;
		int ds = 2 * dx;
		int dt = 2 * (dx - dy);
		if (y0 < y1) { // set the left point to the starting point
			x = x0;
			y = y0;
		}
		else { // exchange the right point to the starting point and left point to the end point
			x = x1;
			y = y1;
			y1 = y0;
			x1 = x0;
		}
		img.setPixel(x, y, Color::RED); // activate the starting point
		while (y < y1) {
			if (d < 0)
				d += ds;
			else {
				if (x > x1){
					x--;
					d += dt;
				}
				else {
					x++;
					d += dt;
				}
			}
			y++;
			img.setPixel(x, y, Color::RED);
		}
	}


	/*---- CERCLE----*/
	int R = 20; //radi
	//centre del cercle
	int xc = 100; 
	int yc = 100;
	x = 0;
	y = R;
	int d = 1 - R;

	img.setPixel(xc, yc, Color::BLUE);

	while (x<y)
	{
		if (d<0)
			d += 2 * x + 2;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;

		img.setPixel(xc + x, yc + y, Color::BLUE);
		img.setPixel(xc - x, yc + y, Color::BLUE);
		img.setPixel(xc - x, yc - y, Color::BLUE);
		img.setPixel(xc + x, yc - y, Color::BLUE);
		img.setPixel(xc + y, yc + x, Color::BLUE);
		img.setPixel(xc - y, yc + x, Color::BLUE);
		img.setPixel(xc - y, yc - x, Color::BLUE);
		img.setPixel(xc + y, yc - x, Color::BLUE);

	}
	


	img.scale( this->window_width, this->window_height );

	renderImage( &img );

	//swap between front buffer and back buffer
	SDL_GL_SwapWindow(this->window);
}

//called after render
void Application::update(double seconds_elapsed)
{
	if (keystate[SDL_SCANCODE_SPACE])
	{
		//...
	}
}

//keyboard press event 
void Application::onKeyPressed( SDL_KeyboardEvent event )
{
	switch(event.keysym.sym)
	{
		case SDLK_ESCAPE: exit(0); break; //ESC key, kill the app
	}
}

//mouse button event
void Application::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse pressed
	{

	}
}

void Application::onMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse unpressed
	{

	}
}

//when the app starts
void Application::start()
{
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}
