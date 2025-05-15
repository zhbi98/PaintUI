
#include "voltage_v.h"

struct voltage_measure_t voltage_measure;

void voltage_level1_menu(unsigned char key_event, unsigned char * vm)
{
    unsigned char page = act_bar_get_page(&_dmm_actbar);

    if (voltage_measure.type == VOLTAGE_DC) {
        if (page == VOLTAGE_LEFT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F1_BTN, NULL, MENU_AC_DC, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    break;

                case F3_KEY_EVT:
                    break;

                case F4_KEY_EVT:
                    break;

                case PREV_KEY_EVT:
                    break;

                case NEXT_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, UNSELECT, vm);
                    break;
            }
        } 

        if (page == VOLTAGE_CENTER) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F1_BTN, NULL, MENU_RANGE, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F2_BTN, NULL, MENU_MAX_MIN, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F3_BTN, NULL, MENU_REL, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F4_BTN, NULL, MENU_HOLD, WHITE, UNSELECT, vm);
                    break;

                case PREV_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, UNSELECT, vm);
                    break;

                case NEXT_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, UNSELECT, vm);
                    break;
            }
        } 

        if (page == VOLTAGE_RIGHT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F1_BTN, NULL, MENU_COMP, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F2_BTN, NULL, MENU_AUTO_SAVE, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F3_BTN, NULL, MENU_MANUAL_SAVE, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F4_BTN, NULL, MENU_VIEW_DATA, WHITE, UNSELECT, vm);
                    break;

                case PREV_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, UNSELECT, vm);
                    break;

                case NEXT_KEY_EVT:
                    break;
            }
        }
    }

    if (voltage_measure.type == VOLTAGE_AC) {
        if (page == VOLTAGE_LEFT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F1_BTN, NULL, MENU_AC_DC, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F2_BTN, NULL, MENU_LO, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F3_BTN, NULL, MENU_PEAK, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    break;

                case PREV_KEY_EVT:
                    break;

                case NEXT_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, UNSELECT, vm);
                    break;
            }
        }

        if (page == VOLTAGE_CENTER) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F1_BTN, NULL, MENU_RANGE, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F2_BTN, NULL, MENU_MAX_MIN, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F3_BTN, NULL, MENU_REL, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F4_BTN, NULL, MENU_HOLD, WHITE, UNSELECT, vm);
                    break;

                case PREV_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, UNSELECT, vm);
                    break;

                case NEXT_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_NEXT_BTN, NULL, MENU_RIGHT, WHITE, UNSELECT, vm);
                    break;
            }
        }

        if (page == VOLTAGE_RIGHT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F1_BTN, NULL, MENU_COMP, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F2_BTN, NULL, MENU_AUTO_SAVE, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F3_BTN, NULL, MENU_MANUAL_SAVE, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_F4_BTN, NULL, MENU_VIEW_DATA, WHITE, UNSELECT, vm);
                    break;

                case PREV_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, DMM_PREV_BTN, NULL, MENU_LEFT, WHITE, UNSELECT, vm);
                    break;

                case NEXT_KEY_EVT:
                    break;
            }
        }
    }
}

void voltage_level1_key_event(unsigned char key_event)
{
    unsigned char page = act_bar_get_page(&_dmm_actbar);

    if (voltage_measure.type == VOLTAGE_DC) {
        if (page == VOLTAGE_LEFT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    break;

                case F2_KEY_EVT:
                    break;

                case F3_KEY_EVT:
                    break;

                case F4_KEY_EVT:
                    break;

                case PREV_KEY_EVT:
                    break;

                case NEXT_KEY_EVT:
                    act_bar_set_page(&_dmm_actbar, VOLTAGE_CENTER);
                    break;
            }
        }

        if (page == VOLTAGE_CENTER) {
            switch (key_event) {
                case F1_KEY_EVT:
                    // image_shot();
                    active_tips(&message_tips[0], second_convert_ticks(100));
                    break;

                case F2_KEY_EVT:
                    break;

                case F3_KEY_EVT:
                    break;

                case F4_KEY_EVT:
                    break;

                case PREV_KEY_EVT:
                    act_bar_set_page(&_dmm_actbar, VOLTAGE_LEFT);
                    break;

                case NEXT_KEY_EVT:
                    act_bar_set_page(&_dmm_actbar, VOLTAGE_RIGHT);
                    break;
            }
        }

        if (page == VOLTAGE_RIGHT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    break;

                case F2_KEY_EVT:
                    break;

                case F3_KEY_EVT:
                    break;

                case F4_KEY_EVT:
                    break;

                case PREV_KEY_EVT:
                    act_bar_set_page(&_dmm_actbar, VOLTAGE_CENTER);
                    break;

                case NEXT_KEY_EVT:
                    break;
            }
        }
    }

    if (voltage_measure.type == VOLTAGE_AC) {
        if (page == VOLTAGE_LEFT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    break;

                case F2_KEY_EVT:
                    break;

                case F3_KEY_EVT:
                    break;

                case F4_KEY_EVT:
                    break;

                case PREV_KEY_EVT:
                    break;

                case NEXT_KEY_EVT:
                    act_bar_set_page(&_dmm_actbar, VOLTAGE_CENTER);
                    break;
            }
        }

        if (page == VOLTAGE_CENTER) {
            switch (key_event) {
                case F1_KEY_EVT:
                    break;

                case F2_KEY_EVT:
                    break;

                case F3_KEY_EVT:
                    break;

                case F4_KEY_EVT:
                    break;

                case PREV_KEY_EVT:
                    act_bar_set_page(&_dmm_actbar, VOLTAGE_LEFT);
                    break;

                case NEXT_KEY_EVT:
                    act_bar_set_page(&_dmm_actbar, VOLTAGE_RIGHT);
                    break;
            }
        }

        if (page == VOLTAGE_RIGHT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    break;

                case F2_KEY_EVT:
                    break;

                case F3_KEY_EVT:
                    break;

                case F4_KEY_EVT:
                    break;

                case PREV_KEY_EVT:
                    act_bar_set_page(&_dmm_actbar, VOLTAGE_LEFT);
                    break;

                case NEXT_KEY_EVT:
                    break;
            }
        }
    }
}

void voltage_level1_key_event_enable(unsigned char key_event)
{
    unsigned char page = act_bar_get_page(&_dmm_actbar);

    if (voltage_measure.type == VOLTAGE_DC) {
        if (page == VOLTAGE_LEFT) {
            _Area[DMM_F1_BTN].valid   = true;
            _Area[DMM_F2_BTN].valid   = true;
            _Area[DMM_F3_BTN].valid   = true;
            _Area[DMM_F4_BTN].valid   = true;
            _Area[DMM_PREV_BTN].valid = true;
            _Area[DMM_NEXT_BTN].valid = true;
        }

        if (page == VOLTAGE_CENTER) {
            _Area[DMM_F1_BTN].valid   = true;
            _Area[DMM_F2_BTN].valid   = true;
            _Area[DMM_F3_BTN].valid   = true;
            _Area[DMM_F4_BTN].valid   = true;
            _Area[DMM_PREV_BTN].valid = true;
            _Area[DMM_NEXT_BTN].valid = true;
        }

        if (page == VOLTAGE_RIGHT) {
            _Area[DMM_F1_BTN].valid   = true;
            _Area[DMM_F2_BTN].valid   = true;
            _Area[DMM_F3_BTN].valid   = true;
            _Area[DMM_F4_BTN].valid   = true;
            _Area[DMM_PREV_BTN].valid = true;
            _Area[DMM_NEXT_BTN].valid = true;
        }
    }

    if (voltage_measure.type == VOLTAGE_AC) {
        if (page == VOLTAGE_LEFT) {
            _Area[DMM_F1_BTN].valid   = true;
            _Area[DMM_F2_BTN].valid   = true;
            _Area[DMM_F3_BTN].valid   = true;
            _Area[DMM_F4_BTN].valid   = true;
            _Area[DMM_PREV_BTN].valid = true;
            _Area[DMM_NEXT_BTN].valid = true;
        }

        if (page == VOLTAGE_CENTER) {
            _Area[DMM_F1_BTN].valid   = true;
            _Area[DMM_F2_BTN].valid   = true;
            _Area[DMM_F3_BTN].valid   = true;
            _Area[DMM_F4_BTN].valid   = true;
            _Area[DMM_PREV_BTN].valid = true;
            _Area[DMM_NEXT_BTN].valid = true;
        }

        if (page == VOLTAGE_RIGHT) {
            _Area[DMM_F1_BTN].valid   = true;
            _Area[DMM_F2_BTN].valid   = true;
            _Area[DMM_F3_BTN].valid   = true;
            _Area[DMM_F4_BTN].valid   = true;
            _Area[DMM_PREV_BTN].valid = true;
            _Area[DMM_NEXT_BTN].valid = true;
        }
    }
}

void voltage_select()
{
    if (act_bar_get_func(&_dmm_actbar) != DMM_VOLTAGE_V)
        return;

    voltage_measure.type++;
    act_bar_set_page(&_dmm_actbar, VOLTAGE_CENTER);

    if (voltage_measure.type > VOLTAGE_AC)
        voltage_measure.type = VOLTAGE_DC; 
}
