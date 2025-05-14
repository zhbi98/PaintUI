
#include "voltage_v.h"

struct voltage_measure_t voltage_measure;

void voltage_level1_menu(unsigned char key_event, unsigned char * vm)
{
    unsigned char page = read_menubar_page();

    if (voltage_measure.type == VOLTAGE_DC) {
        if (page == VOLTAGE_LEFT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F1_MENUBAR_AREA, NULL, MENU_AC_DC, WHITE, UNSELECT, vm);
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
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, NEXT_MENUBAR_AREA, NULL, MENU_RIGHT, WHITE, UNSELECT, vm);
                    break;
            }
        } 

        if (page == VOLTAGE_CENTER) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F1_MENUBAR_AREA, NULL, MENU_RANGE, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F2_MENUBAR_AREA, NULL, MENU_MAX_MIN, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F3_MENUBAR_AREA, NULL, MENU_REL, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F4_MENUBAR_AREA, NULL, MENU_HOLD, WHITE, UNSELECT, vm);
                    break;

                case PREV_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, PREV_MENUBAR_AREA, NULL, MENU_LEFT, WHITE, UNSELECT, vm);
                    break;

                case NEXT_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, NEXT_MENUBAR_AREA, NULL, MENU_RIGHT, WHITE, UNSELECT, vm);
                    break;
            }
        } 

        if (page == VOLTAGE_RIGHT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F1_MENUBAR_AREA, NULL, MENU_COMP, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F2_MENUBAR_AREA, NULL, MENU_AUTO_SAVE, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F3_MENUBAR_AREA, NULL, MENU_MANUAL_SAVE, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F4_MENUBAR_AREA, NULL, MENU_VIEW_DATA, WHITE, UNSELECT, vm);
                    break;

                case PREV_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, PREV_MENUBAR_AREA, NULL, MENU_LEFT, WHITE, UNSELECT, vm);
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
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F1_MENUBAR_AREA, NULL, MENU_AC_DC, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F2_MENUBAR_AREA, NULL, MENU_LO, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F3_MENUBAR_AREA, NULL, MENU_PEAK, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    break;

                case PREV_KEY_EVT:
                    break;

                case NEXT_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, NEXT_MENUBAR_AREA, NULL, MENU_RIGHT, WHITE, UNSELECT, vm);
                    break;
            }
        }

        if (page == VOLTAGE_CENTER) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F1_MENUBAR_AREA, NULL, MENU_RANGE, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F2_MENUBAR_AREA, NULL, MENU_MAX_MIN, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F3_MENUBAR_AREA, NULL, MENU_REL, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F4_MENUBAR_AREA, NULL, MENU_HOLD, WHITE, UNSELECT, vm);
                    break;

                case PREV_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, PREV_MENUBAR_AREA, NULL, MENU_LEFT, WHITE, UNSELECT, vm);
                    break;

                case NEXT_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, NEXT_MENUBAR_AREA, NULL, MENU_RIGHT, WHITE, UNSELECT, vm);
                    break;
            }
        }

        if (page == VOLTAGE_RIGHT) {
            switch (key_event) {
                case F1_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F1_MENUBAR_AREA, NULL, MENU_COMP, WHITE, UNSELECT, vm);
                    break;

                case F2_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F2_MENUBAR_AREA, NULL, MENU_AUTO_SAVE, WHITE, UNSELECT, vm);
                    break;

                case F3_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F3_MENUBAR_AREA, NULL, MENU_MANUAL_SAVE, WHITE, UNSELECT, vm);
                    break;

                case F4_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, F4_MENUBAR_AREA, NULL, MENU_VIEW_DATA, WHITE, UNSELECT, vm);
                    break;

                case PREV_KEY_EVT:
                    display_widget_content(0, 0, CENTER_ALIGN, LAYOUT_R11, PREV_MENUBAR_AREA, NULL, MENU_LEFT, WHITE, UNSELECT, vm);
                    break;

                case NEXT_KEY_EVT:
                    break;
            }
        }
    }
}

void voltage_level1_key_event(unsigned char key_event)
{
    unsigned char page = read_menubar_page();

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
                    set_menubar_page(VOLTAGE_CENTER);
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
                    set_menubar_page(VOLTAGE_LEFT);
                    break;

                case NEXT_KEY_EVT:
                    set_menubar_page(VOLTAGE_RIGHT);
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
                    set_menubar_page(VOLTAGE_CENTER);
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
                    set_menubar_page(VOLTAGE_CENTER);
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
                    set_menubar_page(VOLTAGE_LEFT);
                    break;

                case NEXT_KEY_EVT:
                    set_menubar_page(VOLTAGE_RIGHT);
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
                    set_menubar_page(VOLTAGE_LEFT);
                    break;

                case NEXT_KEY_EVT:
                    break;
            }
        }
    }
}

void voltage_level1_key_event_enable(unsigned char key_event)
{
    unsigned char page = read_menubar_page();

    if (voltage_measure.type == VOLTAGE_DC) {
        if (page == VOLTAGE_LEFT) {
            _Area[F1_MENUBAR_AREA].valid   = true;
            _Area[F2_MENUBAR_AREA].valid   = true;
            _Area[F3_MENUBAR_AREA].valid   = true;
            _Area[F4_MENUBAR_AREA].valid   = true;
            _Area[PREV_MENUBAR_AREA].valid = true;
            _Area[NEXT_MENUBAR_AREA].valid = true;
        }

        if (page == VOLTAGE_CENTER) {
            _Area[F1_MENUBAR_AREA].valid   = true;
            _Area[F2_MENUBAR_AREA].valid   = true;
            _Area[F3_MENUBAR_AREA].valid   = true;
            _Area[F4_MENUBAR_AREA].valid   = true;
            _Area[PREV_MENUBAR_AREA].valid = true;
            _Area[NEXT_MENUBAR_AREA].valid = true;
        }

        if (page == VOLTAGE_RIGHT) {
            _Area[F1_MENUBAR_AREA].valid   = true;
            _Area[F2_MENUBAR_AREA].valid   = true;
            _Area[F3_MENUBAR_AREA].valid   = true;
            _Area[F4_MENUBAR_AREA].valid   = true;
            _Area[PREV_MENUBAR_AREA].valid = true;
            _Area[NEXT_MENUBAR_AREA].valid = true;
        }
    }

    if (voltage_measure.type == VOLTAGE_AC) {
        if (page == VOLTAGE_LEFT) {
            _Area[F1_MENUBAR_AREA].valid   = true;
            _Area[F2_MENUBAR_AREA].valid   = true;
            _Area[F3_MENUBAR_AREA].valid   = true;
            _Area[F4_MENUBAR_AREA].valid   = true;
            _Area[PREV_MENUBAR_AREA].valid = true;
            _Area[NEXT_MENUBAR_AREA].valid = true;
        }

        if (page == VOLTAGE_CENTER) {
            _Area[F1_MENUBAR_AREA].valid   = true;
            _Area[F2_MENUBAR_AREA].valid   = true;
            _Area[F3_MENUBAR_AREA].valid   = true;
            _Area[F4_MENUBAR_AREA].valid   = true;
            _Area[PREV_MENUBAR_AREA].valid = true;
            _Area[NEXT_MENUBAR_AREA].valid = true;
        }

        if (page == VOLTAGE_RIGHT) {
            _Area[F1_MENUBAR_AREA].valid   = true;
            _Area[F2_MENUBAR_AREA].valid   = true;
            _Area[F3_MENUBAR_AREA].valid   = true;
            _Area[F4_MENUBAR_AREA].valid   = true;
            _Area[PREV_MENUBAR_AREA].valid = true;
            _Area[NEXT_MENUBAR_AREA].valid = true;
        }
    }
}

void voltage_select()
{
    if (read_menubar_function() != DMM_VOLTAGE_V)
        return;

    voltage_measure.type++;
    set_menubar_page(VOLTAGE_CENTER);

    if (voltage_measure.type > VOLTAGE_AC)
        voltage_measure.type = VOLTAGE_DC; 
}
