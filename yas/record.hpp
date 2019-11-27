
#ifndef __YAS_RECORD_HPP_INCLUDED__
#define __YAS_RECORD_HPP_INCLUDED__

#include <vector>
#include <string>

#include <stdint.h>

#include <yas/mem_streams.hpp>
#include <yas/binary_iarchive.hpp>
#include <yas/binary_oarchive.hpp>
#include <yas/std_types.hpp>

namespace yas_test {

typedef std::vector<int64_t>     Integers;
typedef std::vector<std::string> Strings;

struct Record {

    Integers ids;
    Strings  strings;

    bool operator==(const Record &other) {
        return (ids == other.ids && strings == other.strings);
    }

    bool operator!=(const Record &other) {
        return !(*this == other);
    }

    template<typename Archive>
    void serialize(Archive &ar)
    {
        ar & ids & strings;
    }
};

template<std::size_t opts>
void to_string(const Record &record, std::string &data) {
    yas::mem_ostream os;
    yas::binary_oarchive<yas::mem_ostream, opts> oa(os);
    oa & record;
    
    auto buf = os.get_intrusive_buffer();
    data.assign(buf.data, buf.size);
}

template<std::size_t opts>
void from_string(Record &record, const std::string &data) {
    yas::mem_istream is(data.c_str(), data.size());
    yas::binary_iarchive<yas::mem_istream, opts> ia(is);
    ia & record;
}

} // namespace

#endif
