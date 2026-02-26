#include "Board/Config.h"
#if defined(CONFIG_EN_RGB)

#include <hardware/gpio.h>

#include "Board/Pico_WS2812/WS2812.hpp"
#include "Board/board_api_private/board_api_private.h"

namespace board_api_rgb {

WS2812& get_ws2812(WS2812::DataFormat format) {
#if defined(GRB_PXL_PIN)
    static WS2812 ws2812_grb = WS2812(GRB_PXL_PIN, 1, pio1, 1, WS2812::FORMAT_GRB);
#endif
#if defined(RGB_PXL_PIN)
    static WS2812 ws2812_rgb = WS2812(RGB_PXL_PIN, 1, pio1, 0, WS2812::FORMAT_RGB);
#endif

#if defined(RGB_PXL_PIN)
    if (format == WS2812::FORMAT_RGB) return ws2812_rgb;
#endif
#if defined(GRB_PXL_PIN)
    return ws2812_grb;
#endif
}

void init() {
#if defined(RGB_PWR_PIN)
    gpio_init(RGB_PWR_PIN);
    gpio_set_dir(RGB_PWR_PIN, GPIO_OUT);
    gpio_put(RGB_PWR_PIN, 1);
#endif

    set_led(0xFF, 0, 0);
}

void set_led(uint8_t r, uint8_t g, uint8_t b) {
#if defined(RGB_PXL_PIN)
    get_ws2812(WS2812::FORMAT_RGB).setPixelColor(0, WS2812::RGB(r, g, b));
    get_ws2812(WS2812::FORMAT_RGB).show();
#elif defined(GRB_PXL_PIN)
    get_ws2812(WS2812::FORMAT_GRB).setPixelColor(0, WS2812::RGB(g, r, b));
    get_ws2812(WS2812::FORMAT_GRB).show();
#endif
}

} // namespace board_api_rgb

#endif // defined(CONFIG_EN_RGB)
