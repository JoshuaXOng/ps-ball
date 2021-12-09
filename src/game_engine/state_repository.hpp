#pragma once 
#include <vector>

class Updateable;
class Renderable;

class StateRepository {

    public:

        std::vector<Updateable*> updateables;
        std::vector<Renderable*> renderables;

};