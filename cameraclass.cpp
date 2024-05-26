////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "cameraclass.h"


CameraClass::CameraClass()
{
	m_position.x = 0.0f;
	m_position.y = 0.0f;
	m_position.z = 0.0f;

	moveLeftRight = 0;
	moveBackForward = 0;

	m_rotation.x = 0.0f;
	m_rotation.y = 0.0f;
	m_rotation.z = 0.0f;

	//Camera information
	camPosition = XMVectorSet(0.0f, 5.0f, -8.0f, 0.0f);
	camTarget = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	camUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//Set the View matrix
	camView = XMMatrixLookAtLH(camPosition, camTarget, camUp);

	//Set the Projection matrix
	camProjection = XMMatrixPerspectiveFovLH(0.4f * 3.14f, (float)800 / (float)600, 1.0f, 1000.0f);
}


CameraClass::CameraClass(const CameraClass& other)
{
}


CameraClass::~CameraClass()
{
}


void CameraClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}


void CameraClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}


XMFLOAT3 CameraClass::GetPosition()
{
	return m_position;
}


XMFLOAT3 CameraClass::GetRotation()
{
	return m_rotation;
}

// This uses the position and rotation of the camera to build and to update the view matrix.
void CameraClass::Render()
{
	//XMVECTOR camUp, camPosition, camTarget;
	
	XMMATRIX rotationMatrix;
	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR camForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR camRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);

	// Setup the position of the camera in the world.
	//camPosition = XMLoadFloat3(&m_position);

	// Setup where the camera is looking by default.
	//camTarget = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
	/*pitch = m_rotation.x * 0.0174532925f;
	yaw   = m_rotation.y * 0.0174532925f;
	roll  = m_rotation.z * 0.0174532925f;*/

	// Create the rotation matrix from the yaw, pitch, and roll values.
	rotationMatrix = XMMatrixRotationRollPitchYaw(pitch, yaw, 0);

	// Transform the lookAt and up vector by the rotation matrix so the view is correctly rotated at the origin.
	camTarget = XMVector3TransformCoord(DefaultRight, rotationMatrix);
	camTarget = XMVector3Normalize(camTarget);

	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(yaw);

	camRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
	camUp = XMVector3TransformCoord(camUp, RotateYTempMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);

	// Moving the Camera
	// 
	// Next we update the position of our camera using the two values, moveLeftRight, and moveBackForward, 
	// and the two vectors, Right, and Forward. To move the camera left and right, we multiply the moveLeftRight 
	// variable with the Right vector, and add that to the Position. Then to move back and forward, we multiply 
	// moveBackForward with the Forward vector and add that to the Position too. The moveLeftRight and 
	// moveBackForward values will be calculated when direct input detects a certain key was pressed (in the 
	// case of this lesson A, S, D, or W).
	// After that we reset the moveLeftRight and moveBackForward variables.
	camPosition += moveLeftRight * camRight;
	camPosition += moveBackForward * camForward;

	if (moveLeftRight > 0)
	{
		moveLeftRight = 0.0f;
	}

	moveLeftRight = 0.0f;
	moveBackForward = 0.0f;
	// Translate the rotated camera position to the location of the viewer.
	camTarget = camPosition + camTarget;

	// Finally create the view matrix from the three updated vectors.
	m_viewMatrix = XMMatrixLookAtLH(camPosition, camTarget, camUp);

	return;
}


void CameraClass::GetViewMatrix(XMMATRIX& viewMatrix)
{
	viewMatrix = m_viewMatrix;
}