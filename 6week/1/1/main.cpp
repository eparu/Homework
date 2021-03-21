#include <iostream>
#include <fstream>
#include <iterator>

enum class CONDITION
{
    prev_slash, /*  / */
    prev_backslash, /* \ */
    in_comment,
    read,
    ignore,
    in_string,
    wait_slash
};


int main(int argc, const char * argv[]) {
    std::fstream fin("test.txt", std::ios::in);
    std::ofstream fout("test_without_comment.txt");
    if (!fin.is_open())
    {
        fout << "File was not found\n";
        return 0;
    }
    std::string text{
                     std::istreambuf_iterator< char > (fin),
        std::istreambuf_iterator< char > ()};

    CONDITION cond = CONDITION::read;

    for (auto i : text)
    {
        switch (cond) {
            case CONDITION::read:
                if (i == '/')
                {
                    cond = CONDITION::prev_slash;
                }
                else if (i == '\\')
                {
                    cond = CONDITION::prev_backslash;
                }
                else if (i == '"')
                {
                    fout << i;
                    cond = CONDITION::in_string;
                }
                else
                {
                    fout  << i;
                }
                break;
            case CONDITION::prev_slash:
                if (i == '/')
                {
                    cond = CONDITION::ignore;
                }
                else if (i == '*')
                {
                    cond = CONDITION::in_comment;
                }
                else
                {
                    cond = CONDITION::read;
                    fout << i;
                }
                break;
            case CONDITION::in_comment:
                if ( i == '*' )
                {
                    cond = CONDITION::wait_slash;
                }
                break;
            case CONDITION::wait_slash:
                if (i == '/')
                {
                    cond = CONDITION::read;
                }
                else
                {
                    cond = CONDITION::in_comment;
                }
                break;
            case CONDITION::in_string:
                if (i == '\\')
                {
                    cond = CONDITION::prev_backslash;
                }
                if (i == '"')
                {
                    cond = CONDITION::read;
                }
                fout << i;
                break;
            case CONDITION::prev_backslash:
                cond = CONDITION::in_string;
                fout << i;
                break;
            case CONDITION::ignore:
                if (i == '\n')
                {
                    fout << i;
                    cond = CONDITION::read;
                }
            default:
                break;
        }
    }

    fout.close();
    return 0;
}

