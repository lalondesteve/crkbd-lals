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

  uint8_t current_layer = get_highest_layer(layer_state);
  if (current_layer > 0){
    uint8_t h, s, v;
    vial_get_user_setting_hsv(current_layer, &h, &s, &v);

    HSV hsv = {h,s,v};
    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
  }


  return false;
}

void eeconfig_init_user(void){
  vial_get_user_setting_hsv(id_layer0, _DEF_COLOR_HSV);
  vial_get_user_setting_hsv(id_layer1, _DEF_COLOR_HSV);
  vial_get_user_setting_hsv(id_layer2, _DEF_COLOR_HSV);
  vial_get_user_setting_hsv(id_layer3, _MAG_COLOR_HSV);
  vial_get_user_setting_hsv(id_layer4, _CYAN_COLOR_HSV);
  vial_get_user_setting_hsv(id_layer5, _DEF_COLOR_HSV);
  vial_get_user_setting_hsv(id_layer6, _CTO_COLOR_HSV);
  vial_get_user_setting_hsv(id_layer7, _DEF_COLOR_HSV);
  vial_get_user_setting_hsv(id_layer8, _DEF_COLOR_HSV);
  vial_get_user_setting_hsv(id_layer9, _DEF_COLOR_HSV);
  vial_get_user_setting_hsv(id_caps, _ALT_CAPS_HSV);
}

void vial_post_config_save_user(void){
  rgb_matrix_indicators_user()
}
