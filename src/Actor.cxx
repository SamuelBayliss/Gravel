#include <gravel/private/Actor.h>

void Gravel::GraphNode::connect(boost::weak_ptr<Gravel::GraphNode> na, boost::weak_ptr<Gravel::GraphNode> nb) {
    
}

Gravel::GraphNode::GraphNode()  { 
    
}

Gravel::GraphNode::~GraphNode() { 
    
}
 
Gravel::GraphNode::BackMap Gravel::GraphNode::back;
Gravel::GraphNode::ParentMap Gravel::GraphNode::parent;
       
 boost::weak_ptr<Gravel::GraphNode> Gravel::Actor::getOutput() const {
     
     Gravel::GraphNode::NodeMap::const_iterator nit = nodes.find(Gravel::Output);
     if (nit == nodes.end()) {
         assert(false);
     }  else { 
         return boost::weak_ptr<Gravel::GraphNode>(nit->second);
     }
   
     
}
 
Gravel::GraphNode::BackMapRange Gravel::GraphNode::getConnections(NodePtr np) { 
    return Gravel::GraphNode::back.equal_range(np);
}
 
Gravel::GraphNode::ConstNodeRange Gravel::Actor::getInputs() const {
    
  return nodes.equal_range(Gravel::Input);
    
  
}

  void Gravel::Actor::setWidth(Gravel::GraphNode::NodePtr node, unsigned width) {
      
  }
  
Gravel::Pointer::Actor Gravel::GraphNode::getParent(Gravel::GraphNode::NodePtr np) { 

std::map<Gravel::GraphNode::NodePtr, Gravel::Pointer::Actor>::iterator nit = parent.find(np);

if(nit == parent.end()) {
 // throw exception
} else {
    return nit->second;
}
 


};

void Gravel::GraphNode::setParents(Gravel::Pointer::Actor ptr) {
       
       Gravel::GraphNode::ConstNodeRange inputs = ptr->getInputs();
       Gravel::GraphNode::NodePtr output = ptr->getOutput();

   }
