#include "scene.hpp"
#include "json.hpp"
#include "next_element.hpp"
#include "any_function.hpp"
#include "life.hpp"

struct scene_reader {
    using json = nlohmann::json;

    scene& s;

    scene_reader( scene& s_init, std::string( filename ) );

    void add_default_conditions();

    void read( bool& b,   const json& j ) { b  = j.get<bool>();   }
    void read( int& i,    const json& j ) { i  = j.get<int>();    }
    void read( float& f,  const json& j ) { f  = j.get<float>();  }
    void read( vec2f& v,  const json& j ) { v  = read_vec2f( j ); }
    void read( vec2i& v,  const json& j ) { v  = read_vec2i( j ); }
    void read( bb2f& bb,  const json& j ) { bb = read_bb2f( j );  }
    void read( bb2i& bb,  const json& j ) { bb = read_bb2i( j );  }
    void read( frgb& f,   const json& j ) { f  = read_frgb( j );  }
    void read( ucolor& u, const json& j ) { u  = read_ucolor( j );}
    void read( std::string& s,  const json& j ) { s = read_string( j ); }
    void read( direction4& d,   const json& j ) { d = read_direction4( j ); }
    void read( pixel_type& p,   const json& j ) { p = read_pixel_type( j ); }
    void read( image_extend& e, const json& j ) { e = read_image_extend( j ); }
    void read( std::optional< int   >& i, const json& j ) { i = j.get<int>();  }    
    void read( std::optional< float >& f, const json& j ) { f = j.get<float>();  }  
    void read( std::vector< vec2f >& v,   const json& j ) { for( auto& k : j ) { v.push_back( read_vec2f( k ) ); } }

    vec2f  read_vec2f(  const json& j );
    vec2i  read_vec2i(  const json& j );
    frgb   read_frgb(   const json& j );
    bb2f   read_bb2f(   const json& j );
    bb2i   read_bb2i(   const json& j );
    ucolor read_ucolor( const json& j );
    std::string  read_string(       const json& j );
    direction4   read_direction4(   const json& j );
    pixel_type   read_pixel_type(   const json& j );
    image_extend read_image_extend( const json& j );

    void read_image(    const json& j );
    void read_rule(     const json& j );   // Cellular automata rule
    void read_effect(   const json& j );
    void read_element(  const json& j );
    void read_function( const json& j );
    void read_cluster(  const json& j );
    void read_eff_list( const json& j, effect_list& elist );

    template< class T > void read_harness( const json& j, harness< T >& h, std::unordered_map< std::string, any_fn< T > >& harness_fns );
    #define READ_ANY_HARNESS( _T_, _U_ ) void read_any_harness( const json& j, harness< _T_ >& h )  { read_harness< _T_ >( j, h, _U_ ); }
    READ_ANY_HARNESS( float,  s.float_fns )
    READ_ANY_HARNESS( int,    s.int_fns )
    READ_ANY_HARNESS( vec2f,  s.vec2f_fns )
    READ_ANY_HARNESS( vec2i,  s.vec2i_fns )
    READ_ANY_HARNESS( bb2f,   s.bb2f_fns )
    READ_ANY_HARNESS( bb2i,   s.bb2i_fns )
    READ_ANY_HARNESS( frgb,   s.frgb_fns )
    READ_ANY_HARNESS( ucolor, s.ucolor_fns )

    //READ_ANY_HARNESS( std::optional< int > )
    //READ_ANY_HARNESS( std::optional< float > )
    //READ_ANY_HARNESS( std::vector< vec2f > )
};