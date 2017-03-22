#include "serialize.hpp"
#include <iostream>
namespace bg = boost::geometry;
int main()
{
    std::string filename = "newdoc.txt";
    typedef bg::model::point<double, 2, bg::cs::cartesian> pnt;
    typedef bg::model::segment<pnt> segment_t;
    typedef bg::model::d2::point_xy<double,bg::cs::cartesian> d2pnt;
    
    d2pnt a(1,2),b;
    //Store 2d point
    {
        std::ofstream ofs(filename);
        boost::archive::text_oarchive oa(ofs);
        oa & a;
    }
    //Load 2d point
    {
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia & b;
    }
    std::cout<<a.x()<<" "<<a.y()<<std::endl;
    std::cout<<b.x()<<" "<<b.y()<<std::endl;
    //Store a segment of <bg::point,bg::point>
    segment_t seg1;
    segment_t seg2(pnt(12.4, 1.1), pnt(5.1, 5.3));
    {
        std::ofstream ofs(filename);
        boost::archive::text_oarchive oa(ofs);
        oa << seg2;
    }
    
    //Load a segment of <bg::point,bg::point>
    {
        // Create and input archive
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia >> seg1;
    }
    double x0 = bg::get<0, 0>(seg1);
    double y0 = bg::get<0, 1>(seg1);
    double x1 = bg::get<1, 0>(seg1);
    double y1 = bg::get<1, 1>(seg1);
    std::cout << x0 << ", " << y0 << ", " << x1 << ", " << y1 << std::endl;
    
    
    
    return 0;
}
