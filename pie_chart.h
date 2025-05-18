#ifndef PIE_CHART_H
#define PIE_CHART_H

// Pie Chart Functions
void pie_slice_draw(float startAngle, float sweepAngle, float height,
                    float r, float g, float b);
void pie_chart_disp();
void pie_chart_reshape(int w, int h);
void pie_chart_idle();
void pie_chart_init();

#endif

















