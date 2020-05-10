#include QMK_KEYBOARD_H

#define _COLEMAK 0
#define _MAC_COLEMAK 1
#define _WIN_SHRTCT 2
#define _MAC_SHRTCT 3
#define _ARROWS_TK 5
#define _GAMING 7
#define _QWERTY_GAMING 9
#define _LOWER 11
#define _RAISE 13
#define _ADJUST 14

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
#define W_NXT_WIN LALT(KC_TAB)
#define W_REOPEN LCTL(LSFT(KC_T))


//Mac short cuts
#define M_COPY LCMD(KC_C)
#define M_CUT LCMD(KC_X)
#define M_FIND LCMD(KC_F)
#define M_PASTE LCMD(KC_V)
#define M_QUIT LCMD(KC_Q)
#define M_SAVE LCMD(KC_S)
#define M_SEL_ALL LCMD(KC_A)
#define M_UNDO LCMD(KC_Z)
#define M_NXT_WIN LCMD(KC_TAB)
#define M_REOPEN LCMD(LSFT(KC_T))
#define M_SEARCH LOPT(KC_SPACE)
#define M_FOLLOW LCMD(LALT(KC_B)) // IntelliJ - go to implementation
#define M_CREATE LALT(KC_ENTER) // IntelliJ - creates code
#define M_SPEC_1 LCTL(LSFT(LCMD(KC_LEFT))) // Spectacle - bottom left
#define M_SPEC_2 LOPT(LCMD(KC_DOWN)) // Spectacle - bottom half
#define M_SPEC_3 LCTL(LSFT(LCMD(KC_RIGHT))) // Spectacle - bottom right
#define M_SPEC_4 LOPT(LCMD(KC_LEFT)) // Spectacle - left half
#define M_SPEC_5 LALT(LCMD(KC_F)) // Spectacle - full screen
#define M_SPEC_6 LOPT(LCMD(KC_RIGHT)) // Spectacle - right half
#define M_SPEC_7 LCTL(LCMD(KC_LEFT)) // Spectacle - top left
#define M_SPEC_8 LOPT(LCMD(KC_UP)) // Spectacle - top half
#define M_SPEC_9 LCTL(LCMD(KC_RIGHT)) // Spectacle - top right

enum combos {
    PARENTHESES,
    BRACKETS,
    BRACES,
};

const uint16_t PROGMEM parentheses_combo[] = {KC_V, KC_M, COMBO_END};
const uint16_t PROGMEM brackets_combo[]    = {KC_C, KC_COMM, COMBO_END};
const uint16_t PROGMEM braces_combo[]      = {KC_X, KC_DOT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [PARENTHESES] = COMBO_ACTION(parentheses_combo),
    [BRACKETS]    = COMBO_ACTION(brackets_combo),
    [BRACES]      = COMBO_ACTION(braces_combo),
};

void process_combo_event(uint8_t combo_index, bool pressed) {
    switch(combo_index) {
        case PARENTHESES:
            if (pressed) {
                register_code(KC_LSFT);
                tap_code(KC_9);
                tap_code(KC_0);
                unregister_code(KC_LSFT);
                tap_code(KC_LEFT);
            }
            break;
        case BRACKETS:
            if (pressed) {
                register_code(KC_LSFT);
                tap_code(KC_LBRC);
                tap_code(KC_RBRC);
                unregister_code(KC_LSFT);
                tap_code(KC_LEFT);
            }
            break;
        case BRACES:
            if (pressed) {
                tap_code(KC_LBRC);
                tap_code(KC_RBRC);
                tap_code(KC_LEFT);
            }
            break;
    }
}

//Tap Dance Declarations
enum {
    LSFT_CAPS  = 0,
    TILDE_QUIT = 1,
    UP         = 2,
    DOWN       = 3,
};

void dance_tilde_esc_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_GRV);
    } else if (state->count == 2) {
        register_code (KC_ESC);
    }
}

void dance_tilde_esc_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_GRV);
    } else if (state->count == 2){
        unregister_code (KC_ESC);
    }
}

void dance_up_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_UP);
    } else if (state->count == 2) {
        register_code (KC_PGUP);
    } else if (state->count == 3) {
        register_code (KC_HOME);
    }
}

void dance_up_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_UP);
    } else if (state->count == 2){
        unregister_code (KC_PGUP);
    } else if (state->count == 3){
        unregister_code (KC_HOME);
    }
}

void dance_down_finished (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code (KC_DOWN);
    } else if (state->count == 2) {
        register_code (KC_PGDOWN);
    } else if (state->count == 3) {
        register_code (KC_END);
    }
}

void dance_down_reset (qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code (KC_DOWN);
    } else if (state->count == 2){
        unregister_code (KC_PGDOWN);
    } else if (state->count == 3){
        unregister_code (KC_END);
    }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [LSFT_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_LSHIFT, KC_CAPSLOCK), // Tap once for shift, twice for caps lock
    [TILDE_QUIT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_tilde_esc_finished, dance_tilde_esc_reset), // Tap once for escape, twice for alt+F4
    [UP]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_up_finished, dance_up_reset),
    [DOWN]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_down_finished, dance_down_reset),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_COLEMAK] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
    TD(TILDE_QUIT), KC_1,  KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_MINS,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_TAB,   KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                               KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN, KC_EQUAL,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_LCTL,   KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                               KC_H,    KC_N,    KC_E,    KC_I,    KC_O,   KC_QUOT,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
    TD(LSFT_CAPS),KC_Z,   KC_X,     KC_C,    KC_V,    KC_B,   KC_PIPE,          KC_MPLY,   KC_K,    KC_M,  KC_COMM,  KC_DOT,  KC_SLSH, KC_RSFT,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    WIN_SHRTCT,KC_SPACE, LOWER,                      RAISE, KC_SFTENT,KC_BSPC
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),

    [_MAC_COLEMAK] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______, _______,  _______, _______, _______, _______,                           _______,  _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, _______,  _______, _______, _______, _______,                           _______,  _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, _______,  _______, _______, _______, _______,                           _______,  _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______, _______,  _______, _______, _______, _______, _______,         _______, _______,  _______, _______, _______, _______, _______,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                    MAC_SHRTCT, _______, _______,                  _______, _______,  _______
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),
    // Not every game has remappable keys
    [_QWERTY_GAMING] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______, _______,  _______, _______, _______, _______,                           _______,  _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______,    KC_Q,   KC_W,    KC_E,   KC_R,     KC_T,                             _______,  _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                             _______,  _______, _______, _______, _______, DF(_COLEMAK),
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_8,           _______, _______,  _______, _______, _______, _______, DF(_MAC_COLEMAK),
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                        KC_6,  KC_SPACE,  KC_7,                    _______, _______,  _______
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),

    [_GAMING] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
       _______, _______,  _______, _______, _______, _______,                           _______,  _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, _______,  _______, _______, _______, _______,                           _______,  _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       _______, _______,  _______, _______, _______, _______,                           _______,  _______, _______, _______, _______, DF(_COLEMAK),
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
       _______, _______,  _______, _______, _______, _______, KC_8,            _______, _______,  _______, _______, _______, _______, DF(_MAC_COLEMAK),
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                        KC_6,  KC_SPACE,  KC_7,                    _______, _______,  _______
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),

    [_LOWER] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______,  _______, TD(UP),   _______, KC_LBRC,                           KC_RBRC,  KC_7,    KC_8,    KC_9,   KC_MINS, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, KC_LEFT, TD(DOWN), KC_RGHT, KC_LCBR,                            KC_RCBR,  KC_P4,   KC_P5,   KC_P6,  KC_PLUS, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, KC_LPRN, _______,          _______, KC_RPRN, KC_P1,    KC_P2,   KC_P3,  KC_EQL, _______,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      _______, _______,  LOWER,                      RAISE,   KC_P0,  KC_DOT
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),

    [_RAISE] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        KC_F12,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                            KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_MINS,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_EQUAL,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, _______,         _______, _______, _______, _______,  _______, KC_BSLS, KC_QUOT,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      _______,  _______, LOWER,                     RAISE,  _______, _______
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),

    [_ADJUST] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        EEP_RST, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, DF(_QWERTY_GAMING),
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        RESET,  _______,  _______, _______, _______, _______,                            _______, _______, KC_VOLU, _______, _______, DF(_GAMING),
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        EEP_RST, _______, _______, _______, _______, _______,                            _______,KC_MPRV, KC_VOLD, KC_MNXT, _______, DF(_COLEMAK),
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, _______, _______, _______, _______, _______, RGB_TOG,          RGB_MOD, _______, _______, _______, _______, _______, DF(_MAC_COLEMAK),
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      _______, _______, _______,                   _______, _______, _______
    //                               └────────┴────────┴────────┘                 └────────┴────────┴────────┘
        ),

        [_WIN_SHRTCT] = LAYOUT(
    //┌────────┬────────┬────────┬────────┬────────┬────────┐                          ┌────────┬────────┬────────┬────────┬────────┬────────┐
        _______, _______, _______, _______, W_QUIT, _______,                            _______, _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
       W_NXT_WIN,_______, _______, W_FIND, _______, _______,                            _______, _______, _______, _______, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______,W_SEL_ALL,_______, W_SAVE, W_REOPEN,_______,                            _______, _______, _______, _______, _______, _______,
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
      M_NXT_WIN, _______, _______, M_FIND, _______, _______,                            _______, M_SPEC_7,M_SPEC_8,M_SPEC_9, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┤                          ├────────┼────────┼────────┼────────┼────────┼────────┤
        _______,M_SEL_ALL,_______, M_SAVE, M_REOPEN, _______,                            _______,M_SPEC_4,M_SPEC_5,M_SPEC_6, _______, _______,
    //├────────┼────────┼────────┼────────┼────────┼────────┼────────┐        ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
        _______, M_UNDO,  M_CUT,   M_COPY, M_PASTE, M_FOLLOW, _______,          _______, _______,M_SPEC_1,M_SPEC_2,M_SPEC_3, _______, _______,
    //└────────┴────────┴────────┴───┬────┴───┬────┴───┬────┴───┬────┘        └───┬────┴───┬────┴───┬────┴───┬────┴────────┴────────┴────────┘
                                      _______, M_SEARCH, _______,                   _______, M_CREATE, _______
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
