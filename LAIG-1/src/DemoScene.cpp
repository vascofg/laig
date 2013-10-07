#include "DemoScene.h"
#include "CGFaxis.h"
#include "CGFapplication.h"

#include "ExampleObject.h"

#include <math.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "CGFappearance.h"

DemoScene::DemoScene(){
	this->scene_cameras.clear(); //limpar vector de c�maras (est�o a ser criadas no constructor do pai (init cameras)
}

void DemoScene::init() 
{
	// Enables lighting computations
	if(this->lightingEnabled)
		glEnable(GL_LIGHTING);

	// Sets up some lighting parameters
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, this->lightingDoubleSided);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, this->lightingLocal);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light::background_ambient);  // Define ambient light

	//Define drawmode
	glPolygonMode(GL_FRONT_AND_BACK, this->drawMode);

	//Define shading
	glShadeModel(this->shadeModel);

	//Define cullface
	if(this->cullface)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(this->cullfaceMode);
	}

	//Define cullorder
	glFrontFace(this->cullorder);

	cout << "CAMERAS: " << endl;
	for(int i = 0;i<this->scene_cameras.size();i++)
		cout << i << endl;

	//this->activateCamera(0);

	// cout lights
	cout << "LIGHTS: " << endl;
	std::list<CGFlight *>::iterator it = scene_lights.begin();
	for(;it!=scene_lights.end();++it)
	{
		cout << ((Light *)(*it))->getID() << endl;
	}


	// Declares and enables a light
	/*float light0_pos[4] = {4.0, 6.0, 5.0, 1.0};
	light0 = new CGFlight(GL_LIGHT0, light0_pos);
	light0->enable();*/

	// Defines a default normal
	glNormal3f(0,0,1);

	obj=new ExampleObject();
	materialAppearance=new CGFappearance();
	textureAppearance=new CGFappearance("data/pyramid.jpg",GL_REPEAT, GL_REPEAT);
	//shader=new CGFshader("data/texshader.vert","data/texshader.frag");

	setUpdatePeriod(0);
}

void DemoScene::update(unsigned long t)
{
	//shader->bind();
	//shader->update(t/400.0);
	//shader->unbind();
	
}
	
void DemoScene::display() 
{

	// ---- BEGIN Background, camera and axis setup
	
	// Clear image and depth buffer everytime we update the scene
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Initialize Model-View matrix as identity (no transformation
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply transformations corresponding to the camera position relative to the origin
	CGFscene::activeCamera->applyView();

	// Draw (and update) light
	std::list<CGFlight *>::iterator it = scene_lights.begin();
	for(;it!=scene_lights.end();++it)
	{
		((Light *)(*it))->draw();
	}

	// Draw axis
	axis.draw();


	// ---- END Background, camera and axis setup


	// ---- BEGIN feature demos

	// Simple object
	materialAppearance->apply();
	obj->draw();

	// textured object

	glTranslatef(0,4,0);
	textureAppearance->apply();
	obj->draw();

	// shader object

	/*glTranslatef(0,4,0);
	shader->bind();
	obj->draw();
	shader->unbind();*/


	// ---- END feature demos

	// We have been drawing in a memory area that is not visible - the back buffer, 
	// while the graphics card is showing the contents of another buffer - the front buffer
	// glutSwapBuffers() will swap pointers so that the back buffer becomes the front buffer and vice-versa
	glutSwapBuffers();
	std::this_thread::sleep_for(std::chrono::milliseconds(17));
}

/*DemoScene::~DemoScene()
{
	delete(shader);
	delete(textureAppearance);
	delete(materialAppearance);
	delete(obj);
	delete(light0);
} commented since values may not exist (parse failed)*/

int DemoScene::addCamera(CGFcamera *c){
	//this->scene_cameras.insert(scene_cameras.begin(), c);
	int id = this->scene_cameras.size();
	this->scene_cameras.push_back(c);
	return id;
}

void DemoScene::addLight(Light *l){
	this->scene_lights.push_back(l);
}

void DemoScene::initCameras(){
	cout << "INITIATING CAMERAS" << endl; //isto n�o � chamado porqu�? porque n�o dei overload ao constructor
}