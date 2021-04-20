/*******************************************************************************
* Copyleft (c) 2020 SaltyKid 1035183478@qq.com
*
* 版权描述信息略
*
* @file    device_initial.h
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
#ifndef __DEVICE_INITIAL_H__
#define __DEVICE_INITIAL_H__

#ifdef __cplusplus
extern "C" {
#endif

/*============================= INCLUDE FILES ===============================*/
#define _DEFAULT_SOURCE /* needed for usleep() */

#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"


/*========================= PERIPHERAL DECLARATION ==========================*/


/*============================ TYPE DEFINITIONS =============================*/


/*============================= ENUM DEFINES ================================*/


/*============================= UNION DEFINES ===============================*/


/*=========================== STRUCTURE DEFINES =============================*/


/*============================ GLOBAL VARIABLES =============================*/

extern lv_indev_t *kb_indev;

/*============================= EXPORTED MACRO ==============================*/


/*========================== FUNCTION PROTOTYPES ============================*/

void global_device_init(void);

#ifdef __cplusplus
}
#endif

#endif