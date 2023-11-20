#pragma once

class Component {
public:
    Component(class Actor *owner, int updateOrder = 100);
    virtual ~Component();

    virtual void update(float delta_time);
    int getUpdateOrder() const { return update_order; }
protected:
    class Actor *owner;
    int update_order;
};