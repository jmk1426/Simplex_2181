#include "AppClass.h"
void Application::InitVariables(void)
{
	//Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	
	//Set the position and target of the camera
	//(I'm at [0,0,10], looking at [0,0,0] and up is the positive Y axis)
	m_pCameraMngr->SetPositionTargetAndUpward(AXIS_Z * 20.0f, ZERO_V3, AXIS_Y);

	//if the light position is zero move it
	if (m_pLightMngr->GetPosition(1) == ZERO_V3)
		m_pLightMngr->SetPosition(vector3(0.0f, 0.0f, 3.0f));

	//if the background is cornflowerblue change it to black (its easier to see)
	if (vector3(m_v4ClearColor) == C_BLUE_CORNFLOWER)
	{
		m_v4ClearColor = vector4(ZERO_V3, 1.0f);
	}

	// Load in the number of orbits from the .ini file
	// Set up a file io object
	std::ifstream myFileName;

	// Open the file
	myFileName.open("A03 - LERP.ini");

	// Create a variable
	String wordFromFile;
	// Search the file for the number of orbits
	while (!myFileName.eof())
	{
		// Get a word from the file
		myFileName >> wordFromFile;

		// check the word received against the word you are looking for
		if (wordFromFile == "Orbits:")
		{
			// If it is the correct word, you know that the next word is the value you need
			// Get it from the file
			myFileName >> wordFromFile;
			// Set the amount of orbits equal to the amount set in the .ini file
			// Needs to be parsed to an int as well
			m_uOrbits = std::atoi(wordFromFile.c_str());
			// Break out of the loop once you are done with the file
			break;
		}
	}
	
	//if there are no segments create 7
	if(m_uOrbits < 1)
		m_uOrbits = 7;

	float fSize = 1.0f; //initial size of orbits

	//creating a color using the spectrum 
	uint uColor = 650; //650 is Red
	//prevent division by 0
	float decrements = 250.0f / (m_uOrbits > 1? static_cast<float>(m_uOrbits - 1) : 1.0f); //decrement until you get to 400 (which is violet)
	/*
		This part will create the orbits, it start at 3 because that is the minimum subdivisions a torus can have
	*/
	uint uSides = 3; //start with the minimal 3 sides
	for (uint i = uSides; i < m_uOrbits + uSides; i++)
	{
		vector3 v3Color = WaveLengthToRGB(uColor); //calculate color based on wavelength
		m_shapeList.push_back(m_pMeshMngr->GenerateTorus(fSize, fSize - 0.1f, 3, i, v3Color)); //generate a custom torus and add it to the meshmanager
		fSize += 0.5f; //increment the size for the next orbit
		uColor -= static_cast<uint>(decrements); //decrease the wavelength
	}

	// Calculate the various stops, start and end points needed
	for (uint i = 0; i < m_uOrbits; i++)
	{
		// Set up a temporary list of to hold the stops in a current orbit
		std::vector<vector3> newListOfStops;

		// Start off with three different waypoints to hit, increment as you go through the loop
		float waypoints = 3 + i;
		// Use the radius to place each sphere on the correct orbit
		float radius = 1 + (0.5 * i);
		// Loop through the points on each orbit and add them to the list of stops
		for (uint j = 0; j < waypoints; j++)
		{
			// Create a value that allows you to move from point to point along each orbit's path
			// Similar to traveling around a circle and getting points on it
			float switchPoints = (PI / 2) - ((j * (2 * PI)) / waypoints);

			// Add each point to the list of stops
			newListOfStops.push_back(vector3((sin(switchPoints) * radius), (cos(switchPoints) * radius), 0));
		}

		// Set up the list of starting points and end points
		startsList.push_back(newListOfStops[0]);
		endsList.push_back(newListOfStops[1]);
		// Push the new list of stops to the list that holds the list of stops
		varyingStopsList.push_back(newListOfStops);
		// Add the new amount of paths to the list of paths from the current orbit
		pathsList.push_back(i);

		fTimer = 0;	//start the new timer at 0
		uClock = m_pSystem->GenClock(); //generate a new clock for that timer
										// Make a float for the max length of the animation between points
		fMax = 1.0f;

	}
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); //view Matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix(); //Projection Matrix
	matrix4 m4Offset = IDENTITY_M4; //offset of the orbits, starts as the global coordinate system
	/*
		The following offset will orient the orbits as in the demo, start without it to make your life easier.
	*/
	m4Offset = glm::rotate(IDENTITY_M4, 1.5708f, AXIS_Z);

	fTimer += m_pSystem->GetDeltaTime(uClock); //get the delta time for the timer

	// draw a shapes
	for (uint i = 0; i < m_uOrbits; ++i)
	{
		m_pMeshMngr->AddMeshToRenderList(m_shapeList[i], glm::rotate(m4Offset, 1.5708f, AXIS_X));

		// Make sure you are using the correct list of stops for the current orbit
		stopsList = varyingStopsList[i];

		// Start at the current path
		startsList[i] = stopsList[pathsList[i]];

		// End at the next path
		// When we hit the final end point, path + 1 will throw an exception
		// Using the modulus will allow us to reset to the first point when we hit the final end point
		endsList[i] = stopsList[(pathsList[i] + 1) % stopsList.size()];

		// The percentage will hold how close you are to the start and end of the path
		// Map the value to be between 0.0 and 1.0
		float fPercent = MapValue(fTimer, 0.0f, fMax, 0.0f, 1.0f);

		//calculate the current position
		// Use glm::lerp to get the linear interpolation between the start and end of the route
		vector3 v3CurrentPos = glm::lerp(startsList[i], endsList[i], fPercent);
		m4Model = glm::translate(m4Offset, v3CurrentPos);

		// If the timer is greater than or equal to the maximum time of the animation, the animation needs to start again
		if (fTimer >= fMax)
		{
			pathsList[i]++; // Go to the next path
			pathsList[i] %= stopsList.size(); // Make sure we are within bounds of the vector
		}

		//draw spheres
		m_pMeshMngr->AddSphereToRenderList(m4Model * glm::scale(vector3(0.1)), C_WHITE);
	}

	// Need to reset the timer outside of the loop because otherwise it will constantly be reset to 0
	if (fTimer >= fMax)
	{
		fTimer = m_pSystem->GetDeltaTime(uClock); // Restart the timer
	}

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
	//release GUI
	ShutdownGUI();
}