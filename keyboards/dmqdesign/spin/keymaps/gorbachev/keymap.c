

#include QMK_KEYBOARD_H

enum layers {
    _NUMPAD,
    _RGB,
    _MACRO
};
enum custom_keycodes {
    HELLO_WORD = SAFE_RANGE,
    HELLO = SAFE_HELLO,
    LUL = SAFE_LUL,
    MUCHATECLA = SAFE_MUCHATECLA,
    CRY = SAFE_CRY,
    FACEPALM = SAFE_FACEPALM,
    OMG = SAFE_OMG,
    HAHASWEAT = SAFE_HAHASWEAT
};
//The below layers are intentionally empty in order to give a good starting point for how to configure multiple layers.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_NUMPAD] = LAYOUT(/* Base */
                KC_7, KC_8, KC_9, TO(_NUMPAD),
                KC_4, KC_5, KC_6, TO(_RGB),
                KC_1, KC_2, KC_3, TO(_MACRO),
                KC_0, KC_DOT, KC_ENTER
                ),
    [_RGB] = LAYOUT(/* Base: First key reset SPIN */
                RESET, KC_NO, KC_NO, KC_TRNS,
                KC_NO, KC_NO, KC_NO, KC_TRNS,
                KC_NO, KC_NO, KC_NO, KC_TRNS,
                RGB_RMOD, RGB_TOG, RGB_MOD
                ),

    [_MACRO] = LAYOUT(/* Base */
                HELLO, LUL, CRY, KC_TRNS,
                FACEPALM, OMG, MUCHATECLA, KC_TRNS,
                HAHASWEAT, KC_F17, KC_F18, KC_TRNS,
                KC_F13, KC_F14, KC_F15
                )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HELLO:
            if (record->event.pressed) {
                SEND_STRING("nik005Yee ");
            }
            break;
        case LUL:
            if (record->event.pressed) {
                SEND_STRING("nik005LUL ");
            }
            break;
        case CRY:
            if (record->event.pressed) {
                SEND_STRING("nik005Cry ");
            }
            break;
        case FACEPALM:
            if (record->event.pressed) {
                SEND_STRING("nik005Palm ");
            }
            break;
        case OMG:
            if (record->event.pressed) {
                SEND_STRING("nik005OMG ");
            }
            break;
        case MUCHATECLA:
            if (record->event.pressed) {
                SEND_STRING("uryftwMUCHA uryftwTECLA ");
            }
            break;
        case HAHASWEAT:
            if (record->event.pressed) {
                SEND_STRING("HahaSweat ");
            }
            break;
    }

    return true;
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        switch (get_highest_layer(layer_state)) {     //break each encoder update into a switch statement for the current layer
            case _NUMPAD:
                if (clockwise) {
                    // Key code Arrow Down
                    tap_code(KC_UP);
                } else {
                    // Key code Arrow UP
                    tap_code(KC_DOWN);
                }
                break;
            case _RGB:
                if (clockwise) {
                    rgblight_increase_hue();
                } else {
                    rgblight_decrease_hue();
                }
                break;
            case _MACRO:
                if (clockwise) {
                    // Media forward
                    tap_code(KC_MFFD);
                    break;
                } else {
                    // Media rewind
                    tap_code(KC_MRWD);
                    break;
                }
                break;
        }
    } else if (index == 1) { /* Second encoder */
        switch (get_highest_layer(layer_state)) {
            case _NUMPAD:
                if (clockwise) {
                    // Key press Page Down
                    tap_code(KC_PGDN);
                } else {
                    // Key press Page UP
                    tap_code(KC_PGUP);
                }
                break;
            case _RGB:
                if (clockwise) {
                    rgblight_increase_sat();
                } else {
                    rgblight_decrease_sat();
                }
                break;
            case _MACRO:
                if (clockwise) {
                    // Next Song
                    tap_code(KC_MNXT);
                    break;
                } else {
                    // Previous Song
                    tap_code(KC_MPRV);
                    break;
                }
                break;
        }
    } else if (index == 2) { /* Third encoder */
        switch (get_highest_layer(layer_state)) {
            case _NUMPAD:
                if (clockwise) {
                    // Mouse wheel UP
                    tap_code(KC_WH_U);
                } else {
                    // Mouse wheel Down
                    tap_code(KC_WH_D);
                }
                break;
            case _RGB:
                if (clockwise) {
                    rgblight_increase_val();
                } else {
                    rgblight_decrease_val();
                }
                break;
            case _MACRO:
                if (clockwise) {
                    // Volume UP
                    tap_code(KC_VOLU);
                    break;
                } else {
                    // Volume Down
                    tap_code(KC_VOLD);
                    break;
                }
                break;
        }
    }
}

layer_state_t layer_state_set_user(layer_state_t state) { //This will run every time the layer is updated
    switch (get_highest_layer(state)) {
        case _NUMPAD:
            setrgb(RGB_WHITE, &led[0]); //Set the top LED to white for the bottom layer
            setrgb(0, 0, 0, &led[1]);
            setrgb(0, 0, 0, &led[2]);
            break;
        case _RGB:
            setrgb(0, 0, 0, &led[0]); //Set the middle LED to white for the middle layer
            setrgb(RGB_WHITE, &led[1]);
            setrgb(0, 0, 0, &led[2]);
            break;
        case _MACRO:
            setrgb(0, 0, 0, &led[0]);
            setrgb(0, 0, 0, &led[1]);
            setrgb(RGB_WHITE, &led[2]); //Set the bottom LED to white for the top layer
            break;
    }
    rgblight_set();
    return state;
}

#ifdef OLED_DRIVER_ENABLE

static const char *ANIMATION_NAMES[] = {"unknown",
	"static",
	"breathing I",
	"breathing II",
	"breathing III",
	"breathing IV",
	"rainbow I",
	"rainbow II",
	"rainbow III",
	"rainbow2 I",
	"rainbow2 II",
	"rainbow2 III",
	"rainbow2 IV",
	"rainbow2 V",
	"rainbow2 VI",
	"snake I",
	"snake II",
	"snake III",
	"snake IV",
	"snake V",
	"snake VI",
	"knight I",
	"knight II",
	"knight III",
	"christmas",
	"static I",
	"static II",
	"static III",
	"static IV",
	"static V",
	"static VI",
	"static VII",
	"static VIII",
	"static IX",
	"static X",
	"rgb test",
	"alternating",
	"twinkle I",
	"twinkle II",
	"twinkle III",
	"twinkle IV",
	"twinkle V",
	"twinkle VI"
};

void rgblight_get_mode_name(uint8_t mode, size_t bufsize, char *buf) {
    snprintf(buf, bufsize, "%-25s", ANIMATION_NAMES[mode]);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
#ifdef LEFT_HAND
    return OLED_ROTATION_180;
#else
    return OLED_ROTATION_0;
#endif
}

void oled_task_user(void) {
    // Host Keyboard Layer Status
    // Translate to desired language
    oled_write_P(PSTR("Capa: "), false);

    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            oled_write_P(PSTR("Numericos\n"), false);
            break;
        case _RGB:
            oled_write_P(PSTR("Lucesitas\n"), false);
            break;
        case _MACRO:
            oled_write_P(PSTR("Cositas\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    static char rgb_mode_name[30];
    rgblight_get_mode_name(rgblight_get_mode(), sizeof(rgb_mode_name), rgb_mode_name);

    oled_write_P(PSTR("Modo: "), false);
    oled_write_ln(rgb_mode_name, false);

    oled_write_ln("PoisonIvy13", false);

}
#endif
