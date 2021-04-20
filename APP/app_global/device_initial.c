/*******************************************************************************
* Copyleft (c) 2020 SaltyKid 1035183478@qq.com
*
* 版权描述信息略
*
* @file    device_initial.c
* @author  SaltyKid
* @version 0.0.1
* @date    2021-04-05
* @license GNU General Public License (GPL) 
* @brief   略
*          This file contains:
*              - 略
*
* -----------------------------------------------------------------------------
* Change History:
*   <Date>      |  <Version>  |  <Author>  |  <Description>
*   2021-04-05  |  v0.0.1     |  SaltyKid  |  Create file
* -----------------------------------------------------------------------------
******************************************************************************/

/*============================= INCLUDE FILES ===============================*/
#include "device_initial.h"


/*============================ GLOBAL VARIABLES =============================*/

lv_indev_t *kb_indev;

/*========================== FUNCTION PROTOTYPES ============================*/

static void hal_init(void);
static int tick_thread(void *data);
static void memory_monitor(lv_task_t *param);

/******************************************************************************
 * @brief        Global Initialize 
 *
 * @param[in]    None
 *
 * @return       None
******************************************************************************/
void global_device_init(void)
{
    /*Initialize LVGL*/
    lv_init();

    /*Initialize the HAL (display, input devices, tick) for LVGL*/
    hal_init();

}



/******************************************************************************
 * @brief        Initialize the Hardware Abstraction Layer (HAL) for the Littlev graphics library
 *
 * @param[in]    None
 *
 * @return       None
******************************************************************************/
static void hal_init(void) 
{
    /* Use the 'monitor' driver which creates window on PC's monitor to simulate a display*/
    monitor_init();

    /*Create a display buffer*/
    static lv_disp_buf_t disp_buf1;
    static lv_color_t buf1_1[LV_HOR_RES_MAX * 120];
    lv_disp_buf_init(&disp_buf1, buf1_1, NULL, LV_HOR_RES_MAX * 120);

    /*Create a display*/
    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
    disp_drv.buffer = &disp_buf1;
    disp_drv.flush_cb = monitor_flush;
    lv_disp_drv_register(&disp_drv);

    /* Add the mouse as input device
    * Use the 'mouse' driver which reads the PC's mouse*/
    mouse_init();
    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv); /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_POINTER;

    /*This function will be called periodically (by the library) to get the mouse position and state*/
    indev_drv.read_cb = mouse_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv);

    /*Set a cursor for the mouse*/
    LV_IMG_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
    lv_obj_t * cursor_obj = lv_img_create(lv_scr_act(), NULL); /*Create an image object for the cursor */
    lv_img_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
    lv_indev_set_cursor(mouse_indev, cursor_obj);             /*Connect the image  object to the driver*/

    /* Tick init.
    * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL about
    * how much time were elapsed Create an SDL thread to do this*/
    SDL_CreateThread(tick_thread, "tick", NULL);


    /*!< 创建一个内存监视器任务，定期打印内存使用情况 */
    lv_task_create(memory_monitor, 5000, LV_TASK_PRIO_MID, NULL);
}


/******************************************************************************
 * @brief        A task to measure the elapsed time for LVGL
 *
 * @param[in]    data: unused
 *
 * @return       None
******************************************************************************/
static int tick_thread(void *data) 
{
    (void)data;

    while (1) {
        SDL_Delay(1);   /*Sleep for 1 millisecond*/
        lv_tick_inc(1); /*Tell LittelvGL that 1 milliseconds were elapsed*/
    }

    return 0;
}


/******************************************************************************
 * @brief        Print the memory usage periodically
 *
 * @param[in]    param: unused
 *
 * @return       None
******************************************************************************/
static void memory_monitor(lv_task_t *param) 
{
    (void)param; /*Unused*/

    lv_mem_monitor_t mon;
    lv_mem_monitor(&mon);
    printf("used: %6d (%3d %%), frag: %3d %%, biggest free: %6d\n",
            (int)mon.total_size - mon.free_size, mon.used_pct, mon.frag_pct,
            (int)mon.free_biggest_size);
}