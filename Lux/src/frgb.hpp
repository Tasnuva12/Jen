// Floating point color using vectors from linalg.h
// Uses look up table to convert to and from integer RGB colors

#ifndef __FRGB_HPP
#define __FRGB_HPP

#include <iostream>
//#include <array>
//#include <algorithm>
#include "linalg.h"

#ifndef R
    #define R x 
#endif // R
#ifndef G
    #define G y
#endif // G
#ifndef B
    #define B z
#endif // B

typedef linalg::vec< float,3 > frgb;

float rf( const frgb &c );
float gf( const frgb &c );
float bf( const frgb &c );

// returns single bytes per component - assumes [0.0, 1.0] range
// clip or constrain out of range values before using
unsigned char rc( const frgb &c );
unsigned char gc( const frgb &c );
unsigned char bc( const frgb &c );

// inline unsigned int ul( const frgb &c ) {} // bit shifty stuff

// set component
void setrf( frgb &c, const float& r );
void setgf( frgb &c, const float& g );
void setbf( frgb &c, const float& b );
void setf(  frgb &c, const float& r, const float& g, const float& b );
frgb setf(  const float& r, const float& g, const float& b );
// TODO - set from bracketed list

void setrc( frgb &c, const unsigned char& r );
void setgc( frgb &c, const unsigned char& g );
void setbc( frgb &c, const unsigned char& b );
void setc(  frgb &c, const unsigned char& r, const unsigned char& g, const unsigned char& b );
frgb setc(           const unsigned char& r, const unsigned char& g, const unsigned char& b );

// I/O operators
//std::ostream &operator << ( std::ostream &out, const frgb& f );
void print_SRGB( const frgb &c );

// to clamp values use linalg::clamp()
void constrain( frgb &c );  // Clip to range [ 0.0, 1.0 ] but keep colors in proportion
//frgb& constrain( const frgb &c );   

void apply_mask( frgb& result, const frgb& layer, const frgb& mask );
// frgb apply_mask( const frgb &base, const frgb &mask, frgb &result );

inline float luminance( const frgb &c );  // Returns approximate visual brightness of color
frgb gray( const frgb &c );        // Grays out the color

// Future: HSV and other color spaces

#endif // __FRGB_HPP