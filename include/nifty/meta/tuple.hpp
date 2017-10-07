#pragma once

#include <utility>
#include <tuple>
#include <type_traits>

#include "nifty/meta/integral_constant.hpp"

namespace nifty{
namespace meta{

    // find the position of a type in a tuple
    template <class T, class Tuple>
    struct TupleTypeIndex;

    template <class T, class... Types>
    struct TupleTypeIndex<T, std::tuple<T, Types...>> 
    :  SizeT<0>{ 
    };

    template <class T, class U, class... Types>
    struct TupleTypeIndex<T, std::tuple<U, Types...>> 
    : SizeT<1 +  TupleTypeIndex<T, std::tuple<Types...>>::value>{
    };




    template<class TUPLE, template<typename ...> typename C>
    struct TransformTuple;

    template<class ... TUPLE_ARGS , template< typename ...  ARGS> class C>
    struct TransformTuple<std::tuple<TUPLE_ARGS ...>, C >{
        typedef std::tuple< C<TUPLE_ARGS> ...> type;
    };

    ///\cond
    namespace detail{
        template<class INDEX_SEQUENCE, template<std::size_t I> typename C>
        struct GenerateTupleImpl;

        template<std::size_t... Ints, template<std::size_t I> typename C>
        struct GenerateTupleImpl<std::index_sequence<Ints ... >, C>{
            typedef std::tuple<C<Ints> ...> type;
        };
    }
    ///\endcond


    template<std::size_t N, template<std::size_t I> typename C>
    struct GenerateTuple :  detail::GenerateTupleImpl<std::make_index_sequence<N>, C>{    
    };



    template<std::size_t N, class T>
    struct GenerateUniformTuple{
        template<std::size_t I>
        using Helper = T;

        typedef GenerateTuple<N, Helper> type;
    };

}
}