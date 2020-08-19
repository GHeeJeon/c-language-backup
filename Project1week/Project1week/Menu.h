/* Menu.h */
#ifndef MENU_H
#define MENU_H

#define ADD_CONTACT  1
#define LIST_BY_NAME 2
#define QUIT_PROGRAM 0

#define CLEAR_INPUT() while( getchar() != '\n' );

int SelectMenu(void);

#endif
