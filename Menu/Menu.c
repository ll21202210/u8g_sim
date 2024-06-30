#include "Menu.h"
#include "SDL_timer.h"
#include "stdlib.h"
#include "stdio.h"

#define Menu_GetTIck SDL_GetTicks   // ms



uint8_t Menu_FindList(uint8_t Menuid, uint8_t Listpos);
void Menu_Sta_Init(uint8_t Menu_id);
uint8_t Menu_GetListCount(uint8_t Menu_id);
void Menu_Sta_AnimCalc();
void Menu_Animation_Calc();

void Func();


#define Menu_Count      (sizeof(Menu) / sizeof(Menu[0]))
const Menu_t Menu[] = { 
// id typ lid act pre name func  para1
    {0, 0, 0, 1, 0, "wqy_chinese_14", NULL, 1},
    {0, 0, 1, 2, 0, "opt2", Func, 0},
    {0, 0, 2, 1, 0, "op22t3", NULL, 2},
    {0, 0, 3, 0, 0, "opt14", NULL, 0},
    {0, 0, 4, 0, 0, "opt225", NULL, 0},
    {0, 0, 5, 0, 0, "opt6", NULL, 0},
    {0, 0, 6, 0, 0, "o21pt7", NULL, 0},
    {0, 0, 7, 1, 0, "opt8", NULL, 1},
    {0, 0, 8, 0, 0, "op2t9", NULL, 0},
    {1, 0, 0, 0, 0, "1110", NULL, 0},
    {1, 0, 1, 0, 0, "111", NULL, 0},
    {1, 0, 2, 1, 0, "opt12", NULL, 0},
    {1, 0, 3, 0, 0, "opt13", NULL, 0},
    {2, 0, 0, 0, 0, "op22t20", NULL, 0},
    {2, 0, 1, 0, 0, "opt21", NULL, 0},
    {2, 0, 2, 1, 0, "opt22", NULL, 0},
    

};
Menu_Sta_t Menu_Sta;
/**
    pos current target  speed;
 */
#define Menu_AnimationCount      (sizeof(Menu_Animation) / sizeof(Menu_Animation[0]))
Menu_Animation_t Menu_Animation[2] = {
    {0, 0, 0, 0.3, 1},
    {0, 0, 0, 0.3, 0}

};

void Func()
{
    printf("called func\n");
}
void Menu_Init(void)
{
    Menu_Sta.Current_Menuid = 0;
    Menu_Sta.Last_Menuid = 2;
    // Menu_Sta_Init(Menu_Sta.Current_Menuid);
}
void Menu_Draw(u8g2_t *u8g2)
{
    int8_t i, pos;
    uint8_t offset;
    static uint32_t tick;
    if(Menu_Sta.Current_Menuid != Menu_Sta.Last_Menuid)
    {
        Menu_Sta_Init(Menu_Sta.Current_Menuid);
        Menu_Sta_AnimCalc();
        Menu_Animation[1].last = 4;
        Menu_Animation[1].current = 0;
        Menu_Sta.Last_Menuid = Menu_Sta.Current_Menuid;
    }
    if(Menu_GetTIck() - tick >= (1000 / MENU_FRATE))
    {
        tick = Menu_GetTIck();
        Menu_Animation_Calc();
        pos = Menu_Sta.List_Firstpos;
        offset = Menu_Sta.List_Offset;
        u8g2_ClearBuffer(u8g2);
        u8g2_SetFont(u8g2, u8g2_font_wqy14_t_gb2312);
        u8g2_SetDrawColor(u8g2, 1);
        for(i = -1; i < 5; i++)
        {
            if((pos + i + Menu_Sta.List_Offset) >= Menu_Sta.List_Firstpos && (pos + i + Menu_Sta.List_Offset) <= (Menu_Sta.List_Firstpos + Menu_Sta.List_Count))
            {
                u8g2_DrawUTF8(u8g2, 10,1 + i*16 + 12 + 16 * Menu_Animation[1].pos, Menu[pos + i + Menu_Sta.List_Offset].ItemName);
            }
            
        }
        u8g2_SetDrawColor(u8g2, 2);
        u8g2_DrawRBox(u8g2, 4,\
         1 + (Menu_Sta.List_Select - Menu_Sta.List_Offset) * 16 - 16 * Menu_Animation[0].pos, \
          110, 14, 0);

        u8g2_SendBuffer(u8g2);

    }
}

void Menu_RunList()
{
    switch(Menu[Menu_Sta.List_Firstpos + Menu_Sta.List_Select].Click_Action){
        case 0:
            break;
        case 1:
            Menu_Sta.Current_Menuid = Menu[Menu_Sta.List_Firstpos + Menu_Sta.List_Select].addp1;

            break;
        case 2:
            Menu[Menu_Sta.List_Firstpos + Menu_Sta.List_Select].Menu_Func();
            break;
        default :
            break;

    }
}
void Menu_PrewPage()
{
    Menu_Sta.Current_Menuid = Menu[Menu_Sta.List_Firstpos + Menu_Sta.List_Select].Preview_Menuid;
}
void Menu_NextOption()
{
    if(Menu_Sta.List_Select < Menu_Sta.List_Count)
    {
        Menu_Sta.List_Select++;
        Menu_Sta_AnimCalc();
    }
    else 
    {
        Menu_Sta.List_Select = 0;
        Menu_Sta_AnimCalc();
    }
}
void Menu_LastOption()
{
    if(Menu_Sta.List_Select == 0)
    {

        Menu_Sta.List_Select = Menu_Sta.List_Count;
        Menu_Sta_AnimCalc();
        
    }
    else 
    {
        Menu_Sta.List_Select--;
        Menu_Sta_AnimCalc();
    }
}
void Menu_Sta_AnimCalc()
{
    if(Menu_Sta.List_Select <= 3)
    {
        Menu_Sta.List_Offset = 0;
        Menu_Animation[0].current = Menu_Sta.List_Select;
        Menu_Animation[1].current = 0;
    }
    else
    {
        
        Menu_Sta.List_Offset = Menu_Sta.List_Select - 3;
        Menu_Animation[1].current = Menu_Sta.List_Offset;
        Menu_Animation[0].current = 3;
    }
}
void Menu_Animation_Calc()
{
    uint8_t i;
    for(i = 0; i < Menu_AnimationCount; i++)
    {
        if(Menu_Animation[i].pos && abs(Menu_Animation[i].pos * 160) < 10 )
            Menu_Animation[i].pos = 0;
        if(Menu_Animation[i].current != Menu_Animation[i].last)
        {
            if(Menu_Animation[i].adden)
                Menu_Animation[i].pos += Menu_Animation[i].current - Menu_Animation[i].last;
            else
                Menu_Animation[i].pos = Menu_Animation[i].current - Menu_Animation[i].last;
            Menu_Animation[i].last = Menu_Animation[i].current;
        }
        Menu_Animation[i].pos -= Menu_Animation[i].pos * Menu_Animation[i].speed;
    }
}
void Menu_Sta_Init(uint8_t Menu_id)
{
    Menu_Sta.List_Firstpos = Menu_FindList(Menu_id, 0);
    Menu_Sta.List_Count = Menu_GetListCount(Menu_id);
    Menu_Sta.List_Select = 0;
    Menu_Sta.List_Offset = 0;

}
uint8_t Menu_GetListCount(uint8_t Menu_id)
{
    uint8_t i, count;
    count = 0;
    for(i = 0; i < Menu_Count; i++)
    {
        if(Menu[i].Menu_id == Menu_id && Menu[i].Menu_Listid > count)
        {
            count = Menu[i].Menu_Listid;
        }

    }
    printf("lcnt %d\n", count);
    return count;
}
uint8_t Menu_FindList(uint8_t Menuid, uint8_t Listpos)
{
    uint8_t i, idx;
    idx = 0;
    for(i = 0; i < Menu_Count; i++)
    {
        if(Menu[i].Menu_id == Menuid && Menu[i].Menu_Listid == Listpos)
        {
            idx = i;
            break;
        }

    }
    printf("mid %d\n", idx);
    return idx;
}