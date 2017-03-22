#include <iosfwd>
#include <fstream>
#include <boost/geometry.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
using namespace boost::archive;
namespace bg = boost::geometry;
//Generalised template to iterate over all dimensions
//Serialize components of model::segment and model::point
template <class P, size_t curlen = 0, size_t len= bg::dimension<P>::value>
struct helper
{
    template <typename Archive>
    static inline void save(Archive & ar, P const& p, unsigned int fileversion)
    {
        typename bg::coordinate_type<P>::type val;
        val = bg::get<curlen>(p);
        ar << val;
        helper<P,curlen+1,len>::save(ar, p, fileversion);
    }
    
    template <typename Archive>
    static inline void load(Archive & ar, P & p, unsigned int fileversion)
    {
        typename bg::coordinate_type<P>::type val;
        ar >> val;
        bg::set<curlen>(p, val);
        helper<P,curlen+1,len>::load(ar, p, fileversion);
    }
};
//Template specialisation to end the recursion
template <class P,size_t len>
struct helper<P,len,len>{
    template <typename Archive>
    static inline void save(Archive & ar, P const& p, unsigned int fileversion){}
    
    template <typename Archive>
    static inline void load(Archive & ar, P & p, unsigned int fileversion){}
};

namespace boost{
    namespace serialization{
        
        template<typename Archive,typename T, typename C>
        void serialize(Archive & ar,bg::model::d2::point_xy<T,C> & d2pnt, unsigned int fileversion){
            ar &  const_cast<T&> (d2pnt.x());
            ar &  const_cast<T&> (d2pnt.y());
        }
        
        template<typename Archive, typename T,size_t DIM, typename C>
        void save(Archive & ar, bg::model::segment<bg::model::point<T,DIM,C>> const& p, unsigned int fileversion)
        {
            helper< bg::model::point<T,DIM,C> >::save(ar, p.first, fileversion);//save first point
            helper< bg::model::point<T,DIM,C> >::save(ar, p.second, fileversion);//save second point
        }
        
        template<typename Archive, typename T,size_t DIM, typename C>
        void load(Archive & ar, bg::model::segment<bg::model::point<T,DIM,C>> & p, unsigned int fileversion)
        {
            helper< bg::model::point<T,DIM,C> >::load(ar, p.first, fileversion);//load first element of pair
            helper< bg::model::point<T,DIM,C> >::load(ar, p.second, fileversion);//load second element
        }

        template<typename Archive, typename T, size_t DIM, typename C>
        void save(Archive & ar, bg::model::point<T,DIM,C> const& point, unsigned int fileversion)
        {
            helper< bg::model::point<T,DIM,C> >::save(ar, point, fileversion);
        }
        
        template<typename Archive, typename T, size_t DIM, typename C>
        void load(Archive & ar, bg::model::point<T,DIM,C> & point, unsigned int fileversion)
        {
            helper< bg::model::point<T,DIM,C> >::load(ar, point, fileversion);
        }
        
        template<typename Archive, typename T,size_t DIM, typename C>
        void serialize(Archive & ar,bg::model::box<bg::model::point<T,DIM,C>> & bx, unsigned int fileversion)
        {
            ar & bx.max_corner();
            ar & bx.min_corner();
        }
        
        template<typename Archive, typename T, size_t DIM, typename C>
        void serialize(Archive & ar, bg::model::point<T,DIM,C> & pnt, unsigned int fileversion)
        {
            split_free(ar,pnt,fileversion);
        }
        
        template<typename Archive, typename T>
        void serialize(Archive & ar, bg::model::segment<T> & seg, unsigned int fileversion)
        {
            split_free(ar,seg,fileversion);
        }
        
    }
}
