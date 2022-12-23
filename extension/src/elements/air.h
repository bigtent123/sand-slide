#ifndef AIR_H
#define AIR_H

#include "element.h"

class Air: public Element {
public:
    const double DECAY = 1.0 / 360;
    const double MOVE = 1.0 / 4;
    const double FLAME = 1.0 / 16;

    void process(SandSimulation *sim, int row, int col) override {
        if (sim->randf() < DECAY) {
            sim->set_cell(row, col, 0);
        }
        if (sim->randf() < FLAME && sim->is_on_fire(row, col)) {
            sim->set_cell(row, col, 5);
        }

        int newRow = row + (int) (sim->randf() * 3) - 1;
        int newCol = col + (int) (sim->randf() * 3) - 1;

        if (sim->randf() < MOVE && sim->in_bounds(newRow, newCol) && 
        sim->randf() < 1.0 - sim->elements.at(sim->get_cell(newRow, newCol))->get_density() / 32.0) {
            sim->move_and_swap(row, col, newRow, newCol);
        } 
    }

    double get_density() override {
        return 32.0;
    }

    double get_explode_resistance() override {
        return 0.1;
    }

    double get_acid_resistance() override {
        return 0.1;
    }
};

#endif // AIR_H