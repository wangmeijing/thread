#include "user_command.h"

user_command::user_command()
{
    type = open_new_document;
    std::cout << " user command" << type << std::endl;
}

user_command::~user_command()
{

}

