#pragma once
#include "quantum.h"

const key_override_t shift_allspace_underscore = ko_make_basic(MOD_MASK_SHIFT, HYPR_T(KC_SPC), KC_UNDS);
const key_override_t shift_space_underscore = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_UNDS);

const key_override_t *key_overrides[] = {
	&shift_space_underscore,
	&shift_allspace_underscore,
  NULL
};
