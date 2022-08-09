#include <iostream>
#include <ctime>
#include "FishingExceptions.h"

enum SectorContent: uint8_t {
    EMPTY,
    BOOT,
    FISH
};

SectorContent Puddle[3][3];

void display_puddle() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            SectorContent val = Puddle[i][j];
            switch(val) {
                case SectorContent::EMPTY: std::cout << '0'; break;
                case SectorContent::BOOT: std::cout << 'L'; break;
                case SectorContent::FISH: std::cout << '&'; break;
                default: std::cout << '?';
            }
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

void init_game() {
    std::srand(std::time(nullptr));

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            Puddle[i][j] = SectorContent::EMPTY;
        }
    }

    int free_cells[9] = {0,1,2,3,4,5,6,7,8};
    int pos, cell, remain = 9;

    pos = rand() % remain;
    cell = free_cells[pos];
    --remain;
    std::swap(free_cells[pos], free_cells[remain]);
    Puddle[cell / 3][cell % 3] = SectorContent::FISH;

    for (int i = 0; i < 3; ++i) {
        pos = rand() % remain;
        cell = free_cells[pos];
        --remain;
        std::swap(free_cells[pos], free_cells[remain]);
        Puddle[cell / 3][cell % 3] = SectorContent::BOOT;
    }
}

void process_selection(int cell) {
    if (cell < 0 || cell > 8) throw std::invalid_argument("cell");

    SectorContent val = Puddle[cell / 3][cell % 3];
    switch(val) {
        case SectorContent::EMPTY: std::cout << "Nothing in this sector. Try another." << std::endl; break;
        case SectorContent::BOOT: throw BootCaughtException();
        case SectorContent::FISH: throw FishCaughtException();
        default: std::cout << '?';
    }
}

int main() {
    init_game();
    display_puddle(); // for debug purposes
    while(true) {
        std::cout << "Choose puddle for fishing (1-9):" << std::endl;
        int cell;
        std::cin >> cell;
        --cell;
        try {
            process_selection(cell);
        } catch (const BootCaughtException& exc) {
            std::cout << exc.what() << std::endl;
            return 0;
        } catch (const FishCaughtException& exc) {
            std::cout << exc.what() << std::endl;
            return 0;
        } catch (const std::invalid_argument& exc) {
            std::cout << "Puddle number must be in range [1-9]." << std::endl;
        }
    }
}
