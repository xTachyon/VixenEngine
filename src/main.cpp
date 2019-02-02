#ifdef __APPLE__

#include <mach-o/dyld.h>
#include <sys/proc_info.h>
#include <libproc.h>
#include <zconf.h>

#endif
#include "Window.h"
#include "render/MasterRender.h"

std::string resourcePath;
graphics::Window *window;
input::Camera *camera;
graphics::MasterRender *render;

int main() {
#ifdef __WIN32__
	resourcePath = "../resources/";
#elif __APPLE__
	char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
	
	proc_pidpath(getpid(), pathbuf, sizeof(pathbuf));
	resourcePath =
			std::string(pathbuf).substr(0, std::string(pathbuf).find_last_of('/')) + std::string("/../resources/");
#endif
	
	window = new graphics::Window("Vixen Engine", 1280, 720);
	camera = new input::Camera(glm::vec3(0.0f, 2.0f, 5.0f));
	render = new graphics::MasterRender();
	
	graphics::Material *material = new graphics::Material(
			graphics::loader::Loader::generateTexture("textures/wall/wall.png"),
			graphics::loader::Loader::generateTexture("textures/wall/wall_normal.png"));
	graphics::Model *model = graphics::loader::Loader::loadModel("models/cube/cube.dae");
	model->getMeshes()[0]->material = material;
	
	render->addEntity(model);
	
	render->addPointTemperatureLight(glm::vec3(3.0f, 3.0f, 5.0f), 5000, 0.0007, 0.00001, 1.0);
	
	render->addTerrain(0, 0);
	render->addTerrain(0, -1);
	render->addTerrain(-1, -1);
	render->addTerrain(-1, 0);
	
	while (!window->shouldClose()) {
		render->render();
	}
	
	delete render;
	delete camera;
	delete window;
	
	return 0;
}