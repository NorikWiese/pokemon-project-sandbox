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

AI_SINGLE_BATTLE_TEST("basic AI would explode")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(50); HP(100); Nature(NATURE_QUIRKY); Ability(ABILITY_TELEPATHY); Speed(58); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(50); Nature(NATURE_QUIRKY); Ability(ABILITY_INNER_FOCUS); Speed(251); Moves(MOVE_RETALIATE, MOVE_SLASH, MOVE_EXPLOSION); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_RETALIATE,  (AI_SCORE_DEFAULT));
            SCORE_EQ_VAL(opponent, MOVE_SLASH,      (AI_SCORE_DEFAULT));
            SCORE_EQ_VAL(opponent, MOVE_EXPLOSION,  (AI_SCORE_DEFAULT));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes trapping moves")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_BIND; }
    PARAMETRIZE { move = MOVE_WRAP; }
    PARAMETRIZE { move = MOVE_FIRE_SPIN; }
    PARAMETRIZE { move = MOVE_CLAMP; }
    PARAMETRIZE { move = MOVE_WHIRLPOOL; }
    PARAMETRIZE { move = MOVE_SAND_TOMB; }
    PARAMETRIZE { move = MOVE_MAGMA_STORM; }
    PARAMETRIZE { move = MOVE_INFESTATION; }
    PARAMETRIZE { move = MOVE_SNAP_TRAP; }
    PARAMETRIZE { move = MOVE_THUNDER_CAGE; }

    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Level(50); HP(100); Nature(NATURE_QUIRKY); Ability(ABILITY_TELEPATHY); Speed(58); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(50); Nature(NATURE_QUIRKY); Ability(ABILITY_INNER_FOCUS); Speed(251); Moves(MOVE_HYPER_BEAM, move); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, move,  (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes status moves")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Level(50); HP(100); Nature(NATURE_QUIRKY); Ability(ABILITY_TELEPATHY); Speed(58); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(50); Nature(NATURE_QUIRKY); Ability(ABILITY_INNER_FOCUS); Speed(251); Moves(MOVE_WILL_O_WISP, MOVE_THUNDER_WAVE, MOVE_FLAMETHROWER); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_WILL_O_WISP,    (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_BEATS_COMPETITORS));
            SCORE_EQ_VAL(opponent, MOVE_THUNDER_WAVE,   (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_BEATS_COMPETITORS));
            SCORE_EQ_VAL(opponent, MOVE_FLAMETHROWER,   (AI_SCORE_DEFAULT));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes protecting")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_PROTECT; }
    PARAMETRIZE { move = MOVE_DETECT; }
    PARAMETRIZE { move = MOVE_KINGS_SHIELD; }
    PARAMETRIZE { move = MOVE_SPIKY_SHIELD; }
    PARAMETRIZE { move = MOVE_BANEFUL_BUNKER; }
    PARAMETRIZE { move = MOVE_OBSTRUCT; }
    PARAMETRIZE { move = MOVE_SILK_TRAP; }
    PARAMETRIZE { move = MOVE_BURNING_BULWARK; }

    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Level(50); HP(100); Nature(NATURE_QUIRKY); Ability(ABILITY_TELEPATHY); Speed(58); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(50); Nature(NATURE_QUIRKY); Ability(ABILITY_INNER_FOCUS); Speed(251); Moves(MOVE_HYPER_BEAM, move); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, move,  (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE));
        }
    }
}