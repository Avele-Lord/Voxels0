// Refactored 20.05.2021	// Looked Through 15.09.2021
#include "Camera.h" // need
#include "imgui/imgui.h" // need
#include "Math.h" // need
#include <algorithm> // need


namespace dx = DirectX;


Camera::Camera() noexcept
{
	Reset();
}
///  NON Refactored start 15.09.2021
DirectX::XMFLOAT3 Camera::GetCamPos()
{
	return Pos;
}

DirectX::XMFLOAT3& Camera::GetCamPosRef()
{
	return Pos;
}
///  NON Refactored end 15.09.2021

Rotation Camera::GetCamRotation()
{
	return Rotation(Pitch, Yaw);
}

// Here why sin and cos flipped start
DirectX::XMMATRIX Camera::GetMatrix() const noexcept
{
	using namespace dx;

	const dx::XMVECTOR ForwardBaseVector = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	// Apply the camera rotations to a base vector
	const auto LookVector = XMVector3Transform(ForwardBaseVector,
		XMMatrixRotationRollPitchYaw(Pitch, Yaw, 0.0f)
	);
	// Generate camera transform (applied to all objects to arrange them relative
	// To camera position/orientation in world) from cam position and direction
	// Camera "top" always faces towards +Y (cannot do a barrel roll)
	const auto CamPosition = XMLoadFloat3(&Pos);
	const auto CamTarget = CamPosition + LookVector;
	return XMMatrixLookAtLH(CamPosition, CamTarget, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
}
// Here why sin and cos flipped end
void Camera::SpawnControlWindow() noexcept
{
	if (ImGui::Begin("Camera"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &Pos.x, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Y", &Pos.y, -80.0f, 80.0f, "%.1f");
		ImGui::SliderFloat("Z", &Pos.z, -80.0f, 80.0f, "%.1f");
		ImGui::Text("Orientation");
		ImGui::SliderAngle("Pitch", &Pitch, 0.995f * -90.0f, 0.995f * 90.0f);
		ImGui::SliderAngle("Yaw", &Yaw, -180.0f, 180.0f);
		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void Camera::Reset() noexcept
{
	Pos = { /*3700.0f, 72.0f, 1050.0f*/ /*4328.0f, 230.0f, 2013.0f*/ /*4140.0f, 0.0f /*600.0f*//*, 1140.0f*/
		/*MAIN ONE START -4060.0f, 20.0f MAIN ONE END*/ /*600.0f*//*MAIN ONE START, 144.0f  MAIN ONE END */ 4308.0f, 630.0f, 2013.0f }; //THIS IS ORIGINAL!!!  START -4060.0f, 20.0f, 144.0f }; ORIGINAL END// /// DOPEST LOCATION IS THIS ONE 4328.0f, 230.0f, 2013.0f
	Pitch = 0.0f/*-0.57f*//*0.0f*/; // PI radians  from -1.5 to 1.5  
	Yaw = 1.57079637f/*2.04f*/; // PI radians   from -1.5 to 1.5 (PROBABLY FORM -PI TO PI OR FROM ) 
}


void Camera::Rotate(float DeltaX, float DeltaY) noexcept
{
	Pitch = std::clamp(Pitch + DeltaY * RotationSpeed, 0.995f * -PI / 2.0f, 0.995f * PI / 2.0f);
	Yaw = WrapAngle(Yaw + DeltaX * RotationSpeed);
}

void Camera::Translate(DirectX::XMFLOAT3 Translation, bool AddPitch) noexcept
{
	dx::XMStoreFloat3(&Translation, dx::XMVector3Transform(
		dx::XMLoadFloat3(&Translation),
		dx::XMMatrixRotationRollPitchYaw(AddPitch ? 0.0f : Pitch , Yaw, 0.0f) *
		dx::XMMatrixScaling(TravelSpeed, TravelSpeed, TravelSpeed)
	));
	Pos = {
		Pos.x + Translation.x,
		Pos.y + Translation.y,
		Pos.z + Translation.z
	};
}





//FOR TEST DELET LATER START
void Camera::SetCam(float Pitch, float Yaw) noexcept
{
	this->Pitch = Pitch;
	this->Yaw = Yaw;
}
//FOR TEST DELET LATER END