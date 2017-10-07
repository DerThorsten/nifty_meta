#pragma once

#include <tuple>
#include <type_traits>

namespace nifty{
namespace meta{

   template<std::size_t VAL>
   using SizeT = std::integral_constant<std::size_t, VAL>;

   template<uint64_t VAL>
   using UInt64T = std::integral_constant<uint64_t, VAL>;

   template<uint32_t VAL>
   using UInt32T = std::integral_constant<uint32_t, VAL>;

   template<uint16_t VAL>
   using UInt16T = std::integral_constant<uint16_t, VAL>;

   template<uint8_t VAL>
   using UInt8T = std::integral_constant<uint8_t, VAL>;

   template<int64_t VAL>
   using Int64T = std::integral_constant<int64_t, VAL>;

   template<int32_t VAL>
   using Int32T = std::integral_constant<int32_t, VAL>;

   template<int16_t VAL>
   using Int16T = std::integral_constant<int16_t, VAL>;

   template<int8_t VAL>
   using Int8T = std::integral_constant<int8_t, VAL>;

   template<bool VAL>
   using Bool = std::integral_constant<bool, VAL>;



}
}