#include "serialize.hpp"
#include <iostream>
namespace bg = boost::geometry;
int main()
{
    std::string filename = "newdoc.txt";
    typedef bg::model::point<double, 3, bg::cs::cartesian> pnt;
    typedef bg::model::segment<pnt> segment_t;
    typedef bg::model::box<pnt> mybox;
    typedef bg::model::d2::point_xy<double,bg::cs::cartesian> d2pnt;
    d2pnt a(1,2),b,c(5,8);
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
    
    pnt a1(8,9,10),a2;
    
    //Store n dimensional point
    {
        std::ofstream ofs(filename);
        boost::archive::text_oarchive oa(ofs);
        oa & a1
    }
    //Load n dimesional point
    {
        std::ifstream ifs(filename);
        boost::archive::text_iarchive ia(ifs);
        ia & a2;
    }
    return 0;
}
