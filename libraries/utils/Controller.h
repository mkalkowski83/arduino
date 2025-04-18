#ifndef CONTROLLER_H
#define CONTROLLER_H

// Abstract interface for all controllers in the system
class Controller {
public:
    // Virtual destructor
    virtual ~Controller() {}
    
    // Controller initialization
    virtual void begin() = 0;
    
    // Update controller state
    virtual void update() = 0;
    
    // Returns controller description (optional implementation)
    virtual const char* getName() {
        return "GenericController";
    }
};

#endif 