#include <iostream>
#include <string>

using StringPair = std::pair<std::string, std::string>;

static const StringPair TestData[] = {
    {"", ""},
    {"A", "A"},
    {"AA", "A2"},
    {"AAA", "A3"},
    {"ABC", "ABC"},
    {"AAAAAAAAAAAAA", "A13"},
    {"ABBCDDDXYYY", "AB2CD3XY3"},
    {"AABBBCDDXY", "A2B3CD2XY"},
    {"AAAAAAAAAAAABBBCCCCCCCCCCCCCCCCCDDXY", "A12B3C17D2XY"},
};

void EncodeCharRepetitionsInPlace(std::string & str) {
    if (str.empty())
        return;

    size_t shift = 0;
    size_t cur_count = 1;
    char cur_c = str[0];

    for (size_t i = 1; i < str.size(); ++i) {
        if (str[i] != cur_c) {
            if (cur_count != 1) {
                shift += cur_count - 1;

                std::string num_str = std::to_string(cur_count);
                num_str.copy(&str[i - shift], num_str.size());

                shift -= num_str.size();
                cur_count = 1;
            }
            str[i - shift] = str[i];
            cur_c = str[i];

        } else {
            ++cur_count;
        }
    }

    if (cur_count != 1) {
        shift += cur_count - 1;

        std::string num_str = std::to_string(cur_count);
        num_str.copy(&str[str.size() - shift], num_str.size());

        shift -= num_str.size();
    }
    str.resize(str.size() - shift);
}

int main()
{
    for (auto sp : TestData) {
        std::string orig = sp.first;
        std::string expected = sp.second;
        auto orig_copy(orig);

        EncodeCharRepetitionsInPlace(orig);
        if (orig != expected) {
            std::cerr << "EncodeCharRepetitionTest failed: string '" << orig_copy << "' was encoded to '" << orig << "', but expected '" << expected << "'" << std::endl;
            return 1;
        }
    }
    std::cout << "EncodeCharRepetitionTest successful!" << std::endl;
    return 0;
}
