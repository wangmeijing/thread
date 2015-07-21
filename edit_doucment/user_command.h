#ifndef USER_COMMAND_H
#define USER_COMMAND_H
#include <iostream>

enum command_type{open_new_document};//用户命令，这里只有一个就是“新建”

class user_command
{
public:
    user_command();
    ~user_command();

    command_type type;
};

#endif // USER_COMMAND_H
