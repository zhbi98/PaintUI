
#include "setting.h"

void setting_level1_menu(unsigned char key_event, unsigned char * vm)
{
    switch (key_event) {
        case F1_KEY_EVT:
            display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F1_MENUBAR_AREA, NULL, MENU_MINUS, WHITE, UNSELECT, vm);
            break;

        case F2_KEY_EVT:
            display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F2_MENUBAR_AREA, NULL, MENU_UP, WHITE, UNSELECT, vm);
            break;

        case F3_KEY_EVT:
            display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F3_MENUBAR_AREA, NULL, MENU_DOWN, WHITE, UNSELECT, vm);
            break;

        case F4_KEY_EVT:
            display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F4_MENUBAR_AREA, NULL, MENU_ADD, WHITE, UNSELECT, vm);
            break;

        case PREV_KEY_EVT:
            display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, PREV_MENUBAR_AREA, NULL, MENU_LEFT, WHITE, UNSELECT, vm);
            break;

        case NEXT_KEY_EVT:
            display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, NEXT_MENUBAR_AREA, NULL, MENU_RIGHT, WHITE, UNSELECT, vm);
            break;
    }
}

void setting_level1_key_event(unsigned char key_event)
{
    switch (key_event) {
        case F1_KEY_EVT:
            set_equip_time(-1);
            set_equip_date(-1);
            set_apo_time(-1);

            if (get_param_number() == SETUP_COMP_MAX) {
                set_value_type(SETUP_COMP_MAX);
                value_ud_flip(-1);
            }
            if (get_param_number() == SETUP_COMP_MIN) {
                set_value_type(SETUP_COMP_MIN);
                value_ud_flip(-1);
            }

            set_comp_type(-1);
            set_record_rate(-1);
            set_memory_mode(-1);
            set_back_light(-1);
            set_light_time(-1);
            set_sound_status(-1);
            set_theme_color(-1);
            display_area1_flush_enable();
            display_setting_area2_flush_enable();
            break;

        case F2_KEY_EVT:
            vpos_selected(-1);
            display_setting_area2_flush_enable();
            break;

        case F3_KEY_EVT:
            vpos_selected(1);
            display_setting_area2_flush_enable();
            break;

        case F4_KEY_EVT:
            set_equip_time(1);
            set_equip_date(1);
            set_apo_time(1);

            if (get_param_number() == SETUP_COMP_MAX) {
                set_value_type(SETUP_COMP_MAX);
                value_ud_flip(1); 
            }
            if (get_param_number() == SETUP_COMP_MIN) {
                set_value_type(SETUP_COMP_MIN);
                value_ud_flip(1);
            }

            set_comp_type(1);
            set_record_rate(1);
            set_memory_mode(1);
            set_back_light(1);
            set_light_time(1);
            set_sound_status(1);
            set_theme_color(1);
            display_area1_flush_enable();
            display_setting_area2_flush_enable();
            break;

        case PREV_KEY_EVT:
            hpos_selected(-1);

            if (get_param_number() == SETUP_COMP_MAX) {
                set_value_type(SETUP_COMP_MAX);
                digit_lr_move(-1);
            }
            if (get_param_number() == SETUP_COMP_MIN) {
                set_value_type(SETUP_COMP_MIN);
                digit_lr_move(-1);
            }

            display_setting_area2_flush_enable();
            display_area1_flush_enable();
            break;

        case NEXT_KEY_EVT:
            hpos_selected(1);

            if (get_param_number() == SETUP_COMP_MAX) {
                set_value_type(SETUP_COMP_MAX);
                digit_lr_move(1);
            }
            if (get_param_number() == SETUP_COMP_MIN) {
                set_value_type(SETUP_COMP_MIN);
                digit_lr_move(1);
            }

            display_setting_area2_flush_enable();
            display_area1_flush_enable();
            break;
    }
}

void setting_level1_key_event_enable(unsigned char key_event)
{
    _Area[F1_MENUBAR_AREA].valid   = true;
    _Area[F2_MENUBAR_AREA].valid   = true;
    _Area[F3_MENUBAR_AREA].valid   = true;
    _Area[F4_MENUBAR_AREA].valid   = true;
    _Area[PREV_MENUBAR_AREA].valid = true;
    _Area[NEXT_MENUBAR_AREA].valid = true;
}
