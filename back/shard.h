#include <cstdint>
#include <map>
#include <string>


class Shard
{
    public:
        typedef std::map<uint64_t, std::string> MapType;

    private:
        static constexpr int MAX_SIZE = 64 << 10;

        std::string _filename;
        MapType _cache;

    public:
        Shard(std::string const& filename);

        void
        Read();

        void
        Insert(
            uint64_t index,
            std::string const& row,
            std::string& old_record,
            uint64_t push_over_index,
            std::string& push_over_value);

        void
        Write();

        std::string const&
        File_Name() const
        {
            return _filename;
        }

        size_t
        Record_Count() const
        {
            return _cache.size();
        }

        MapType::const_iterator
        begin() const
        {
            return _cache.begin();
        }

        MapType::const_iterator
        end() const
        {
            return _cache.end();
        }
};

