#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";

	//Set the position and target of the camera
	m_pCameraMngr->SetPositionTargetAndUpward(vector3(5.0f,3.0f,15.0f), ZERO_V3, AXIS_Y);

	m_pModel = new Simplex::Model();
	m_pModel->Load("Sorted\\WallEye.bto");
	
	m_stopsList.push_back(vector3(-4.0f, -2.0f, 5.0f));
	m_stopsList.push_back(vector3(1.0f, -2.0f, 5.0f));

	m_stopsList.push_back(vector3(-3.0f, -1.0f, 3.0f));
	m_stopsList.push_back(vector3(2.0f, -1.0f, 3.0f));

	m_stopsList.push_back(vector3(-2.0f, 0.0f, 0.0f));
	m_stopsList.push_back(vector3(3.0f, 0.0f, 0.0f));

	m_stopsList.push_back(vector3(-1.0f, 1.0f, -3.0f));
	m_stopsList.push_back(vector3(4.0f, 1.0f, -3.0f));

	m_stopsList.push_back(vector3(0.0f, 2.0f, -5.0f));
	m_stopsList.push_back(vector3(5.0f, 2.0f, -5.0f));

	m_stopsList.push_back(vector3(1.0f, 3.0f, -5.0f));
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	// Draw the model
	m_pModel->PlaySequence();

	//Get a timer
	static float fTimer = 0;	//store the new timer
	static uint uClock = m_pSystem->GenClock(); //generate a new clock for that timer
	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for that timer

	//calculate the current position
	vector3 v3CurrentPos;
	
	//your code goes here
	v3CurrentPos = vector3(0.0f, 0.0f, 0.0f);
	//-------------------
	
	// Make a 2 vectors: 1 to hold the start of the current path and 1 to hold the end of it
	vector3 start;
	vector3 end;

	//The path is basically an index that tells you which set of points to LERP between
	static int path = 0;

	// Start at the current path
	start = m_stopsList[path];

	// End at the next path
	// When we hit the final end point, path + 1 will throw an exception
	// Using the modulus will allow us to reset to the first point when we hit the final end point
	end = m_stopsList[(path + 1) % m_stopsList.size()];

	// The percentage will hold how close you are to the start and end of the path
	// Make a float for the max length of the animation between points
	float fMax = 3.0f;
	// Map the value to be between 0.0 and 1.0
	float fPercent = MapValue(fTimer, 0.0f, fMax, 0.0f, 1.0f);

	// Use glm::lerp to get the linear interpolation between the start and end of the route
	v3CurrentPos = glm::lerp(start, end, fPercent);

	// Translate the model to its current position
	matrix4 m4Model = glm::translate(v3CurrentPos);
	m_pModel->SetModelMatrix(m4Model);

	// If the timer is greater than or equal to the maximum time of the animation, the animation needs to start again
	if (fTimer >= fMax)
	{
		path++; // Go to the next path
		fTimer = m_pSystem->GetDeltaTime(uClock); // Restart the timer
		path %= m_stopsList.size(); // Make sure we are within bounds of the vector
	}

	m_pMeshMngr->Print("\nTimer: ");//Add a line on top
	m_pMeshMngr->PrintLine(std::to_string(fTimer), C_YELLOW);

	// Draw stops
	for (uint i = 0; i < m_stopsList.size(); ++i)
	{
		m_pMeshMngr->AddSphereToRenderList(glm::translate(m_stopsList[i]) * glm::scale(vector3(0.05f)), C_GREEN, RENDER_WIRE);
	}
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	SafeDelete(m_pModel);
	//release GUI
	ShutdownGUI();
}