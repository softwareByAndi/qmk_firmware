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

// #define TAPPING_TERM 150
static bool is_mac = false;

enum polyglot_layers {
   _KB_MAIN,
   _STENO,

   _NUM_SYM,
   _MACROS,
   _SETTINGS,
};

#define KB_MAIN DF(_KB_MAIN)
#define STENO DF(_STENO)

#define NUM_SYM MO(_NUM_SYM)
#define SETTINGS MO(_SETTINGS)
#define MACROS MO(_MACROS)

#define MY_DQOT LSFT(KC_QUOT)
#define MY_RCHV LSFT(KC_DOT)
#define MY_LCHV LSFT(KC_COMM)
#define ALT_SFT LALT(KC_LSFT)
#define CTL_SFT LCTL(KC_LSFT)
#define CTL_ALT LCTL(KC_LALT)

enum custom_keycodes {
   OS_MAC = SAFE_RANGE,
   OS_WIN,
   OSK_TST, // test key
   OSK_CTL, // ctrl for win and cmd for mac
   OSK_NXT, // ctrl on win and opt on mac (for skipping to next word using arrow keys)
   IS_QUOT,
   IS_BSLS,
   IS_MINS,
};

void ignore_shift(uint16_t keycode) {
   uint8_t mod_state = get_mods(); // Save the currently applied modifiers
   if (mod_state & MOD_MASK_SHIFT) {
      del_mods(MOD_MASK_SHIFT);
      tap_code(keycode);
      set_mods(mod_state); // Restore the original modifier state
   } else {
      tap_code(keycode);
   }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case OS_MAC:
         if (record->event.pressed) {
            is_mac = true;
         }
         return false;
      case OS_WIN:
         if (record->event.pressed) {
            is_mac = false;
         }
         return false;
      case OSK_CTL:
         if (record->event.pressed) {
            if (is_mac) {
                  register_code(KC_LGUI);
            } else {
                  register_code(KC_LCTL);
            }
         } else {
            if (is_mac) {
                  unregister_code(KC_LGUI);
            } else {
                  unregister_code(KC_LCTL);
            }
         }
         return false;
      case OSK_NXT:
         if (record->event.pressed) {
            if (is_mac) {
                  register_code(KC_LALT);
            } else {
                  register_code(KC_LCTL);
            }
         } else {
            if (is_mac) {
                  unregister_code(KC_LALT);
            } else {
                  unregister_code(KC_LCTL);
            }
         }
         return false;
      case OSK_TST:
         if (record->event.pressed) {
            // print current os mode
            if (is_mac) {
               SEND_STRING("MAC mode");
            } else {
               SEND_STRING("WIN mode");
            }
         }
         return false;
      case IS_QUOT:
         if (record->event.pressed) {
            ignore_shift(KC_QUOT);
         }
         return false;
      case IS_BSLS:
         if (record->event.pressed) {
            ignore_shift(KC_BSLS);
         }
         return false;
      case IS_MINS:
         if (record->event.pressed) {
            ignore_shift(KC_MINS);
         }
         return false;
    }

    return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

   [_KB_MAIN] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      KC_ESC,    KC_Q,    KC_W,    KC_E,  KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_TAB,    KC_A,    KC_S,    KC_D,  KC_F,    KC_G,        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_ENT,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      OSK_CTL,   KC_Z,    KC_X,    KC_C,  KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                  MACROS, NUM_SYM, KC_LSFT,     KC_SPC,  NUM_SYM, SETTINGS
                              //`--------------------------'   `--------------------------'
   ),

   [_STENO] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      XXXXXXX, STN_S1,  STN_TL,  STN_PL,  STN_HL,  STN_ST1,     STN_ST3,  STN_FR,  STN_PR,  STN_LR,  STN_TR,  STN_DR,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, STN_S2,  STN_KL,  STN_WL,  STN_RL,  STN_ST2,     STN_ST4,  STN_RR,  STN_BR,  STN_GR,  STN_SR,  STN_ZR,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      SETTINGS, KC_LSFT, KC_LCTL, KC_LALT, KC_LCMD, KC_SPC,     XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, NUM_SYM,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 STN_N1,  STN_A,   STN_O,       STN_E,    STN_U,   STN_N2
                              //`--------------------------'   `--------------------------'
   ),

   [_NUM_SYM] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.  ,-----------------------------------------------------.
      KC_LGUI,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
   //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
      KC_TAB,  KC_GRV,  KC_COMM, KC_SPC,  KC_DOT,  IS_QUOT,    KC_EQL,  IS_MINS, KC_UNDS, KC_LBRC, KC_RBRC, KC_DEL,
   //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, KC_SLSH, MY_DQOT, KC_SCLN,    KC_AMPR, KC_PIPE, MY_LCHV, MY_RCHV, IS_BSLS, _______,
   //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 _______, _______, KC_LSFT,    KC_RSFT, _______, KC_RALT
                              //`--------------------------'  `--------------------------'
   ),

   [_MACROS] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      KC_LGUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F5,       KC_F6, XXXXXXX,  KC_UP,  XXXXXXX,  XXXXXXX, LCTL(LALT(KC_DEL)),
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LCTL, KC_LALT, XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      OSK_NXT, XXXXXXX, KC_F5,   KC_F6,   XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, 
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______, XXXXXXX, XXXXXXX,     XXXXXXX, _______, SETTINGS
                              //`--------------------------'   `--------------------------'
   ),

   [_SETTINGS] = LAYOUT_split_3x6_3(
   //,-----------------------------------------------------.   ,-----------------------------------------------------.
      KC_MPLY, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  XXXXXXX,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLU, KC_MNXT,     XXXXXXX, XXXXXXX, XXXXXXX, OS_WIN,  OS_MAC,  OSK_TST,
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_MPRV,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KB_MAIN, STENO, 
   //|--------+--------+--------+--------+--------+--------|   |--------+--------+--------+--------+--------+--------|
                                 _______, XXXXXXX, XXXXXXX,     XXXXXXX, _______, _______
                              //`--------------------------'   `--------------------------'
   ),
};

