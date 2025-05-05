// !!! DO NOT ADD #pragma once !!! //


// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)
RGB_MATRIX_EFFECT(STATIC_WHITE)
RGB_MATRIX_EFFECT(the_matrix)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

#define _BL 0
#define _FN 1
#define _ESP 2
#define _VIM 3

extern bool repeat_use_register;
//extern keyrecord_t repeat_last_record;
extern uint8_t user_red_key_index;
extern uint8_t g_vim_count;
extern uint8_t rgb_current_layer;

// e.g: A simple effect, self-contained within a single method
static bool STATIC_WHITE(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);

#define F1 (g_led_config.matrix_co[0][1])
#define PSCR 13
#define SRLK 14
#define PAUS 15
#define GRV 16
#define blink (g_rgb_timer & (0x1 << 9))
  for (uint8_t i = led_min; i < led_max; i++) {
    if(i == PSCR || i == SRLK || i == PAUS){
      rgb_matrix_set_color(i, 0x0, 0x0, 0x0);
      continue;
    }

    //VIM mode
    if (rgb_current_layer == _VIM){
      if ( i == g_led_config.matrix_co[4][4] && blink) { //VIM Mode, blink V green
        rgb_matrix_set_color(i, 0x00, 0xaa, 0x00);
      }else if (g_vim_count > 1 && i == g_led_config.matrix_co[1][g_vim_count]){ //VIM count highligh number in red
        rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
      }else{
        rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
      }
 //   if ( i == user_red_key_index && (g_rgb_timer & (0x1 << 9) ) ) { //Recording, blink @
 //     rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
 //   //} else if (i == r && repeat_use_register){ //Register value
 //   //  rgb_matrix_set_color(i, 0xff, 0x00, 0x00);
    }else if (rgb_current_layer == _FN){
      if (i == F1){
        rgb_matrix_set_color(i, 0xff, 0x33, 0x33);
      }else{
        rgb_matrix_set_color(i, 0x33, 0x33, 0xff);
      }
    }else if (rgb_current_layer == _ESP){
      if (i == GRV && blink){
        rgb_matrix_set_color(i, 0x00, 0x00, 0xff);
      }else{
        rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
      }
    }else{
      if (g_vim_count > 1 && i == g_led_config.matrix_co[1][g_vim_count]){ //VIM count highligh number in green
          rgb_matrix_set_color(i, 0x00, 0xff, 0x00);
      }else{
        rgb_matrix_set_color(i, 0xff, 0xff, 0xff);
      }
    }
  }
  return led_max < DRIVER_LED_TOTAL;
}

static bool the_matrix(effect_params_t* params) {
  RGB_MATRIX_USE_LIMITS(led_min, led_max);
#define THE_MATRIX_COL 0
#define THE_MATRIX_START 1
#define THE_MATRIX_END 2
#define THE_MATRIX_ROWS_COUNT 5
#define THE_MATRIX_COLS_COUNT 12
  static uint8_t green_rows[3][3] = { 
    [0] = { 4, 0, 3 },
    [1] = { 8, 0, 5 },
    [2] = { 12, 0, 2 }
  };

  uint16_t time      = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 4);
 
  for (uint8_t i = led_min; i < led_max; i++) {
    RGB_MATRIX_TEST_LED_FLAGS();
    rgb_matrix_set_color(i, 0x00, 0x00, 0x00);
  }
  //FillGreen
  for(uint8_t i = 0; i < 3; i++){
    uint8_t col = green_rows[i][THE_MATRIX_COL];
    for(uint8_t j = green_rows[i][THE_MATRIX_START]; j <= green_rows[i][THE_MATRIX_END]; j++){
      if(j>=0){
        uint8_t led_i = g_led_config.matrix_co[j][col];
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(led_i, 0x00, 0x33, 0x00);
      }
    }

    if ( !(time % 10) ) { 
      green_rows[i][THE_MATRIX_END] = green_rows[i][THE_MATRIX_END] + 1;
      if(green_rows[i][THE_MATRIX_END] > THE_MATRIX_ROWS_COUNT){
        green_rows[i][THE_MATRIX_COL] = (green_rows[i][THE_MATRIX_COL] + 1) % THE_MATRIX_COLS_COUNT; 
        //green_rows[i][THE_MATRIX_COL] = rand() % THE_MATRIX_COLS_COUNT; 
        green_rows[i][THE_MATRIX_START] = 0;
        green_rows[i][THE_MATRIX_END] = 1;
      }
    }
  }

  return led_max < DRIVER_LED_TOTAL;
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
