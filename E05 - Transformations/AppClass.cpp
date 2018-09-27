#include "AppClass.h"
void Application::InitVariables(void)
{
	//init the mesh
	//m_pMesh = new MyMesh();
	//m_pMesh->GenerateCube(1.0f, C_WHITE);
	//m_pMesh->GenerateSphere(1.0f, 5, C_WHITE);

	// Fill the meshObjects data structure with 46 MyMesh objects
	for (int i = 0; i <= 45; ++i)
	{
		meshObjects.push_back(new MyMesh());
		meshObjects[i]->GenerateCube(1.0f, C_WHITE);
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

	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	
	// Create the scale and translate for each cube
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(0.5f, 0.5f, 0.5f));
	static float value = -3.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 0.0f, 3.0f));
	value += 0.01f;

	matrix4 m4Translate2 = glm::translate(IDENTITY_M4, vector3(value, -0.5f, 3.0f));
	//value += 0.01f;

	matrix4 m4Translate3 = glm::translate(IDENTITY_M4, vector3(value, -1.0f, 3.0f));
	//value += 0.01f;

	static float value2 = -2.5f;
	matrix4 m4Translate4 = glm::translate(IDENTITY_M4, vector3(value2, 0.0f, 3.0f));
	value2 += 0.01f;

	matrix4 m4Translate5 = glm::translate(IDENTITY_M4, vector3(value2, 0.5f, 3.0f));
	//value2 += 0.01f;

	static float value3 = -2.0f;
	matrix4 m4Translate6 = glm::translate(IDENTITY_M4, vector3(value3, 2.0f, 3.0f));
	value3 += 0.01f;

	matrix4 m4Translate7 = glm::translate(IDENTITY_M4, vector3(value3, 1.0f, 3.0f));
	//value3 += 0.01f;

	matrix4 m4Translate8 = glm::translate(IDENTITY_M4, vector3(value3, 0.5f, 3.0f));
	//value3 += 0.01f;

	matrix4 m4Translate9 = glm::translate(IDENTITY_M4, vector3(value3, 0.0f, 3.0f));
	//value3 += 0.01f;

	matrix4 m4Translate10 = glm::translate(IDENTITY_M4, vector3(value3, -0.5f, 3.0f));
	//value3 += 0.01f;

	matrix4 m4Translate11 = glm::translate(IDENTITY_M4, vector3(value3, -1.0f, 3.0f));
	//value3 += 0.01f;

	static float value4 = -1.5f;
	matrix4 m4Translate12 = glm::translate(IDENTITY_M4, vector3(value4, 1.5f, 3.0f));
	value4 += 0.01f;

	matrix4 m4Translate13 = glm::translate(IDENTITY_M4, vector3(value4, 1.0f, 3.0f));
	//value4 += 0.01f;

	matrix4 m4Translate14 = glm::translate(IDENTITY_M4, vector3(value4, 0.0f, 3.0f));
	//value4 += 0.01f;

	matrix4 m4Translate15 = glm::translate(IDENTITY_M4, vector3(value4, -0.5f, 3.0f));
	//value4 += 0.01f;

	matrix4 m4Translate16 = glm::translate(IDENTITY_M4, vector3(value4, -1.5f, 3.0f));
	//value4 += 0.01f;


	static float value5 = -1.0f;
	matrix4 m4Translate17 = glm::translate(IDENTITY_M4, vector3(value5, 1.0f, 3.0f));
	value5 += 0.01f;

	matrix4 m4Translate18 = glm::translate(IDENTITY_M4, vector3(value5, 0.5f, 3.0f));
	//value5 += 0.01f;

	matrix4 m4Translate19 = glm::translate(IDENTITY_M4, vector3(value5, 0.0f, 3.0f));
	//value5 += 0.01f;

	matrix4 m4Translate20 = glm::translate(IDENTITY_M4, vector3(value5, -0.5f, 3.0f));
	//value5 += 0.01f;

	matrix4 m4Translate21 = glm::translate(IDENTITY_M4, vector3(value5, -1.5f, 3.0f));
	//value5 += 0.01f;

	static float value6 = -0.5f;
	matrix4 m4Translate22 = glm::translate(IDENTITY_M4, vector3(value6, 1.0f, 3.0f));
	value6 += 0.01f;

	matrix4 m4Translate23 = glm::translate(IDENTITY_M4, vector3(value6, 0.5f, 3.0f));
	//value6 += 0.01f;

	matrix4 m4Translate24 = glm::translate(IDENTITY_M4, vector3(value6, 0.0f, 3.0f));
	//value6 += 0.01f;

	matrix4 m4Translate25 = glm::translate(IDENTITY_M4, vector3(value6, -0.5f, 3.0f));
	//value6 += 0.01f;

	static float value7 = 0.0f;
	matrix4 m4Translate26 = glm::translate(IDENTITY_M4, vector3(value7, 1.0f, 3.0f));
	value7 += 0.01f;

	matrix4 m4Translate27 = glm::translate(IDENTITY_M4, vector3(value7, 0.5f, 3.0f));
	//value7 += 0.01f;

	matrix4 m4Translate28 = glm::translate(IDENTITY_M4, vector3(value7, 0.0f, 3.0f));
	//value7 += 0.01f;

	matrix4 m4Translate29 = glm::translate(IDENTITY_M4, vector3(value7, -0.5f, 3.0f));
	//value7 += 0.01f;

	matrix4 m4Translate30 = glm::translate(IDENTITY_M4, vector3(value7, -1.5f, 3.0f));
	//value7 += 0.01f;

	static float value8 = 0.5f;
	matrix4 m4Translate31 = glm::translate(IDENTITY_M4, vector3(value8, 1.5f, 3.0f));
	value8 += 0.01f;

	matrix4 m4Translate32 = glm::translate(IDENTITY_M4, vector3(value8, 1.0f, 3.0f));
	//value8 += 0.01f;

	matrix4 m4Translate33 = glm::translate(IDENTITY_M4, vector3(value8, 0.0f, 3.0f));
	//value8 += 0.01f;

	matrix4 m4Translate34 = glm::translate(IDENTITY_M4, vector3(value8, -0.5f, 3.0f));
	//value8 += 0.01f;

	matrix4 m4Translate35 = glm::translate(IDENTITY_M4, vector3(value8, -1.5f, 3.0f));
	//value8 += 0.01f;

	static float value9 = 1.0f;
	matrix4 m4Translate36 = glm::translate(IDENTITY_M4, vector3(value9, 2.0f, 3.0f));
	value9 += 0.01f;

	matrix4 m4Translate37 = glm::translate(IDENTITY_M4, vector3(value9, 1.0f, 3.0f));
	//value9 += 0.01f;

	matrix4 m4Translate38 = glm::translate(IDENTITY_M4, vector3(value9, 0.5f, 3.0f));
	//value9 += 0.01f;

	matrix4 m4Translate39 = glm::translate(IDENTITY_M4, vector3(value9, 0.0f, 3.0f));
	//value9 += 0.01f;

	matrix4 m4Translate40 = glm::translate(IDENTITY_M4, vector3(value9, -0.5f, 3.0f));
	//value9 += 0.01f;

	matrix4 m4Translate41 = glm::translate(IDENTITY_M4, vector3(value9, -1.0f, 3.0f));
	//value9 += 0.01f;

	static float value10 = 1.5f;
	matrix4 m4Translate42 = glm::translate(IDENTITY_M4, vector3(value10, 0.0f, 3.0f));
	value10 += 0.01f;

	matrix4 m4Translate43 = glm::translate(IDENTITY_M4, vector3(value10, 0.5f, 3.0f));
	//value10 += 0.01f;

	static float value11 = 2.0f;
	matrix4 m4Translate44 = glm::translate(IDENTITY_M4, vector3(value11, 0.0f, 3.0f));
	value11 += 0.01f;

	matrix4 m4Translate45 = glm::translate(IDENTITY_M4, vector3(value11, -0.5f, 3.0f));
	//value11 += 0.01f;

	matrix4 m4Translate46 = glm::translate(IDENTITY_M4, vector3(value11, -1.0f, 3.0f));
	//value11 += 0.01f;

	// Create the model for each cube

	matrix4 m4Model = m4Translate * m4Scale;

	matrix4 m4Model2 = m4Translate2 * m4Scale;

	matrix4 m4Model3 = m4Translate3 * m4Scale;

	matrix4 m4Model4 = m4Translate4 * m4Scale;

	matrix4 m4Model5 = m4Translate5 * m4Scale;

	matrix4 m4Model6 = m4Translate6 * m4Scale;

	matrix4 m4Model7 = m4Translate7 * m4Scale;

	matrix4 m4Model8 = m4Translate8 * m4Scale;

	matrix4 m4Model9 = m4Translate9 * m4Scale;

	matrix4 m4Model10 = m4Translate10 * m4Scale;

	matrix4 m4Model11 = m4Translate11 * m4Scale;

	matrix4 m4Model12 = m4Translate12 * m4Scale;

	matrix4 m4Model13 = m4Translate13 * m4Scale;

	matrix4 m4Model14 = m4Translate14 * m4Scale;

	matrix4 m4Model15 = m4Translate15 * m4Scale;

	matrix4 m4Model16 = m4Translate16 * m4Scale;

	matrix4 m4Model17 = m4Translate17 * m4Scale;

	matrix4 m4Model18 = m4Translate18 * m4Scale;

	matrix4 m4Model19 = m4Translate19 * m4Scale;

	matrix4 m4Model20 = m4Translate20 * m4Scale;

	matrix4 m4Model21 = m4Translate21 * m4Scale;

	matrix4 m4Model22 = m4Translate22 * m4Scale;

	matrix4 m4Model23 = m4Translate23 * m4Scale;

	matrix4 m4Model24 = m4Translate24 * m4Scale;

	matrix4 m4Model25 = m4Translate25 * m4Scale;

	matrix4 m4Model26 = m4Translate26 * m4Scale;

	matrix4 m4Model27 = m4Translate27 * m4Scale;

	matrix4 m4Model28 = m4Translate28 * m4Scale;

	matrix4 m4Model29 = m4Translate29 * m4Scale;

	matrix4 m4Model30 = m4Translate30 * m4Scale;

	matrix4 m4Model31 = m4Translate31 * m4Scale;

	matrix4 m4Model32 = m4Translate32 * m4Scale;

	matrix4 m4Model33 = m4Translate33 * m4Scale;

	matrix4 m4Model34 = m4Translate34 * m4Scale;

	matrix4 m4Model35 = m4Translate35 * m4Scale;

	matrix4 m4Model36 = m4Translate36 * m4Scale;

	matrix4 m4Model37 = m4Translate37 * m4Scale;

	matrix4 m4Model38 = m4Translate38 * m4Scale;

	matrix4 m4Model39 = m4Translate39 * m4Scale;

	matrix4 m4Model40 = m4Translate40 * m4Scale;

	matrix4 m4Model41 = m4Translate41 * m4Scale;

	matrix4 m4Model42 = m4Translate42 * m4Scale;

	matrix4 m4Model43 = m4Translate43 * m4Scale;

	matrix4 m4Model44 = m4Translate44 * m4Scale;

	matrix4 m4Model45 = m4Translate45 * m4Scale;

	matrix4 m4Model46 = m4Translate46 * m4Scale;

	// Render each model

	meshObjects[0]->Render(m4Projection, m4View, m4Model);

	meshObjects[1]->Render(m4Projection, m4View, m4Model2);

	meshObjects[2]->Render(m4Projection, m4View, m4Model3);

	meshObjects[3]->Render(m4Projection, m4View, m4Model4);

	meshObjects[4]->Render(m4Projection, m4View, m4Model5);

	meshObjects[5]->Render(m4Projection, m4View, m4Model6);

	meshObjects[6]->Render(m4Projection, m4View, m4Model7);

	meshObjects[7]->Render(m4Projection, m4View, m4Model8);

	meshObjects[8]->Render(m4Projection, m4View, m4Model9);

	meshObjects[9]->Render(m4Projection, m4View, m4Model10);

	meshObjects[10]->Render(m4Projection, m4View, m4Model11);

	meshObjects[11]->Render(m4Projection, m4View, m4Model12);

	meshObjects[12]->Render(m4Projection, m4View, m4Model13);

	meshObjects[13]->Render(m4Projection, m4View, m4Model14);

	meshObjects[14]->Render(m4Projection, m4View, m4Model15);

	meshObjects[15]->Render(m4Projection, m4View, m4Model16);

	meshObjects[16]->Render(m4Projection, m4View, m4Model17);

	meshObjects[17]->Render(m4Projection, m4View, m4Model18);

	meshObjects[18]->Render(m4Projection, m4View, m4Model19);

	meshObjects[19]->Render(m4Projection, m4View, m4Model20);

	meshObjects[20]->Render(m4Projection, m4View, m4Model21);

	meshObjects[21]->Render(m4Projection, m4View, m4Model22);

	meshObjects[22]->Render(m4Projection, m4View, m4Model23);

	meshObjects[23]->Render(m4Projection, m4View, m4Model24);

	meshObjects[24]->Render(m4Projection, m4View, m4Model25);

	meshObjects[25]->Render(m4Projection, m4View, m4Model26);

	meshObjects[26]->Render(m4Projection, m4View, m4Model27);

	meshObjects[27]->Render(m4Projection, m4View, m4Model28);

	meshObjects[28]->Render(m4Projection, m4View, m4Model29);

	meshObjects[29]->Render(m4Projection, m4View, m4Model30);

	meshObjects[30]->Render(m4Projection, m4View, m4Model31);

	meshObjects[31]->Render(m4Projection, m4View, m4Model32);

	meshObjects[32]->Render(m4Projection, m4View, m4Model33);

	meshObjects[33]->Render(m4Projection, m4View, m4Model34);

	meshObjects[34]->Render(m4Projection, m4View, m4Model35);

	meshObjects[35]->Render(m4Projection, m4View, m4Model36);

	meshObjects[36]->Render(m4Projection, m4View, m4Model37);

	meshObjects[37]->Render(m4Projection, m4View, m4Model38);

	meshObjects[38]->Render(m4Projection, m4View, m4Model39);

	meshObjects[39]->Render(m4Projection, m4View, m4Model40);

	meshObjects[40]->Render(m4Projection, m4View, m4Model41);

	meshObjects[41]->Render(m4Projection, m4View, m4Model42);

	meshObjects[42]->Render(m4Projection, m4View, m4Model43);

	meshObjects[43]->Render(m4Projection, m4View, m4Model44);

	meshObjects[44]->Render(m4Projection, m4View, m4Model45);

	meshObjects[45]->Render(m4Projection, m4View, m4Model46);
	
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
	SafeDelete(m_pMesh);

	// Delete each MyMesh object

	for (int i = 0; i < meshObjects.size(); i++)
	{
		delete meshObjects[i];
	}

	//release GUI
	ShutdownGUI();
}