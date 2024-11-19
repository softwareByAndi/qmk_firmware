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
- moved arrow keys to right side in RAISE layer
- remove transparent keys in RAISE layer
- remove transparent keys in LOWER layer
- cleaned whitespace

- update STENO layout
   - add RAISE layer
   - add LOWER layer
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

enum polyglot_layers {
    _QWERTY,
    _STENO,
    _RAISE,
    _LOWER,
    _SETTINGS
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define SETTINGS MO(_SETTINGS)
#define QWERTY DF(_QWERTY)
#define STENO DF(_STENO)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   [_QWERTY] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      KC_ESC,    KC_Q,    KC_W,    KC_E,   KC_R,   KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,   KC_F,   KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 KC_LGUI,  RAISE,  KC_LSFT,     KC_SPC,  LOWER,   KC_RALT
                              //`--------------------------'   `--------------------------'
   ),

   [_STENO] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      XXXXXXX, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,     STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,     STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      LOWER,   KC_LSFT, KC_LCTL, KC_LALT, KC_LCMD, KC_SPC,      XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RAISE,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 STN_N1,  STN_A,   STN_O,       STN_E,    STN_U,   STN_N2
                              //`--------------------------'   `--------------------------'
   ),

   [_RAISE] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      KC_LGUI,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_TAB,   KC_A,   KC_S,    KC_D,    XXXXXXX, XXXXXXX,     KC_MINS, KC_PLUS,  KC_UP,  XXXXXXX,  XXXXXXX, KC_DEL,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    XXXXXXX,     KC_UNDS, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, RAISE,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 KC_LGUI, RAISE,   KC_LSFT,     KC_SPC, SETTINGS, KC_RALT
                              //`--------------------------'   `--------------------------'
   ),

   [_LOWER] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_GRV,  KC_COMM,  KC_DOT, KC_SLSH, KC_QUOT,     KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_ENT,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      LOWER,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SCLN,     KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 KC_LGUI, SETTINGS, KC_LSFT,    KC_SPC,  LOWER,   KC_RALT
                              //`--------------------------'   `--------------------------'
   ),

   [_SETTINGS] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, QWERTY,  STENO,   XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, STENO,   QWERTY,  _______, 
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, SETTINGS, XXXXXXX,    XXXXXXX, SETTINGS, XXXXXXX
                              //`--------------------------'   `--------------------------'
   ),

};

