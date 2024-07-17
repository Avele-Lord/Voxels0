#pragma once
// Refactored 20.05.2021	// Looked Through 15.09.2021
#include <DirectXMath.h> // need


struct Rotation
{
	Rotation(float Pitch, float Yaw)
		:
		Pitch(Pitch),
		Yaw(Yaw)
	{}
	float Pitch;
	float Yaw;
};


class Camera
{
public:
	Camera() noexcept;
	DirectX::XMMATRIX GetMatrix() const noexcept;
	void SpawnControlWindow() noexcept;
	void Reset() noexcept;
	void Rotate(float dx, float dy) noexcept;
	void Translate(DirectX::XMFLOAT3 Translation, bool AddPitch) noexcept;
	///  NON Refactored start 13.04.2021
	DirectX::XMFLOAT3 GetCamPos();
	DirectX::XMFLOAT3& GetCamPosRef();
	///  NON Refactored end 13.04.2021
	Rotation GetCamRotation();
	void SetCam(float PitchIn, float YawIn) noexcept; //FOR TEST DELET LATER
private:
	DirectX::XMFLOAT3 Pos;
	float Pitch;
	float Yaw;
	static constexpr float TravelSpeed = 12.0f;
	static constexpr float RotationSpeed = 0.004f;
};