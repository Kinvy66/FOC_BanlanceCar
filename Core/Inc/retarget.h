/**
* @file retarget.h
* @author Kinvy
* @email kinvy66@163.com
* @date: 2025/2/27 
* @description: 
**/

#ifndef __RETARGET_H
#define __RETARGET_H

#include "stm32f4xx_hal.h"
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

void RetargetInit(UART_HandleTypeDef *huart);

int _isatty(int fd);

int _write(int fd, char *ptr, int len);

int _close(int fd);

int _lseek(int fd, int ptr, int dir);

int _read(int fd, char *ptr, int len);

int _fstat(int fd, struct stat *st);


#endif //__RETARGET_H
