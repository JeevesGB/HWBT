/*
 * trs_layout.c
 * Auto-converted from TRS UI layout definition (VERSION 9.279, MODE 1)
 * Defines leaderboard/results screen layout for a racing game.
 * Targets: XENON (Xbox 360), PS2, WII, PC — all at their native resolutions.
 */

#include <stddef.h>

/* -------------------------------------------------------------------------
 * Platform / resolution definitions
 * ---------------------------------------------------------------------- */

typedef enum {
    PLATFORM_XENON   = 0,   /* 1280 x 720  */
    PLATFORM_PS2     = 1,   /*  640 x 480  */
    PLATFORM_WII     = 2,   /*  640 x 480  */
    PLATFORM_PC      = 3,   /* 1280 x 720  */
    PLATFORM_DEFAULT = 4,   /*  640 x 480  */
    PLATFORM_COUNT   = 5
} Platform;

typedef struct {
    Platform    id;
    int         width;
    int         height;
} PlatformDef;

static const PlatformDef g_platforms[PLATFORM_COUNT] = {
    { PLATFORM_XENON,   1280, 720 },
    { PLATFORM_PS2,      640, 480 },
    { PLATFORM_WII,      640, 480 },
    { PLATFORM_PC,      1280, 720 },
    { PLATFORM_DEFAULT,  640, 480 },
};

/* -------------------------------------------------------------------------
 * Camera
 * ---------------------------------------------------------------------- */

typedef struct {
    int   id;                   /* camera slot index            */
    int   params[5];            /* generic int params (-1 = unused) */
    float pos[3];               /* world position x,y,z         */
    float rot[9];               /* 3x3 rotation matrix (row-major) */
    float fov;                  /* field-of-view in degrees      */
    int   extra[4];             /* misc flags / refs (-1 = none) */
} Camera;

static const Camera g_camera = {
    .id     = 1,
    .params = { -1, -1, -1, -1, -1 },
    .pos    = { 0.0f, 0.0f, 0.0f },
    .rot    = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    },
    .fov    = 45.0f,
    .extra  = { 0, -1, -1, -1 }
};

/* -------------------------------------------------------------------------
 * Flash (sprite sheet / animation strip definitions)
 * Each entry references a named Flash symbol and its frame ranges.
 * ---------------------------------------------------------------------- */

#define FLASH_MAX_FRAMES 48

typedef struct {
    const char *name;
    float       framerate;          /* frames per second           */
    int         unknown_a;          /* field 2 (always 23 here)    */
    int         unknown_b;          /* field 3 (always 0 here)     */
    int         frames[FLASH_MAX_FRAMES]; /* frame indices          */
    int         last_frame;         /* final / wrap-to frame       */
    int         loop;               /* 1 = looping, 0 = one-shot   */
} FlashDef;

/* Total number of Flash symbols defined in the source */
#define FLASH_COUNT 8

static const FlashDef g_flash[FLASH_COUNT] = {
    {
        "TRS_back",
        60.0f, 23, 0,
        { 106,109,192,199,222, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        229, 1
    },
    {
        "TRS_header",
        60.0f, 23, 0,
        { 106,109,192,199,222, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        229, 0
    },
    {
        "TRS_arrangement",
        60.0f, 23, 0,
        { 1,2,3,4,5, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        6, 0
    },
    {
        "TRS_stats",
        60.0f, 23, 0,
        { 47,50,59,66,89, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        90, 1
    },
    {
        "TRS_positions",
        60.0f, 23, 0,
        { 259,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        260, 0
    },
    {
        "TRS_button",
        60.0f, 23, 0,
        { 24,25,34,40,60, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
        64, 0
    },
    {
        "TRS_arrow",
        60.0f, 23, 0,
        {
            24,24,99,99,124, 0,0,0,0,0,0,
            276,301,149,224,250,275,125,149,224,249,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        },
        302, 0
    },
    {
        "TRS_arrow_0",
        60.0f, 23, 0,
        {
            24,24,99,99,124, 0,0,0,0,0,0,
            276,301,149,224,250,275,125,149,224,249,
            0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
        },
        302, 0   /* no trailing loop flag in source — treated as 0 */
    },
};

/* -------------------------------------------------------------------------
 * Per-platform rectangle: x, y, z(depth), w, h
 * ---------------------------------------------------------------------- */

typedef struct {
    float x, y, z, w, h;
} PlatformRect;

typedef struct {
    PlatformRect r[PLATFORM_COUNT]; /* indexed by Platform enum */
} MultiRect;

/* -------------------------------------------------------------------------
 * Flash Dialogs  (UI element layout descriptors)
 *
 * Each dialog entry is represented as a tagged union / discriminated struct.
 * The raw format is complex and context-sensitive; we capture the essentials:
 *   - dialog_type  : leading integer flag
 *   - id / ref     : integer identifiers / component references
 *   - label        : optional string label (NULL if absent)
 *   - rect         : per-platform bounding rectangles
 * ---------------------------------------------------------------------- */

typedef struct {
    int        dialog_type;
    int        ref_a;
    int        ref_b;
    int        ref_c;
    const char *label;          /* NULL when no label present */
    MultiRect  rect;
} FlashDialog;

/* Helper macro: fill a MultiRect with (x,y,z,w,h) per platform.
   Order: XENON, PS2, WII, PC, DEFAULT                                   */
#define MRECT(xe_x,xe_y,xe_z,xe_w,xe_h, \
              p2_x,p2_y,p2_z,p2_w,p2_h, \
              pc_x,pc_y,pc_z,pc_w,pc_h, \
              df_x,df_y,df_z,df_w,df_h) \
    { { \
        { xe_x, xe_y, xe_z, xe_w, xe_h }, /* XENON   */ \
        { p2_x, p2_y, p2_z, p2_w, p2_h }, /* PS2     */ \
        { p2_x, p2_y, p2_z, p2_w, p2_h }, /* WII = PS2 */ \
        { pc_x, pc_y, pc_z, pc_w, pc_h }, /* PC      */ \
        { df_x, df_y, df_z, df_w, df_h }  /* DEFAULT */ \
    } }

/* Dialog table — one entry per FLASHDIALOGS block element.
   Entries with only Default -1 -1 (component refs, no rect) are
   represented with all rect fields set to -1.                           */

static const FlashDialog g_dialogs[] = {

    /* --- Outer background panel --- */
    { 20, 0, -1, 0, NULL,
      MRECT(180.0f,  0.0f, 85.5f, 920.0f, 549.0f,
             67.5f,  0.0f, 87.5f, 505.0f, 305.0f,
            180.0f,  0.0f, 85.5f, 920.0f, 549.0f,
             67.5f,  0.0f, 87.5f, 505.0f, 305.0f) },

    /* --- Inner panel --- */
    { 0, 2, -1, 1, NULL,
      MRECT(180.0f,  8.0f, 85.0f, 920.0f, 549.0f,
             67.0f,  7.0f, 87.0f, 506.0f, 305.0f,
            180.0f,  8.0f, 85.0f, 920.0f, 549.0f,
             67.0f,  7.0f, 87.0f, 506.0f, 305.0f) },

    /* --- name_text component ref (no rect) --- */
    { 0, -1, -1, -1, "name_text",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* --- Heading label --- */
    { 0, -1, 0, 2, "Heading Here",
      MRECT(950.0f, 20.0f, 349.0f,  90.0f,  51.0f,
            473.0f, 19.0f, 242.0f,  50.0f,  28.0f,
            950.0f, 20.0f, 349.0f,  90.0f,  51.0f,
            473.0f, 19.0f, 242.0f,  50.0f,  28.0f) },

    /* ---- Rank rows 5 → 1 (arrangement + position + vehicle + player + points each) ---- */

    /* Rank 5 — arrangement component ref */
    { 0, -1, -1, -1, "arrangement",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 5 — row background strip */
    { 0, 2, -1, 3, NULL,
      MRECT(185.0f,  57.0f, 545.0f, 910.0f, 100.0f,
             70.0f,  56.0f, 350.0f, 499.0f,  55.0f,
            185.0f,  57.0f, 545.0f, 910.0f, 100.0f,
             70.0f,  56.0f, 350.0f, 499.0f,  55.0f) },

    /* Rank 5 — position component ref */
    { 1, -1, -1, -1, "position",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 5 — position icon rect */
    { 0, -1, 4, -1, NULL,
      MRECT(  0.0f, 22.0f,   0.0f,  94.0f,  60.0f,
               0.0f, 21.0f,   0.0f,  51.0f,  32.0f,
               0.0f, 22.0f,   0.0f,  94.0f,  60.0f,
               0.0f, 21.0f,   0.0f,  51.0f,  32.0f) },

    /* Rank 5 — vehicle component ref (id 502) */
    { 2, -1, -1, -1, "vehicle",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 5 — player component ref (id 503) */
    { 0, -1, -1, -1, "player",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 5 — points component ref (id 505) */
    { 0, -1, -1, -1, "points",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 5 — points label "+x" */
    { 0, 5, -1, 2, "+x",
      MRECT(595.0f,  62.0f, 270.0f,  90.0f,  51.0f,
            295.0f,  61.0f, 190.0f,  50.0f,  28.0f,
            595.0f,  62.0f, 270.0f,  90.0f,  51.0f,
            295.0f,  61.0f, 190.0f,  50.0f,  28.0f) },

    /* Rank 4 — arrangement */
    { 0, -1, -1, -1, "arrangement",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 4 — row strip */
    { 0, 2, -1, 3, NULL,
      MRECT(185.0f,  99.0f, 246.0f, 910.0f, 100.0f,
             70.5f,  98.0f, 175.0f, 499.0f,  55.0f,
            185.0f,  99.0f, 246.0f, 910.0f, 100.0f,
             70.5f,  98.0f, 175.0f, 499.0f,  55.0f) },

    /* Rank 4 — position ref */
    { 1, -1, -1, -1, "position",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 4 — position icon */
    { 0, -1, 4, -1, NULL,
      MRECT(  0.0f, 64.0f,   0.0f,  94.0f,  60.0f,
               0.0f, 63.0f,   0.0f,  51.0f,  32.0f,
               0.0f, 64.0f,   0.0f,  94.0f,  60.0f,
               0.0f, 63.0f,   0.0f,  51.0f,  32.0f) },

    /* Rank 4 — vehicle ref (id 402) */
    { 2, -1, -1, -1, "vehicle",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 4 — player ref (id 403) */
    { 0, -1, -1, -1, "player",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 4 — points ref (id 405) */
    { 0, -1, -1, -1, "points",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 4 — points label "+x" */
    { 0, 5, -1, 2, "+x",
      MRECT(595.0f, 104.0f, 360.0f,  90.0f,  51.0f,
            295.0f, 103.0f, 235.0f,  50.0f,  28.0f,
            595.0f, 104.0f, 360.0f,  90.0f,  51.0f,
            295.0f, 103.0f, 235.0f,  50.0f,  28.0f) },

    /* Rank 3 — arrangement */
    { 0, -1, -1, -1, "arrangement",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 3 — row strip */
    { 0, 2, -1, 3, NULL,
      MRECT(185.0f, 141.0f, 327.0f, 910.0f, 100.0f,
             70.5f, 140.0f, 216.0f, 499.0f,  55.0f,
            185.0f, 141.0f, 327.0f, 910.0f, 100.0f,
             70.5f, 140.0f, 216.0f, 499.0f,  55.0f) },

    /* Rank 3 — position ref */
    { 1, -1, -1, -1, "position",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 3 — position icon */
    { 0, -1, 4, -1, NULL,
      MRECT(  0.0f, 106.0f,  0.0f,  94.0f,  60.0f,
               0.0f, 105.0f,  0.0f,  51.0f,  32.0f,
               0.0f, 106.0f,  0.0f,  94.0f,  60.0f,
               0.0f, 105.0f,  0.0f,  51.0f,  32.0f) },

    /* Rank 3 — vehicle ref (id 302) */
    { 2, -1, -1, -1, "vehicle",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 3 — player ref (id 303) */
    { 0, -1, -1, -1, "player",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 3 — points ref (id 305) */
    { 0, -1, -1, -1, "points",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 3 — points label "+x" */
    { 0, 5, -1, 2, "+x",
      MRECT(595.0f, 146.0f, 450.0f,  90.0f,  51.0f,
            295.0f, 145.0f, 280.0f,  50.0f,  28.0f,
            595.0f, 146.0f, 450.0f,  90.0f,  51.0f,
            295.0f, 145.0f, 280.0f,  50.0f,  28.0f) },

    /* Rank 2 — arrangement */
    { 0, -1, -1, -1, "arrangement",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 2 — row strip */
    { 0, 2, -1, 3, NULL,
      MRECT(185.0f, 183.0f, 391.0f, 910.0f, 100.0f,
             70.5f, 182.0f, 267.0f, 499.0f,  55.0f,
            185.0f, 183.0f, 391.0f, 910.0f, 100.0f,
             70.5f, 182.0f, 267.0f, 499.0f,  55.0f) },

    /* Rank 2 — position ref */
    { 1, -1, -1, -1, "position",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 2 — position icon */
    { 0, -1, 4, -1, NULL,
      MRECT(  0.0f, 148.0f,  0.0f,  94.0f,  60.0f,
               0.0f, 147.0f,  0.0f,  51.0f,  32.0f,
               0.0f, 148.0f,  0.0f,  94.0f,  60.0f,
               0.0f, 147.0f,  0.0f,  51.0f,  32.0f) },

    /* Rank 2 — vehicle ref (id 202) */
    { 2, -1, -1, -1, "vehicle",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 2 — player ref (id 203) */
    { 0, -1, -1, -1, "player",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 2 — points ref (id 205) */
    { 0, -1, -1, -1, "points",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 2 — points label "+x" */
    { 0, 5, -1, 2, "+x",
      MRECT(595.0f, 188.0f, 540.0f,  90.0f,  51.0f,
            295.0f, 187.0f, 325.0f,  50.0f,  28.0f,
            595.0f, 188.0f, 540.0f,  90.0f,  51.0f,
            295.0f, 187.0f, 325.0f,  50.0f,  28.0f) },

    /* Rank 1 — arrangement */
    { 0, -1, -1, -1, "arrangement",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 1 — row strip */
    { 0, 2, -1, 3, NULL,
      MRECT(185.0f, 225.0f, 463.0f, 910.0f, 100.0f,
             70.5f, 224.0f, 307.0f, 499.0f,  55.0f,
            185.0f, 225.0f, 463.0f, 910.0f, 100.0f,
             70.5f, 224.0f, 307.0f, 499.0f,  55.0f) },

    /* Rank 1 — position ref */
    { 1, -1, -1, -1, "position",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 1 — position icon */
    { 0, -1, 4, -1, NULL,
      MRECT(  0.0f, 190.0f,  0.0f,  94.0f,  60.0f,
               0.0f, 189.0f,  0.0f,  51.0f,  32.0f,
               0.0f, 190.0f,  0.0f,  94.0f,  60.0f,
               0.0f, 189.0f,  0.0f,  51.0f,  32.0f) },

    /* Rank 1 — vehicle ref (id 102) */
    { 2, -1, -1, -1, "vehicle",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 1 — player ref (id 103) */
    { 0, -1, -1, -1, "player",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Rank 1 — points ref (id 105) */
    { 0, -1, -1, -1, "points",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* ---- Footer row ---- */

    /* Arrow right */
    { 0, 5, -1, 7, NULL,
      MRECT(643.5f, 230.0f, 621.0f,  51.0f,  24.0f,
            323.0f, 229.0f, 356.0f,  29.0f,  13.0f,
            643.5f, 230.0f, 621.0f,  51.0f,  24.0f,
            323.0f, 229.0f, 356.0f,  29.0f,  13.0f) },

    /* Arrow left */
    { 0, 0, -1, 6, NULL,
      MRECT(593.5f, 233.0f, 620.0f,  51.0f,  25.0f,
            296.5f, 232.0f, 356.0f,  29.0f,  13.0f,
            593.5f, 233.0f, 620.0f,  51.0f,  25.0f,
            296.5f, 232.0f, 356.0f,  29.0f,  13.0f) },

    /* Score / result text */
    { 0, 2, -1, 5, NULL,
      MRECT(1062.0f, 236.0f, 606.0f,  90.0f,  42.0f,
             490.0f, 235.0f, 383.0f,  54.0f,  25.0f,
            1062.0f, 236.0f, 606.0f,  90.0f,  42.0f,
             490.0f, 235.0f, 383.0f,  54.0f,  25.0f) },

    /* r_text component ref */
    { 0, -1, -1, -1, "r_text",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Continue button */
    { 0, 5, -1, -1, "continue",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },

    /* Generic btn ref */
    { 0, 5, -1, -1, "btn",
      MRECT(-1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1, -1,-1,-1,-1,-1) },
};

#define DIALOG_COUNT ((int)(sizeof(g_dialogs) / sizeof(g_dialogs[0])))

/* -------------------------------------------------------------------------
 * Font
 * ---------------------------------------------------------------------- */

typedef struct {
    int         id;
    const char *style;          /* e.g. "mainmenu"               */
    const char *archive;        /* asset archive filename        */
    int         slot;           /* font slot index               */
} FontDef;

static const FontDef g_font = { 1, "mainmenu", "A_TRS_FontsArchive.arc", 5 };

/* -------------------------------------------------------------------------
 * Font styles  (r, g, b, a  ×2 for normal+highlight, scale, flags…)
 * ---------------------------------------------------------------------- */

typedef struct {
    int   size;
    unsigned char r, g, b, a;
    unsigned char hr, hg, hb, ha;  /* highlight colour */
    float scale;
    int   flag_a;
    int   flag_b;
    int   type;
    int   weight;
    int   extra;
} FontStyle;

static const FontStyle g_font_styles[4] = {
    { 4,   255,0,255,255, 0,255,1,0,   1.0f, 0, 0, 1, 4, 0 },
    { 0,   255,0,255,255, 0,255,1,0,   1.0f, 0, 0, 0, 8, 0 },
    { 0,   255,0,255,255, 0,255,1,0,   1.0f, 0, 0, 2, 8, 1 },
    { 0,   255,0,255,255, 0,255,1,0,   1.0f, 0, 0, 0, 8, 1 },
};

/* -------------------------------------------------------------------------
 * Images  (vehicle thumbnails + player icons)
 * ---------------------------------------------------------------------- */

typedef struct {
    const char *name;
    const char *archive;
    int         texture_id;   /* -1 = player icon (no fixed texture) */
    int         flag;
} ImageDef;

#define IMAGE_COUNT 32

static const ImageDef g_images[IMAGE_COUNT] = {
    { "vehicle_supertsunami",    "A_TRS_ImagesArchive1.arc",  1030, 1 },
    { "vehicle_16angels",        "A_TRS_ImagesArchive2.arc",  1002, 1 },
    { "vehicle_24seven",         "A_TRS_ImagesArchive3.arc",  1001, 1 },
    { "vehicle_bonecrusher",     "A_TRS_ImagesArchive4.arc",  1011, 1 },
    { "vehicle_brutilistic",     "A_TRS_ImagesArchive5.arc",  1003, 1 },
    { "vehicle_bullygoat",       "A_TRS_ImagesArchive6.arc",  1004, 1 },
    { "vehicle_chicane",         "A_TRS_ImagesArchive7.arc",  1012, 1 },
    { "vehicle_coolone",         "A_TRS_ImagesArchive8.arc",  1005, 1 },
    { "vehicle_covelite",        "A_TRS_ImagesArchive9.arc",  1013, 1 },
    { "vehicle_dakar",           "A_TRS_ImagesArchive10.arc", 1014, 1 },
    { "vehicle_demon",           "A_TRS_ImagesArchive11.arc", 1006, 1 },
    { "vehicle_dieselboy",       "A_TRS_ImagesArchive12.arc", 1007, 1 },
    { "vehicle_formul8r",        "A_TRS_ImagesArchive13.arc", 1008, 1 },
    { "vehicle_hellfire",        "A_TRS_ImagesArchive14.arc", 1009, 1 },
    { "vehicle_hollowback",      "A_TRS_ImagesArchive15.arc", 1015, 1 },
    { "vehicle_jackhammer",      "A_TRS_ImagesArchive16.arc", 1016, 1 },
    { "vehicle_middrift",        "A_TRS_ImagesArchive17.arc", 1017, 1 },
    { "vehicle_mstsuzuka",       "A_TRS_ImagesArchive18.arc", 1018, 1 },
    { "vehicle_muscletone",      "A_TRS_ImagesArchive19.arc", 1019, 1 },
    { "vehicle_nitrodoorslammer","A_TRS_ImagesArchive20.arc", 1010, 1 },
    { "vehicle_offtrack",        "A_TRS_ImagesArchive21.arc", 1020, 1 },
    { "vehicle_phantomracer",    "A_TRS_ImagesArchive22.arc", 1021, 1 },
    { "vehicle_powerbomb",       "A_TRS_ImagesArchive23.arc", 1022, 1 },
    { "vehicle_rockster",        "A_TRS_ImagesArchive24.arc", 1023, 1 },
    { "vehicle_shadowmk2",       "A_TRS_ImagesArchive25.arc", 1024, 1 },
    { "vehicle_sk2battlespec",   "A_TRS_ImagesArchive26.arc", 1025, 1 },
    { "vehicle_sooofast",        "A_TRS_ImagesArchive27.arc", 1026, 1 },
    { "vehicle_spectyte",        "A_TRS_ImagesArchive28.arc", 1027, 1 },
    { "vehicle_speedbump",       "A_TRS_ImagesArchive29.arc", 1028, 1 },
    { "vehicle_spinebuster",     "A_TRS_ImagesArchive30.arc", 1029, 1 },
    { "player_1",                "A_TRS_ImagesArchive31.arc",   -1, 1 },
    { "player_2",                "A_TRS_ImagesArchive32.arc",   -1, 0 },
};

/* -------------------------------------------------------------------------
 * Image lists  (groups of image indices)
 * ---------------------------------------------------------------------- */

#define IMAGELIST_COUNT 2
#define VEHICLES_LIST   0
#define PLAYERS_LIST    1

static const int g_vehicle_image_indices[30] = {
     0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10,11,12,13,14,15,16,17,18,19,
    20,21,22,23,24,25,26,27,28,29
};

static const int g_player_image_indices[2] = { 30, 31 };

typedef struct {
    int         type;
    int         count;
    const int  *indices;
} ImageList;

static const ImageList g_image_lists[IMAGELIST_COUNT] = {
    { 2, 30, g_vehicle_image_indices },
    { 2,  2, g_player_image_indices  },
};

/* -------------------------------------------------------------------------
 * Clip rectangle  (scroll / visibility clipping region)
 * ---------------------------------------------------------------------- */

static const MultiRect g_clip_rect = MRECT(
    200.0f, 240.0f, 875.0f, 380.0f,  /* XENON  x,y,w,h (z unused here) */
     80.0f, 175.0f, 480.0f, 190.0f,  /* PS2              */
    200.0f, 240.0f, 875.0f, 380.0f,  /* PC               */
     80.0f, 175.0f, 480.0f, 190.0f   /* Default          */
);

/* -------------------------------------------------------------------------
 * Timeline events
 * Sourced from NUMTIMELINES 4 / SUBTIMELINES 4 / EVENTS blocks.
 * Each event: { count, flash_id, time, ref_a, comp, flag_a, flag_b, flag_c, frame_a, frame_b }
 * ---------------------------------------------------------------------- */

typedef struct {
    int   event_type;   /* 0 = standard, 1 = looping, etc. */
    int   flash_id;     /* index into g_flash[]              */
    float time;         /* trigger time in seconds           */
    int   ref;          /* -1 = none                         */
    int   component;    /* component index                   */
    int   flag_a;
    int   flag_b;
    int   flag_c;
    int   frame_start;
    int   frame_end;
} TimelineEvent;

/* Sub-timeline 0 — positional/show events */
#define TIMELINE0_COUNT 21
static const TimelineEvent g_timeline0[TIMELINE0_COUNT] = {
    { 25, 0,  0.0f,         -1,  9, 0, 0, 1, 0,   259 },
    { 25, 3,  3.33333325f,  -1, 13, 0, 0, 1, 0,    47 },
    { 25, 0,  0.0f,         -1,  6, 0, 0, 1, 0,   259 },
    { 25, 3,  1.76666665f,  -1,  7, 0, 0, 1, 0,    47 },
    { 25, 0,  0.0f,         -1,  0, 0, 0, 1, 0,   106 },
    { 25, 0,  0.0f,         -1,  3, 0, 0, 1, 0,   259 },
    { 25, 3,  4.11666679f,  -1, 16, 0, 0, 1, 0,    47 },
    { 25, 3,  4.90000009f,  -1, 19, 0, 0, 1, 0,    24 },
    { 25, 0,  0.0f,         -1, 15, 0, 0, 1, 0,   259 },
    { 25, 0,  0.0f,         -1,  1, 0, 0, 1, 0,   106 },
    { 25, 0,  0.0f,         -1, 12, 0, 0, 1, 0,   259 },
    { 25, 0,  0.0f,         -1,  4, 0, 0, 1, 0,    47 },
    { 25, 3,  2.54999995f,  -1, 10, 0, 0, 1, 0,    47 },
    { 25, 0,  0.0f,         -1,  2, 0, 1, 1, 0,     0 },
    { 25, 3,  3.33333325f,  -1, 11, 0, 1, 1, 0,     1 },
    { 25, 3,  2.54999995f,  -1,  8, 0, 1, 1, 0,     1 },
    { 25, 3,  1.76666665f,  -1,  5, 0, 1, 1, 0,     1 },
    { 25, 3,  4.11666679f,  -1, 14, 0, 1, 1, 0,     1 },
    {  0, 3,  5.30000019f,  -1, 17, 0, 0, 1, 0,    24 },
    { 25, 3,  4.90000009f,  -1, 18, 0, 0, 1, 0,    24 },
    { 25, 0,  0.0f,         -1,  0, 0, 0, 0, 0,     0 }, /* sentinel */
};

/* Sub-timeline 1 — colour/state events (snap to frame 0) */
#define TIMELINE1_COUNT 21
static const TimelineEvent g_timeline1[TIMELINE1_COUNT] = {
    { 25, 0,  0.0f, -1,  9, 0, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1, 13, 0, 0, 1,  66,  89 },
    { 25, 0,  0.0f, -1,  6, 0, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  7, 0, 0, 1,  66,  89 },
    { 25, 0,  0.0f, -1,  0, 0, 0, 1, 199, 222 },
    { 25, 0,  0.0f, -1,  3, 0, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1, 16, 0, 0, 1,  66,  89 },
    { 25, 0,  0.0f, -1, 19, 0, 0, 1,  40,  60 },
    { 25, 0,  0.0f, -1, 15, 0, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  1, 0, 0, 1, 199, 222 },
    { 25, 0,  0.0f, -1, 12, 0, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  4, 0, 0, 1,  66,  89 },
    { 25, 0,  0.0f, -1, 10, 0, 0, 1,  66,  89 },
    { 25, 0,  0.0f, -1,  2, 0, 1, 1,   0,   0 },
    { 25, 0,  0.0f, -1, 11, 0, 1, 1,   4,   5 },
    { 25, 0,  0.0f, -1,  8, 0, 1, 1,   4,   5 },
    { 25, 0,  0.0f, -1,  5, 0, 1, 1,   4,   5 },
    { 25, 0,  0.0f, -1, 14, 0, 1, 1,   4,   5 },
    {  0, 0,  0.416666656f, -1, 17, 0, 0, 1,  99, 124 },
    { 25, 0,  0.0f, -1, 18, 0, 0, 1,  99, 124 },
    { 25, 0,  0.0f, -1,  0, 0, 0, 0,   0,   0 }, /* sentinel */
};

/* Sub-timelines 2 & 3 are identical — selected/highlighted state */
#define TIMELINE23_COUNT 21
static const TimelineEvent g_timeline2[TIMELINE23_COUNT] = {
    { 25, 0,  0.0f, -1,  9, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1, 13, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1,  6, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  7, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1,  0, 1, 0, 1, 109, 192 },
    { 25, 0,  0.0f, -1,  3, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1, 16, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1, 19, 1, 0, 1,  25,  34 },
    { 25, 0,  0.0f, -1, 15, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  1, 1, 0, 1, 109, 192 },
    { 25, 0,  0.0f, -1, 12, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  4, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1, 10, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1,  2, 0, 1, 1,   0,   0 }, /* sub-tl 2: flag=0 */
    { 25, 0,  0.0f, -1, 11, 0, 1, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  8, 1, 1, 1,   2,   3 },
    { 25, 0,  0.0f, -1,  5, 1, 1, 1,   2,   3 },
    { 25, 0,  0.0f, -1, 14, 1, 1, 1,   2,   3 },
    {  0, 0,  1.38333332f, -1, 17, 1, 0, 1,  24,  99 },
    { 25, 0,  0.0f, -1, 18, 1, 0, 1,  24,  99 },
    { 25, 0,  0.0f, -1,  0, 0, 0, 0,   0,   0 }, /* sentinel */
};

/* Sub-timeline 3 — same as 2 except comp[13] flag_a=1 */
static const TimelineEvent g_timeline3[TIMELINE23_COUNT] = {
    { 25, 0,  0.0f, -1,  9, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1, 13, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1,  6, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  7, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1,  0, 1, 0, 1, 109, 192 },
    { 25, 0,  0.0f, -1,  3, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1, 16, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1, 19, 1, 0, 1,  25,  34 },
    { 25, 0,  0.0f, -1, 15, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  1, 1, 0, 1, 109, 192 },
    { 25, 0,  0.0f, -1, 12, 1, 0, 1,   0,   0 },
    { 25, 0,  0.0f, -1,  4, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1, 10, 1, 0, 1,  50,  59 },
    { 25, 0,  0.0f, -1,  2, 1, 1, 1,   2,   3 }, /* flag_a=1 vs tl2 */
    { 25, 0,  0.0f, -1, 11, 1, 1, 1,   2,   3 },
    { 25, 0,  0.0f, -1,  8, 1, 1, 1,   2,   3 },
    { 25, 0,  0.0f, -1,  5, 1, 1, 1,   2,   3 },
    { 25, 0,  0.0f, -1, 14, 1, 1, 1,   2,   3 },
    {  0, 0,  1.38333332f, -1, 17, 1, 0, 1,  24,  99 },
    { 25, 0,  0.0f, -1, 18, 1, 0, 1,  24,  99 },
    { 25, 0,  0.0f, -1,  0, 0, 0, 0,   0,   0 }, /* sentinel */
};

/* Timeline table */
typedef struct {
    int                   count;
    const TimelineEvent  *events;
} Timeline;

static const Timeline g_timelines[4] = {
    { TIMELINE0_COUNT,  g_timeline0  },
    { TIMELINE1_COUNT,  g_timeline1  },
    { TIMELINE23_COUNT, g_timeline2  },
    { TIMELINE23_COUNT, g_timeline3  },
};

/* -------------------------------------------------------------------------
 * Interface  (component wiring / highlight / focus order)
 * ---------------------------------------------------------------------- */

typedef struct {
    int comp_id;
    int ref_a;
    int ref_b;
} CompBinding;

typedef struct {
    int          init_flags[6];       /* 5 240 0 0 1 -1 … */
    CompBinding  comp_ids[5];
    /* HighlighterDialog focus chain — pairs of (comp_id, dialog_id) */
    int          highlight_chain[40]; /* raw pairs from source        */
    int          highlight_count;
} InterfaceDef;

static const InterfaceDef g_interface = {
    /* init block: 5 240 0 0 1 -1 -1 -1 -1 0 -1 0 5 -1 14 0 */
    .init_flags = { 5, 240, 0, 0, 1, -1 },

    /* CompIDs lines */
    .comp_ids = {
        { 100, -1, 11 },
        { 200, -1,  8 },
        { 300, -1,  5 },
        { 400, -1,  2 },
        { 500, -1, -1 },
    },

    /*
     * HighlighterDialog focus / nav chain.
     * Each pair: { comp_to_highlight, target_dialog_id }
     * -1 entries mark blanks / unused slots.
     */
    .highlight_chain = {
        -1,  15,   -1,  12,  201,  -1,    0,  -1,  -1,   4,
       500,  -1,    7, 400,  -1,    1,   -1,  -1,  19,  -1,
        -1,  15,  101,  -1,  10,  300,   -1,   6, 401,  -1,
        13, 200,   -1,  16, 100,   -1,   17, 800,  -1,   3,
       501,  -1,    9, 301,  -1,   18,  700,  -1,  -1,  -1,
    },
    .highlight_count = 48,
};