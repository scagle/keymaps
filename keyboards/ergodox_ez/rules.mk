# vim: foldmethod=marker

# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file


# Features {{{

# My Custom Features
SCAGLE_LEDS_ENABLE = yes          # [+]   Onboard LEDs
SCAGLE_KEY_SWAP_ENABLE = yes      # [?]   Dynamically Swappable keys
SCAGLE_SLEEP_ENABLE = yes         # [+]   Turn off all lights after X minutes of inactivity

# QMK/External Features
RGBLIGHT_ENABLE = yes             # [++]  RGB Lights. Animations defined in config.h
TAP_DANCE_ENABLE = yes            # [+]   Multiple presses = Multiple variations of key presses
COMBO_ENABLE = no                 # [?]   TODO: Combination of keys = specific unique key press
BOOTMAGIC_ENABLE = no             # [?]

LTO_ENABLE = yes                  # [--]  Link Time Optimization by GCC
COMMAND_ENABLE = no               # [++]  Allow "Magic" TMK commands
CONSOLE_ENABLE = no               # [+++] Allow dumping to console (with "sudo hid_listen")

# }}} Features


# Sources {{{

SRC += src/background_functions/transitions.c

# Keep track of features to be printed out by keyboard's CKC_VERSION key.
ENABLED_FEATURES=

ifeq ($(strip $(SCAGLE_LEDS_ENABLE)), yes)
	ENABLED_FEATURES += leds,
	SRC += feature/ui_functions/leds.c
	OPT_DEFS += -DSCAGLE_LEDS_ENABLE  # Add it manually, since it's custom
endif

ifeq ($(strip $(SCAGLE_KEY_SWAP_ENABLE)), yes)
	ENABLED_FEATURES += key_swap,
	SRC += feature/key_functions/key_swap.c
	OPT_DEFS += -DSCAGLE_KEY_SWAP_ENABLE  # Add it manually, since it's custom
endif

ifeq ($(strip $(SCAGLE_SLEEP_ENABLE)), yes)
	ENABLED_FEATURES += sleep,
	SRC += feature/background_functions/sleep.c
	OPT_DEFS += -DSCAGLE_SLEEP_ENABLE  # Add it manually, since it's custom
endif

ifeq ($(strip $(RGBLIGHT_ENABLE)), yes)
	ENABLED_FEATURES += rgb_light,
	SRC += feature/ui_functions/rgb_light.c
endif

ifeq ($(strip $(TAP_DANCE_ENABLE)), yes)
	ENABLED_FEATURES += tap_dance,
	SRC += feature/key_functions/tap_dance.c
endif

ifeq ($(strip $(COMBO_ENABLE)), yes)
	ENABLED_FEATURES += combo,
	SRC += feature/key_functions/combo.c
endif

# }}} Sources


# Options {{{

KEYMAP_BRANCH = $(shell \
 if [ -d "${KEYMAP_PATH}/.git" ]; then \
  cd "${KEYMAP_PATH}"; \
 fi; \
 git rev-parse --abbrev-ref HEAD 2>/dev/null)

KEYMAP_DATE = $(shell date)

OPT_DEFS += -DKEYMAP_BRANCH=\"$(KEYMAP_BRANCH)\"
OPT_DEFS += -DKEYMAP_DATE=\""$(KEYMAP_DATE)"\"
OPT_DEFS += -DENABLED_FEATURES=\""$(strip $(ENABLED_FEATURES))"\"


# }}} Options
