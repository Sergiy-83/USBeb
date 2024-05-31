#ifndef __S83_GUI_H
#define __S83_GUI_H

#include <stdbool.h>
#include <stdint.h>

void GUI_init(void);
void GUI_loading(void);

void GUI_print_static_text(void);
void GUI_print_interface(void);
void GUI_print_cursor(uint32_t index);
void GUI_print_cursor_2(void);
void GUI_print_scroll_bar(uint8_t arg_p_pos_cursor, uint8_t arg_p_window);
void GUI_print_time_PB(uint32_t arg_percent);
void GUI_print_poff_screen(void);


void GUI_clear_cursor(uint32_t index);
void GUI_clear_cursor_2(void);
void GUI_clear_string(uint32_t index);

void GUI_print_toast(char* arg_msg, uint8_t arg_len, uint16_t arg_color);
void GUI_clear_toast(void);
	
uint32_t GUI_get_string_len(void);
#endif