#ifndef BASE_SHARD_H__INCLUDED
#define BASE_SHARD_H__INCLUDED

#include "i-shard.h"

#include <cstdint>
#include <map>
#include <string>


namespace Store
{
    namespace Back
    {
        using std::string;

        class Base_Shard: public I_Shard<string>
        {
            public:
                typedef std::map<uint64_t, string> Map_Type;

            private:
                static constexpr int MAX_SIZE = 64 << 10;

                string _filename;
                Map_Type _cache;

            protected:
                virtual
                void
                Insert(
                    uint64_t index,
                    string const& row,
                    string& old_record,
                    uint64_t& push_over_index,
                    string& push_over_value);

                virtual
                bool
                Retrieve(
                    uint64_t index,
                    string& row) const;

            public:
                Base_Shard(string const& filename);

                virtual
                void
                Read();

                virtual
                void
                Write();

                virtual
                string const&
                File_Name() const
                {
                    return _filename;
                }

                virtual
                size_t
                Record_Count() const
                {
                    return _cache.size();
                }

                Map_Type::const_iterator
                begin() const
                {
                    return _cache.begin();
                }

                Map_Type::const_iterator
                end() const
                {
                    return _cache.end();
                }
        };
    }  // namespace Back
} // namespace Store

#endif  // BASE_SHARD_H__INCLUDED

