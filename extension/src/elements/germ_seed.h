#ifndef GERMINATED_SEED_H
#define GERMINATED_SEED_H

#include "element.h"

class GerminatedSeed: public Element {
public:
    const double GROW = 1.0 / 1024;
    const double FLAME = 1.0 / 48;
    const double POWDER = 1.0 / 1.3;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() >= POWDER)
            return;

        // Catch on fire
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
            return;
        } else if (sim->is_poisoned(row, col)) {
            sim->set_cell(row, col, 16);
            return;
        }

        sim->move_and_swap(row, col, row + 1, col);

        // Turn into grass
        if (sim->randf() < GROW && sim->touch_count(row, col, 11) > 0) {
            sim->set_cell(row, col, 14);
        } 
    }

    double get_density() override {
        return 2.0;
    }

    double get_explode_resistance() override {
        return 0.05;
    }

    double get_acid_resistance() override {
        return 0.05;
    }
};

#endif // GERMINATED_SEED_H