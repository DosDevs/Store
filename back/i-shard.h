#ifndef I_SHARD_H__INCLUDED
#define I_SHARD_H__INCLUDED

#include <cstdint>
#include <map>
#include <string>


namespace Store
{
    namespace Back
    {
        using std::string;

        template<typename T>
        struct I_Shard
        {
            virtual ~I_Shard() {}

            virtual void Read() = 0;
            virtual void Write() = 0;

            virtual
            void
            Insert(
                uint64_t index,
                T const& row,
                T& old_record,
                uint64_t& push_over_index,
                T& push_over_value) = 0;

            virtual
            bool
            Retrieve(
                uint64_t index,
                T& row) const = 0;

            virtual
            string const&
            File_Name() const = 0;

            virtual
            size_t
            Record_Count() const = 0;
        };
    }  // namespace Back
} // namespace Store

#endif  // I_SHARD_H__INCLUDED


