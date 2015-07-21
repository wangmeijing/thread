#include <iostream>
#include <thread>]

#include "user_command.h"

using namespace std;

//“新建”这一操作
void open_document_and_display_gui(const std::string& filename)
{
    cout <<" open file: " <<filename <<endl;
}

//是否完成编辑
bool done_eaditing()
{
    cout <<"done editing.........." <<endl;
    return true;
}


//获取用户命令，这里就是获取"新建“
user_command get_user_input()
{
    cout <<" get user input........." <<endl;
    return user_command();
}


std::string get_filename_from_user(){
    return "foo.doc";
}

//处理用户的普通输入，即文档编写
void process_user_input(const user_command& cmd)
{
    cout <<" process user input........." <<endl;
}

//假设初始时文档A执行edit_document，发现用户有”新建“命令到达，
//则开启一个线程去供文档B使用，且立即detach这个线程
void edit_document(const std::string& filename)
{
    open_document_and_display_gui(filename);

    /*bool isFinish =*/ done_eaditing();

//    while(isFinish)
//    {
        user_command cmd=get_user_input();

        cout <<cmd.type <<endl;
        if(cmd.type==0){
            const std::string new_name=get_filename_from_user();
            cout << "new open file: " << new_name<<endl;

            thread t(edit_document,new_name);
            t.detach();//立即执行detach，这里可以肯定thread t和线程相关，故不需要检测joina
        }
        else
            process_user_input(cmd);//普通文档编辑
//    }

}
int main(){
    edit_document("bar.doc");
    return 0;
}
