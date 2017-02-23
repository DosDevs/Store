#ifndef SHARD_H__INCLUDED
#define SHARD_H__INCLUDED

#include "base-shard.h"

namespace Store
{
    namespace Back
    {
        using std::string;

        template<typename T>
        struct Shard: protected Base_Shard, public I_Shard<T> {
            class Transforming_Iterator {
                private:
                    typedef Base_Shard::Map_Type Base_Map_Type;

                    Base_Map_Type::const_iterator _base_iterator;

                public:
                    Transforming_Iterator(
                            Base_Map_Type const& map):
                        _base_iterator(map.begin())
                    {}

                    Transforming_Iterator(
                            Base_Map_Type::const_iterator const& base_iterator):
                        _base_iterator(base_iterator)
                    {}

                    Transforming_Iterator(
                            Transforming_Iterator const& that):
                        Transforming_Iterator(that._base_iterator)
                    {}

                    T operator*() const
                    {
                        return T::Parse(*_base_iterator);
                    }

                    //
                    // TODO: Fix the increment operators.
                    //

                    Transforming_Iterator operator++(int)
                    {
                        _base_iterator++;
                        return *this;
                    }

                    Transforming_Iterator operator++()
                    {
                        _base_iterator++;
                        return *this;
                    }

                    bool operator==(Transforming_Iterator const& that) const
                    { return (_base_iterator == that._base_iterator); }

                    bool operator!=(Transforming_Iterator const& that) const
                    { return (_base_iterator != that._base_iterator); }
            };

            Shard(string const& filename):
                Base_Shard(filename),
                I_Shard<T>()
            {}

            virtual void Read()     { Base_Shard::Read(); }
            virtual void Write()    { Base_Shard::Write(); }

            virtual string const& File_Name() const
            { return Base_Shard::File_Name(); }

            virtual size_t Record_Count() const
            { return Base_Shard::Record_Count(); }

            Transforming_Iterator
            begin() const
            { return Transforming_Iterator(Base_Shard::begin()); }

            Transforming_Iterator
            end() const
            { return Base_Shard::end(); }

            virtual
            void
            Insert(
                uint64_t index,
                T const& row,
                T& old_record,
                uint64_t& push_over_index,
                T& push_over_value)
            {
                string new_str;
                row.Serialize(new_str);

                string old_str;
                string push_over_str;

                Base_Shard::Insert(
                        index,
                        new_str,
                        old_str,
                        push_over_index,
                        push_over_str);

                if (!old_str.empty())
                    old_record.Parse(old_str);

                if (!push_over_str.empty())
                    old_record.Parse(push_over_str);
            }

            virtual
            bool
            Retrieve(
                uint64_t index,
                T& row) const
            {
                string temp;

                if (!Retrieve(index, temp))
                    return false;

                row.Parse(temp);
                return true;
            }
        };
    }  // namespace Back
} // namespace Store

#endif  // SHARD_H__INCLUDED

