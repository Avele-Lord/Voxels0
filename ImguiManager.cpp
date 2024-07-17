// Refactored 15.04.2021	// Looked Through 15.09.2021
#include "ImguiManager.h" // need 
#include "imgui/imgui.h" // need 


ImguiManager::ImguiManager()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
}

ImguiManager::~ImguiManager()
{
	ImGui::DestroyContext();
}