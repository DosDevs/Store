#include <iostream>
#include <vector>

#include "logging/logging.h"

#include "shard.h"


using std::string;

class Command
{
    private:
        static string _empty_string;
        string _line;

        std::vector<string> _tokens;

    public:
        Command(string const& line):
            _line(line)
        {
            size_t pos = 0;

            do {
                while (line[pos] == ' ')
                    ++pos;

                auto next_pos = line.find(' ', pos);

                _tokens.push_back(line.substr(pos, next_pos));
                pos = next_pos;
            } while (pos != string::npos);
        }

        string const& operator[](size_t index) const
        {
            return
                ((index < _tokens.size())?
                    _tokens[index]:
                    _empty_string);
        }

        size_t Token_Count() const
        {
            return _tokens.size();
        }
};

string Command::_empty_string;

using Store::Back::Shard;

struct Record: public Marshall::Record {
    int ID;
    string Name;
    string Description;
};

void Insert(Command const& command, Shard<Record>& shard);
void Write(Command const& command, Shard<Record>& shard);
void List(Command const& command, Shard<Record>& shard);

int main(int argc, char* argv[], char* env[])
{
    if (argc < 2)
    {
        ERROR << "No arguments were provied.";
        return -1;
    }

    if (argc != 2)
    {
        ERROR << "Usage: " << argv[0] << " <filename>";
        return -2;
    }

    Shard<Record> shard(argv[1]);
    
    for(;;) {
        std::cout << "OK ";
        std::cout.flush();

        string line;
        std::getline(std::cin, line);

        Command command = line;

        if (command[0] == "insert")
            Insert(command, shard);
        else
        if (command[0] == "write")
            Write(command, shard);
        else
        if (command[0] == "list")
            List(command, shard);
        else
        if (command[0] == "exit")
            break;
    }

    INFO << "Exiting.";

    return 0;
}

void Command_Usage_Error(string const& command, string const& args = "")
{
    ERROR << "Usage: " << command << args;
}

void Insert(Command const& command, Shard<Record>& shard)
{
    if (command.Token_Count() != 3)
        return Command_Usage_Error(command[0], " <key> <value>");

    uint64_t key = lexical_cast<uint64_t>(command[1]);
    INFO << "Inserting key: " << lexical_cast<string>(key);

    Record old_record;
    string old_value;

    uint64_t push_over_key;
    string push_over_value;

    try {
        shard.Insert(
            key,
            Record::Parse(command[2]),
            old_record,
            push_over_key,
            push_over_value);
    } catch (...) {
        INFO << "There has been an error parsing the record: " << command[2];
    }

    try {
        old_record.As_String(old_value);
    } catch (...) {
        INFO << "There has been an error converting record to string.";
    }

    if (!old_value.empty())
        INFO << "Replaced old value: " << old_value;

    if (!push_over_value.empty())
        INFO << "Push-over entry with key " << lexical_cast<string>(push_over_key) << " needs a new home.";
}

void Write(Command const& command, Shard<Record>& shard)
{
    if (command.Token_Count() != 1)
        return Command_Usage_Error(command[0]);

    INFO << "Writing " << lexical_cast<string>(shard.Record_Count()) << " records to " << shard.File_Name() << ".";

    shard.Write();
}

void List(Command const& command, Shard<Record>& shard)
{
    if (command.Token_Count() != 1)
        return Command_Usage_Error(command[0]);

    INFO << "The shard contains " << lexical_cast<string>(shard.Record_Count()) << " records.";

    for (auto pair: shard)
    {
        INFO << "\tKey: " << lexical_cast<string>(pair.first);
    }
}

