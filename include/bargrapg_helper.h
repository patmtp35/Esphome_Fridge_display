#include "esphome.h"

using namespace esphome;

void draw_bargraph(Display *it,
                   float value,
                   float min_val,
                   float max_val,
                   int x,
                   int y,
                   int bar_width,
                   int bar_height,
                   int step,
                   int segments,               // ⚡ Nouveau : nombre de segments
                   Color low_color,
                   Color mid_color,
                   Color high_color,
                   Color background = Color(0,0,0))   // ⚡ Nouveau : fond (effacement)
{
    // Sécurisation de la valeur
    if (value < min_val) value = min_val;
    if (value > max_val) value = max_val;

    // Pourcentage 0 → 1
    float pct = (value - min_val) / (max_val - min_val);
    int bars = (int)(pct * segments);

    // 🔥 Efface la zone avant de redessiner
    it->filled_rectangle(x, y, segments * step, bar_height, background);

    // 🔥 Calcul des transitions de couleurs
    int low_limit  = segments * 0.3;   // 30%
    int mid_limit  = segments * 0.6;   // 60%

    for (int i = 0; i < bars; i++) {
        Color col;
        if (i < low_limit)      col = low_color;
        else if (i < mid_limit) col = mid_color;
        else                    col = high_color;

        it->filled_rectangle(x + (i * step), y, bar_width, bar_height, col);
    }
}
