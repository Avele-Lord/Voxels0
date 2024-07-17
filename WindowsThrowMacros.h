#pragma once
// Refactored 15.04.2021	// Looked Through 15.09.2021


#define CHWND_EXCEPT( HR ) Window::HrException( __LINE__,__FILE__,(HR) )
#define CHWND_LAST_EXCEPT() Window::HrException( __LINE__,__FILE__,GetLastError() )
#define CHWND_NOGFX_EXCEPT() Window::NoGfxException( __LINE__,__FILE__ )