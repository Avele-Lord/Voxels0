#pragma once
// Refactored 15.04.2021	// Looked Through 15.09.2021


// HRESULT HR should exist in the local scope for these macros to work

#define GFX_EXCEPT_NOINFO(HR) Graphics::HrException( __LINE__,__FILE__,(HR) )
#define GFX_THROW_NOINFO(Hrcall) if( FAILED( HR = (Hrcall) ) ) throw Graphics::HrException( __LINE__,__FILE__,HR )

#ifndef NDEBUG
#define GFX_EXCEPT(HR) Graphics::HrException( __LINE__,__FILE__,(HR),InfoManager.GetMessages() )
#define GFX_THROW_INFO(Hrcall) InfoManager.Set(); if( FAILED( HR = (Hrcall) ) ) throw GFX_EXCEPT(HR)
#define GFX_DEVICE_REMOVED_EXCEPT(HR) Graphics::DeviceRemovedException( __LINE__,__FILE__,(HR),InfoManager.GetMessages() )
#define GFX_THROW_INFO_ONLY(Call) InfoManager.Set(); (Call); {auto Messages = InfoManager.GetMessages(); if(!Messages.empty()) {throw Graphics::InfoException( __LINE__,__FILE__,Messages);}}
#else
#define GFX_EXCEPT(HR) Graphics::HrException( __LINE__,__FILE__,(HR) )
#define GFX_THROW_INFO(Hrcall) GFX_THROW_NOINFO(Hrcall)
#define GFX_DEVICE_REMOVED_EXCEPT(HR) Graphics::DeviceRemovedException( __LINE__,__FILE__,(HR) )
#define GFX_THROW_INFO_ONLY(Call) (Call)
#endif

// Macro for importing infoManager into local scope
// this.GetInfoManager(Graphics& gfx) must exist
#ifdef NDEBUG
#define INFOMAN(Gfx) HRESULT HR
#else
#define INFOMAN(Gfx) HRESULT HR; DxgiInfoManager& InfoManager = GetInfoManager((Gfx))
#endif