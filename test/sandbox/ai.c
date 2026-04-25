#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"

AI_SINGLE_BATTLE_TEST("No Ai -> all default")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Moves(MOVE_RETALIATE, MOVE_SLASH, MOVE_PROTECT, MOVE_SWORDS_DANCE); }
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
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Moves(MOVE_RETALIATE, MOVE_SLASH, MOVE_EXPLOSION, MOVE_PROTECT); }
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
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Moves(move, MOVE_HYPER_BEAM, MOVE_PROTECT, MOVE_ELECTRIC_TERRAIN); }
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
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Moves(MOVE_WILL_O_WISP, MOVE_THUNDER_WAVE, MOVE_FLAMETHROWER, MOVE_HYPER_BEAM); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_WILL_O_WISP,    (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_BEATS_COMPETITORS));
            SCORE_EQ_VAL(opponent, MOVE_THUNDER_WAVE,   (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_BEATS_COMPETITORS));
            SCORE_EQ_VAL(opponent, MOVE_FLAMETHROWER,   (AI_SCORE_DEFAULT));
            SCORE_EQ_VAL(opponent, MOVE_HYPER_BEAM,     (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE));
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
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Moves(MOVE_HYPER_BEAM, move); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, move,  (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes screens but not when brick break etc.")
{
    enum Move move;
    
    PARAMETRIZE { move = MOVE_DEFOG; }
    PARAMETRIZE { move = MOVE_BRICK_BREAK; }
    PARAMETRIZE { move = MOVE_PSYCHIC_FANGS; }
    PARAMETRIZE { move = MOVE_RAGING_BULL; }

    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE, move); }
        OPPONENT(SPECIES_KANGASKHAN) { Moves(MOVE_REFLECT, MOVE_LIGHT_SCREEN); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_REFLECT,        (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + ((move != MOVE_DEFOG) ? AI_SCORE_LOSES_TO_COMPETITORS : 0)));
            SCORE_EQ_VAL(opponent, MOVE_LIGHT_SCREEN,   (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + ((move != MOVE_DEFOG) ? AI_SCORE_LOSES_TO_COMPETITORS : 0)));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes terrains")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_MISTY_TERRAIN; }
    PARAMETRIZE { move = MOVE_GRASSY_TERRAIN; }
    PARAMETRIZE { move = MOVE_ELECTRIC_TERRAIN; }
    PARAMETRIZE { move = MOVE_PSYCHIC_TERRAIN; }

    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Moves(MOVE_HYPER_BEAM, move); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, move,  (AI_SCORE_DEFAULT + AI_SCORE_COMPETES_WITH_SLOW_KILL));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes fake out but only turn 1")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Moves(MOVE_FAKE_OUT); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_FAKE_OUT,  (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_COMPETES_WITH_SLOW_KILL));
        }
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_FAKE_OUT,  AI_SCORE_DEFAULT);
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI sees slow kills")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { HP(1); Speed(2); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Speed(1); Moves(MOVE_PROTECT, MOVE_TACKLE, MOVE_FLAMETHROWER); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_PROTECT,        (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE));
            SCORE_EQ_VAL(opponent, MOVE_TACKLE,         (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_SLOW_KILL));
            SCORE_EQ_VAL(opponent, MOVE_FLAMETHROWER,   (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_SLOW_KILL));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI sees fast kills")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { HP(1); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Speed(2); Moves(MOVE_PROTECT, MOVE_TACKLE, MOVE_FLAMETHROWER); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_PROTECT,        (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE));
            SCORE_EQ_VAL(opponent, MOVE_TACKLE,         (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_FAST_KILL));
            SCORE_EQ_VAL(opponent, MOVE_FLAMETHROWER,   (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_FAST_KILL));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI understands Sturdy")
{
    KNOWN_FAILING;
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Level(1); Ability(ABILITY_STURDY); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(50); Moves(MOVE_PROTECT, MOVE_TACKLE, MOVE_FLAMETHROWER); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_PROTECT,        (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE));
            SCORE_EQ_VAL(opponent, MOVE_TACKLE,         (AI_SCORE_DEFAULT));
            SCORE_EQ_VAL(opponent, MOVE_FLAMETHROWER,   (AI_SCORE_DEFAULT));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI understands nothing kills and picks highest damage move")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Moves(MOVE_PROTECT, MOVE_TACKLE, MOVE_HYPER_BEAM); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_PROTECT,        (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE));
            SCORE_EQ_VAL(opponent, MOVE_TACKLE,         (AI_SCORE_DEFAULT));
            SCORE_EQ_VAL(opponent, MOVE_HYPER_BEAM,     (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI rolls damage and thus only sees kill sometimes")
{
    PASSES_RANDOMLY(5, 10, RNG_AI_DAMAGE_ROLL);
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Level(100); Speed(1); HP(124); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(100); Speed(2); Moves(MOVE_HYPER_BEAM); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, MOVE_HYPER_BEAM, (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_FAST_KILL));
            //SCORE_EQ_VAL(opponent, MOVE_TACKLE, (AI_SCORE_DEFAULT));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes Explosion depending on HP percent (<10 percent)")
{
    enum Move move;
    
    PARAMETRIZE { move = MOVE_EXPLOSION; }
    PARAMETRIZE { move = MOVE_SELF_DESTRUCT; }
    PARAMETRIZE { move = MOVE_MISTY_EXPLOSION; }

    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Level(100); Speed(2); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(100); Speed(1); MaxHP(100); HP(9); Moves(move); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
                                         //default
                                                             // Explosion AI
            SCORE_EQ_VAL(opponent, move, (AI_SCORE_DEFAULT + AI_SCORE_COMPETES_WITH_SLOW_KILL + AI_SCORE_BEATS_COMPETITORS));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes Explosion depending on HP percent (<33 percent)")
{
    enum Move move;
    
    PARAMETRIZE { move = MOVE_EXPLOSION; }
    PARAMETRIZE { move = MOVE_SELF_DESTRUCT; }
    PARAMETRIZE { move = MOVE_MISTY_EXPLOSION; }

    PASSES_RANDOMLY(7, 10, RNG_EXPLOSION_CHANCE);
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Level(100); Speed(2); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(100); Speed(1); MaxHP(100); HP(15); Moves(move); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
                                         //default
                                                            // Explosion AI
            SCORE_EQ_VAL(opponent, move, (AI_SCORE_DEFAULT + 8));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes Explosion depending on HP percent (<66 percent)")
{
    enum Move move;
    
    PARAMETRIZE { move = MOVE_EXPLOSION; }
    PARAMETRIZE { move = MOVE_SELF_DESTRUCT; }
    PARAMETRIZE { move = MOVE_MISTY_EXPLOSION; }

    PASSES_RANDOMLY(3, 10, RNG_EXPLOSION_CHANCE);
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Level(100); Speed(2); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(100); Speed(1); MaxHP(100); HP(50); Moves(move); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
                                         //default
                                                             // Explosion AI
            SCORE_EQ_VAL(opponent, move, (AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_BEATS_COMPETITORS));
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes Explosion depending on HP percent (Full HP)")
{
    enum Move move;
    
    PARAMETRIZE { move = MOVE_EXPLOSION; }
    PARAMETRIZE { move = MOVE_SELF_DESTRUCT; }
    PARAMETRIZE { move = MOVE_MISTY_EXPLOSION; }

    PASSES_RANDOMLY(1, 20, RNG_EXPLOSION_CHANCE);
    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Level(100); Speed(2); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Level(100); Speed(1); MaxHP(100); HP(100); Moves(MOVE_TACKLE, move, MOVE_PROTECT, MOVE_ACROBATICS); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            //SCORE_EQ_VAL(opponent, MOVE_TACKLE, AI_SCORE_DEFAULT);
                                         //default
                                                            // Explosion AI
            SCORE_EQ_VAL(opponent, move, AI_SCORE_DEFAULT + AI_SCORE_GOOD_MOVE + AI_SCORE_BEATS_COMPETITORS);
            EXPECT_MOVE(opponent, move);
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI likes Tailwind/Trick Room when slower")
{
    enum Move move;
    
    PARAMETRIZE { move = MOVE_TAILWIND; }
    PARAMETRIZE { move = MOVE_TRICK_ROOM; }

    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Speed(2); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Speed(1); MaxHP(100); HP(100); Moves(MOVE_TACKLE, move, MOVE_PROTECT, MOVE_ACROBATICS); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, move, AI_SCORE_DEFAULT + AI_SCORE_COMPETES_WITH_SLOW_KILL);
            EXPECT_MOVE(opponent, move);
        }
    }
}

AI_SINGLE_BATTLE_TEST("AI doesnt like Tailwind/Trick Room when faster")
{
    enum Move move;
    
    PARAMETRIZE { move = MOVE_TAILWIND; }
    PARAMETRIZE { move = MOVE_TRICK_ROOM; }

    GIVEN {
        AI_FLAGS(AI_FLAG_STANDARD_TRAINER);
        PLAYER(SPECIES_WOBBUFFET) { Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_KANGASKHAN) { Speed(2); MaxHP(100); HP(100); Moves(MOVE_TACKLE, move, MOVE_PROTECT, MOVE_ACROBATICS); }
    } WHEN {
        TURN {
            MOVE(player, MOVE_TACKLE);
            SCORE_EQ_VAL(opponent, move, AI_SCORE_DEFAULT);
        }
    }
}