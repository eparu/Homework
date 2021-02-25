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
    phonebook.insert({ "A", 3329 });
    phonebook.insert({ "B", 8909 });
    phonebook.insert({ "B", 7909 });


    auto & tipografie = phonebook.get < 0 > ();
    auto & agency = phonebook.get < 1 > ();
    auto & customer = phonebook.get < 2 > ();



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


    std::cout << "Find phone numbers B:\n";
    auto iterator = customer.equal_range("B");
    for (auto i = iterator.first; i != iterator.second; i++)
    {
        std::cout << "  " << i->name << " " << i->phone << std::endl;
    }


    std::cout << "Delete B 7909:\n";
    auto iterator_to_delete = customer.equal_range("B");
    for (auto i = iterator_to_delete.first; i != iterator_to_delete.second; i++)
    {
        if (i->phone == 7909)
        {
            customer.erase(i);
            break;
        }
    }
    for (const auto & i : tipografie)
    {

        std::cout << "  " << i.name << ' ' << i.phone << std::endl;
    }


    std::cout << "Delete all B\n";
    auto iterator_to_delete_all = customer.equal_range("B");
    customer.erase(iterator_to_delete_all.first, iterator_to_delete_all.second);
    for (const auto & i : tipografie)
    {

        std::cout << "  " << i.name << ' ' << i.phone << std::endl;
    }
    return 0;
}
