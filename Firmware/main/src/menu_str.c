/**
 * @file menu_str.c
 *
 */

/*********************
 *      INCLUDES
 *********************/

#include "menu_str.h"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

const uint8_t * 
const menu_content[] = {
  "RANGE",  /**000*/
  "MAX/MIN",/**001*/
  "REL",    /**002*/
  "HOLD",   /**003*/
  "COMP",   /**010*/
  "AC+DC",  /**011*/
  "Lo",     /**012*/
  "Loz",    /**013*/
  "PEAK",   /**014*/
  "DISPLAY",/**015*/
  "RECORD", /**016*/
  "SAVE",   /**017*/
  "LOG",    /**018*/
  "<",      /**004*/
  ">",      /**005*/
  "^",      /**006*/
  "v",      /**007*/
  "+",      /**008*/
  "-",      /**009*/
};

const uint8_t * 
const list_content[] = {
  "1/2",            /**000*/
  "Set Time",       /**001*/
  "Set Date",       /**002*/
  "Auto Power Off",    /**003*/
  "Compare Max",    /**004*/
  "Compare Min",    /**005*/
  "Compare Type",   /**006*/
  "Record Rate",    /**007*/
  "Memory Mode",    /**008*/
  "2/2",            /**009*/
  "Brightness",     /**010*/
  "Display On",/**011*/
  "Voice",          /**012*/
  "Display Mode", /**013*/
};

const uint8_t * 
const tips_content[] = {
  "Battery Below 20%", /**000*/
  "Battery Below 15%", /**001*/
  "Battery Below 10%", /**002*/
  "Dev Ver 1.0.0",  /**003*/
};
