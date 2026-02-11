#include "quantum.h"
#include "layers.h"


bool update_capslock_led_state(bool caps_state){
  if (caps_state || host_keyboard_led_state().caps_lock || is_caps_word_on()){
    rgb_matrix_set_color_all(_CAPS_COLOR);
    return true;
  }
  return false;
} 

void caps_word_set_user(bool active){
  update_capslock_led_state(active);
}

bool led_update_user(led_t led_state){
  update_capslock_led_state(led_state.caps_lock);
  return true;
}

bool rgb_matrix_indicators_user(void){
  bool caps = update_capslock_led_state(false);
  if (caps){
    return false;
  }

  switch (get_highest_layer(layer_state)){
    case _FKEYS:
      rgb_matrix_set_color_all(_FKEYS_COLOR);
      break;
    case _NUMPAD:
      rgb_matrix_set_color_all(_NUM_COLOR);
      break;
    case _SUDOKU:
      rgb_matrix_set_color_all(_SUDOKU_COLOR);
      break;
    case _NUM:
    case _CHAR:
    default:
      return false;
  }
  return false;
}

void my_default_color(void){
  rgb_matrix_enable();
  rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
  rgb_matrix_set_color_all(_DEF_COLOR);
}

void keyboard_post_init_user(void){
  my_default_color();
}

void eeconfig_init_user(void){
  my_default_color();
  rgb_matrix_sethsv(_DEF_COLOR_HSV);
}

