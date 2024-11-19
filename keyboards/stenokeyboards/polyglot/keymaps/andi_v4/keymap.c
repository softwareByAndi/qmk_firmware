/*
Copyright 2023 StenoKeyboards

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
# CHANGES MADE:
- swapped some keys around
- moved arrow keys to right side in NUMBERS layer
- remove transparent keys in NUMBERS layer
- remove transparent keys in SYMBOLS layer
- cleaned whitespace

- update STENO layout
   - add NUMBERS layer
   - add SYMBOLS layer
   - remove volume keys
   - remove arrow keys
- added SETTINGS layer 
   - F1-F10 keys
   - move layer toggles
      - QWERTY
      - STENO
- move all layer toggles into SETTINGS layer

- remove transparency in temp layers
*/

#include QMK_KEYBOARD_H

#define PAUSE KC_MEDIA_PLAY_PAUSE

enum polyglot_layers {
    _QWERTY,
    _QWERTY_WIN,
    _STENO,
    _NUMBERS,
    _SYMBOLS,
    _SETTINGS
};

#define NUMBERS MO(_NUMBERS)
#define SYMBOLS MO(_SYMBOLS)
#define SETTINGS MO(_SETTINGS)
#define QWERTY DF(_QWERTY)
#define QWERTY_WIN DF(_QWERTY_WIN)
#define STENO DF(_STENO)

enum custom_keycodes {
    SINGLE_QUOTE = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case SINGLE_QUOTE:
         // force single quote to be sent without shift
         if (record->event.pressed) {
            uint8_t mod_state = get_mods(); // Save the currently applied modifiers
            if (mod_state & MOD_MASK_SHIFT) {
                  del_mods(MOD_MASK_SHIFT);
                  tap_code(KC_QUOT);
                  set_mods(mod_state); // Restore the original modifier state
            } else {
                  tap_code(KC_QUOT);
            }
         }
         return false;
    }

    return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   [_QWERTY] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      KC_ESC,    KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,   KC_F,   KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LGUI,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX,  NUMBERS, KC_LSFT,    KC_SPC,  SYMBOLS,   KC_RALT
                              //`--------------------------'   `--------------------------'
   ),

   [_QWERTY_WIN] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LCTL, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______, _______, _______,     _______, _______, _______
                              //`--------------------------'   `--------------------------'
   ),

   [_STENO] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      XXXXXXX, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,     STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,     STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      SYMBOLS, KC_LSFT, KC_LCTL, KC_LALT, KC_LCMD, KC_SPC,      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NUMBERS,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 STN_N1,  STN_A,   STN_O,       STN_E,    STN_U,   STN_N2
                              //`--------------------------'   `--------------------------'
   ),

   [_NUMBERS] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.            ,-----------------------------------------------------.
      KC_LGUI,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                 KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
   //|--------+--------+--------+--------+--------+--------|            |--------+--------+--------+--------+--------+--------|
      KC_TAB,  XXXXXXX, XXXXXXX, KC_QUOT, KC_DOT,  SINGLE_QUOTE,     KC_EQL,  KC_MINS,  KC_UP,  KC_LBRC,  KC_RBRC, KC_DEL,
   //|--------+--------+--------+--------+--------+--------|            |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, KC_BSLS, _______,
   //|--------+--------+--------+--------+--------+--------|            |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, NUMBERS, KC_LSFT,              KC_SPC,  _______, KC_RALT
                              //`--------------------------'            `--------------------------'
   ),

   [_SYMBOLS] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     XXXXXXX, XXXXXXX, KC_PLUS, XXXXXXX, XXXXXXX, KC_BSPC,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_GRV,  KC_COMM, KC_SPC,  KC_DOT,  KC_QUOT,     KC_EQL,  KC_MINS, KC_UNDS, XXXXXXX, XXXXXXX, KC_ENT,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, KC_SLSH, XXXXXXX, KC_SCLN,     XXXXXXX, XXXXXXX, KC_AMPR, KC_PIPE, KC_BSLS, KC_TILD,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 SETTINGS, _______, KC_LSFT,    KC_SPC,  SYMBOLS, KC_RALT
                              //`--------------------------'   `--------------------------'
   ),

   [_SETTINGS] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      KC_MPLY, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLU, KC_MNXT,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_MPRV,     XXXXXXX, XXXXXXX, XXXXXXX, QWERTY_WIN, QWERTY, STENO, 
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______, XXXXXXX, XXXXXXX,     XXXXXXX, _______, XXXXXXX
                              //`--------------------------'   `--------------------------'
   ),

};

