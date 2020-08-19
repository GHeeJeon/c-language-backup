#pragma once
/* Menu.h */
#ifndef MENU_H
#define MENU_H

#define ADD_CONTACT  1
#define LIST_BY_NAME 2
#define FIND_CONTACT 3
#define QUIT_PROGRAM 0

#define CLEAR_INPUT() while( getchar() != '\n' );

int SelectMenu(void);

#define MODIFY_CONTACT 1
#define DELETE_CONTACT 2
#define PREVIOUS_MENU  0

int SelectFindMenu(void);

#endif