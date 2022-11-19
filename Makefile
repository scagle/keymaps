USER = scagle
KEYBOARDS = ergodox_ez

# keymap path
PATH_ergodox_ez = ergodox_ez

# keyboard name
NAME_ergodox_ez = ergodox_ez

all: $(KEYBOARDS)

.PHONY: $(KEYBOARDS)
$(KEYBOARDS):
	# Link keymaps into qmk_firmware
	ln -sf $(shell pwd)/user qmk_firmware/users/$(USER)
	ln -sf $(shell pwd)/keyboards/$@ qmk_firmware/keyboards/$(PATH_$@)/keymaps/$(USER)

	# run lint check
	cd qmk_firmware; qmk lint -km $(USER) -kb $(NAME_$@) --strict
	
	# run build
	make BUILD_DIR=$(shell pwd)/build -j1 -C qmk_firmware $(NAME_$@):$(USER)

clean:
	git --git-dir qmk_firmware/.git reset --hard
	git --git-dir qmk_firmware/.git clean -xfd
