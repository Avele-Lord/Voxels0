#include "OOMobSystem.h"
#include "OOMobComponent.h"
#include "OOMob.h"





//////////MY ECS ////   start///////////
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//  PLAN on OnMobCreated function
// 1 seporet it on TWO FUNCTIONS 
// 2 one function will be at compile time
// 2.1 AND this funciton will check which mobs goes througfh the requairments which don't
// 3  second function will be at run time
// 3.1 and it will just run and att indexes in systems OF ALL NEW MOB
// 4 this will SPEED UP A LOT the game iff i will be crteating A LOT OF NEW MOBS EVERY SECOND!!! SO DO IT!! 
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^




// 1 the questio is can system have as requairment or optional components BASICLY not liek one weapon compoentn but like two or three weapon compoentns to be alowas to proces on some systems BUT if i willdo somthing liek thta it will be rear and i will just implement manualy thoes rear systems!

OOMobSystem::OOMobSystem()
{
	// TODO (but WHAT??? 
}


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// NOW NOW it's all cool and fine AND will work 
// BUT it will work ONLY IFF enityty has unique components so like ONLY one weapon for entity no liek3 or 5 or 10 weapons on one entity
// SO SOMMHOW i have to change and it and redo it somhow so MOB WHOUDL BE ABLE TO have  like same compoentns liek 3 weapon compoentns oOR EVEN LIKE whatever else duplicates compoentns LIKE 2 half bars components or whatevefr else i want!
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// 1: has to suport optional components in systems
// 2: has to suport multiple copmonents on one entity
// 3: has to go through ALL systems and put matching entities copmonents in thoes systems index vectors
// 4: SO MY idea of this function is be called  on each system seporetly NOT in forlyp not virtual functyion
// 4: and i will just overLOAD (not overide cos no virtual!) the base funcion of base syste class
// 4: and porbably just in overLOADED version just one change is just pass in base version different vectors of componenindex requairments and optional components.
// 5: this function will go through ALL entity componentns no matter what COS i have possibility to add oto ne entity the same components like 3 weapon components so i will need to go to the very end!
void OOMobSystem::OnMobCreated(const OOMob& MobIn, std::vector<std::vector<unsigned int>*>&/* * *//* or std::vector<std::vector<unsigned int>*>  /*can don't work cos reference or pointer just delet itself imidietly so use conreat vector*/  AllIndexesOfComponentSystem, std::vector<MobComponentTypes> CallItSomthingLikeAllComponentTypesIDontKnow, std::vector<MobComponentTypes> MobComponentTypesRequired, std::vector<MobComponentTypes> MobComponentTypesOptional)
{
//	// loop through all the copmonents on this enityty and see if any tuples match
	const std::vector<OOMobComponent*>& MobComponents = MobIn.GetAllComponents();
	std::vector<OOMobComponent*> MatchedMobComponents = { nullptr };
	int NumberOfAllRequiredMatchingComponents = MobComponentTypesRequired.size();
	bool IsMatchingComponent = false;
	bool IsOptionalComponent = false;
	int CurrentNumberOfAllMatchingComponents = 0;
	// no break out of loop cos no matter what have to run through ALL the components cos i have optinal and repeated compoentns! 
	for (int i = 0; i < MobComponents.size(); i++)
	{
		MobComponentTypes CurrentMobComponentType = MobComponents[i]->GetCompType();
	
		for (int j = 0; j < MobComponentTypesRequired.size(); j++)
		{
			if (MobComponentTypesRequired[j] == CurrentMobComponentType)
			{
				IsMatchingComponent = true;
				break;
			}
		}

		if (IsMatchingComponent == false)
		{
			for (int k = 0; k < MobComponentTypesOptional.size(); k++)
			{
				if (MobComponentTypesOptional[k] == CurrentMobComponentType)
				{
					IsMatchingComponent = true;
					IsOptionalComponent = true;
					break;
				}
			}
		}

		if (IsMatchingComponent)
		{
			// SO THIS bit of code INSTED OF putring anything in AllIndexesOfComponentSystem I MUST FIRTS make some class which contains entity ID or like mroe like entity and component ID AND what component it is (comp type)
			// and put in this array matching component and the type of compoentn
			// AND basicly AT THE END after this loop have some csome other for loop which  CHECK that ALL reuqairment component are in this entity AND IF IT IS then we take from this vector which we fill in this bit of code and put all entity IDS in coirespanding component vectors
			if (!IsOptionalComponent)
			{
				bool IsDuplicateComponent = false; 
				for (int j = 0; j < MatchedMobComponents.size(); j++)
				{
					if (MatchedMobComponents[j]->GetCompType() == CurrentMobComponentType)
					{
						IsDuplicateComponent = true;
						break;
					}
				}
				if (!IsDuplicateComponent)
				{
					CurrentNumberOfAllMatchingComponents++;
				}
			}
			MatchedMobComponents.emplace_back(MobComponents[i]);
			IsMatchingComponent = false;
			IsOptionalComponent = false;
		}
	}


	// IFF all requared comps are present push em in thoes indexes vectors
	if (CurrentNumberOfAllMatchingComponents == NumberOfAllRequiredMatchingComponents)
	{
	///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// DUDE well you dummy COS with the same components on one mob i.e 3 weapon componetns on one mob IT'S EASEYYYYYYYY cos dude every component HAVE INDEX IN WHICH ARRAY IT IS so you just put that index and YOU ARE DONE !! 
	///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		std::vector<MobComponentTypes> AllMobComponentTypes = std::vector<MobComponentTypes>(MobComponentTypesRequired.begin(), MobComponentTypesRequired.end());
		AllMobComponentTypes.insert(AllMobComponentTypes.end(), MobComponentTypesOptional.begin(), MobComponentTypesOptional.end());

		for (int i = 0; i < MatchedMobComponents.size(); i++)
		{
			OOMobComponent* MatchedMobComponent = MatchedMobComponents[i];
			MobComponentTypes MatchedMobComponentType = MatchedMobComponent->GetCompType();
			for (int j = 0; j < AllMobComponentTypes.size(); j++)
			{
				if (AllMobComponentTypes[j] == MatchedMobComponentType)  
				{
					std::vector<unsigned int>* IndexesOfComponentSystem = AllIndexesOfComponentSystem[j];   
					IndexesOfComponentSystem->emplace_back(MatchedMobComponent->GetCompIndex());
					break;
				}
			}
		}


		////////////////////////////// this not this bit of coed it's  componet from othe r bit of code // START 
		// SO THIS bit of code INSTED OF putring anything in AllIndexesOfComponentSystem I MUST FIRTS make some class which contains entity ID or like mroe like entity and component ID AND what component it is (comp type)
		// and put in this array matching component and the type of compoentn
		// AND basicly AT THE END after this loop have some csome other for loop which  CHECK that ALL reuqairment component are in this entity AND IF IT IS then we take from this vector which we fill in this bit of code and put all entity IDS in coirespanding component vectors
		////////////////////////////// this not this bit of coed it's  componet from othe r bit of code // END 
		/// !!!!!!!!!!!!!!!!!!!!!!!! OK SO HERE I WILL BE puting ID of entity and liek component ID and entity ID BASICLY ID or even YEAH HASH
		/// BASICLY I PUT HASH of component and entitiyi ID together AND IT'S A MUST to don't calcylate hash over and over again later insted calcylate it once here and you are done
		/// SOOOO basicly i put in hash function like <MobID, ComponentType > and i will get corect mob together with component hash
		///!!!! OK COOL BUUUUUUT read below it wont'; work with multiple compoentns! 
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		/// NOW NOW it's all cool and fine AND will work 
		/// BUT it will work ONLY IFF enityty has unique components so like ONLY one weapon for entity no liek3 or 5 or 10 weapons on one entity
		/// SO SOMMHOW i have to change and it and redo it somhow so MOB WHOUDL BE ABLE TO have  like same compoentns liek 3 weapon compoentns oOR EVEN LIKE whatever else duplicates compoentns LIKE 2 half bars components or whatevefr else i want!
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		///^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		// basicly put macging component in  AllIndexesOfComponentSystem
		//AllIndexesOfComponentSystem = ???

	}

//  TODO : so here my aim is just to check DOES this entity has ALL the requairment compoentns
//	AND if it have all requaired components then that entity passes the test AND all thoes requaired components added in indexes vectors
  //!!!!!!!!!!!!!! ALSO if it passes ALL components which are optional for this system AND this entity has ADD to vectors of indexes for optiona components
 //so  i will need anyways go through ALL copmponent ontill i find all riquairment and o optional then break
 //if not found all requairments  RIJECT ALL entity 
 // i don't realy know how it's gonna look tho some for loop ro what not and it must be for or less generic so i be able to put any system vectors of indexes through this fucntion to don't rewrite the same code again and again

///  





//	CompTuple CompTupleL;
//	size_t MatchingComps = 0;
//	for (auto& CompPair : Mob.GetComponents())
//	{
//		if (ProcessMobComponent<0, Comps...>(CompPair.first, CompPair.second, CompTupleL))
//		{
//			++MatchingComps;
			//if (MatchingComps == sizeof...(Comps))
			//{
			//	Components.emplace_back(std::move(CompTupleL));
			//	MobIdToIndexMap.emplace(MobIn.GetId(), Components.size() - 1);
			//	break;
			//}
//		}
//	}
}



//////////MY ECS ////   end///////////







//////////ORIGINAL ECS ////   start///////////


//OOMobSystem::OOMobSystem(OOMobManager * MobManagerP)
//	:
//	OOBaseMobSystem(MobManagerP)
//{}


//template <class... Comps>
//void OOMobSystem<Comps...>::OnMobCreated(const OOMob& MobIn)
//{
//	// loop through all the copmonents on this enityty and see if any tuples match
//	CompTuple CompTupleL;
//	size_t MatchingComps = 0;
//	for (auto& CompPair : Mob.GetComponents())
//	{
//		if (ProcessMobComponent<0, Comps...>(CompPair.first, CompPair.second, CompTupleL))
//		{
//			++MatchingComps;
			//if (MatchingComps == sizeof...(Comps))
			//{
			//	Components.emplace_back(std::move(CompTupleL));
			//	MobIdToIndexMap.emplace(MobIn.GetId(), Components.size() - 1);
			//	break;
			//}
//		}
//	}
//}


//template <class... Comps>
//void OOMobSystem<Comps...>::OnMobDestroyed(MobId MobIdIn)
//{
//	const auto FindIt = MobIdToIndexMap.find(MobIdIn);
//	if (FindIt != MobIdToIndexMap.end())
//	{
//		// move the back element to overwrite this one
//		Components[FindIt->second] = std::move(Components.back());
//		Components.pop_back();
//
//		// We need to figure out which entity the moved component belongs to so we can update the id to index map.
//		// Since all component in a single tuple are owned by the same entity,  we can just grab the first one and query its id.
//		const auto* MovedCompP = std::get<0>(Components[FindIt->second]);
//
//		// find the entry for the moved id and update it with the new index 
//		auto MovedTupleId = MobIdToIndexMap.find(MovedCompP->GetMobId());
//		assert(MovedTupleId != MobIdToIndexMap.end()); // should be impossible
//		MovedTupleId->second = FindIt->second;
//	}
//}


void OOMobSystem::Update(float DeltaTime/*, Context* ContextP*/)
{
	// do stuff(i.e render or move or damage etc!)(well it';s actualy sistem base SO DO NOTHING I GESS!
	//for (int i = 0; i < NumOfMobsWhichPassedRequairmentForThisSystem; i++)
	//{
	//	MobTransform = AllMobTransforms[i];
	//	MobPhisics = AllMobPhisicss[i];
	//	MobColision = AllMobColisions[i];

	//	// do stuff with  MobTransform , MobPhisics ,  MobColision

	//}
}


//template <class... Comps>
//template<size_t Index, class CompType, class ...CompArgs>
//inline bool OOMobSystem::ProcessMobComponent(ComponentId ComponentIdIn, OMobComponent* ComponentP, CompTuple& TupleToFill)
//{
//	if (CompType)::ID = ComponentIdIn)
//	{
//		std::get<Index>(TupleToFill) = static_cast<CompTuple*>(ComponentP);
//		return true;
//	}
//	else
//	{
//		return ProcessMobComponent<Index + 1, CompArgs...>(ComponentIdIn, ComponentP, TupleToFill);
//	}
//}
//
//template <class... Comps>
//template<size_t Index>
//inline bool OOMobSystem::ProcessMobComponent(ComponentId ComponentIdIn, OOMobComponent* ComponentP, CompTuple& TupleToFill)
//{
//	return false;
//}


//////////ORIGINAL ECS ////   end///////////
