#pragma once

#include <exception>

class FishCaughtException: public std::exception {
public:
    const char* what() const noexcept override {
        return "Fish caught!";
    }
};

class BootCaughtException: public std::exception {
public:
    const char* what() const noexcept override {
        return "Boot caught...";
    }
};