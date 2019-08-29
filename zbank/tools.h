#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>

#define pf printf
#define sf scanf
#define ID_PATH "./account/id.dat"
#define ACC_PATH "./account"

// 初始化id
void init_id(size_t id);
// 获取id
size_t get_id(void);
char get_cmd(char stat,char end);
char* get_str(char* str,size_t size);

#endif//TOOLS_H
