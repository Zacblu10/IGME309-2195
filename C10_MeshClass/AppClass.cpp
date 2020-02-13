#include "AppClass.h"
void Application::InitVariables(void)
{
	//Make MyMesh object
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCone(1.0f,2.0f,12, C_BROWN);

	//Make MyMesh object
	m_pMesh1 = new MyMesh();
	m_pMesh1->GenerateCube(1.0f, C_WHITE);
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
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix(); 
	matrix4 m4Model; 


	static DWORD dLastFrame = GetTickCount(); 
	static DWORD dStartTime = GetTickCount();
	DWORD dCurrentTime = GetTickCount(); 

	matrix4 m4RotX = glm::rotate(IDENTITY_M4, glm::radians(v3Rotation.x), AXIS_X);
	matrix4 m4RotY = glm::rotate(IDENTITY_M4, glm::radians(v3Rotation.y), AXIS_Y);
	matrix4 m4RotZ = glm::rotate(IDENTITY_M4, glm::radians(v3Rotation.z), AXIS_Z);

	m4Model = m4RotX * m4RotY* m4RotZ; 


	m_pMesh->Render(m4Projection,m4View, m4Model);
	//m_pMesh1->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), glm::translate(vector3( 3.0f, 0.0f, 0.0f)));
		
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();
	
#pragma region Debugging Information
	//Print info on the screen
	uint nEmptyLines = 18;
	for (uint i = 0; i < nEmptyLines; ++i)
		m_pMeshMngr->PrintLine("");//Add a line on top
	//m_pMeshMngr->Print("						");
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), C_YELLOW);

	//m_pMeshMngr->Print("						");
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->PrintLine(std::to_string(m_pSystem->GetFPS()), C_RED);

	m_pMeshMngr->Print("Timer: ");
	m_pMeshMngr->PrintLine(std::to_string((dCurrentTime - dStartTime)/1000.0f), C_RED);
	m_pMeshMngr->Print("Delta Time: ");
	m_pMeshMngr->PrintLine(std::to_string(dCurrentTime - dLastFrame), C_RED);

#pragma endregion

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		v3Rotation.x += 1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			v3Rotation.x -= 2.0f;

		}

	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
		v3Rotation.y += 1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			v3Rotation.y -= 2.0f;

		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		v3Rotation.z += 1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			v3Rotation.z -= 2.0f;

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		v3Rotation = vector3(0.0f, 0.0f, 0.0f);
	}

	//render list call
	m_uRenderCallCount = m_pMeshMngr->Render();

	//clear the render list
	m_pMeshMngr->ClearRenderList();
	
	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();

	dLastFrame = GetTickCount(); 
}
void Application::Release(void)
{
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	SafeDelete(m_pMesh1);
	//release GUI
	ShutdownGUI();
}