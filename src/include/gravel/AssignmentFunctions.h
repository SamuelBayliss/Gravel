/* 
 * File:   AssignmentFunctions.h
 * Author: sb1708
 *
 * Created on June 13, 2013, 1:20 PM
 */

#ifndef ASSIGNMENTFUNCTIONS_H
#define	ASSIGNMENTFUNCTIONS_H

#include <gravel/Symbol.h>
#include <gravel/Expression.h>
#include <gravel/Annotation.h>

namespace Gravel {
  Gravel::Pointer::EdgeAnnotation Reset( Gravel::Symbol, Gravel::Expression);
 Gravel::Pointer::EdgeAnnotation Delay( Gravel::Edge);
 Gravel::Pointer::EdgeAnnotation Assign (Gravel::Edge );
};
#endif	/* ASSIGNMENTFUNCTIONS_H */

