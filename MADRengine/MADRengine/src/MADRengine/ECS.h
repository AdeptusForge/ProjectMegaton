#include "MADRpch.h"
#include <map>
#include "Events.h"
#include <memory>
#include "nlohmann/json.hpp"

int minimumCapacity = 128;
int maxByteCapacity;

struct ComponentID;

class Component : public EventListener 
{
	


};

template<typename T>
class ComponentManager :public EventListener 
{
private:
	void* storage;
	std::unordered_map<ComponentID, T*> IDKeeping;
	T* last = nullptr;

	void CompressStorage() 
	{



	}


public:
	int size = 0;
	int capacity = minimumCapacity;

	ComponentManager()
	{
		capacity = minimumCapacity;
		storage = malloc(sizeof(T) * capacity);
		firstEmptySlot = storage;
	}

	~ComponentManager()
	{
		if (storage != nullptr)
			free(storage);
	}

	struct fmt::formatter<ComponentManager> : fmt::formatter<std::string>
	{
		auto format(ComponentManager my, format_context& ctx) const -> decltype(ctx.out())
		{
			return format_to(ctx.out(), "[my_type size={}]", my.size);
		}
	};



	bool Reallocate(int newCapacity) 
	{
		if (newCapacity != capacity && newCapacity > size)
		{
			newStorage = std::malloc(sizeof(T) * minimumCapacity);
			if (newStorage != nullptr) 
			{
				
				std::memcpy(newStorage, storage, sizeof(T) * capacity);
				capacity = newCapacity;
				std::cout << "Reallocated to " << capacity << std::endl;
				storage = newStorage;
				return true;
			}
			else
			{
				std::cout << "Allocation Failed" << std::endl;
				return false;
			}
		}
		else if (newCapacity == capacity)
		{
			std::cout << "Cannot reallocate to the same capacity size" << std::endl;
		}
		std::cout << "Deletion of end elements with reallocation." << std::endl;

		return false;
	}


	bool CreateComponent() 
	{
		T* placementAddress = last + sizeof(T);
		size++;
		*(placementAddress) = T();
		if (size > capacity) 
		{
			Reallocate(capacity * 2);
		}

	}

	template<typename T>
	bool DeleteComponent(ComponentID component) 
	{
		T& found = RetrieveComponent(component);
		if (found != nullptr) 
		{
			std::cout << "Delete component: " << component << std::endl;
			return true;
		}
		return false;
	}

	bool ValidID(ComponentID ID)
	{


	}

	//Assumes correct ID. Use ValidID to check first before using.
	T& RetrieveComponent(ComponentID ID)
	{
		T* index = IDKeeping.find(ID);
		return *index;
	}



};