#pragma once 
#include <vector>

class Intervalable;
class Updateable;
class Renderable;

class StateRepository {

    public:

        std::vector<Intervalable*> intervalables;
        std::vector<Updateable*> updateables;
        std::vector<Renderable*> renderables;

};