#include "AppClass.h"
void Application::InitVariables(void)
{
	m_pCameraMngr->SetCameraMode(CAM_ORTHO_Z);

	//init the mesh
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_BLUE);
	
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
	
	matrix4 m4Scale = glm::scale(IDENTITY_M4, vector3(2.0f,2.0f,2.0f));
	static float value = 0.0f;
	matrix4 m4Translate = glm::translate(IDENTITY_M4, vector3(value, 0.0f, 0.0f));
	value += 0.03f;

	//matrix4 m4Model = m4Translate * m4Scale;
	matrix4 m4Model = m4Scale * m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	matrix4 m4Origin = m4Model; 

	//matrix4 m4Translate;


	//right of start
	for (int i = 0; i < 5; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(1.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}
	for (int i = 0; i < 2; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(0.0f, -1.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}
	//snap back to the origin
	m4Model = m4Origin;

	//left of start
	for (int i = 0; i < 5; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(-1.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}
	for (int i = 0; i < 2; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(0.0f, -1.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}
	//snap back to the origin
	m4Model = m4Origin;

	//go down a line
	m4Translate = glm::translate(m4Model, vector3(0.0f, -1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	//right 
	for (int i = 0; i < 3; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(1.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}
	for (int i = 0; i < 1; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(0.0f, -1.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}

	//snap back to the origin
	m4Model = m4Origin;
	m4Translate = glm::translate(m4Model, vector3(0.0f, -1.0f, 0.0f));
	m4Model = m4Translate;

	//left
	for (int i = 0; i < 3; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(-1.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}
	for (int i = 0; i < 1; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(0.0f, -1.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}

	//snap back to the origin
	m4Model = m4Origin;
	m4Translate = glm::translate(m4Model, vector3(0.0f, -3.0f, 0.0f));
	m4Model = m4Translate;

	//right 
	for (int i = 0; i < 2; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(1.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}

	m4Translate = glm::translate(m4Model, vector3(-2.0f, 0.0f, 0.0f));
	m4Model = m4Translate;

	//left
	for (int i = 0; i < 2; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(-1.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
	}

	//snap back to the origin
	m4Model = m4Origin;
	//go up a line
	m4Translate = glm::translate(m4Model, vector3(0.0f, 1.0f, 0.0f));
	m4Model = m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	//right 
	m4Translate = glm::translate(m4Model, vector3(1.0f, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(m4Model, vector3(2.0f, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(m4Model, vector3(1.0f, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);


	//snap back to the origin
	m4Model = m4Origin;
	//go up a line
	m4Translate = glm::translate(m4Model, vector3(0.0f, 1.0f, 0.0f));
	m4Model = m4Translate;
	//left
	m4Translate = glm::translate(m4Model, vector3(-1.0f, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(m4Model, vector3(-2.0f, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	m4Translate = glm::translate(m4Model, vector3(-1.0f, 0.0f, 0.0f));
	m4Model = m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);

	//snap back to the origin
	m4Model = m4Origin;
	//go up 2 lines
	m4Translate = glm::translate(m4Model, vector3(0.0f, 2.0f, 0.0f));
	m4Model = m4Translate;
	m_pMesh->Render(m4Projection, m4View, m4Model);
	
	//right 
	for (int i = 0; i < 3; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(1.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
		if (i == 1)
		{
			m4Translate = glm::translate(m4Model, vector3(0.0f, 1.0f, 0.0f));
			m4Model = m4Translate;
			m_pMesh->Render(m4Projection, m4View, m4Model);
			m4Translate = glm::translate(m4Model, vector3(0.0f, -1.0f, 0.0f));
			m4Model = m4Translate;

		}
		if (i == 2)
		{
			m4Translate = glm::translate(m4Model, vector3(0.0f, 2.0f, 0.0f));
			m4Model = m4Translate;
			m_pMesh->Render(m4Projection, m4View, m4Model);
			m4Translate = glm::translate(m4Model, vector3(0.0f, -2.0f, 0.0f));
			m4Model = m4Translate;
		}
	}
	//snap back to the origin
	m4Model = m4Origin;
	//go up 2 lines
	m4Translate = glm::translate(m4Model, vector3(0.0f, 2.0f, 0.0f));
	m4Model = m4Translate;

	//left of start
	for (int i = 0; i < 3; i++)
	{
		m4Translate = glm::translate(m4Model, vector3(-1.0f, 0.0f, 0.0f));
		m4Model = m4Translate;
		m_pMesh->Render(m4Projection, m4View, m4Model);
		if (i == 1)
		{
			m4Translate = glm::translate(m4Model, vector3(0.0f, 1.0f, 0.0f));
			m4Model = m4Translate;
			m_pMesh->Render(m4Projection, m4View, m4Model);
			m4Translate = glm::translate(m4Model, vector3(0.0f, -1.0f, 0.0f));
			m4Model = m4Translate;

		}
		if (i == 2)
		{
			m4Translate = glm::translate(m4Model, vector3(0.0f, 2.0f, 0.0f));
			m4Model = m4Translate;
			m_pMesh->Render(m4Projection, m4View, m4Model);
			m4Translate = glm::translate(m4Model, vector3(0.0f, -2.0f, 0.0f));
			m4Model = m4Translate;
		}
	}



	
	
	// draw a skybox
	m_pMeshMngr->AddSkyboxToRenderList();

	// draw the grid
	m_pMeshMngr->AddGridToRenderList();

	
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

	//release GUI
	ShutdownGUI();
}