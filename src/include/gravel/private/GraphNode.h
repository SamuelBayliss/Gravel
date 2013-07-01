/* 
 * File:   Node.h
 * Author: sb1708
 *
 * Created on May 20, 2013, 12:08 PM
 */

#ifndef NODE_H
#define	NODE_H

#include <gravel/private/Definitions.h>

#include "gravel/Context.h"

namespace Gravel { 

 class GraphNode { 
   
    public :     
        
          typedef std::multimap<GraphEdgeDirection, Gravel::Pointer::GraphNode > NodeMap;
          typedef std::pair<GraphEdgeDirection, Gravel::Pointer::GraphNode > NodePair;
          typedef NodeMap::const_iterator ConstNodeIterator;
          typedef NodeMap::iterator NodeIterator;
       
          typedef std::pair<NodeIterator, NodeIterator> NodeRange;
          typedef std::pair<ConstNodeIterator, ConstNodeIterator> ConstNodeRange;
          
          
          
          
          typedef std::map<Gravel::WeakPointer::GraphNode, Gravel::WeakPointer::GraphNode> EdgeMap;
         
          
          typedef std::map<Edge, Gravel::Pointer::EdgeAnnotation> AnnotationMap;
        
          
          typedef EdgeMap::iterator EdgeMapIterator;
          typedef std::pair<EdgeMapIterator, EdgeMapIterator> BackMapRange;
         
          typedef std::map<Gravel::WeakPointer::GraphNode, Gravel::Pointer::Actor> ParentMap;
        
        // Destructor
        ~GraphNode();
        
        // points to implementation (which is an actor)

        static Gravel::Pointer::Actor getParent(Gravel::Pointer::GraphNode);
        static Gravel::Pointer::Actor getParent(Gravel::GraphNode::ConstNodeIterator);
         
     
         static Gravel::Collection::EdgeAnnotation getAnnotations(Gravel::Pointer::Edge);
         static BackMapRange getConnections(Gravel::Pointer::GraphNode);
         
        // Graph Node destructor removes back-link and removes from ring
        static void connect(Gravel::Pointer::GraphNode, Gravel::Pointer::GraphNode);
        static void connect(Gravel::Edge);
        static void annotate(Gravel::Edge&, Gravel::Pointer::EdgeAnnotation&);
        
        
        unsigned getWidth();
        // Default Constructor
        static Gravel::Pointer::GraphNode Create(Gravel::GraphNode::NodeMap&, const Gravel::GraphEdgeDirection&);
         private: 
                 GraphNode();
        unsigned width;
        
        static EdgeMap edges;
        static AnnotationMap annotations;
        
       
        
        
        // Copy Constructor is declared but not implemented
        
        // Equality Assignment is declared but not implemented
    };
    
        namespace Collection { 
        typedef std::pair<Gravel::GraphNode::ConstNodeIterator, Gravel::GraphNode::ConstNodeIterator> GraphNodeRange;
     }
    
};

#endif	/* NODE_H */

