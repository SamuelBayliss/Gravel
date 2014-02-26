
#include <gravel/Annotation.h>

#include <gravel/private/GraphNode.h>

Gravel::Pointer::EdgeAnnotation Gravel::Annotation::ClockedAssignment::Create(Gravel::Edge edge) {
    
    Gravel::Pointer::EdgeAnnotation ca = Gravel::Pointer::ClockedAssignment(new Gravel::Annotation::ClockedAssignment(edge));
    Gravel::GraphNode::connect(edge);
    Gravel::GraphNode::annotate(edge, ca);
    return ca;
}

Gravel::Pointer::EdgeAnnotation Gravel::Annotation::ContinuousAssignment::Create(Gravel::Edge edge) {
     Gravel::Pointer::EdgeAnnotation ca = Gravel::Pointer::ContinuousAssignment(new Gravel::Annotation::ContinuousAssignment(edge));
    Gravel::GraphNode::connect(edge);   
     Gravel::GraphNode::annotate(edge, ca);
     return ca;
}

Gravel::Pointer::EdgeAnnotation Gravel::Annotation::Reset::Create(Gravel::Edge edge) {
      Gravel::Pointer::EdgeAnnotation rst = Gravel::Pointer::Reset(new Gravel::Annotation::Reset(edge));
        Gravel::GraphNode::connect(edge);
      Gravel::GraphNode::annotate(edge,rst);
      return rst;
}

Gravel::Pointer::EdgeAnnotation Gravel::Annotation::Enable::Create(Gravel::Edge edge, Gravel::Expression expression) {
    Gravel::Pointer::EdgeAnnotation ena = Gravel::Pointer::Enable(new Gravel::Annotation::Enable(edge, expression));
    Gravel::GraphNode::connect(edge);
    Gravel::GraphNode::annotate(edge, ena);
        return ena;
}

Gravel::Annotation::Enable::Enable(Gravel::Edge, Gravel::Expression) { 
    
}

std::ostream& Gravel::Annotation::Enable::process(std::ostream&) { 
    
}

Gravel::Annotation::Reset::Reset(Gravel::Edge) { 
    
}

std::ostream& Gravel::Annotation::Reset::process(std::ostream&) { 
    
}

Gravel::Annotation::ClockedAssignment::ClockedAssignment(Gravel::Edge) { 
    
}

std::ostream& Gravel::Annotation::ClockedAssignment::process(std::ostream&) { 
    
}

Gravel::Annotation::ContinuousAssignment::ContinuousAssignment(Gravel::Edge) { 
    
}

std::ostream& Gravel::Annotation::ContinuousAssignment::process(std::ostream&) { 
    
}