/* 
 * File:   Streams.h
 * Author: sb1708
 *
 * Created on May 6, 2013, 11:41 PM
 */

#ifndef STREAMS_H
#define	STREAMS_H

#include <streambuf>
#include <functional>
#include <cassert>
#include <ostream>
#include <cctype>
#include <vector>
/*
 
 * streambuf::pbase() is base
 * streambuf::pptr() is current position
 * streambuf::epptr() is one past final element of array
 
 * 
 * overflow is called whenever the put pointer is equal to the end put pointer
 * 
 * sync writes the buffered data to the target
 */

//template <class charT, class Traits = char_traits<charT> >
//class FormattedStream : public std::basic_ostream<charT, Traits> {


#endif	/* STREAMS_H */

