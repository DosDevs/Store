#include "shard.h"

#include <fstream>
#include <string>
#include <utility>

#include "logging/lexical_cast.h"


using std::string;


Shard::Shard(std::string const& filename):
    _filename(filename)
{}

void
Shard::Read()
{
    if (!_cache.empty())
        _cache.clear();

    std::ifstream stream(_filename);

    if (!stream)
        return;

    while(stream)
    {
        string index;
        std::getline(stream, index);
        std::getline(stream, _cache[lexical_cast<uint64_t>(index)]);
    }
}

void
Shard::Insert(
        uint64_t index,
        string const& row,
        string& old_record,
        uint64_t push_over_index,
        std::string& push_over_value)
{
    if (_cache.empty())
        Read();

    auto old_iter = _cache.insert(make_pair(index, row));

    if (!old_iter.second)
        old_record = old_iter.first->second;

    if (Record_Count() > MAX_SIZE)
    {
        auto const& last = *(_cache.rbegin());
        push_over_index = last.first;
        push_over_value = last.second;
        _cache.erase(last.first);
    }
}

void
Shard::Write()
{
    std::ofstream stream(_filename);

    if (!stream)
        return;

    for (auto pair: _cache)
    {
        stream << pair.first << '\n' << pair.second << '\n';
    }

    stream.close();
}

