
#include "stdio.h"
#include "u8g2.h"
#include "SDL_timer.h"
// #include    "sdl/i686-w64-mingw32/include/SDL2/sdl.h"

u8g2_t u8g2;

int main()
{
    int k;
    uint64_t tick;
    volatile uint8_t i;
    char str[20];
    u8g2_SetupBuffer_SDL_128x64(&u8g2, &u8g2_cb_r0);
    u8x8_InitDisplay(u8g2_GetU8x8(&u8g2));
    u8x8_SetPowerSave(u8g2_GetU8x8(&u8g2), 0);
    u8g2_ClearBuffer(&u8g2);

    for (;;)
    {

        u8g2_FirstPage(&u8g2);
        do
        {
            u8g2_SetFont(&u8g2, u8g2_font_wqy16_t_gb2312);
            u8g2_DrawUTF8(&u8g2, 5, 17, "中文");
            sprintf(str, "num:%d", i);
            u8g2_DrawStr(&u8g2, 5, 27, str);
            u8g2_SetFont(&u8g2, u8g2_font_open_iconic_embedded_1x_t);
            u8g2_DrawGlyph(&u8g2, i, 56, 0x0041);
            

        } while (u8g2_NextPage(&u8g2));
        if(SDL_GetTicks64() - tick >= 50)
        {
            tick = SDL_GetTicks64();
            i = (uint8_t)((i + 1)* 1.2) %  110;
        }
        
        k = u8g_sdl_get_key();
        if (k == 'q')
            break;
    }
    return 0;
}
