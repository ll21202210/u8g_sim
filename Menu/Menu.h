#ifndef _MENU_H_
#define _MENU_H_

#include "stdio.h"
#include "u8g2.h"

//  帧率设置
#define MENU_FRATE  50



typedef unsigned char  uint8_t;
typedef void(*Menu_func_t)();

typedef struct 
{
    uint8_t Menu_id;
    uint8_t Menu_Type; // 0 列表模式 1 图标横向  2 执行函数绘制界面
    uint8_t Menu_Listid;
    uint8_t Click_Action;   // 0 无 1 跳转菜单 2 执行函数 
    uint8_t Preview_Menuid;
    uint8_t *ItemName;
    Menu_func_t Menu_Func;
    uint8_t addp1;      // 跳转的菜单id
}Menu_t;

typedef struct
{
    uint8_t Current_Menuid;
    uint8_t Last_Menuid;
    uint8_t List_Firstpos;
    uint8_t List_Select;
    uint8_t List_Count;
    uint8_t List_Offset;
}Menu_Sta_t;

typedef struct {
    float pos;
    uint8_t current;
    uint8_t last;
    float speed;
    uint8_t adden;
}Menu_Animation_t;


void Menu_Init(void);
void Menu_Draw(u8g2_t *u8g2);

void Menu_NextOption();
void Menu_LastOption();
void Menu_RunList();
void Menu_PrewPage();


#endif /** _MENU_H_ */
