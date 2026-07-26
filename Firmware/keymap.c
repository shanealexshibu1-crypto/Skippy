#include QMK_KEYBOARD_H
#include <math.h>

enum custom_keycodes {
    RGB_THEME_CYCLE_NEXT = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        /* esc, F1-F12 */
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        /* ` 1-9 0 - = delete */
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_DEL,
        /* tab qwertyuiop [ ] backslash */
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        /* caps asdfghjkl ; ' enter */
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        /* shift zxcvbnm , . / shift, up */
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        /* ctrl opt cmd space cmd opt fn, left down right */
        KC_LCTL, KC_LALT, KC_LGUI, KC_SPC, KC_RGUI, KC_RALT, MO(1), KC_LEFT, KC_DOWN, KC_RGHT
    ),
    
    [1] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};


enum combo_events { FN_SPACE_RGB_CYCLE };

const uint16_t PROGMEM fn_space_combo[] = {MO(1), KC_SPC, COMBO_END};

combo_t key_combos[] = {
    [FN_SPACE_RGB_CYCLE] = COMBO(fn_space_combo, RGB_THEME_CYCLE_NEXT),
};

static uint8_t rgb_theme_index = 0; 

static void apply_rgb_theme(uint8_t index) {
    switch (index) {
        case 0:
            rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
            rgb_matrix_sethsv(0, 0, 0); // off
            break;
        case 1:
            rgb_matrix_enable();
            rgb_matrix_mode(RGB_MATRIX_SPLASH);
            rgb_matrix_sethsv(0, 0, 255); 
            break;
        case 2:
            rgb_matrix_enable();
            rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
            rgb_matrix_sethsv(0, 255, 255);
            break;
    }
}


#define S1_PIN GP22
#define S1_DEBOUNCE_MS 20

static bool     s1_last_state  = false; 
static uint32_t s1_last_change = 0;

void keyboard_post_init_user(void) {
    setPinInputHigh(S1_PIN); 
}

void matrix_scan_user(void) {
    bool pressed = !readPin(S1_PIN); // active low
    if (pressed != s1_last_state && timer_elapsed32(s1_last_change) > S1_DEBOUNCE_MS) {
        s1_last_state  = pressed;
        s1_last_change = timer_read32();
        if (pressed) {
            tap_code(KC_MUTE);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGB_THEME_CYCLE_NEXT:
            if (record->event.pressed) {
                rgb_theme_index = (rgb_theme_index + 1) % 3;
                apply_rgb_theme(rgb_theme_index);
            }
            return false;
    }
    return true;
}

static const unsigned char PROGMEM hat_frame_rest[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xC0,
    0xE0, 0xF0, 0xF8, 0xFC, 0xFC, 0xFE, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFE, 0xFE, 0xFE, 0xFC, 0xFC, 0xF8, 0xF0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E,
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3E, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x78, 0xFC, 0xFC,
    0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
    0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC,
    0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0x7C, 0x78, 0x30, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#define HAT_W 56
#define HAT_H 26
#define HAT_X 36 
#define HAT_BASE_Y 20 

#define HAT_BOUNCE_MAX 14 
static const int8_t  hat_y_offsets[]     = {0, -3, -10, -4, 2, -1, 0};  
static const uint8_t hat_scale_percent[] = {100, 110, 100, 108, 80, 105, 100}; 

#define HAT_BOB_INTERVAL_MS 200 

static uint32_t bob_timer = 0;
static uint8_t  bob_step  = 0;


static void clear_hat_region(void) {
    for (uint8_t y = HAT_BASE_Y - HAT_BOUNCE_MAX; y < HAT_BASE_Y + HAT_H + HAT_BOUNCE_MAX; y++) {
        for (uint8_t x = HAT_X; x < HAT_X + HAT_W; x++) {
            oled_write_pixel(x, y, false);
        }
    }
}

static void draw_hat(const unsigned char *frame, int8_t y_offset, uint8_t scale_percent) {
    uint8_t scaled_h = (HAT_H * scale_percent) / 100;
    for (uint8_t y = 0; y < scaled_h; y++) {
        uint8_t src_y = (uint8_t)(((uint16_t)y * HAT_H) / scaled_h);
        uint8_t page  = src_y / 8;
        uint8_t bit   = src_y % 8;
        for (uint8_t x = 0; x < HAT_W; x++) {
            uint8_t byte = pgm_read_byte(&frame[page * HAT_W + x]);
            bool    on   = byte & (1 << bit);
            if (on) {
                oled_write_pixel(HAT_X + x, HAT_BASE_Y + y_offset + y, true);
            }
        }
    }
}

#define BOX_X0 28
#define BOX_Y0 0
#define BOX_X1 100 e
#define BOX_Y1 63

static float wave_offset = 0.0f;

static void draw_box(void) {
    for (uint8_t x = BOX_X0; x <= BOX_X1; x++) {
        oled_write_pixel(x, BOX_Y0, true);
        oled_write_pixel(x, BOX_Y1, true);
    }
    for (uint8_t y = BOX_Y0; y <= BOX_Y1; y++) {
        oled_write_pixel(BOX_X0, y, true);
        oled_write_pixel(BOX_X1, y, true);
    }
}

static void draw_waves(void) {
    
    for (uint8_t x = 0; x < BOX_X0 - 1; x++) {
        int y1 = 50 + (int)(sin(x * 0.3f + wave_offset) * 4);
        int y2 = 54 + (int)(cos(x * 0.24f - wave_offset * 0.7f) * 3);
        for (uint8_t y = y1; y < 64; y++) oled_write_pixel(x, y, true);
        for (uint8_t y = y2; y < 64; y++) oled_write_pixel(x, y, true);
    }
    for (uint8_t x = BOX_X1 + 2; x < 128; x++) {
        uint8_t xi = x - (BOX_X1 + 2);
        int     y1 = 50 + (int)(sin(xi * 0.3f + wave_offset) * 4);
        int     y2 = 54 + (int)(cos(xi * 0.24f - wave_offset * 0.7f) * 3);
        for (uint8_t y = y1; y < 64; y++) oled_write_pixel(x, y, true);
        for (uint8_t y = y2; y < 64; y++) oled_write_pixel(x, y, true);
    }
    wave_offset += 0.15f;
}

bool oled_task_user(void) {
    uint8_t wpm = get_current_wpm();

    
    draw_box();

    
    draw_waves();

    
    char wpm_buf[10];
    snprintf(wpm_buf, sizeof(wpm_buf), "WPM: %u", wpm);
    uint8_t text_col = (21 - (uint8_t)strlen(wpm_buf)) / 2; 
    oled_set_cursor(text_col > 21 ? 0 : text_col, 0);
    oled_write(wpm_buf, false);

    
    if (timer_elapsed32(bob_timer) > HAT_BOB_INTERVAL_MS) {
        bob_timer = timer_read32();
        bob_step  = (bob_step + 1) % (sizeof(hat_y_offsets) / sizeof(hat_y_offsets[0]));
    }
    clear_hat_region();
    draw_hat(hat_frame_rest, hat_y_offsets[bob_step], hat_scale_percent[bob_step]);

    
    oled_set_cursor(6, 7);
    oled_write("ONE PIECE", false);

    return false;
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}