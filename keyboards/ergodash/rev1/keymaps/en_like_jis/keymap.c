#include QMK_KEYBOARD_H

// レイヤーの名前を定義。
enum layer_names {
    _BASE,
    _SHIFT,
    _CURSOR,
    _CURSFT
};

// カスタムキーコードはここに定義。挙動は、process_record_user関数で実装。
enum custom_keycodes {
    CK_LSFT = SAFE_RANGE,
    CK_RSFT
};

// 各レイヤーごとのキー配置を定義。
// 使用可能なキーコードの一覧は以下。
// https://docs.qmk.fm/#/ja/keycodes
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,--------------------------------------------------.                    ,--------------------------------------------------.
   * |   `  |   1  |   2  |   3  |    4   |   5  |  F5  |                    |  F2  |   6  |    7   |   8  |   9  |   0  |  -   |
   * |------+------+------+------+--------+------+------|                    |------+------+--------+------+------+------+------|
   * |  ESC |   q  |   w  |   e  |    r   |   t  |  F6  |                    |  F10 |   y  |    u   |   i  |   o  |   p  |  =   |
   * |------+------+------+------+--------+------+------|                    |------+------+--------+------+------+------+------|
   * |  Tab |   a  |   s  |   d  |    f   |   g  |  F8  |                    |  F12 |   h  |    j   |   k  |   l  |   ;  |  '   |
   * |------+------+------+------+--------+------+-------------.      ,------+------+------+--------+------+------+------+------|
   * | CTRL |   z  |   x  |   c  |    v   |   b  |      |VD_PRV|      |VD_NXT|      |   n  |    m   |   ,  |   .  |   /  |  \   |
   * |-------------+------+------+--------+------|      |------|      ,------|      |------+--------+------+------+------+------|
   * | ---- |  GUI |  DEL ||||||||Alt/MHEN|CK_SFT| Space|CURSOR|      |CURSOR| Enter|CK_SFT|Alt/HENK||||||||   [  |  ]   | PSCR |
   * ,---------------------------------------------------------.      ,---------------------------------------------------------.
   */
  [_BASE] = LAYOUT(
     S(KC_LBRC), KC_1   , KC_2  , KC_3  , KC_4           , KC_5    , KC_F5                                       , KC_F2  , KC_6    , KC_7           , KC_8    , KC_9   , KC_0   , KC_MINS   , \
     KC_ESC    , KC_Q   , KC_W  , KC_E  , KC_R           , KC_T    , KC_F6                                       , KC_F10 , KC_Y    , KC_U           , KC_I    , KC_O   , KC_P   , S(KC_MINS), \
     KC_TAB    , KC_A   , KC_S  , KC_D  , KC_F           , KC_G    , KC_F8                                       , KC_F12 , KC_H    , KC_J           , KC_K    , KC_L   , KC_SCLN, S(KC_7)   , \
     KC_LCTL   , KC_Z   , KC_X  , KC_C  , KC_V           , KC_B             , G(C(KC_LEFT))       , G(C(KC_RGHT))         , KC_N    , KC_M           , KC_COMM , KC_DOT , KC_SLSH, KC_JYEN   , \
     KC_NO     , KC_LGUI, KC_DEL        , LALT_T(KC_MHEN), CK_LSFT , KC_SPC , MO(_CURSOR)         , MO(_CURSOR)  , KC_ENT , CK_RSFT , RALT_T(KC_HENK)          , KC_RBRC, KC_BSLS, KC_PSCR     \
  ),
  /* Shift_layer(Shiftキー押したとき)
   * ,------------------------------------------------.                    ,------------------------------------------------.
   * |  ~   |   !  |   @  |   #  |   $  |   %  |      |                    |      |   ^  |   &  |   *  |   (  |   )  |  _   |
   * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
   * |      |   Q  |   W  |   E  |   R  |   T  |      |                    |      |   Y  |   U  |   I  |   O  |   P  |  +   |
   * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
   * |      |   A  |   S  |   D  |   F  |   G  |      |                    |      |   H  |   J  |   K  |   L  |   :  |  "   |
   * |------+------+------+------+------+------+------|------.      ,------+------+------+------+------+------+------+------|
   * |      |   Z  |   X  |   C  |   V  |   B  |      |VD_CLS|      |VD_NEW|      |   N  |   M  |   <  |   >  |   ?  |  |   |
   * |-------------+------+------+------+------|      |------|      |------|      |------+------+------+------+------+------|
   * |      |      |      ||||||||      |      |      |CURSFT|      |CURSFT|      |      |      ||||||||   {  |  }   |      |
   * ,-------------------------------------------------------.      ,-------------------------------------------------------.
   */
  [_SHIFT] = LAYOUT(
    S(KC_EQL) ,S(KC_1)   ,KC_LBRC   ,S(KC_3)   ,S(KC_4)   ,S(KC_5)   ,S(KC_F5)                               , S(KC_F2)  ,KC_EQL   ,S(KC_6)   ,S(KC_QUOT),S(KC_8)   ,S(KC_9)   ,S(KC_RO)  , \
    S(KC_ESC) ,S(KC_Q)   ,S(KC_W)   ,S(KC_E)   ,S(KC_R)   ,S(KC_T)   ,S(KC_F6)                               , S(KC_F10) ,S(KC_Y)  ,S(KC_U)   ,S(KC_I)   ,S(KC_O)   ,S(KC_P)   ,S(KC_SCLN), \
    S(KC_TAB) ,S(KC_A)   ,S(KC_S)   ,S(KC_D)   ,S(KC_F)   ,S(KC_G)   ,S(KC_F8)                               , S(KC_F12) ,S(KC_H)  ,S(KC_J)   ,S(KC_K)   ,S(KC_L)   ,KC_QUOT   ,S(KC_2)   , \
    S(KC_LCTL),S(KC_Z)   ,S(KC_X)   ,S(KC_C)   ,S(KC_V)   ,S(KC_B)              ,G(C(KC_F4))    , G(C(KC_D))             ,S(KC_N)  ,S(KC_M)   ,S(KC_COMM),S(KC_DOT) ,S(KC_SLSH),S(KC_JYEN), \
    _______   ,S(KC_LGUI),S(KC_DEL)            ,S(KC_LALT),_______   ,S(KC_SPC) ,MO(_CURSFT)    , MO(_CURSFT),S(KC_ENT)  ,_______  ,S(KC_RALT)           ,S(KC_RBRC),S(KC_BSLS),_______     \
  ),
  /* Cursor(E=MC^2押したとき)
   * ,------------------------------------------------.                    ,------------------------------------------------.
   * |  F11 |  F1  |  F2  |  F3  |  F4  |  F5  |      |                    |      |  F6  |  F7  |  F8  |  F9  |  F10 |  F12 |
   * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
   * | SLEEP|      |      |      |      |      |      |                    |      | Home | PgDw | PgUp |  End |      |      |
   * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
   * |TSK_VW|      |      |      |      |      |      |                    |      | Left | Down |  Up  | Right|      |      |
   * |------+------+------+------+------+------+------+------.      ,------+------+------+------+------+------+------+------|
   * | C+A+D|      |      |      |      |      |      |      |      |      |      |   {  |   }  |   [  |   ]  |      |      |
   * |-------------+------+------+------+------|      |------|      |------|      |------+------+------+------+------+------|
   * |      |      |      ||||||||      |CURSFT|      |      |      |      | BSPC |CURSFT|      ||||||||      |      |      |
   * ,-------------------------------------------------------.      ,-------------------------------------------------------.
   */
  [_CURSOR] = LAYOUT(
    KC_F11     , KC_F1  , KC_F2  , KC_F3  , KC_F4   , KC_F5      , _______                          , _______, KC_F6     , KC_F7      , KC_F8  , KC_F9  , KC_F10 , KC_F12 , \
    KC_SLEP    , _______, _______, _______, _______ , _______    , _______                          , _______, KC_HOME   , KC_PGDN    , KC_PGUP, KC_END , _______, _______, \
    G(KC_TAB)  , _______, _______, _______, _______ , _______    , _______                          , _______, KC_LEFT   , KC_DOWN    , KC_UP  , KC_RGHT, _______, _______, \
    LCA(KC_DEL), _______, _______, _______, _______ , _______             , _______        , _______         , S(KC_RBRC), S(KC_BSLS) , KC_RBRC, KC_BSLS, _______, _______, \
    _______    , _______, _______         , _______ , MO(_CURSFT), _______, _______        , _______, KC_BSPC, MO(_CURSFT), _______            , _______, _______, _______  \
  ),
  /* Cursor Shift(ShiftとE=MC^2の同時押し)
   * ,------------------------------------------------.                    ,------------------------------------------------.
   * |↑F11 | ↑F1 | ↑F2 | ↑F3 | ↑F4 | ↑F5 |      |                    |      | ↑F6 | ↑F7 | ↑F8 | ↑F9 |↑F10 |↑F12 |
   * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |↑HOME|↑PGDW|↑PGUP|↑END |      |      |
   * |------+------+------+------+------+------+------|                    |------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |                    |      |↑LEFT|↑DOWN| ↑UP |↑RGHT|      |      |
   * |------+------+------+------+------+------+------+------.      ,------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * |-------------+------+------+------+------|      |------|      |------|      |------+------+------+------+------+------|
   * |      |      |      ||||||||      |      |      |      |      |      |↑BSPC|      |      ||||||||      |      |      |
   * ,-------------------------------------------------------.      ,-------------------------------------------------------.
   */
  [_CURSFT] = LAYOUT(
    S(KC_F11), S(KC_F1), S(KC_F2), S(KC_F3), S(KC_F4), S(KC_F5), _______                        , _______   , S(KC_F6)   , S(KC_F7)   , S(KC_F8)   , S(KC_F9)   , S(KC_F10) , S(KC_F12) , \
    _______  , _______ , _______ , _______ , _______ , _______ , _______                        , _______   , S(KC_HOME) , S(KC_PGDN) , S(KC_PGUP) , S(KC_END)  , _______   , _______   , \
    _______  , _______ , _______ , _______ , _______ , _______ , _______                        , _______   , S(KC_LEFT) , S(KC_DOWN) , S(KC_UP)   , S(KC_RGHT) , _______   , _______   , \
    _______  , _______ , _______ , _______ , _______ , _______          , _______,       _______            , _______    , _______    , _______    , _______    , _______   , _______   , \
    _______  , _______ , _______           , _______ , _______ , _______, _______,       _______, S(KC_BSPC), _______    , _______                 , _______    , _______   , _______     \
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool pressed_ck_lsft;
    static bool pressed_ck_rsft;

    switch (keycode) {
        case CK_LSFT:
            pressed_ck_lsft = record->event.pressed;
            if (record->event.pressed) {
                // when key is pressed
                // Shiftレイヤーを有効にしつつ、Shiftキーをプレス
                layer_on(_SHIFT);
                register_code(KC_LSHIFT);
            } else {
                // when keycode QMKBEST is released
                // Shiftレイヤーを無効にしつつ、Shiftキーをリリース
                if (!pressed_ck_rsft) { layer_off(_SHIFT); }
                unregister_code(KC_LSHIFT);
            }
            break;
        case CK_RSFT:
            pressed_ck_rsft = record->event.pressed;
            if (record->event.pressed) {
                // when key is pressed
                // Shiftレイヤーを有効にしつつ、Shiftキーをプレス
                layer_on(_SHIFT);
                register_code(KC_RSHIFT);
            } else {
                // when keycode QMKBEST is released
                // Shiftレイヤーを無効にしつつ、Shiftキーをリリース
                if (!pressed_ck_lsft) { layer_off(_SHIFT); }
                unregister_code(KC_RSHIFT);
            }
            break;
        default:
            // カスタムShiftキーが押されてたら、追加の動作を行う
            if (pressed_ck_lsft || pressed_ck_rsft) {
                if (record->event.pressed) {
                    // when key is pressed
                    // Shiftキーをリリースする
                    if (pressed_ck_lsft) { unregister_code(KC_LSHIFT); }
                    if (pressed_ck_rsft) { unregister_code(KC_RSHIFT); }
            } else {
                    // when keycode QMKBEST is released
                    // Shiftキーをプレスする
                    if (pressed_ck_lsft) { register_code(KC_LSHIFT); }
                    if (pressed_ck_rsft) { register_code(KC_RSHIFT); }
                }
            }
            break;
    }
    return true;
}

