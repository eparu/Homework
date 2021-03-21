#include <iostream>
#include <fstream>

enum class CONDITION
{
    prev_slash, /*  / */
    prev_backslash, /* \ */
    in_comment,
    read,
    in_string,
    wait_slash
};


int main(int argc, const char * argv[]) {
    std::ifstream fin("test.txt");
    std::ofstream fout("test_without_comment.txt");
    if (!fin.is_open())
    {
        fout << "File was not found\n";
        return 0;
    }
    std::string str;

    CONDITION cond = CONDITION::read;
    while(getline(fin, str))
    {
        for (auto i : str)
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
                        goto next_string;
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
                default:
                    break;
            }
        }
    next_string:
        fout << std::endl;
    }
    fout.close();
    return 0;
}

