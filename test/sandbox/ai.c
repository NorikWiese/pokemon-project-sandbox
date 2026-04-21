#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"

AI_SINGLE_BATTLE_TEST("No Ai -> all default")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(50); HP(100); Nature(NATURE_QUIRKY); Ability(ABILITY_TELEPATHY); Speed(58); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(50); Nature(NATURE_QUIRKY); Ability(ABILITY_INNER_FOCUS); Speed(251); Moves(MOVE_RETALIATE, MOVE_SLASH); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_RETALIATE,  (AI_SCORE_DEFAULT));
            SCORE_EQ_VAL(opponent, MOVE_SLASH,      (AI_SCORE_DEFAULT));
        }
    }
}