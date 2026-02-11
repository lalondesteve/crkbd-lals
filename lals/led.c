#include "quantum.h"
#include "layers.h"
#include "transactions.h"

// Logic to sync caps word between splits
static bool slave_caps_word_state = false;

void slave_caps_word_callback(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data){
  const bool *status = (const bool*)in_data;
  slave_caps_word_state = *status;
};

void housekeeping_task_user(void){
  if (is_keyboard_master()){
    static bool last_caps_word_state = false;
    bool current_state = is_caps_word_on();

    if (current_state != last_caps_word_state){
      last_caps_word_state = current_state;

      transaction_rpc_send(USER_SYNC_CAPS_WORD, sizeof(current_state), &current_state);
    }
  }
};

bool get_caps_word_synced(void){
  if (is_keyboard_master()){
    return is_caps_word_on();
  } else {
    return slave_caps_word_state;
  }
};

bool update_capslock_led_state(bool caps_state){
  if (caps_state || host_keyboard_led_state().caps_lock || get_caps_word_synced()){
    rgb_matrix_set_color_all(_CAPS_COLOR);
    return true;
  }
  return false;
};

void caps_word_set_user(bool active){
  if (active){
    update_capslock_led_state(true);
  } else {
    update_capslock_led_state(true);
  }
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
  transaction_register_rpc(USER_SYNC_CAPS_WORD, slave_caps_word_callback);
}

void eeconfig_init_user(void){
  my_default_color();
  rgb_matrix_sethsv(_DEF_COLOR_HSV);
}

