#include "OOSkeleton.h"

OOSkeleton::OOSkeleton()
	:
	OOMob(549978)//,
	//LeftHand(8),
	//RightHand(9)
{
	Components.emplace_back(OOMob::TheMobManager->AddComponentToArrayOfComps(MobComponentTypes::RenderableComponent)); // by this i have to add compoent to skeleton basicly that compoent whodul be conected to skeleton mob by ID of skeleton!!
	AddComponentToMob(MobComponentTypes::RenderableComponent);
		



	// BASICLY what i'm gonna do IS to asign ALL compoentns of other mobs which are composing this mob ASIGN EM to the vector of compoentns OF THE MAIN OUR MOB (and MAY BE delet redundent vectors repiting once form thoes smaller composing mobs OR may be odnt' dlete cos i will need thoes vectors later IF LIEK my mob losses the weapon etc!! ) 
	//std::vector<OOMobComponent*>& AllBowComponents = this->Bow.Components;
	//std::vector<OOMobComponent*>& AllSkeletonComponents = this->Components;
	//AllSkeletonComponents.insert(AllSkeletonComponents.end(), AllBowComponents.begin(), AllBowComponents.end());
}
