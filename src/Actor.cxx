#include <gravel/private/Actor.h>

#include "gravel/Context.h"



void Gravel::GraphNode::connect(Gravel::Pointer::GraphNode na, Gravel::Pointer::GraphNode nb) {
    

    back.insert(BackMapPair(   Gravel::WeakPointer::GraphNode(na), Gravel::WeakPointer::GraphNode(nb)));
}

Gravel::GraphNode::GraphNode() :width(1)  { 
    
}

Gravel::GraphNode::~GraphNode() { 
    
}
 
unsigned Gravel::GraphNode::getWidth() {
    return width;
}

Gravel::GraphNode::BackMap Gravel::GraphNode::back;

Gravel::Pointer::GraphNode Gravel::Actor::getOutput() const {
     
     Gravel::GraphNode::NodeMap::const_iterator nit = nodes.find(Gravel::Output);
     if (nit == nodes.end()) {
         assert(false);
     }  else { 
         return (nit->second);
     }
   
     
}
 
Gravel::GraphNode::BackMapRange Gravel::GraphNode::getConnections(Gravel::Pointer::GraphNode np) { 
    return Gravel::GraphNode::back.equal_range(np);
}
 
Gravel::GraphNode::ConstNodeRange Gravel::Actor::getInputs() const {
    
  return nodes.equal_range(Gravel::Input);
    
  
}

  void Gravel::Actor::setWidth(Gravel::Pointer::GraphNode node, unsigned width) {
      
  }
  
    Gravel::Actor::Actor() : initialized(false) {
        
    }


Gravel::Pointer::Actor Gravel::GraphNode::getParent(Gravel::Pointer::GraphNode np) { 

    assert(np.get() != NULL);
    
    Gravel::Context * ctx = Gravel::Context::getInstance();
    return ctx->getParent(np);

};

Gravel::Pointer::Actor Gravel::GraphNode::getParent(Gravel::GraphNode::ConstNodeIterator it) { 

    Gravel::Context * ctx = Gravel::Context::getInstance();
    return ctx->getParent(it->second);

};


void Gravel::Actor::initialize(Gravel::Pointer::Actor actor) {
    Gravel::Context * ctx = Gravel::Context::getInstance();
    // store a weak pointer
    ctx->insert(actor);
    initialized = true;
 /*   Gravel::GraphNode::ConstNodeIterator cit;
    for (cit = nodes.begin() ; cit != nodes.end() ; cit++) {
        Gravel::WeakPointer::GraphNode wn = cit->second;
        Gravel::Pointer::GraphNode node = wn.lock();
        
    
    }
   */ 
}


Gravel::Pointer::GraphNode Gravel::GraphNode::Create(GraphNode::NodeMap & nodes, const Gravel::GraphEdgeDirection & direction) {
    Gravel::Pointer::GraphNode node(new Gravel::GraphNode());
    

    nodes.insert(Gravel::GraphNode::NodePair(direction, node));
    return node;  
}

