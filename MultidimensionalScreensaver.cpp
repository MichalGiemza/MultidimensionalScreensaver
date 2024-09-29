#define ALLEGRO_UNSTABLE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <random>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "MultidimensionalScreensaver.h"
#include "Tools.h"
#include "Visualization.h"
#include "OptimizationMethod.h"
#include "GradientDescent.h"
#include "Simulation.h"

const int textLen = 100;
const char *l1 = "Algorithm: MDS            Optimization method: Gradient descent";
const char *l2_t = "Output dimension: 2D      Input shape: %dD %s";
const char *l3 = "Mapping...";
const char *cursor = "_";

const char *vshad = "vertex.hlsl";
const char *pshad = "pixel.hlsl";

const double tDrawingMax = 10;
const int msPerChar = 20;

// TODO: Amber screen style - background, lines, terminal text
// TODO: Dodać obrót do wyświetlania symulacji -------------------------------------------
// TODO: Pauza na spację / inny trigger / skrót klawiszowy

void abort_example(char const *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}

void init(ALLEGRO_DISPLAY *&display, ALLEGRO_FONT *&font, ALLEGRO_TIMER *&timer, ALLEGRO_EVENT_QUEUE *&queue, ALLEGRO_SHADER *&shader) {
    if (!al_init()) {
        abort_example("Could not init Allegro.\n");
    }
    al_init_font_addon();
    al_init_image_addon();
    al_install_mouse();
    al_install_keyboard();

    al_set_new_display_flags(ALLEGRO_PROGRAMMABLE_PIPELINE);

    display = al_create_display(displayWidth, displayHeight);
    if (!display) {
        abort_example("Error creating display\n");
    }

    // Shaders
    shader = al_create_shader(ALLEGRO_SHADER_HLSL);
    al_attach_shader_source_file(shader, ALLEGRO_VERTEX_SHADER, vshad);
    al_attach_shader_source_file(shader, ALLEGRO_PIXEL_SHADER, pshad);
    if (!al_build_shader(shader)) {
        abort_example("Could not build shaders.\n");
    } else {
        printf(al_get_shader_log(shader));
    }

    al_init_ttf_addon();
    if (!al_is_ttf_addon_initialized()) {
        abort_example("Could not init font addon.\n");
    }

    al_init_primitives_addon();
    if (!al_is_primitives_addon_initialized()) {
        abort_example("Could not init primitives addon.\n");
    }

    //font = al_create_builtin_font();
    font = al_load_ttf_font("courbd.ttf", 20, 0);
    timer = al_create_timer(1.0 / 60);

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    // Init random
    std::srand(std::time(0));
}

void generateText(char *l1, const char *shapeType, int shapeDimension) {
    sprintf_s(l1, textLen, l2_t, shapeDimension, shapeType);
}

void generateFrameText(char *buffer, char *src, int currChar, int maxChar, bool isLastLine = false) {
    sprintf_s(buffer, textLen, src);
    int n = std::min(currChar, maxChar);
    buffer[n] = '_';
    buffer[n + 1] = 0;

    if (currChar > maxChar and (currChar / 10) % 2 == 1)
        buffer[n] = 0;
    if (currChar > maxChar and not isLastLine)
        buffer[n] = 0;
}

int countChars(char *str) {
    int i = 0;
    while (str[i] != 0) { i++; }
    return i;
}

void textDrawing(ALLEGRO_FONT *font, const ALLEGRO_COLOR &colorBg, const ALLEGRO_COLOR &color, char *l2, double tNow, double tStarted, bool *simulate) {
    int currentChar = (tNow - tStarted) * 1000 / msPerChar;
    double x = 8, y = 60;
    double th = al_get_font_line_height(font);
    char buffer[textLen];
    *simulate = false;

    int l1_cn = countChars((char *)l1);
    generateFrameText(buffer, (char *)l1, currentChar, l1_cn);
    al_draw_textf(font, color, x, y, 0, buffer);
    currentChar -= l1_cn;
    if (currentChar <= 0)
        return;

    int l2_cn = countChars((char *)l2);
    generateFrameText(buffer, (char *)l2, currentChar, l2_cn);
    al_draw_textf(font, color, x, y + th, 0, buffer);
    currentChar -= l2_cn;
    if (currentChar <= 0)
        return;

    int l3_cn = countChars((char *)l3);
    generateFrameText(buffer, (char *)l3, currentChar, l3_cn, true);
    al_draw_textf(font, color, x, y + 2 * th, 0, buffer);
    currentChar -= l3_cn;

    *simulate = true;
}

void handleTimings(double &tNow, double &tRedraw, double &tStarted) {
    tNow = al_get_time();
    if (tRedraw <= tNow) {
        tStarted = tNow;
        tRedraw = tStarted + tDrawingMax;
    }
}

void handleSimulation(double &tNow, double &tRedraw, double &tStarted, Simulation **sim) {
    // Init new
    if (tNow == tStarted) {
        char *t = rand() % 2 ? (char *)hypercubeType : (char *)simplexType;
        int dim = t == hypercubeType ? 2 + rand() % 4 : 2 + rand() % 20;
        double step = 0.24875 * dim - 0.4875;
        double eps = -0.00012375 * dim + 0.0012475;
        *sim = new Simulation(dim, t, step, eps);
    }
    // Simulate
    (**sim).update();
}

void handleDrawingVisualization(double &tNow, double &tRedraw, double &tStarted, Simulation *sim, Visualization **v) {
    // Init new
    if (tNow == tStarted) {
        *v = new Visualization(sim);
    }
    // Draw
    (**v).draw();
}

int main(int argc, char **argv) {
    ALLEGRO_DISPLAY *display = nullptr;
    ALLEGRO_TIMER *timer = nullptr;
    ALLEGRO_EVENT_QUEUE *queue = nullptr;
    ALLEGRO_FONT *font = nullptr;
    ALLEGRO_SHADER *shader = nullptr;
    ALLEGRO_BITMAP *backbuffer = nullptr;
    bool redraw = true;
    Visualization *v = nullptr;
    Simulation *sim = nullptr;
    unsigned char *p;
    int x, y;
    char l2[textLen];
    double tNow = 0, tRedraw = 0, tStarted = 0;
    bool simulate = false;

    float u_time = 0.0;
    float resolution[2] = { (float)displayWidth, (float)displayHeight };
    int hour, min_, sec;
    float h[2], m[2], s[2] = { 0.0, 0.0 };
    int gmt = 2 * 3600;

    (void)argc;
    (void)argv;

    static float tints[3] =
    {
        1.0, 1.0, 1.0
    };

    init(display, font, timer, queue, shader);
    //al_use_shader(shader);

    while (true) {
        ALLEGRO_EVENT event;
        al_wait_for_event(queue, &event);

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                break;
        }
        if (event.type == ALLEGRO_EVENT_TIMER)
            redraw = true;

        if (redraw && al_is_event_queue_empty(queue)) {
            backbuffer = al_get_backbuffer(display);
            al_set_target_bitmap(backbuffer);

            al_set_shader_float_vector("tint", 3, tints, 1);

            al_clear_to_color(color3);
            //al_clear_to_color(al_map_rgb(0, 0, 0));
            //DEBUG LINES
            //al_draw_line(100, 100, 700, 100, al_map_rgb(255, 255, 0), 5);
            //al_draw_line(100, 200, 700, 200, al_map_rgb(255, 255, 0), 5);
            // Time handling
            handleTimings(tNow, tRedraw, tStarted);
            // Text drawing
            textDrawing(font, colorBg, color, l2, tNow, tStarted, &simulate); // TODO uncomment
            // Shape simulation and drawing
            handleSimulation(tNow, tRedraw, tStarted, &sim);
            generateText(l2, sim->getPolytope(), sim->getDimIn());
            handleDrawingVisualization(tNow, tRedraw, tStarted, sim, &v);

            // Finished, flip display
            al_flip_display();
            redraw = false;
        }

        // TODO: updated stress value with fading effect? (multiple lines like in LL chat)
    }

    al_destroy_font(font);

    return 0;
}