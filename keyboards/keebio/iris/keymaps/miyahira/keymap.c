#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _MAC_COLEMAK 1
#define _WIN_SHRTCT 2
#define _MAC_SHRTCT 3
#define _LOWER 4
#define _RAISE 5
#define _ADJUST 6

enum custom_keycodes {
    COLEMAK = SAFE_RANGE,
    LOWER,
    RAISE,
    ADJUST,
    WIN_SHRTCT,
    MAC_SHRTCT,
};

//Windows short cuts
#define W_COPY LCTL(KC_C)
#define W_CUT LCTL(KC_X)
#define W_FIND LCTL(KC_F)
#define W_PASTE LCTL(KC_V)
#define W_QUIT LALT(KC_F4)
#define W_SAVE LCTL(KC_S)
#define W_SEL_ALL LCTL(KC_A)
#define W_UNDO LCTL(KC_Z)
//add alt tab

//Mac short cuts
#define M_COPY LCMD(KC_C)
#define M_CUT LCMD(KC_X)
#define M_FIND LCMD(KC_F)
#define M_PASTE LCMD(KC_V)
#define M_QUIT LCMD(KC_Q)
#define M_SAVE LCMD(KC_S)
#define M_SEL_ALL LCMD(KC_A)
#define M_UNDO LCMD(KC_Z)
//add alt tab


//Tap Dance Declarations
enum {
    LSFT_CAPS  = 0,
    TILDE_QUIT = 1,
};

void dance_tilde_quit_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_GRV);
    } else if (state->count == 2) {
        register_code (KC_ESC);
    } else if (state->count == 3) {
        register_code (KC_LALT);
        register_code (KC_F4);
    }
}

void dance_tilde_quit_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_GRV);
    } else if (state->count == 2){
        unregister_code (KC_ESC);
    } else if (state->count == 3) {
        unregister_code (KC_LALT);
        unregister_code (KC_F4);
    }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [LSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSHIFT, KC_CAPSLOCK), // Tap once for shift, twice for caps lock
    [TILDE_QUIT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_tilde_quit_finished, dance_tilde_quit_reset) // Tap once for escape, twice for alt+F4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    TD(TILDE_QUIT), KC_1,  KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_RALT,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LCTL,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,   KC_QUOT,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    TD(LSFT_CAPS),KC_Z,   KC_X,     KC_C,    KC_V,    KC_B,   KC_GRV,          KC_MPLY,   KC_K,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    WIN_SHRTCT, KC_SPACE, LOWER,                    RAISE,  KC_BSPC,  KC_ENT
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),


    [_MAC_COLEMAK] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    TD(TILDE_QUIT), KC_1,  KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_RALT,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_BSLS,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LCTL,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,   KC_QUOT,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    TD(LSFT_CAPS),KC_Z,   KC_X,     KC_C,    KC_V,    KC_B,   KC_GRV,          KC_MPLY,   KC_K,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                       MAC_SHRTCT, KC_SPACE, LOWER,                    RAISE,  KC_BSPC,  KC_ENT
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
),

    [_LOWER] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______,  KC_1,    KC_UP,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, KC_LEFT, KC_DOWN, KC_RGHT,   KC_UP,  KC_LBRC,                         KC_RBRC,   KC_P4,   KC_P5,   KC_P6, KC_PLUS,  DF(_COLEMAK),
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, KC_LCBR, KC_LPRN,         KC_RPRN, KC_RCBR,  KC_P1,   KC_P2,   KC_P3,   KC_EQL, DF(_MAC_COLEMAK),
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   _______,  KC_DEL, _______,                   _______,  KC_DEL,  KC_P0
//                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
),

[_RAISE] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    RGB_TOG, KC_EXLM, KC_VOLU, KC_HASH, KC_DLR,  KC_PERC,                           KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
   _______, KC_MPRV, KC_VOLD, KC_MNXT, KC_PGUP, KC_UNDS,                            KC_EQL,  KC_HOME, RGB_HUI, RGB_SAI, RGB_VAI, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______, _______, _______, _______, KC_PGDN, KC_MINS, RGB_TOG,          RGB_MOD, KC_PLUS, KC_END,  RGB_HUD, RGB_SAD, RGB_VAD, _______,
//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                  _______, _______, _______,                   _______, _______, _______
//                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
),

[_ADJUST] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
     RESET,  _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   _______, _______, _______,                   _______, _______, _______
//                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
),

        [_WIN_SHRTCT] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    _______, _______, _______, _______, W_QUIT, _______,                            _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______, _______, W_FIND, _______, _______,                            _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______,W_SEL_ALL,_______, W_SAVE, _______, _______,                            _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______, W_UNDO,  W_CUT,   W_COPY, W_PASTE, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   _______, _______, _______,                   _______, _______, _______
//                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
),

        [_MAC_SHRTCT] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    _______, _______, _______, _______, M_QUIT, _______,                            _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______, _______, _______, M_FIND, _______, _______,                            _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
    _______,M_SEL_ALL,_______, M_SAVE, _______, _______,                            _______, _______, _______, _______, _______, _______,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    _______, M_UNDO,  M_CUT,   M_COPY, M_PASTE, _______, _______,          _______, _______, _______, _______, _______, _______, _______,
//└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                   _______, _______, _______,                   _______, _______, _______
//                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
            break;
        case WIN_SHRTCT:
            if (record->event.pressed) {
                layer_on(_WIN_SHRTCT);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_WIN_SHRTCT);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case MAC_SHRTCT:
            if (record->event.pressed) {
                layer_on(_MAC_SHRTCT);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_MAC_SHRTCT);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
            break;
    }
    return true;
}


void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
}
