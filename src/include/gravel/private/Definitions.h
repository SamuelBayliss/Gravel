/* 
 * File:   Defintions.h
 * Author: sb1708
 *
 * Created on June 26, 2013, 4:00 PM
 */

#ifndef DEFINTIONS_H
#define	DEFINTIONS_H

/* Contains forward definitions of all concepts used in application */

#include <set>
#include <map>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace Gravel { 
  
    
    
  
    class Actor;
    class GraphNode;
    
    class Module;

    class Expression;
    class Symbol;
    
    namespace Implementation { 
        class Module;
    }
    
    namespace Annotation { 
        class EdgeAnnotation;
        class ContinuousAssignment;
        class ClockedAssignment;
        class Enable;
        class Reset;
    }
    
    namespace Interface { 
        class Actor;
    }
    
    namespace Pointer { 
        typedef boost::shared_ptr<Gravel::Actor> Actor; 
        typedef boost::shared_ptr<Gravel::Annotation::EdgeAnnotation> EdgeAnnotation;
        typedef boost::shared_ptr<Gravel::GraphNode> GraphNode;
        typedef boost::shared_ptr<Gravel::Implementation::Module> Module;
        typedef   boost::shared_ptr<Gravel::Annotation::ClockedAssignment> ClockedAssignment;
        typedef   boost::shared_ptr<Gravel::Annotation::ContinuousAssignment> ContinuousAssignment;
        typedef   boost::shared_ptr<Gravel::Annotation::Reset> Reset;
        typedef   boost::shared_ptr<Gravel::Annotation::Enable> Enable;
     
    };
    
    namespace WeakPointer { 
          typedef boost::weak_ptr<Gravel::GraphNode> GraphNode;
    };
    
    typedef std::pair<Gravel::WeakPointer::GraphNode, Gravel::WeakPointer::GraphNode> Edge;
    
    namespace Collection {         
      typedef std::set<Gravel::Pointer::EdgeAnnotation> EdgeAnnotation;

      typedef std::set<Gravel::Pointer::Actor> Actor;
      typedef std::set<Gravel::Pointer::GraphNode> GraphNode;
    }  
    
    namespace Exception { 
         class GraphNodeNotFound;
     }
    
    
    typedef enum GraphEdgeDirection {Input, Output};
    
};

   
#endif	/* DEFINTIONS_H */

