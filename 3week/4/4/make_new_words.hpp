#ifndef make_new_words_h
#define make_new_words_h

std::set < std::string > make_random_words(std::size_t N, std::size_t length = 10)
{
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast < std::size_t > (std::chrono::system_clock::now().time_since_epoch().count()));

    std::set < std::string > words;

    for (std::string s(length, '_'); words.size() < N; words.insert(s))
    {
        for (auto & c : s)
            c = letter(e);
    }
    return words;
}


#endif /* make_new_words_h */
