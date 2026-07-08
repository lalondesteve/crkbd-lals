#include "override.h"
#include "process_key_override.h"
#include "quantum.h"

const key_override_t shift_space_underscore =
    ko_make_with_layers_and_negmods(MOD_MASK_SHIFT, LT2(KC_SPC), KC_UNDS, ~0, MOD_MASK_ALT | MOD_MASK_GUI);

const key_override_t *key_overrides[] = {&shift_space_underscore, NULL};
