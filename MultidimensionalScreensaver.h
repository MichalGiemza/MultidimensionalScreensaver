#pragma once

void abort_example(char const *format, ...);
void init(ALLEGRO_DISPLAY *&display, ALLEGRO_FONT *&font, ALLEGRO_TIMER *&timer, ALLEGRO_EVENT_QUEUE *&queue);
void handleTimings(double &tNow, double &tRedraw, double &tStarted);
void textDrawing(ALLEGRO_FONT *font, const ALLEGRO_COLOR &colorBg, const ALLEGRO_COLOR &color, char *l2, double tNow, double tStarted, bool *simulate);
