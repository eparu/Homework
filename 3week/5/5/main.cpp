#include <iostream>
#include <string>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost::multi_index;

struct Person
{
    std::string name;
    unsigned int phone;
};

using persons_multi_index = multi_index_container < Person, indexed_by<
    ordered_non_unique < member < Person, std::string, &Person::name > >,
    random_access <>,
    hashed_non_unique < member < Person, std::string, &Person::name > >
>>;

int main(int argc, char ** argv)
{
    persons_multi_index phonebook;

    phonebook.insert({ "A",    1234 });
    phonebook.insert({ "B",    6789 });
    phonebook.insert({ "C",  101112 });


    auto & tipografie = phonebook.get < 0 > ();
    auto & agency = phonebook.get < 1 > ();
    auto & customer = phonebook.get < 2 > ();

    phonebook.insert({ "A", 3329 });
    phonebook.insert({ "B", 8909 });
    phonebook.insert({ "B", 7909 });



    std::cout << "Tipografie:\n";
    for (const auto & i : tipografie)
    {

        std::cout << "  " << i.name << ' ' << i.phone << std::endl;
    }

    std::cout << "\nAdvert agency:\n";
    for (const auto & i : agency)
    {

        std::cout << "  " << i.name << ' ' << i.phone << std::endl;
    }

    auto begin = customer.lower_bound("A");
    auto end   = customer.upper_bound("A");

    return 0;
}
