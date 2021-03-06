#pragma once

#include "game_config.h"
#include "engine/texture.h"
#include "engine/button.h"
#include "random.h"

enum class game_state {
    MENU = 0,
    RUN = 1,
    GAME_OVER = 2
};

struct game {
    game();

    game(const game &) = delete;

    game &operator=(game) = delete;

    void run();

private:
    size_t score;
    size_t current_score = 0;
    const game_config &config;
    game_state state = game_state::MENU;

    button_textures textures;
    engine::texture normal;
    engine::texture hover;
    engine::texture active;
    engine::texture back_texture;
    engine::texture bird_texture;
    engine::texture tube_texture;

    random rnd;
};
