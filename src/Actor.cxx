#include <gravel/private/Actor.h>

#include <gravel/Context.h>

#include <boost/bind.hpp>

Gravel::GraphNode::EdgeMap Gravel::GraphNode::edges;
Gravel::GraphNode::AnnotationMap Gravel::GraphNode::annotations;


void Gravel::GraphNode::connect(Gravel::Pointer::GraphNode na, Gravel::Pointer::GraphNode nb) {
    

    edges.insert(Edge(   Gravel::WeakPointer::GraphNode(na), Gravel::WeakPointer::GraphNode(nb)));
}

void Gravel::GraphNode::connect(Gravel::Edge edge) { 
     edges.insert(edge);
}

Gravel::GraphNode::GraphNode() :width(1)  { 
    
}

Gravel::GraphNode::~GraphNode() { 
    
}
 
unsigned Gravel::GraphNode::getWidth() {
    return width;
}



Gravel::Pointer::GraphNode Gravel::Actor::getOutput() const {
     
     Gravel::GraphNode::NodeMap::const_iterator nit = nodes.find(Gravel::Output);
     if (nit == nodes.end()) {
         assert(false);
     }  else { 
         return (nit->second);
     }
   
     
}
 
    static Gravel::Collection::EdgeAnnotation Gravel::GraphNode::getAnnotations(Gravel::Pointer::Edge edge) {
        Gravel::GraphNode::AnnotationMap::iterator amit = annotations.equal_range(edge);
        Gravel::Collection
    }

void Gravel::GraphNode::annotate(Gravel::Edge& edge , Gravel::Pointer::EdgeAnnotation& annotation) { 
    annotations.insert(std::pair<Gravel::Edge, Gravel::Pointer::EdgeAnnotation>(edge, annotation));
}

Gravel::GraphNode::BackMapRange Gravel::GraphNode::getConnections(Gravel::Pointer::GraphNode np) { 
    return Gravel::GraphNode::edges.equal_range(np);
}
 
Gravel::Collection::GraphNode Gravel::Actor::getInputs() const {
  Gravel::Collection::GraphNode inputs;
  
  Gravel::GraphNode::ConstNodeRange range = nodes.equal_range(Gravel::Input);
  
  std::insert_iterator<Gravel::Collection::GraphNode> ii(inputs, inputs.begin());
  std::transform(range.first, range.second, ii, boost::bind(&Gravel::GraphNode::NodeMap::value_type::second, _1));
  return inputs;}


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

