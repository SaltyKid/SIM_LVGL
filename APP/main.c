
/*******************************************************************************
* Copyleft (c) 2020 SaltyKid 1035183478@qq.com
*
* 版权描述信息略
*
* @file    main.c
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



/*========================== FUNCTION PROTOTYPES ============================*/

/******************************************************************************
 * @brief        Main
 *
 * @param[in]    argc: unused
 * 
 * @param[in]    argv: unused
 *
 * @return       None
******************************************************************************/
int main(int argc, char **argv)
{
    (void)argc; /*Unused*/
    (void)argv; /*Unused*/

    global_device_init();

    while (1) {
        /* Periodically call the lv_task handler.
        * It could be done in a timer interrupt or an OS task too.*/
        lv_task_handler();
        usleep(5 * 1000);
    }

    return 0;
}


