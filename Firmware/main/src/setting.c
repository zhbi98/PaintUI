
#include "setting.h"

void setting_level1_menu(unsigned char key_event, unsigned char * vm)
{
    switch (key_event) {
    case F1_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, DMM_F1_BTN, NULL, MENU_MINUS, WHITE, INV_OFF, vm);
        break;

    case F2_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, DMM_F2_BTN, NULL, MENU_UP, WHITE, INV_OFF, vm);
        break;

    case F3_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, DMM_F3_BTN, NULL, MENU_DOWN, WHITE, INV_OFF, vm);
        break;

    case F4_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, DMM_F4_BTN, NULL, MENU_ADD, WHITE, INV_OFF, vm);
        break;

    case PREV_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, INV_OFF, vm);
        break;

    case NEXT_KEY_EVT:
        display_N1string(0, 0, ALIGN_CENTER, LAYOUT_R11, DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, INV_OFF, vm);
        break;
    }
}

void setting_level1_key_event(unsigned char key_event)
{
    switch (key_event) {
        case F1_KEY_EVT:
            lv_time_set_val(-1);
            lv_date_set_val(-1);
            lv_apoff_set_val(-1);

            if (lv_tab_get_opti_id() == DEV_COMP_MAX) {
                set_value_type(DEV_COMP_MAX);
                value_ud_flip(-1);
            }
            if (lv_tab_get_opti_id() == DEV_COMP_MIN) {
                set_value_type(DEV_COMP_MIN);
                value_ud_flip(-1);
            }

            lv_comp_set_type_val(-1);
            lv_mem_set_val(-1);
            lv_bright_set_val(-1);
            lv_dispoff_set_val(-1);
            lv_voice_set_val(-1);
            lv_dark_set_val(-1);
            dev_topbar_cont_flush_enable();
            ctl_tabv_cont_flush_enable();
            break;

        case F2_KEY_EVT:
            lv_tab_set_line(-1);
            ctl_tabv_cont_flush_enable();
            break;

        case F3_KEY_EVT:
            lv_tab_set_line(1);
            ctl_tabv_cont_flush_enable();
            break;

        case F4_KEY_EVT:
            lv_time_set_val(1);
            lv_date_set_val(1);
            lv_apoff_set_val(1);

            if (lv_tab_get_opti_id() == DEV_COMP_MAX) {
                set_value_type(DEV_COMP_MAX);
                value_ud_flip(1); 
            }
            if (lv_tab_get_opti_id() == DEV_COMP_MIN) {
                set_value_type(DEV_COMP_MIN);
                value_ud_flip(1);
            }

            lv_comp_set_type_val(1);
            lv_mem_set_val(1);
            lv_bright_set_val(1);
            lv_dispoff_set_val(1);
            lv_voice_set_val(1);
            lv_dark_set_val(1);
            dev_topbar_cont_flush_enable();
            ctl_tabv_cont_flush_enable();
            break;

        case PREV_KEY_EVT:
            lv_tab_set_hidx(-1);

            if (lv_tab_get_opti_id() == DEV_COMP_MAX) {
                set_value_type(DEV_COMP_MAX);
                digit_lr_move(-1);
            }
            if (lv_tab_get_opti_id() == DEV_COMP_MIN) {
                set_value_type(DEV_COMP_MIN);
                digit_lr_move(-1);
            }

            ctl_tabv_cont_flush_enable();
            dev_topbar_cont_flush_enable();
            break;

        case NEXT_KEY_EVT:
            lv_tab_set_hidx(1);

            if (lv_tab_get_opti_id() == DEV_COMP_MAX) {
                set_value_type(DEV_COMP_MAX);
                digit_lr_move(1);
            }
            if (lv_tab_get_opti_id() == DEV_COMP_MIN) {
                set_value_type(DEV_COMP_MIN);
                digit_lr_move(1);
            }

            ctl_tabv_cont_flush_enable();
            dev_topbar_cont_flush_enable();
            break;
    }
}

void setting_level1_key_event_enable(unsigned char key_event)
{
    _Area[DMM_F1_BTN].valid   = true;
    _Area[DMM_F2_BTN].valid   = true;
    _Area[DMM_F3_BTN].valid   = true;
    _Area[DMM_F4_BTN].valid   = true;
    _Area[DMM_PREV_BTN].valid = true;
    _Area[DMM_NEXT_BTN].valid = true;
}
