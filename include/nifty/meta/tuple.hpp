#pragma once

#include <tuple>
#include <type_traits>

namespace nifty{
namespace meta{

   template<std::size_t VAL>
   using SizeT = std::integral_constant<std::size_t, VAL>;

    


    template <class T, class Tuple>
    struct TupleTypeIndex;

    template <class T, class... Types>
    struct TupleTypeIndex<T, std::tuple<T, Types...>> 
    :  SizeT<0>
    { 

    };

    template <class T, class U, class... Types>
    struct TupleTypeIndex<T, std::tuple<U, Types...>> 
    : SizeT<1 +  TupleTypeIndex<T, std::tuple<Types...>>::value>
    {

    };


    template<class TUPLE, template<typename ...> typename C>
    struct TransformTuple;

    template<class ... TUPLE_ARGS , template< typename ...  ARGS> class C>
    struct TransformTuple<std::tuple<TUPLE_ARGS ...>, C >{
        typedef std::tuple< C<TUPLE_ARGS> ...> type;
    };



}
}