#pragma once
#include <rapidjson/document.h>

class Component {
public:
	enum TypeID {
		TComponent = 0,
		TSpriteComponent,
		NUM_COMPONENT_TYPES
	};
   	static const char* TypeNames[NUM_COMPONENT_TYPES];


    Component(class Actor *owner, int updateOrder = 100);
    virtual ~Component();

	virtual TypeID GetType() const = 0;

	virtual void LoadProperties(const rapidjson::Value& inObj);
	virtual void SaveProperties(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObj) const;
    virtual void update(float delta_time);
    int getUpdateOrder() const { return update_order; }
   	template <typename T>
	static Component* Create(class Actor* actor, const rapidjson::Value& inObj) {
		// Dynamically allocate component of type T
		T* t = new T(actor);
		// Call LoadProperties on new component
		t->LoadProperties(inObj);
		return t;
	}
protected:
    class Actor *owner;
    int update_order;
};