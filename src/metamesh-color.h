/* -*- C++ -*- */

#ifndef METAMESH_COLOR
#define METAMESH_COLOR

// This file provides some rgb colors, placed into namespace metamesh::color.

// rgb_average
// For internal use
namespace metamesh {
namespace internal {
   inline rgb rgb_average(const rgb &, const rgb &);
   inline rgb rgb_average(const rgb &, const rgb &, const rgb &, const rgb &);
}
}



// =============================================================================
// Miscellaneous colors
// Most of these are "Crayola" crayon colors that were listed on a Wikipedia
// page. The page has long since been updated, and, sometime, I may update
// these as well. Or, I might leave them as-is, for compatibility with existing
// codes, and just add additional Crayola colors, perhaps using ThisStyle.
// We also have a few miscellaneous, non-Crayola colors here.
// =============================================================================

namespace metamesh {
namespace color {
namespace {

// ------------------------
// Crayola
// My original list
// ------------------------

// Having one long list of const rgbs seemed to confuse emacs' text-coloring
// mechanism, so I broke up this list into groups of 10 colors apiece.

const rgb
   almond                  (239, 222, 205),
   antique_brass           (205, 149, 117),
   apricot                 (253, 217, 181),
   aquamarine              (120, 219, 226),
   asparagus               (135, 169, 107),
   atomic_tangerine        (255, 164, 116),
   banana_mania            (250, 231, 181),
   beaver                  (159, 129, 112),
   bittersweet             (253, 124, 110),
   black                   (  0,   0,   0);

const rgb
   blizzard_blue           (172, 229, 238),
   blue                    ( 31, 117, 254),
   blue_bell               (162, 162, 208),
   blue_gray               (102, 153, 204),
   blue_green              ( 13, 152, 186),
   blue_violet             (115, 102, 189),
   blush                   (222,  93, 131),
   brick_red               (203,  65,  84),
   brown                   (180, 103,  77),
   burnt_orange            (255, 127,  73);

const rgb
   burnt_sienna            (234, 126,  93),
   cadet_blue              (176, 183, 198),
   canary                  (255, 255, 153),
   caribbean_green         ( 28, 211, 162),
   carnation_pink          (255, 170, 204),
   cerise                  (221,  68, 146),
   cerulean                ( 29, 172, 214),
   chestnut                (188,  93,  88),
   copper                  (221, 148, 117),
   cornflower              (154, 206, 235);

const rgb
   cotton_candy            (255, 188, 217),
   dandelion               (253, 219, 109),
   denim                   ( 43, 108, 196),
   desert_sand             (239, 205, 184),
   eggplant                (110,  81,  96),
   electric_lime           (206, 255,  29),
   fern                    (113, 188, 120),
   forest_green            (109, 174, 129),
   fuchsia                 (195, 100, 197),
   fuzzy_wuzzy             (204, 102, 102);

const rgb
   gold                    (231, 198, 151),
   goldenrod               (252, 217, 117),
   granny_smith_apple      (168, 228, 160),
   gray                    (149, 145, 140),
   green                   ( 28, 172, 120),
   green_blue              ( 17, 100, 180),
   green_yellow            (240, 232, 145),
   hot_magenta             (255,  29, 206),
   inchworm                (178, 236,  93),
   indigo                  ( 93, 118, 203);

const rgb
   jazzberry_jam           (202,  55, 103),
   jungle_green            ( 59, 176, 143),
   laser_lemon             (254, 254,  34),
   lavender                (252, 180, 213),
   lemon_yellow            (255, 244,  79),
   macaroni_and_cheese     (255, 189, 136),
   magenta                 (246, 100, 175),
   magic_mint              (170, 240, 209),
   mahogany                (205,  74,  76),
   maize                   (237, 209, 156);

const rgb
   manatee                 (151, 154, 170),
   mango_tango             (255, 130,  67),
   maroon                  (200,  56,  90),
   mauvelous               (239, 152, 170),
   melon                   (253, 188, 180),
   midnight_blue           ( 26,  72, 118),
   mountain_meadow         ( 48, 186, 143),
   mulberry                (197,  75, 140),
   navy_blue               ( 25, 116, 210),
   neon_carrot             (255, 163,  67);

const rgb
   olive_green             (186, 184, 108),
   orange                  (255, 117,  56),
   orange_red              (255,  43,  43),
   orange_yellow           (248, 213, 104),
   orchid                  (230, 168, 215),
   outer_space             ( 65,  74,  76),
   outrageous_orange       (255, 110,  74),
   pacific_blue            ( 28, 169, 201),
   peach                   (255, 207, 171),
   periwinkle              (197, 208, 230);

const rgb
   piggy_pink              (253, 221, 230),
   pine_green              ( 21, 128, 120),
   pink_flamingo           (252, 116, 253),
   pink_sherbert           (247, 143, 167),
   plum                    (142,  69, 133),
   purple_heart            (116,  66, 200),
   purple_mountains_majesty(157, 129, 186),
   purple_pizzazz          (254,  78, 218),
   radical_red             (255,  73, 108),
   raw_sienna              (214, 138,  89);

const rgb
   raw_umber               (113,  75,  35),
   razzle_dazzle_rose      (255,  72, 208),
   razzmatazz              (227,  37, 107),
   red                     (238,  32,  77),
   red_orange              (255,  83,  73),
   red_violet              (192,  68, 143),
   robins_egg_blue         ( 31, 206, 203),
   royal_purple            (120,  81, 169),
   salmon                  (255, 155, 170),
   scarlet                 (252,  40,  71);

const rgb
   screamin_green          (118, 255, 122),
   sea_green               (159, 226, 191),
   sepia                   (165, 105,  79),
   shadow                  (138, 121,  93),
   shamrock                ( 69, 206, 162),
   shocking_pink           (251, 126, 253),
   silver                  (205, 197, 194),
   sky_blue                (128, 218, 235),
   spring_green            (236, 234, 190),
   sunglow                 (255, 207,  72);

const rgb
   sunset_orange           (253,  94,  83),
   tan                     (250, 167, 108),
   teal_blue               ( 24, 167, 181),
   thistle                 (235, 199, 223),
   tickle_me_pink          (252, 137, 172),
   timberwolf              (219, 215, 210),
   tropical_rain_forest    ( 23, 128, 109),
   tumbleweed              (222, 170, 136),
   turquoise_blue          (119, 221, 231),
   unmellow_yellow         (255, 255, 102);

const rgb
   violet                  (146, 110, 174),
   purple = violet,
   violet_blue             ( 50,  74, 178),
   violet_red              (247,  83, 148),
   vivid_tangerine         (255, 160, 137),
   vivid_violet            (143,  80, 157),
   white                   (255, 255, 255),
   wild_blue_yonder        (162, 173, 208),
   wild_strawberry         (255,  67, 164),
   wild_watermelon         (252, 108, 133);

const rgb
   wisteria                (205, 164, 222),
   yellow                  (252, 232, 131),
   yellow_green            (197, 227, 132),
   yellow_orange           (255, 174,  66);


// ------------------------
// Other
// ------------------------

   const rgb gray_very_dark  ( 44);
   const rgb gray_dark       ( 86);
   const rgb gray_medium     (128);
   const rgb gray_light      (170);
   const rgb gray_very_light (212);

   const rgb gray_red   = internal::rgb_average(gray_medium, brick_red);
   const rgb gray_green = internal::rgb_average(gray_medium, jungle_green);
   const rgb gray_blue  = internal::rgb_average(gray_medium, denim);

   const rgb slight_red =
      internal::rgb_average(gray_medium,gray_medium,gray_medium, brick_red);
   const rgb slight_green =
      internal::rgb_average(gray_medium,gray_medium,gray_medium, jungle_green);
   const rgb slight_blue =
      internal::rgb_average(gray_medium,gray_medium,gray_medium, denim);


// ------------------------
// Crayola "Silver Swirls"
// ------------------------

   const rgb aztec_gold       (0xc3,0x99,0x53);
   const rgb burnished_brown  (0xa1,0x7a,0x74);
   const rgb cerulean_frost   (0x6d,0x9b,0xc3);
   const rgb cinnamon_satin   (0xcd,0x60,0x7e);

   const rgb copper_penny     (0xad,0x6f,0x69);
   const rgb cosmic_cobalt    (0x2e,0x2d,0x88);
   const rgb glossy_grape     (0xab,0x92,0xb3);
   const rgb granite_gray     (0x67,0x67,0x67);

   const rgb green_sheen      (0x6e,0xae,0xa1);
   const rgb lilac_luster     (0xae,0x98,0xaa);
   const rgb misty_moss       (0xbb,0xb4,0x77);
   const rgb mystic_maroon    (0xad,0x43,0x79);

   const rgb pearly_purple    (0xb7,0x68,0xa2);
   const rgb pewter_blue      (0x8b,0xa8,0xb7);
   const rgb polished_pine    (0x5d,0xa4,0x93);
   const rgb quick_silver     (0xa6,0xa6,0xa6);

   const rgb rose_dust        (0x9e,0x5e,0x6f);
   const rgb rusty_red        (0xda,0x2c,0x43);
   const rgb shadow_blue      (0x77,0x8b,0xa5);
   const rgb shiny_shamrock   (0x5f,0xa7,0x78);

   const rgb steel_teal       (0x5f,0x8a,0x8b);
   const rgb sugar_plum       (0x91,0x4e,0x75);
   const rgb twilight_lavender(0x8a,0x49,0x6b);
   const rgb wintergreen_dream(0x56,0x88,0x7d);


// ------------------------
// Crayola "Gem Tones"
// ------------------------

   const rgb amethyst    (0x64,0x60,0x9a);
   const rgb citrine     (0x93,0x37,0x09);
   const rgb emerald     (0x14,0xa9,0x89);
   const rgb jade        (0x46,0x9a,0x84);

   const rgb jasper      (0xd0,0x53,0x40);
   const rgb lapis_lazuli(0x43,0x6c,0xb9);
   const rgb malachite   (0x46,0x94,0x96);
   const rgb moonstone   (0x3a,0xa8,0xc1);

   const rgb onyx        (0x35,0x38,0x39);
   const rgb peridot     (0xab,0xad,0x48);
   const rgb pink_pearl  (0xb0,0x70,0x80);
   const rgb rose_quartz (0xbd,0x55,0x9c);

   const rgb ruby        (0xaa,0x40,0x69);
   const rgb sapphire    (0x2d,0x5d,0xa1);
   const rgb smokey_topaz(0x83,0x2a,0x0d);
   const rgb tigers_eye  (0xb5,0x69,0x17);


// ------------------------
// Crayola "Pearl Brite"
// ------------------------

   const rgb aqua_pearl           (0x5f,0xbe,0xd7);
   const rgb black_coral_pearl    (0x54,0x62,0x6f);
   const rgb caribbean_green_pearl(0x6a,0xda,0x8e);
   const rgb cultured_pearl       (0xf5,0xf5,0xf5);

   const rgb key_lime_pearl       (0xe8,0xf4,0x8c);
   const rgb mandarin_pearl       (0xf3,0x7a,0x48);
   const rgb midnight_pearl       (0x70,0x26,0x70);
   const rgb mystic_pearl         (0xd6,0x52,0x82);

   const rgb ocean_blue_pearl     (0x4f,0x42,0xb5);
   const rgb ocean_green_pearl    (0x48,0xbf,0x91);
   const rgb orchid_pearl         (0x7b,0x42,0x59);
   const rgb rose_pearl           (0xf0,0x38,0x65);

   const rgb salmon_pearl         (0xf1,0x44,0x4a);
   const rgb sunny_pearl          (0xf2,0xf2,0x7a);
   const rgb sunset_pearl         (0xf1,0xcc,0x79);
   const rgb turquoise_pearl      (0x3b,0xbc,0xd0);


// ------------------------
// Crayola "Metallic FX"
// ------------------------

   const rgb alloy_orange          (0xc4,0x62,0x10);
   const rgb bdazzled_blue         (0x2e,0x58,0x94);
   const rgb big_dip_o_ruby        (0x9c,0x25,0x42);
   const rgb bittersweet_shimmer   (0xbf,0x4f,0x51);

   const rgb blast_off_bronze      (0xa5,0x71,0x64);
   const rgb cyber_grape           (0x58,0x42,0x7c);
   const rgb deep_space_sparkle    (0x4a,0x64,0x6c);
   const rgb gold_fusion           (0x85,0x75,0x4e);

   const rgb illuminating_emerald  (0x31,0x91,0x77);
   const rgb metallic_seaweed      (0x0a,0x7e,0x8c);
   const rgb metallic_sunburst     (0x9c,0x7c,0x38);
   const rgb razzmic_berry         (0x8d,0x4e,0x85);

   const rgb sheen_green           (0x8f,0xd4,0x00);
   const rgb shimmering_blush      (0xd9,0x86,0x95);
   const rgb sonic_silver          (0x75,0x75,0x75);
   const rgb steel_blue            (0x00,0x81,0xab);

}
}  // color
}  // metamesh



// =============================================================================
// Color spectra
// Really, the following should eventually be done in a much more elegant
// way, and one that is more flexible for users.
// =============================================================================

namespace metamesh {

namespace internal {

   // rnd: round to type <integral>
   // Generic and long double cases
   // Class <integral> must be specified in the call!
   template<class integral, class real>
   inline integral rnd(const real &val)
   { return integral(val < 0 ? val-0.5  : val+0.5 ); }

   template<class integral>
   inline integral rnd(const long double &val)
   { return integral(val < 0 ? val-0.5L : val+0.5L); }

   // rgb_average, 2-argument
   inline rgb rgb_average(const rgb &a, const rgb &b)
   {
      using uchar = unsigned char;
      using dbl = double;

      return rgb(
         rnd<uchar>(op::half(dbl(a.r) + dbl(b.r))),
         rnd<uchar>(op::half(dbl(a.g) + dbl(b.g))),
         rnd<uchar>(op::half(dbl(a.b) + dbl(b.b)))
      );
   }

   // rgb_average, 4-argument
   inline rgb rgb_average(
      const rgb &a, const rgb &b,
      const rgb &c, const rgb &d
   ) {
      using uchar = unsigned char;
      using dbl = double;

      return rgb(
         rnd<uchar>(0.25*( dbl(a.r) + dbl(b.r) + dbl(c.r) + dbl(d.r) )),
         rnd<uchar>(0.25*( dbl(a.g) + dbl(b.g) + dbl(c.g) + dbl(d.g) )),
         rnd<uchar>(0.25*( dbl(a.b) + dbl(b.b) + dbl(c.b) + dbl(d.b) ))
      );
   }

namespace {
   // spectrum6_size
   // spectrum6
   const std::size_t spectrum6_size = 6;
   const rgb spectrum6[spectrum6_size] = {
      color::red,
      color::neon_carrot,
      color::unmellow_yellow,
      color::green,
      color::blue,
      color::fuchsia
   };

   // above: "*   *   *   *   *   *"
   // below: "* a * a * a * a * a * a [white]"
   // where * is a "roygbv," "a" is average

   // spectrum12_size
   // spectrum12
   const std::size_t spectrum12_size = 12;
   const rgb spectrum12[spectrum12_size] = {
      spectrum6[0], rgb_average(spectrum6[0], spectrum6[1]),
      spectrum6[1], rgb_average(spectrum6[1], spectrum6[2]),
      spectrum6[2], rgb_average(spectrum6[2], spectrum6[3]),
      spectrum6[3], rgb_average(spectrum6[3], spectrum6[4]),
      spectrum6[4], rgb_average(spectrum6[4], spectrum6[5]),
      spectrum6[5], rgb_average(spectrum6[5], color::white)
   };
}

}  // internal



// spectrum6
// spectrum12
namespace color {
namespace {
   // vector: 6-color spectrum
   const std::vector<rgb> spectrum6(
      &internal::spectrum6[0],
      &internal::spectrum6[0] + internal::spectrum6_size
   );

   // vector: 12-color spectrum
   const std::vector<rgb> spectrum12(
      &internal::spectrum12[0],
      &internal::spectrum12[0] + internal::spectrum12_size
   );
}
}  // color

}  // metamesh

#endif
