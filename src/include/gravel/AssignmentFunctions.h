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
#include <gravel/Assignment.h>
namespace Gravel {
  void Reset( Gravel::Symbol, Gravel::Expression);
  void Delay( Gravel::Assignment, Gravel::Expression);
};
#endif	/* ASSIGNMENTFUNCTIONS_H */

