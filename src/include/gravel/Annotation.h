/* 
 * File:   AssignmentAnnotation.h
 * Author: sb1708
 *
 * Created on June 20, 2013, 6:15 PM
 */

#ifndef ASSIGNMENTANNOTATION_H
#define	ASSIGNMENTANNOTATION_H


#include <gravel/private/Definitions.h>
#include <gravel/Expression.h>

namespace Gravel { 




namespace Annotation { 

/* processing an annotation make do lookups on the actor / edge model but may not change it */
    
/* processing an annotation may add output to module, but */
    
class EdgeAnnotation{ 
public:
  virtual  std::ostream& process(std::ostream&) = 0;  

};
    

class ContinuousAssignment : public Gravel::Annotation::EdgeAnnotation{ 
    public:
    // implies continuous assignment between an expression and a symbol
        ContinuousAssignment(Gravel::Edge);
        std::ostream& process(std::ostream&);
         
  static Gravel::Pointer::EdgeAnnotation Create(Gravel::Edge);
};

class ClockedAssignment : public Gravel::Annotation::EdgeAnnotation{ 
    public:
        ClockedAssignment(Gravel::Edge);
        std::ostream& process(std::ostream&);
    // implies clocked assignment between an expression and a symbol
   static Gravel::Pointer::EdgeAnnotation Create(Gravel::Edge);
};

class Enable : public Gravel::Annotation::EdgeAnnotation{ 
    public:
        Enable(Gravel::Edge, Gravel::Expression);
        std::ostream& process(std::ostream&);
    // implies that a clocked assignment has an enable signal
      static Gravel::Pointer::EdgeAnnotation Create(Gravel::Edge, Gravel::Expression);
private : 
    
};

class Reset : public Gravel::Annotation::EdgeAnnotation { 
    // implies that a signal has a reset value
public:
      Reset(Gravel::Edge);
      std::ostream& process(std::ostream&);
      static Gravel::Pointer::EdgeAnnotation Create(Gravel::Edge);
};

};



};

#endif	/* ASSIGNMENTANNOTATION_H */

