#ifndef SNOW_H
#define SNOW_H

#include "element.h"

class Snow: public Element {
public:
    const double FLAME = 1.0 / 32;
    const double POWDER = 1.0 / 3;
    const double MELT = 1.0 / 1024;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER)
            return;
        if ((sim->randf() < FLAME && sim->is_on_fire(row, col)) || sim->randf() < MELT) {
            sim->set_cell(row, col, 3);
            return;
        }
        bool bot_left = sim->is_swappable(row, col, row + 1, col - 1);
        bool bot = sim->is_swappable(row, col, row + 1, col);
        bool bot_right = sim->is_swappable(row, col, row + 1, col + 1);
        if (bot) {
            sim->move_and_swap(row, col, row + 1, col);
        } else if (bot_left && bot_right) {
            sim->move_and_swap(row, col, row + 1, col + (sim->randf() < 0.5 ? 1 : -1));
        } else if (bot_left) {
            sim->move_and_swap(row, col, row + 1, col - 1);
        } else if (bot_right) {
            sim->move_and_swap(row, col, row + 1, col + 1);
        }
    }

    double get_density() override {
        return 0.9;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.95;
    }
};

#endif // SNOW_H